// Obstacle cpp File

#include "Obstacle.h"
#include "BoidManager.h"

// Sets default values
AObstacle::AObstacle() {
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	staticObstacleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Model"));
	staticObstacleComponent->SetWorldScale3D(FVector(5.0f, 5.0f, 5.0f));
	this->SetRootComponent(staticObstacleComponent);
}

// Called when the game starts or when spawned
void AObstacle::BeginPlay() {
	Super::BeginPlay();	
}

// Called every frame
void AObstacle::Tick(float DeltaTime){
	Super::Tick(DeltaTime);
	FVector obstacleLocation = GetActorLocation();

	// Destroy any Static Obstacles that are located outside the current bounding box constraint size
	if (obstacleLocation.X > Manager->boundingBoxSizeX || obstacleLocation.X < -Manager->boundingBoxSizeX || obstacleLocation.Y > Manager->boundingBoxSizeY || obstacleLocation.Y < -Manager->boundingBoxSizeY || obstacleLocation.Z > Manager->boundingBoxSizeZ || obstacleLocation.Z < -Manager->boundingBoxSizeZ) {
		Manager->staticObstaclesArray.Remove(this);
		Destroy();
	}
}