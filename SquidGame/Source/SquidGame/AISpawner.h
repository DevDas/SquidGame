// @Copyright 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AISpawner.generated.h"

UCLASS()
class SQUIDGAME_API AAISpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "SpawnAI")
		UClass* SpawningClass = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Grid")
		FTransform NextTransform;

	UPROPERTY(EditAnywhere, Category = "Grid")
		int32 Row = 5;

	UPROPERTY(EditAnywhere, Category = "Grid")
		int32 Column = 10;

	// X-Axis
	UPROPERTY(EditAnywhere, Category = "Grid")
		float RowGap = 100.f;

	// Y-Axis
	UPROPERTY(EditAnywhere, Category = "Grid")
		float ColumnGap = 100.f;
};
