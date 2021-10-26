// @Copyright 


#include "SquidGame/AI/AICRedLightGreenLight.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "SquidGame/SquidGameCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"
#include "Kismet/GamePlayStatics.h"
#include "SquidGame/Doll.h"

void AAICRedLightGreenLight::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackBoardComp = nullptr;
	UseBlackboard(BlackBoardData, BlackBoardComp);

	RunBehaviorTree(AIBehavior);

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADoll::StaticClass(), OutActors);
	if (OutActors.Num() > 0)
	{
		if (OutActors[0])
		{
			ADoll* Doll = Cast<ADoll>(OutActors[0]);
			if (Doll)
			{
				Doll->OnLightChange.AddDynamic(this, &AAICRedLightGreenLight::LightChanged);
			}
		}
	}


}

void AAICRedLightGreenLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAICRedLightGreenLight::LightChanged(ELightType LightType)
{
	if (LightType == ELightType::RedLight)
	{
		float RedLightDelay = FMath::RandRange(0.f, RedLightDelayRange);
		FTimerHandle Handle_ChangeToRedLight;
		GetWorld()->GetTimerManager().SetTimer(Handle_ChangeToRedLight, this, &AAICRedLightGreenLight::SetAsRedLight, RedLightDelay);
	}
	else if (LightType == ELightType::GreenLight)
	{
		float GreenLightDelay = FMath::RandRange(0.f, GreenLightDelayRange);
		FTimerHandle Handle_ChangeToGreenLight;
		GetWorld()->GetTimerManager().SetTimer(Handle_ChangeToGreenLight, this, &AAICRedLightGreenLight::SetAsGreenLight, GreenLightDelay);
	}
}

void AAICRedLightGreenLight::SetAsGreenLight()
{
	bIsGreenLight = true;
}

void AAICRedLightGreenLight::SetAsRedLight()
{
	bIsGreenLight = false;
}

bool AAICRedLightGreenLight::IsGreenLight()
{
	return bIsGreenLight;
}