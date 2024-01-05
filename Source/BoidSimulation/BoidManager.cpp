// BoidManager cpp File

#include "BoidManager.h"
#include "Boid.h"
#include "Obstacle.h"
#include "DynamicObstacle.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ABoidManager::ABoidManager() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	transform = CreateDefaultSubobject<USceneComponent>("BoidManager Root Scene Component");
	this->SetRootComponent(transform);
	// Boid and Obstacle Static Mesh Definitions
	birdMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Birds/Bird_Mesh.Bird_Mesh'")).Object;
	fishMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Fish/Fish_Mesh.Fish_Mesh'")).Object;
	rabbitMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Rabbit/Rabbit_Mesh.Rabbit_Mesh'")).Object;
	staticObstacleMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	dynamicObstacleCone = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Cone_Mesh.Cone_Mesh'")).Object;
	dynamicObstacleShark = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Fish/Shark_Mesh.Shark_Mesh'")).Object;
	dynamicObstacleFox = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Models/Fox/Fox_Mesh.Fox_Mesh'")).Object;
}

// Called when the game starts or when spawned
void ABoidManager::BeginPlay() {
	Super::BeginPlay();
}

// Called every frame
void ABoidManager::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	for (ABoid* Boid : MyBoids) {
		Boid->UpdateBoid(DeltaTime);
	}

	for (ADynamicObstacle* dynamicObstacle : dynamicObstaclesArray) {
		dynamicObstacle->UpdateDynamicObstacle(DeltaTime);
	}
}

// Reset the Settings to their default values - called in WB_BoidSettings
void ABoidManager::ResetSettingsToDefaults() {
	spawnCount = 150;
	spawnRadius = 10000.0f;
	neighbourRadius = 4000.0f;
	separationWeight = 1.0f;
	cohesionWeight = 1.0f;
	alignmentWeight = 1.0f;
	speed = 5000.0f;
	maxVelocity = 1.0f;
	constrainForce = 1.0f;
}
// Reset the Extras to their default values - called in WB_BoidSettings
void ABoidManager::ResetExtrasToDefaults() {
	boundingBoxSizeX = 5000.0f;
	boundingBoxSizeY = 5000.0f;
	boundingBoxSizeZ = 5000.0f;
	staticObstaclesCount = 10;
	dynamicObstaclesCount = 3;
	boidAvoidance = true;
	obstacleAvoidance = true;
	showDebugBox = false;
}

// Boid Getter Functions:
// Get Number of Boids to Spawn - called in WB_BoidSettings
int ABoidManager::GetBoidSpawnCount() {
	return spawnCount;
}
// Get Boid Spawn Radius - called in WB_BoidSettings
float ABoidManager::GetBoidSpawnRadius() {
	return spawnRadius;
}
// Get Boid Neighbour Radius - called in WB_BoidSettings
float ABoidManager::GetBoidNeighbourRadius() {
	return neighbourRadius;
}
// Get Boid Separation Weight - called in WB_BoidSettings
float ABoidManager::GetBoidSeparationWeight() {
	return separationWeight;
}
// Get Boid Cohesion Weight - called in WB_BoidSettings
float ABoidManager::GetBoidCohesionWeight() {
	return cohesionWeight;
}
// Get Boid Alignment Weight - called in WB_BoidSettings
float ABoidManager::GetBoidAlignmentWeight() {
	return alignmentWeight;
}
// Get Boid Speed - called in WB_BoidSettings
float ABoidManager::GetBoidSpeed() {
	return speed;
}
// Get Boid Max Velocity - called in WB_BoidSettings
float ABoidManager::GetBoidMaxVelocity() {
	return maxVelocity;
}
// Get Boid Constrain Force - called in WB_BoidSettings
float ABoidManager::GetBoidConstrainForce() {
	return constrainForce;
}
// Get Bounding Box X Value - called in WB_BoidSettings
float ABoidManager::GetBoundingBoxX() {
	return boundingBoxSizeX;
}
// Get Bounding Box Y Value - called in WB_BoidSettings
float ABoidManager::GetBoundingBoxY() {
	return boundingBoxSizeY;
}
// Get Bounding Box Z Value - called in WB_BoidSettings
float ABoidManager::GetBoundingBoxZ() {
	return boundingBoxSizeZ;
}
// Get Number of Static Obstacles to Spawn - called in WB_BoidSettings
int ABoidManager::GetStaticObstaclesCount() {
	return staticObstaclesCount;
}
// Get Number of Dynamic Obstacles to Spawn - called in WB_BoidSettings
int ABoidManager::GetDynamicObstaclesCount() {
	return dynamicObstaclesCount;
}

