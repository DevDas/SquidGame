// @Copyright 


#include "SquidGame/AI/BTD_IsGreenLight.h"
#include "SquidGame/AI/AICRedLightGreenLight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTD_IsGreenLight::UBTD_IsGreenLight()
{
	NodeName = "Is Green Light";
}

bool UBTD_IsGreenLight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return OwnerComp.GetBlackboardComponent()->GetValueAsBool(FName("IsGreenLight"));
}