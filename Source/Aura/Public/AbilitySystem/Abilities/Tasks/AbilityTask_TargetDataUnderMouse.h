// CopyRight Yuanx

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_TargetDataUnderMouse.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature,const FVector&,Data);


UCLASS()
class AURA_API UAbilityTask_TargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,Category="Ability|Tasks",meta=(Displayname = "TargetDataUnderMouse",BlueprintInternalUseOnly = "true",HidePin = "OwneringAbility",DefaultToSelf = "OwneringAbility"))
	static UAbilityTask_TargetDataUnderMouse* CreateAbilityTask_TargetDataUnderMouse(UGameplayAbility* OwneringAbility);

	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature ValidData;
	
private:

	virtual void Activate() override;
};