// Boid Setter Functions:
// Set Number of Boids to Spawn - called in WB_BoidSettings
void ABoidManager::SetBoidSpawnCount(int numOfBoidsToSpawn) {
	spawnCount = numOfBoidsToSpawn;
}
// Set Boid Spawn Radius - called in WB_BoidSettings
void ABoidManager::SetBoidSpawnRadius(float boidSpawnRadius) {
	spawnRadius = boidSpawnRadius;
}
// Set Boid Neighbour Radius - called in WB_BoidSettings
void ABoidManager::SetBoidNeighbourRadius(float boidNeighbourRadius) {
	neighbourRadius = boidNeighbourRadius;
}
// Set Boid Separation Weight - called in WB_BoidSettings
void ABoidManager::SetBoidSeparationWeight(float boidSeparationWeight) {
	separationWeight = boidSeparationWeight;
}
// Set Boid Cohesion Weight - called in WB_BoidSettings
void ABoidManager::SetBoidCohesionWeight(float boidCohesionWeight) {
	cohesionWeight = boidCohesionWeight;
}
// Set Boid Alignment Weight - called in WB_BoidSettings
void ABoidManager::SetBoidAlignmentWeight(float boidAlignmentWeight) {
	alignmentWeight = boidAlignmentWeight;
}
// Set Boid Speed - called in WB_BoidSettings
void ABoidManager::SetBoidSpeed(float boidSpeed) {
	speed = boidSpeed;
}
void ABoidManager::SetBoidMaxVelocity(float boidMaxVelocity) {
	maxVelocity = boidMaxVelocity;
}
void ABoidManager::SetBoidConstrainForce(float boidConstrainForce) {
	constrainForce = boidConstrainForce;
}
// Set Number of Obstacles to Spawn - called in WB_BoidSettings
void ABoidManager::SetStaticObstaclesCount(int numOfObstacles) {
	staticObstaclesCount = numOfObstacles;
}
// Set Bounding Box X Value - called in WB_BoidSettings
void ABoidManager::SetBoundingBoxX(float boundingBoxX) {
	boundingBoxSizeX = boundingBoxX;
}
// Set Bounding Box Y Value - called in WB_BoidSettings
void ABoidManager::SetBoundingBoxY(float boundingBoxY) {
	boundingBoxSizeY = boundingBoxY;
}
// Set Bounding Box Z Value - called in WB_BoidSettings
void ABoidManager::SetBoundingBoxZ(float boundingBoxZ) {
	boundingBoxSizeZ = boundingBoxZ;
}
// Set Number of Dynamic Obstacles to Spawn - called in WB_BoidSettings
void ABoidManager::SetDynamicObstaclesCount(int numOfDynamicObstacles) {
	dynamicObstaclesCount = numOfDynamicObstacles;
}

// Changes the Boid Model to Birds and the DynamicObstacle Model to Cones in run-time - called in WB_BoidSettings
void ABoidManager::BirdTheme() {
	myThemes = ThemeEnum::BIRD;
	for (ABoid* Boid : MyBoids) {
		Boid->boidMesh->SetStaticMesh(birdMesh);
	}
	for (ADynamicObstacle* dynamicObstacle : dynamicObstaclesArray) {
		dynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleCone);
		dynamicObstacle->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
	}
}
// Changes the Boid Model to Fish and the DynamicObstacle Model to Sharks in run-time - called in WB_BoidSettings
void ABoidManager::FishTheme() {
	myThemes = ThemeEnum::FISH;
	for (ABoid* Boid : MyBoids) {
		Boid->boidMesh->SetStaticMesh(fishMesh);
	}
	for (ADynamicObstacle* dynamicObstacle : dynamicObstaclesArray) {
		dynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleShark);
		dynamicObstacle->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
	}
}
// Changes the Boid Model to Rabbits and the DynamicObstacle Model to Foxes in run-time - called in WB_BoidSettings
void ABoidManager::RabbitTheme() {
	myThemes = ThemeEnum::RABBIT;
	for (ABoid* Boid : MyBoids) {
		Boid->boidMesh->SetStaticMesh(rabbitMesh);
	}
	for (ADynamicObstacle* dynamicObstacle : dynamicObstaclesArray) {
		dynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleFox);
		dynamicObstacle->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
	}
}

