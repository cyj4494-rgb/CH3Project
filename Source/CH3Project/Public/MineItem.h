#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "MineItem.generated.h"


UCLASS()
class CH3PROJECT_API AMineItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
	AMineItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDamage;

	void ActivateItem(AActor* Activator) override;
};
