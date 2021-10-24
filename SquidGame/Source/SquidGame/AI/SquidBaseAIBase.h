// @Copyright 

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SquidBaseAIBase.generated.h"

/**
 * 
 */
UCLASS()
class SQUIDGAME_API ASquidBaseAIBase : public AAIController
{
	GENERATED_BODY()
	
public :

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
};
