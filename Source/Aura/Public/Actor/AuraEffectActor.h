// CopyRight Yuanx

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolity
{
	ApplyOnOverlap,
	ApplyOnEndOverlop,
	DoNotApply
};



UENUM(BlueprintType)
enum class EEffectRemovePolity
{
	RemoveOnEndOverlop,
	DoNotRemove
};

UCLASS()
class AURA_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor,TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	bool bDestroyOnEffectRemoval = false;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	EEffectApplicationPolity InstantEffectApplicationPolityPolicy = EEffectApplicationPolity::DoNotApply;
	

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	EEffectApplicationPolity DurationEffectApplicationPolityPolicy = EEffectApplicationPolity::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	EEffectApplicationPolity InfinitEffectApplicationPolityPolicy = EEffectApplicationPolity::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Applied  Effect")
	EEffectRemovePolity InfiniteffectremovePolityPolicy = EEffectRemovePolity::RemoveOnEndOverlop;
	
};
