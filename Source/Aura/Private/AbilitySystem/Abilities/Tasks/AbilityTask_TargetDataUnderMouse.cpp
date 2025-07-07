// CopyRight Yuanx


#include "AbilitySystem/Abilities/Tasks/AbilityTask_TargetDataUnderMouse.h"

UAbilityTask_TargetDataUnderMouse* UAbilityTask_TargetDataUnderMouse::CreateAbilityTask_TargetDataUnderMouse(
	UGameplayAbility* OwneringAbility)
{
	UAbilityTask_TargetDataUnderMouse* MyObj = NewAbilityTask<UAbilityTask_TargetDataUnderMouse>(OwneringAbility);
	return MyObj;
}

void UAbilityTask_TargetDataUnderMouse::Activate()
{
	APlayerController* PC = Ability->GetCurrentActorInfo()->PlayerController.Get();
	if (PC)
	{
		FHitResult Hit;
		PC->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
		ValidData.Broadcast(Hit.Location);
	}
}