// Assigns a Boid to a neighbourhood if they are within a given neighbourhood radius of other boids 
TArray<class ABoid*> ABoidManager::GetBoidNeighbourHood(ABoid* thisBoid) {
	TArray<class ABoid*> neighbourhoodBoids;

	// Check if thisBoid is the closest Distance - loop through every boid until you find the closest one
	for (ABoid* Boid : MyBoids) {
		if (Boid == thisBoid || !Boid) {
			continue;
		}
		float aDistance = (Boid->GetActorLocation() - thisBoid->GetActorLocation()).Length();
		// Determines how close a boid must be to form a neighbourhood (anything below this values will form a neighbourhood)
		if (aDistance < neighbourRadius) {
			neighbourhoodBoids.Add(Boid);
		}
	}
	return neighbourhoodBoids;
}

// Contains the logic for spawning new boids into the Simulation - the previous ones are removed and replaced by new boids
// Occurs when the Spawn Count Slider value is decreased below the current boid number
void ABoidManager::SpawnNewBoids() {
	// Spawn in Boids
	for (int i = 0; i < spawnCount; i++) {
		FVector boidSpawnLocation = (FMath::VRand() * FMath::RandRange(0.0f, spawnRadius)) + GetActorLocation();
		FRotator boidSpawnRotation = GetActorRotation();

		ABoid* newBoid = GetWorld()->SpawnActor<ABoid>(boidSpawnLocation, boidSpawnRotation);
		// Gets the current Theme upon Spawning in Boids and sets their static mesh model to match the theme
		switch (myThemes) {
		case ThemeEnum::BIRD:
			newBoid->boidMesh->SetStaticMesh(birdMesh);
			break;
		case ThemeEnum::FISH:
			newBoid->boidMesh->SetStaticMesh(fishMesh);
			break;
		case ThemeEnum::RABBIT:
			newBoid->boidMesh->SetStaticMesh(rabbitMesh);
			break;
		default:
			newBoid->boidMesh->SetStaticMesh(birdMesh);
			break;
		}
		//Set the new Boid to be thisBoid using the forward declaration of BoidManager
		newBoid->Manager = this;
		MyBoids.Add(newBoid);
	}
}
// Contains the logic for spawning extra boids into the Simulation - the previous ones remain and extra boids are spawned
// Occurs when the Spawn Count Slider value is increased above the current boid number
void ABoidManager::SpawnExtraBoids() {
	// Stores currentBoids that are present in the Simulation
	int currentBoids = MyBoids.Num();

	// Spawn in Extra Boids without destroying the current ones
	for (int i = 0; i < spawnCount - currentBoids; i++) {
		FVector boidSpawnLocation = (FMath::VRand() * FMath::RandRange(0.0f, spawnRadius)) + GetActorLocation();
		FRotator boidSpawnRotation = GetActorRotation();

		ABoid* newBoid = GetWorld()->SpawnActor<ABoid>(boidSpawnLocation, boidSpawnRotation);
		// Gets the current Theme upon Spawning in Boids and sets their model to match the theme
		switch (myThemes) {
		case ThemeEnum::BIRD:
			newBoid->boidMesh->SetStaticMesh(birdMesh);
			break;
		case ThemeEnum::FISH:
			newBoid->boidMesh->SetStaticMesh(fishMesh);
			break;
		case ThemeEnum::RABBIT:
			newBoid->boidMesh->SetStaticMesh(rabbitMesh);
			break;
		default:
			newBoid->boidMesh->SetStaticMesh(birdMesh);
			break;
		}
		//Set the new Boid to be thisBoid using the forward declaration of BoidManager
		newBoid->Manager = this;
		MyBoids.Add(newBoid);
	}
}
// Called when the Spawn Boids Button is pressed inside the BoidSettings Widget Blueprint
void ABoidManager::SpawnBoidManager() {
	// Checks if the spawnCount value is greater than the number of current boids
	if (spawnCount > MyBoids.Num()) {
		SpawnExtraBoids();
	}
	// Checks if the spawnCount value is less than the number of current boids
	else if (spawnCount < MyBoids.Num()) {
		// Delete any existing boids before spawning in new ones
		for (ABoid* Boid : MyBoids) {
			Boid->Destroy();
		}
		// Empty the array of boids so the performance doesn't degrade after spawning in boids multiple times
		MyBoids.Empty();
		// Only spawn in new boids if there are not anymore existing ones in the simulation - Checks if the boids have been removed properly
		if (MyBoids.IsEmpty() == true) {
			SpawnNewBoids();
		}
	}
}

// Extra Settings Checkbox Setter Functions:
// Set Boid Avoidance CheckBox state - called in WB_BoidSettings
void ABoidManager::SetBoidAvoidance(bool canAvoid) {
	boidAvoidance = canAvoid;
}
// Set Obstacle Avoidance CheckBox state - called in WB_BoidSettings
void ABoidManager::SetObstacleAvoidance(bool canAvoid) {
	obstacleAvoidance = canAvoid;
}
// Set Slow-motion CheckBox state - called in WB_BoidSettings
void ABoidManager::SetSlowMotion(bool canSlowMo) {
	if (canSlowMo == true) {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.5f);
	}
	else if (canSlowMo == false) {
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
	}
}

