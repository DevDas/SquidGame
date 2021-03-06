// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Doll.generated.h"

UENUM(BlueprintType)
enum ELightType
{
	None,
	RedLight,
	GreenLight
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLightChange, ELightType, LightType);

UCLASS()
class SQUIDGAME_API ADoll : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoll();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class USceneComponent* SceneComp = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UStaticMeshComponent* DollMesh = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void ChangeLight();

	UFUNCTION(BlueprintCallable)
	void PlayGreenLightRedLightSong();

	UFUNCTION(BlueprintCallable)
	void RedLight();

	UFUNCTION(BlueprintCallable)
	void GreenLight();

	UFUNCTION(BlueprintCallable)
		TArray<AActor*> ScanningForEleminatePlayers();

	UFUNCTION(BlueprintCallable)
		void EleminatePlayers();

	UPROPERTY(BlueprintReadOnly)
		class UAudioComponent* SpawnedGreenLightRedLightSong = nullptr;

	UPROPERTY(EditAnywhere)
		class USoundBase* GreenLightRedLightSongClass = nullptr;

	UPROPERTY(EditAnywhere)
		class USoundBase* TurningSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DollRotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SwitchToGreenLightDelay = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.05", ClampMax = "1.0"))
		float ScanningForEleminationDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.1", ClampMax = "2.0"))
		float EleminationDelay = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator DefaultRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FRotator TargetRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TEnumAsByte<ELightType> CurrentLight = ELightType::None;

	UPROPERTY(BlueprintAssignable)
	FOnLightChange OnLightChange;

private:

	float CurrentEleminationProcessDelay  = 0.1f;
};
