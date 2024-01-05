// Obstacle header File


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class BOIDSIMULATION_API AObstacle : public AActor {
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	class ABoidManager* Manager;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStaticMeshComponent* staticObstacleComponent;
};