// Dynamic Obstacle cpp File

#include "DynamicObstacle.h"
#include "BoidManager.h"
#include "Boid.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ADynamicObstacle::ADynamicObstacle() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the Static Mesh for the Obstacles - A Cone
	dynamicObstacleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	this->SetRootComponent(dynamicObstacleComponent);
}

// Called when the game starts or when spawned
void ADynamicObstacle::BeginPlay() {
	Super::BeginPlay();
}

// Check if the Dynamic Obstacle is within 650 units from the boid it is pursuing
bool ADynamicObstacle::BoidCatchCheck(bool caughtBoid) {
	if (FVector::Dist(GetActorLocation(), Manager->MyBoids.operator[](boidNumToPursue)->GetActorLocation()) < 650.0f) {
		this->hasCaughtBoid = true;
	}
	return this->hasCaughtBoid;
}
// Picks a random Boid to Pursue out of all boids currently spawned in
int ADynamicObstacle::PickRandomBoid(int boidNumberToPursue) {
	if (Manager->MyBoids.Num() >= 1) {
		this->boidNumToPursue = FMath::RandRange(0, Manager->MyBoids.Num() - 1);
	}
	hasCaughtBoid = false;
	return this->boidNumToPursue;
}

// Specific Seek function for Dynamic Obstacles
FVector ADynamicObstacle::SeekBoid(FVector position) {
	FVector newVelocity = position - GetActorLocation() ;
	newVelocity.Normalize();
	return newVelocity;
}
// Calculates a force based on where the target is going to be in 'x' amount of frames
// Anticipates this location based on the targets current velocity
FVector ADynamicObstacle::PursueBoid(ABoid* targetPosition) {
	FVector currentPos = GetActorLocation();
	FVector distance = targetPosition->GetActorLocation() - currentPos;

	// Dynamically finds the distance between the pursuer and the target as well as the maximum velocity the target can achieve
	int pursueWeight = distance.Length() / Manager->maxVelocity; 

	// Find the targets predicted future location and Seek towards it
	FVector futurePos = targetPosition->GetActorLocation() + targetPosition->currentVelocity * pursueWeight;
	return SeekBoid(futurePos);
}

// Called every frame
void ADynamicObstacle::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Custom Dynamic Obstacle Update Function
void ADynamicObstacle::UpdateDynamicObstacle(float DeltaTime) {
	FVector dynamicObstacleLocation = GetActorLocation();
	FRotator dynamicObstacleRotation = GetActorRotation();

	// Check if the boid to pursue still exists - the player may have generated a new set of boids
	if (Manager->MyBoids.IsValidIndex(boidNumToPursue) == true) {
		BoidCatchCheck(hasCaughtBoid);
		// Chooses a New Boid to Pursue once one has been caught
		if (hasCaughtBoid == true) {
			PickRandomBoid(boidNumToPursue);
		}
		// Check if there are any Boids in the Simulation
		if (Manager->MyBoids.Num() >= 1) {
			// Pursue the chosen target boid
			targetVelocity = PursueBoid(Manager->MyBoids.operator[](boidNumToPursue));
		}
	}
	else {
		// Choose a new Boid to pursue as the old one has been removed from the simulaion
		PickRandomBoid(boidNumToPursue);
	}
	
	// Apply Force Logic
	FVector steeringForce = targetVelocity - currentVelocity;

	currentVelocity += steeringForce * DeltaTime;
	dynamicObstacleLocation += (currentVelocity * Manager->speed * pursueSpeedMultiplier * DeltaTime);
	
	SetActorLocation(dynamicObstacleLocation);

	// Rotate the boid in the direction of its velocity
	dynamicObstacleRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + currentVelocity);
	// Smooth the rotation to make it look more natural and realistic
	dynamicObstacleRotation = FMath::RInterpTo(this->GetActorRotation(), dynamicObstacleRotation, GetWorld()->DeltaTimeSeconds, 50.0f);
	// Set actor rotation to velocity
	SetActorRotation(dynamicObstacleRotation);
}