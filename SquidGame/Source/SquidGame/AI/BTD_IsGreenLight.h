// @Copyright 

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTD_IsGreenLight.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API UBTD_IsGreenLight : public UBTDecorator
{
	GENERATED_BODY()
	
public:

	UBTD_IsGreenLight();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
