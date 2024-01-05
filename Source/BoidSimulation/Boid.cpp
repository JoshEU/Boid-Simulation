// BoidManager cpp File

#include "Boid.h"
#include "BoidManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Obstacle.h"
#include "DynamicObstacle.h"

// Sets default values
ABoid::ABoid() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	boidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	boidMesh->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	this->SetRootComponent(boidMesh);
}

// Called when the game starts or when spawned
void ABoid::BeginPlay() {
	Super::BeginPlay();
}

// Calculates a force to drive a particular agent towards a target location
FVector ABoid::Seek(FVector position) {
	FVector newVelocity = position - GetActorLocation();
	newVelocity.Normalize();
	return newVelocity;
}
// Calculates a force to drive a particular agent away from a target location
FVector ABoid::Flee(FVector position) {
	FVector newVelocity = GetActorLocation() - position;
	newVelocity.Normalize();
	return newVelocity;
}

// Keep Flock spaced apart - calculates a repulsing force away from all neighbouring boids
FVector ABoid::Separation(TArray<ABoid*> neighbours) {
	// Check if there are any neighbouring boids to prevent dividing by 0
	if (neighbours.Num() == 0) {
		return FVector::ZeroVector;
	}

	FVector avgFleeVelocity = FVector::ZeroVector;

	// Get Separation Steering force for each of the boid's neighbours
	for (ABoid* Boid : neighbours) {
		// Add all Flee Forces together
		avgFleeVelocity += Flee(Boid->GetActorLocation());
	}

	// Get the flock average separation force & Return the force
	avgFleeVelocity /= neighbours.Num();
	avgFleeVelocity.Normalize();
	// Evade from the average position using a calculated force
	return avgFleeVelocity;
}
// Make Flock stay together - all gather around a similar location
FVector ABoid::Cohesion(TArray<ABoid*> neighbours) {
	// Check if there are any neighbouring boids to prevent dividing by 0
	if (neighbours.Num() == 0) {
		return FVector::ZeroVector;
	}

	FVector avgLocation = FVector::ZeroVector;
	 
	for (ABoid* Boid : neighbours) {
		// Add all neighbouring positions together to find the average
		avgLocation += Boid->GetActorLocation();
	}

	// Get cohesion force of flock in order to find the average flock location
	// Find average location of all neighbouring boids
	avgLocation /= neighbours.Num();
	avgLocation -= this->currentVelocity;
	avgLocation.Normalize();

	// Seek towards the average location
	return Seek(avgLocation);
}
// Steer Flock of Boids in the same direction - all have the same velocity
FVector ABoid::Alignment(TArray<ABoid*> neighbours) {
	// Check if there are any neighbouring boids to prevent dividing by 0
	if (neighbours.Num() == 0) {
		return FVector::ZeroVector;
	}

	FVector newVelocity = FVector::ZeroVector;

	// Get Alignment Steering force for each of the boid's neighbours
	for (ABoid* Boid : neighbours) {
		// Add all neighbours velocitys together
		newVelocity += Boid->currentVelocity;
	}

	// Get alignment force in order to find the average flock direction
	// Find average velocity of all neighbouring boids
	newVelocity /= neighbours.Num();
	newVelocity.Normalize();

	// Steer towards the average velocity
	return newVelocity;
}

// Seek towards a randomised target on the edge of a sphere that is located somewhere within the bounding box constraints (mimics random aimless movement)
FVector ABoid::Wander(float radius, float jitter) {
	FVector myLocation = GetActorLocation();

	// Check if the boid is close enough to the destination - within 500 units
	if (FVector::Dist(myLocation, wanderDestination) < 500.0f || wanderDestination == FVector::ZeroVector) {
		// Generate a new destination (inside the constraning box) for the boid to wander towards
		FVector projectedPos = FVector(FMath::RandRange(-Manager->boundingBoxSizeX, Manager->boundingBoxSizeX), FMath::RandRange(-Manager->boundingBoxSizeY, Manager->boundingBoxSizeY), FMath::RandRange(-Manager->boundingBoxSizeZ, Manager->boundingBoxSizeZ));

		// Find the new destination to wander towards
		wanderDestination = projectedPos + (FMath::VRand() * FMath::RandRange(0.0f, radius));
	}
	// Every frame - Add some jitter to the Boids movement to make it more realistic
	FVector jitterDestination =  Seek(wanderDestination) + (FMath::VRand() * FMath::RandRange(0.0f, jitter));

	return jitterDestination;
}

