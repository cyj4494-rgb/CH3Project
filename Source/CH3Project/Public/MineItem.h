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

	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	float ExplosionDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Item");
	int32 ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects");
	USoundBase* ExplosionSound;
	bool bHasExploded;

	FTimerHandle ExplosionTimerHandle;

	void ActivateItem(AActor* Activator) override;

	void Explode();
};
