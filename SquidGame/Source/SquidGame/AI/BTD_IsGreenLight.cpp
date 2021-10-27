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
	bool bSuccess = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	if (!bSuccess) return false;

	AAICRedLightGreenLight* RedLightGreenLightController = Cast<AAICRedLightGreenLight>(OwnerComp.GetAIOwner());
	if (!RedLightGreenLightController) return false;

	if (RedLightGreenLightController->IsGreenLight())
	{
		UE_LOG(LogTemp, Warning, TEXT("True"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("False"))
	}

	return RedLightGreenLightController->IsGreenLight();
}