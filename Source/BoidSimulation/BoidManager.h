// BoidManager header File


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoidManager.generated.h"

// ENUM for Boid Themes
UENUM()
enum class ThemeEnum : uint8 {
	FISH UMETA(DisplayName = "Fish Theme"),
	BIRD UMETA(DisplayName = "Bird Theme"),
	RABBIT UMETA(DisplayName = "Rabbit Theme")
};

UCLASS()

class BOIDSIMULATION_API ABoidManager : public AActor {
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ABoidManager();

	// Boid Settings Variables:
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, Category = "Settings")
	int spawnCount = 150; // Min = 0 - Max = 500
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float spawnRadius = 10000.0f; // Min = 0 - Max = 15000.0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float neighbourRadius = 4000.0f; // Min = 0 - Max = 7500.0
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float separationWeight = 1.0f; // Min = -3 - Max = 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float cohesionWeight = 1.0f; // Min = -3 - Max = 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float alignmentWeight = 1.0f; // Min = -3 - Max = 3
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float speed = 5000.0f; // Min = 0 - Max = 10000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings") 
	float maxVelocity = 1.0f; // Min = 0 - Max = 25
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float constrainForce = 1.0f; // Min = 0 - Max = 5

	// Boid Extras Variables:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	float boundingBoxSizeX = 5000.0f; // Min = 1000 - Max = 10000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	float boundingBoxSizeY = 5000.0f; // Min = 1000 - Max = 10000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	float boundingBoxSizeZ = 5000.0f; // Min = 1000 - Max = 10000
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	int staticObstaclesCount = 10; // Min = 0 - Max = 25
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	int dynamicObstaclesCount = 3; // Min = 0 - Max = 5
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	bool boidAvoidance = true; // Toggle ON/OFF
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	bool obstacleAvoidance = true; // Toggle ON/OFF
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Extra")
	bool showDebugBox = false; // Toggle ON/OFF

	// Obstacle Variables:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMesh* staticObstacleMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMesh* dynamicObstacleCone;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMesh* dynamicObstacleShark;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	UStaticMesh* dynamicObstacleFox;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TArray<class AObstacle*> staticObstaclesArray;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Obstacle")
	TArray<class ADynamicObstacle*> dynamicObstaclesArray;

	// Theme Variables:
	ThemeEnum myThemes;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Themes")
	UStaticMesh* birdMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Themes")
	UStaticMesh* fishMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Themes")
	UStaticMesh* rabbitMesh;

	// Declare Misc Variables:
	USceneComponent* transform;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Misc")
	TArray<class ABoid*> MyBoids;
	
	// Declare Boid Settings Getter Functions:
	UFUNCTION(BlueprintCallable)
	int GetBoidSpawnCount();
	UFUNCTION(BlueprintCallable)
	float GetBoidSpawnRadius();
	UFUNCTION(BlueprintCallable)
	float GetBoidNeighbourRadius();
	UFUNCTION(BlueprintCallable)
	float GetBoidSeparationWeight();
	UFUNCTION(BlueprintCallable)
	float GetBoidCohesionWeight();
	UFUNCTION(BlueprintCallable)
	float GetBoidAlignmentWeight();
	UFUNCTION(BlueprintCallable)
	float GetBoidSpeed();
	UFUNCTION(BlueprintCallable)
	float GetBoidMaxVelocity();
	UFUNCTION(BlueprintCallable)
	float GetBoidConstrainForce();
	
	// Declare Boid Extras Getter Functions:
	UFUNCTION(BlueprintCallable)
	float GetBoundingBoxX();
	UFUNCTION(BlueprintCallable)
	float GetBoundingBoxY();
	UFUNCTION(BlueprintCallable)
	float GetBoundingBoxZ();
	UFUNCTION(BlueprintCallable)
	int GetStaticObstaclesCount();
	UFUNCTION(BlueprintCallable)
	int GetDynamicObstaclesCount();

	// Declare Boid Settings Setter Functions:
	UFUNCTION(BlueprintCallable)
	void SetBoidSpawnCount(int numOfBoids);
	UFUNCTION(BlueprintCallable)
	void SetBoidSpawnRadius(float boidSpawnRadius);
	UFUNCTION(BlueprintCallable)
	void SetBoidNeighbourRadius(float boidNeighbourRadius);
	UFUNCTION(BlueprintCallable)
	void SetBoidSeparationWeight(float boidSeparationWeight);
	UFUNCTION(BlueprintCallable)
	void SetBoidAlignmentWeight(float boidAlignmentWeight);
	UFUNCTION(BlueprintCallable)
	void SetBoidCohesionWeight(float boidCohesionWeight);
	UFUNCTION(BlueprintCallable)
	void SetBoidSpeed(float boidSpeed);
	UFUNCTION(BlueprintCallable)
	void SetBoidMaxVelocity(float boidMaxVelocity);
	UFUNCTION(BlueprintCallable)
	void SetBoidConstrainForce(float boidConstrainForce);

	// Declare Boid Extras Setter Functions:
	UFUNCTION(BlueprintCallable)
	void SetBoundingBoxX(float boundingBoxX);
	UFUNCTION(BlueprintCallable)
	void SetBoundingBoxY(float boundingBoxY);
	UFUNCTION(BlueprintCallable)
	void SetBoundingBoxZ(float boundingBoxZ);
	UFUNCTION(BlueprintCallable)
	void SetStaticObstaclesCount(int numOfObstacles);
	UFUNCTION(BlueprintCallable)
	void SetDynamicObstaclesCount(int numOfDynamicObstacles);

	// Declare Boid Settings Misc Functions:
	UFUNCTION(BlueprintCallable)
	void SpawnNewBoids();
	UFUNCTION(BlueprintCallable)
	void SpawnExtraBoids();
	UFUNCTION(BlueprintCallable)
	void SpawnBoidManager();
	UFUNCTION(BlueprintCallable)
	void ResetSettingsToDefaults();

	// Declare Boid Extras Misc Functions:
	UFUNCTION(BlueprintCallable)
	void SetBoidAvoidance(bool canAvoid);
	UFUNCTION(BlueprintCallable)
	void SetObstacleAvoidance(bool canAvoid);
	UFUNCTION(BlueprintCallable)
	void SetSlowMotion(bool canSlowMo);
	UFUNCTION(BlueprintCallable)
	void DrawConstraintBox();
	UFUNCTION(BlueprintCallable)
	void HideConstraintBox();
	UFUNCTION(BlueprintCallable)
	void SpawnStaticObstacles();
	UFUNCTION(BlueprintCallable)
	void SpawnDynamicObstacles();
	UFUNCTION(BlueprintCallable)
	void ResetExtrasToDefaults();

	// Declare Boid Theme Functions:
	UFUNCTION(BlueprintCallable)
	void BirdTheme();
	UFUNCTION(BlueprintCallable)
	void FishTheme();
	UFUNCTION(BlueprintCallable)
	void RabbitTheme();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<class ABoid*> GetBoidNeighbourHood(ABoid* thisBoid);
};