// Fill out your copyright notice in the Description page of Project Settings.


#include "Doll.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "Components/AudioComponent.h"
#include "SquidGameCharacter.h"

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

	FTimerHandle Handle_ScanForEleminatePlayers;
	GetWorld()->GetTimerManager().SetTimer(Handle_ScanForEleminatePlayers, this, &ADoll::EleminatePlayers, ScanningForEleminationDelay);

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

	CurrentEleminationProcessDelay = 0.1f;
}

TArray<AActor*> ADoll::ScanningForEleminatePlayers()
{
	TArray<AActor*> EleminatedPlayers;
	TArray<AActor*> OutScanedPlayers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASquidGameCharacter::StaticClass(), OutScanedPlayers);

	for (AActor* ScannedPlayer : OutScanedPlayers)
	{
		ASquidGameCharacter* SquidCharacter{ Cast<ASquidGameCharacter>(ScannedPlayer) };
		if (SquidCharacter)
		{
			if (SquidCharacter->GetVelocity().Size() > 0.f)
			{
				EleminatedPlayers.Add(SquidCharacter);
			}
		}
	}

	return EleminatedPlayers;
}

void ADoll::EleminatePlayers()
{
	TArray<AActor*> PlayersToEleminate = ScanningForEleminatePlayers();

	if (CurrentLight == ELightType::RedLight)
	{	
		if (PlayersToEleminate.Num() > 0)
		{
			for (AActor* Player : PlayersToEleminate)
			{
				if (Player)
				{
					ASquidGameCharacter* SquidCharacter{ Cast<ASquidGameCharacter>(Player) };
					if (SquidCharacter)
					{
						if (!SquidCharacter->IsEleminated())
						{
							SquidCharacter->EleminateFromGame(CurrentEleminationProcessDelay);
							CurrentEleminationProcessDelay += EleminationDelay;
						}					
					}
				}
			}

			FTimerHandle Handle_ReScan;
			GetWorld()->GetTimerManager().SetTimer(Handle_ReScan, this, &ADoll::EleminatePlayers, 0.1f);
		}
		else
		{			
			
		}
	}

	if (PlayersToEleminate.Num() <= 0)
	{
		FTimerHandle Handle_SwitchGreenLight;

		CurrentEleminationProcessDelay = FMath::Clamp(CurrentEleminationProcessDelay, 3.f, 60.f);
		GetWorld()->GetTimerManager().SetTimer(Handle_SwitchGreenLight, this, &ADoll::GreenLight, CurrentEleminationProcessDelay);
		UE_LOG(LogTemp, Warning, L"Delay : %f", CurrentEleminationProcessDelay)
	}
}

