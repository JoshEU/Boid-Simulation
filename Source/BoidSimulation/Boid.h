// BoidManager header File


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Boid.generated.h"

UCLASS()
class BOIDSIMULATION_API ABoid : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoid();

	FVector currentVelocity = FVector::ZeroVector;
	FVector targetVelocity = FVector::ZeroVector;
	TArray<class ABoid*> nearestBoid;
	
	// Forward declaration meaning you don't need to #include BoidManager
	class ABoidManager* Manager;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector wanderDestination;

	FVector Seek(FVector position);
	FVector Flee(FVector position);
	FVector Separation(TArray<ABoid*> neighbours);
	FVector Cohesion(TArray<ABoid*> neighbours);
	FVector Alignment(TArray<ABoid*> neighbours);
	FVector Wander(float radius, float jitter);
	void ConstrainBoids(FVector location, FVector targetVelocity);
	void BoidAvoidance(FVector location, FVector targetVelocity, TArray<ABoid*> closestBoids);
	void ObstacleAvoidance(FVector location, FVector targetVelocity);
	FVector ApplyFlockingBehaviours(FVector targetVelocity, TArray<ABoid*> closestBoids);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateBoid(float DeltaTime);
	UStaticMeshComponent* boidMesh;	
};