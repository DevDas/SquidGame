// Fill out your copyright notice in the Description page of Project Settings.


#include "Doll.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
ADoll::ADoll()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(FName("SceneComp"));
	RootComponent = SceneComp;

	DollMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("DollMesh"));
	DollMesh->AttachToComponent(SceneComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

// Called when the game starts or when spawned
void ADoll::BeginPlay()
{
	Super::BeginPlay();
	
	DefaultRotation = GetActorRotation();
	TargetRotation = FRotator(DefaultRotation.Pitch, DefaultRotation.Yaw + 180.f, DefaultRotation.Roll);

	RedLight();
}

// Called every frame
void ADoll::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ChangeLight();
}

void ADoll::ChangeLight()
{		
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotation, GetWorld()->DeltaTimeSeconds, DollRotationSpeed);
	SetActorRotation(CurrentRotation);
}

void ADoll::PlayGreenLightRedLightSong()
{
	SpawnedGreenLightRedLightSong = UGameplayStatics::SpawnSound2D(this, GreenLightRedLightSongClass, 1.f, 1.f, 0.f, nullptr, false, false);
	if (SpawnedGreenLightRedLightSong)
	{
		SpawnedGreenLightRedLightSong->OnAudioFinished.AddDynamic(this, &ADoll::RedLight);
	}
}

void ADoll::RedLight()
{
	if (CurrentLight != ELightType::None)
	{
		UGameplayStatics::PlaySound2D(this, TurningSound);
	}

	CurrentLight = ELightType::RedLight;
	FRotator Swap = TargetRotation;
	TargetRotation = DefaultRotation;
	DefaultRotation = Swap;

	if (SpawnedGreenLightRedLightSong)
	{
		SpawnedGreenLightRedLightSong->DestroyComponent();
	}
	
	// TODO Check For EleminatePlayers
	FTimerHandle Handle_SwitchGreenLight;
	GetWorld()->GetTimerManager().SetTimer(Handle_SwitchGreenLight, this, &ADoll::GreenLight, SwitchToGreenLightDelay);

	OnLightChange.Broadcast(CurrentLight);
}

void ADoll::GreenLight()
{
	CurrentLight = ELightType::GreenLight;
	FRotator Swap = TargetRotation;
	TargetRotation = DefaultRotation;
	DefaultRotation = Swap;

	UGameplayStatics::PlaySound2D(this, TurningSound);

	FTimerHandle Handle_PlayGreenLightRedLightSong;
	GetWorld()->GetTimerManager().SetTimer(Handle_PlayGreenLightRedLightSong, this, &ADoll::PlayGreenLightRedLightSong, 0.8f);

	OnLightChange.Broadcast(CurrentLight);
}

TArray<AActor*> ADoll::ScanningForEleminatePlayers()
{
	TArray<AActor*> EleminatedPlayers;


	return EleminatedPlayers;
}

void ADoll::EleminatePlayers()
{
	TArray<AActor*> PlayersToEleminate = ScanningForEleminatePlayers();

	for (AActor* Player : PlayersToEleminate)
	{
		// TODO Call Players Death Event
	}
}