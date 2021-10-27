// @Copyright 


#include "SquidGame/AI/BTD_IsGreenLight.h"
#include "SquidGame/AI/AICRedLightGreenLight.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "AIController.h"
#include "Kismet/KismetSystemLibrary.h"

UBTD_IsGreenLight::UBTD_IsGreenLight()
{
	NodeName = "Is Green Light";
}

bool UBTD_IsGreenLight::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UE_LOG(LogTemp, Warning, TEXT("Calling"))

	AAICRedLightGreenLight* RedLightGreenLightController = Cast<AAICRedLightGreenLight>(OwnerComp.GetAIOwner());

	return false;//RedLightGreenLightController && RedLightGreenLightController->IsGreenLight();
}