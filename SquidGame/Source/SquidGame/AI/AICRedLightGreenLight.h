// @Copyright 

#pragma once

#include "CoreMinimal.h"
#include "SquidGame/AI/SquidBaseAIBase.h"
#include "SquidGame/Doll.h"
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

	UFUNCTION(BlueprintPure)
	bool IsGreenLight() const;

	UFUNCTION()
	void LightChanged(ELightType LightType);

	void SetAsGreenLight();
	void SetAsRedLight();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "3.0"))
		float RedLightDelayRange = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "3.0"))
		float GreenLightDelayRange = 1.f;

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		float AcceptanceRadius = 200;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBehaviorTree* AIBehavior = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
		class UBlackboardData* BlackBoardData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AICondition")
		bool bIsGreenLight = false;
};
