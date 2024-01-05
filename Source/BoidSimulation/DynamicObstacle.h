// Dynamic Obstacle header File


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DynamicObstacle.generated.h"

UCLASS()
class BOIDSIMULATION_API ADynamicObstacle : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamicObstacle();

	class ABoidManager* Manager;
	class ABoid* BoidClass;
	
	FVector currentVelocity = FVector::ZeroVector;
	FVector targetVelocity = FVector::ZeroVector;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int boidNumToPursue = 0;
	bool hasCaughtBoid = true;
	float pursueSpeedMultiplier = 1.5f;
	
	int PickRandomBoid(int boidNumToPursue);
	bool BoidCatchCheck(bool hasCaughtBoid);
	FVector SeekBoid(FVector position);
	FVector PursueBoid(ABoid* boidPosition);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateDynamicObstacle(float DeltaTime);
	UStaticMeshComponent* dynamicObstacleComponent;
};