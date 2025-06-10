// CopyRight Yuanx


#include "AbilitySystem/Data/AttributeInfo.h"

FAuraAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
	for (const FAuraAttributeInfo& Info : AttributeInfomation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("不能为 在 AttributeInfo [%s] 中 为  AttributeTag [%s] 找到 Info "),*GetNameSafe(this),*AttributeTag.ToString());
	}

	return FAuraAttributeInfo();
}
