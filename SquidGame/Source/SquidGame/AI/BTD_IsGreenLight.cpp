// @Copyright 


#include "SquidGame/AI/BTD_IsGreenLight.h"
#include "SquidGame/SquidGameCharacter.h"
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

	ASquidGameCharacter* AIPawn = Cast<ASquidGameCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (!AIPawn) return false;
	return true;
}