// Constrains Boids to a custom bounding box
void ABoid::ConstrainBoids(FVector location, FVector boidTargetVelocity) {
	if (location.X > Manager->boundingBoxSizeX || location.X < -Manager->boundingBoxSizeX || location.Y > Manager->boundingBoxSizeY || location.Y < -Manager->boundingBoxSizeY || location.Z > Manager->boundingBoxSizeZ || location.Z < -Manager->boundingBoxSizeZ) {
		// Move towards centre - only when outside of the bounding box multiplied by the constraining force
		targetVelocity += Seek(FVector::Zero()) * Manager->constrainForce ;
	}
}
// If Boids are within 350 units from one another they will be aware of this and avoid collision
void ABoid::BoidAvoidance( FVector location, FVector boidTargetVelocity, TArray<ABoid*> closestBoids) {
	// A Boid must be in a neighbourhood and BoidAvoidance Checkbox state should be true
	if (closestBoids.Num() > 0 && Manager->boidAvoidance == true) {

		// Avoid colliding with neighbouring boids within a certain radius
		for (ABoid* Boid : closestBoids) {
			if (FVector::Dist(location, Boid->GetActorLocation()) < 350.0f) {
				// Move away from the neighbouring boid(s) as it is too close multiplied by a force of 10
				this->targetVelocity += Flee(Boid->GetActorLocation()) * 10;
			}
		}
	}
}
// Contains functionality for Boids avoiding both Static and Dynamic Obstacles
void ABoid::ObstacleAvoidance(FVector location, FVector boidTargetVelocity) {
	
	if (Manager->obstacleAvoidance == true) {
		// Static Obstacle Avoidance - Check if a Boid is within 1500 units from a Static Obstacle, if so they will be aware of this and avoid collision through evasion
		for (AActor* staticObstacle : Manager->staticObstaclesArray) {
			// Flee if the boid is within a set distance from any static obstacles
			if (FVector::Dist(location, staticObstacle->GetActorLocation()) < 1500.0f) {
				this->targetVelocity += Flee(staticObstacle->GetActorLocation()) * 10;
			}
		}
		// Dynamic Obstacle Avoidance - Check if a Boid is within 550 units from a Dynamic Obstacle, if so they will be aware of this and avoid collision through evasion
		for (AActor* dynamicObstacle : Manager->dynamicObstaclesArray) {
			// Flee if the boid is within a set distance from any dynamic obstacles
			if (FVector::Dist(location, dynamicObstacle->GetActorLocation()) < 550.0f) {
				// Replicate realistic movement when avoiding other boids (quickly dart in another direction - focused mainly on fish evading sharks)
				this->currentVelocity += Flee(dynamicObstacle->GetActorLocation());
			}
		}
	}
}
// Apply all the Flocking Behaviours and Steering Forces to the Boids velocity using a Truncating running sum with priority
// Top Priority - Cohesion | Alignment | Separation | Wandering - No Priority
FVector ABoid::ApplyFlockingBehaviours(FVector boidTargetVelocity, TArray<ABoid*> closestBoids) {
	this->targetVelocity += Cohesion(closestBoids) * Manager->cohesionWeight;

	// Only add remaining flocking behaviours and wandering if the boids current target velocity magnitude is less than the given maxVelocity set inside the UI
	if (this->targetVelocity.Length() < Manager->maxVelocity) {
		this->targetVelocity += Alignment(closestBoids) * Manager->alignmentWeight;
	}
	if (this->targetVelocity.Length() < Manager->maxVelocity) {
		this->targetVelocity += Separation(closestBoids) * Manager->separationWeight;
	}
	if (this->targetVelocity.Length() < Manager->maxVelocity) {
		this->targetVelocity += Wander(FMath::RandRange(50.0f, 100.0f), FMath::RandRange(0.0f, 0.05f));
	}
	this->targetVelocity.Normalize();
	return this->targetVelocity;
}

// Called every frame
void ABoid::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

// Custom Boid Update Function
void ABoid::UpdateBoid(float DeltaTime) {
	// Check for valid BoidManager
	if (Manager == nullptr) {
		return;
	}

	// Reset targetVelocity back to 0 every frame
	targetVelocity = FVector::ZeroVector;
	FVector boidLocation = GetActorLocation();
	FRotator boidRotation = GetActorRotation();
	// Gets the Boid NeighbourHoods positions and stores them inside an array
	TArray<ABoid*> closestBoids = Manager->GetBoidNeighbourHood(this);

	ConstrainBoids(boidLocation, targetVelocity);
	BoidAvoidance(boidLocation, targetVelocity, closestBoids);
	ObstacleAvoidance(boidLocation, targetVelocity);

	// Check if the Boid is in a neighbourhood or not
	if (closestBoids.Num() == 0) {
		// Wander around in search for other flocks
		Wander(FMath::RandRange(50.0f, 100.0f), FMath::RandRange(0.0f, 0.05f));
		this->targetVelocity += Seek(wanderDestination);
	}
	else if (closestBoids.Num() > 0) {
		// Boid is in a flock so apply flocking behaviours
		ApplyFlockingBehaviours(targetVelocity, closestBoids);
	}

	// Apply Steering Force Logic
	FVector steeringForce = targetVelocity - currentVelocity;
	currentVelocity += steeringForce * DeltaTime;
	// Apply Velocity
	boidLocation += (currentVelocity * Manager->speed * DeltaTime);
	boidLocation += targetVelocity;

	SetActorLocation(boidLocation);

	// Rotate the boid in the direction of its velocity
	boidRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + currentVelocity);
	// Smooth the rotation to make it look more natural and realistic
	boidRotation = FMath::RInterpTo(this->GetActorRotation(), boidRotation, GetWorld()->DeltaTimeSeconds, 10.0f);
	// Set actor rotation to velocity
	SetActorRotation(boidRotation);
}