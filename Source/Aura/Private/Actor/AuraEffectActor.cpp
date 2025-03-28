// CopyRight Yuanx


#include "Actor/AuraEffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/AuraAttributeSet.h"

// Sets default values
AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}


void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}


//
void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{

	//使用GetAbilitySystemComponent能够直接获取到相应的ASC
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (nullptr == TargetASC) return;

	check(GameplayEffectClass);

	//如果对最后一个函数内的参数不熟悉，可以由下往上写
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass,1.f,EffectContextHandle);
	FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());


	//如果需要删除infinite effect，则存储effect handle
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfinitEffectRemovePolityPolicy == EEffectRemovePolity::RemoveOnEndOverlop)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
	
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}
	if (InfinitEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}
} 

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnEndOverlop)
	{
		ApplyEffectToTarget(TargetActor,InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnEndOverlop)
	{
		ApplyEffectToTarget(TargetActor,DurationGameplayEffectClass);
	}

	if (InfinitEffectApplicationPolityPolicy == EEffectApplicationPolity::ApplyOnEndOverlop)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGameplayEffectClass);
	}

	if (InfinitEffectRemovePolityPolicy == EEffectRemovePolity::RemoveOnEndOverlop)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent((TargetActor));

		if (!IsValid(TargetASC)) return;

		
		//循环过程中不能直接删除，可能会导致游戏崩溃。需要创建一个数组存储，循环完之后再删除
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> HandlePair:ActiveEffectHandles)
		{
			if (TargetASC == HandlePair.Value)
			{
				//Removes GameplayEffect by Handle. StacksToRemove=-1 will remove all stacks.
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key,1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		for (auto Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}

