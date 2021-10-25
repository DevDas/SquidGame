// @Copyright 


#include "SquidGame/AI/AICRedLightGreenLight.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "SquidGame/SquidGameCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"

void AAICRedLightGreenLight::BeginPlay()
{
	Super::BeginPlay();

	UBlackboardComponent* BlackBoardComp = nullptr;
	UseBlackboard(BlackBoardData, BlackBoardComp);

	RunBehaviorTree(AIBehavior);
}

void AAICRedLightGreenLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}