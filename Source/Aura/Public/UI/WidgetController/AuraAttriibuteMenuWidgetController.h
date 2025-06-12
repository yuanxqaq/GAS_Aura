// CopyRight Yuanx

#pragma once

#include "CoreMinimal.h"
#include "AuraWidgetController.h"
#include "AuraAttriibuteMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttriibuteMenuWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDepencedencies() override;
};