// Called when the Draw Debug Box checkbox state is ticked inside the BoidSettings Widget Blueprint.
// It visualises the Boids bounding box in which they cannot travel too far from
void ABoidManager::DrawConstraintBox() {
	// Clears the Previous Constraining Box Gizmo Outlines
	FlushPersistentDebugLines(GetWorld());
	
	// Draws a Gizmo Box that is visualised in the simulation
	DrawDebugBox(GetWorld(), FVector(0, 0, 0), FVector(boundingBoxSizeX, boundingBoxSizeY, boundingBoxSizeZ), FColor::Red, true, -1.0f, 0U, 100.0f); 
}
// Called when the Draw Debug Box checkbox state is un-ticked inside the BoidSettings Widget Blueprint
void ABoidManager::HideConstraintBox() {
	// Hide the Constraining Box
	FlushPersistentDebugLines(GetWorld());
}

// Called when the Spawn Obstacles Button is pressed inside the BoidSettings Widget Blueprint
void ABoidManager::SpawnStaticObstacles() {
	// Delete any existing obstacles before spawning in new ones
	for (AActor* obstacle : staticObstaclesArray) {
		obstacle->Destroy();
	}
	// Empty the array of obstacles
	staticObstaclesArray.Empty();
	// Spawn in new Obstacles within the Bounding Box
	for (int i = 0; i < staticObstaclesCount; i++) {
		FVector obstacleSpawnLocation = FVector(FMath::RandRange(-boundingBoxSizeX, boundingBoxSizeX), FMath::RandRange(-boundingBoxSizeY, boundingBoxSizeY),
			FMath::RandRange(-boundingBoxSizeZ, boundingBoxSizeZ));
		FRotator obstacleSpawnRotation = GetActorRotation();

		AObstacle* newStaticObstacle = GetWorld()->SpawnActor<AObstacle>(obstacleSpawnLocation, obstacleSpawnRotation);
		newStaticObstacle->staticObstacleComponent->SetStaticMesh(staticObstacleMesh);

		//Set the new Obstacle to be thisObstacle using the forward declaration of BoidManager
		newStaticObstacle->Manager = this;
		staticObstaclesArray.Add(newStaticObstacle);
	}
}

// Called when the Spawn Dynamic Obstacles Button is pressed inside the BoidSettings Widget Blueprint
void ABoidManager::SpawnDynamicObstacles() {
	// Delete any existing dynamic obstacles before spawning in new ones
	for (AActor* dynamicObstacle : dynamicObstaclesArray) {
		dynamicObstacle->Destroy();
	}
	// Empty the array of dynamic obstacles
	dynamicObstaclesArray.Empty();
	// Spawn in new Dynamic Obstacles within the Bounding Box
	for (int i = 0; i < dynamicObstaclesCount; i++) {
		FVector dynamicObstacleSpawnLocation = FVector(FMath::RandRange(-boundingBoxSizeX, boundingBoxSizeX), FMath::RandRange(-boundingBoxSizeY, boundingBoxSizeY),
			FMath::RandRange(-boundingBoxSizeZ, boundingBoxSizeZ));
		FRotator dynamicObstacleSpawnRotation = GetActorRotation();

		ADynamicObstacle* newDynamicObstacle = GetWorld()->SpawnActor<ADynamicObstacle>(dynamicObstacleSpawnLocation, dynamicObstacleSpawnRotation);
		
		// Gets the current Theme upon Spawning in Dynamic Obstacles and sets their model to match the theme
		switch (myThemes) {
		case ThemeEnum::BIRD:
			newDynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleCone);
			newDynamicObstacle->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
			break;
		case ThemeEnum::FISH:
			newDynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleShark);
			newDynamicObstacle->SetActorScale3D(FVector(2.0f, 2.0f, 2.0f));
			break;
		case ThemeEnum::RABBIT:
			newDynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleFox);
			newDynamicObstacle->SetActorScale3D(FVector(5.0f, 5.0f, 5.0f));
			break;
		default:
			newDynamicObstacle->dynamicObstacleComponent->SetStaticMesh(dynamicObstacleCone);
			newDynamicObstacle->SetActorScale3D(FVector(3.0f, 3.0f, 3.0f));
			break;
		}
		//Set the new Dynamic Obstacle to be this Obstacle using the forward declaration of BoidManager
		newDynamicObstacle->Manager = this;
		dynamicObstaclesArray.Add(newDynamicObstacle);
	}
}