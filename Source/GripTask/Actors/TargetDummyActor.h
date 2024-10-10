// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GripTask/Interfaces/AttributeInterface.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "TargetDummyActor.generated.h"

class UAttributeComponent;
class UTargetComponent;

UCLASS()
class GRIPTASK_API ATargetDummyActor : public AActor, public ITargetInterface, public IAttributeInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Transient)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, Transient)
	UTargetComponent* TargetComponent;

public:
	// Sets default values for this actor's properties
	ATargetDummyActor();
	virtual bool IsTarget() override;
	virtual UTargetComponent* GetActorTargetComponent() override;
	virtual UAttributeComponent* GetAttributeComponent() override;
	virtual void SetupCharacterStats(FName Id) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
};
