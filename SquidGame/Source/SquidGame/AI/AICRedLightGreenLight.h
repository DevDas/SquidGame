// @Copyright 

#pragma once

#include "CoreMinimal.h"
#include "SquidGame/AI/SquidBaseAIBase.h"
#include "AICRedLightGreenLight.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API AAICRedLightGreenLight : public ASquidBaseAIBase
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* AIBehavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardData* BlackBoardData;
};
