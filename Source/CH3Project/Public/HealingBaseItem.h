
#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingBaseItem.generated.h"

UCLASS()
class CH3PROJECT_API AHealingBaseItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AHealingBaseItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float HealAmount;

	void virtual ActivateItem(AActor* Activator) override;
};
