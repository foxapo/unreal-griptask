// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GripTask/Interfaces/UTargetInterface.h"
#include "TargetDummyActor.generated.h"

class UAttributeComponent;
class UTargetComponent;

UCLASS()
class GRIPTASK_API ATargetDummyActor : public AActor, public ITargetInterface
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Stats, meta = (AllowPrivateAccess = "true"))
	UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Target, meta = (AllowPrivateAccess = "true"))
	UTargetComponent* TargetComponent;

public:
	// Sets default values for this actor's properties
	ATargetDummyActor();
	virtual bool IsTarget() const override;
	virtual UTargetComponent* GetActorTargetComponent() override; 
	virtual UAttributeComponent* GetAttributeComponent() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	
};
