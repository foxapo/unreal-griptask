// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GripTask/Interfaces/AttributeInterface.h"
#include "GripTask/Interfaces/TargetInterface.h"
#include "TargetDummyActor.generated.h"

UCLASS()
class GRIPTASK_API ATargetDummyActor : public AActor, public ITargetInterface, public IAttributeInterface
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent* NameplateComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UArrowComponent* ArrowComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

public:
	ATargetDummyActor();
	virtual bool IsTarget() override;
	virtual UTargetComponent* GetActorTargetComponent() override;
	virtual UAttributeComponent* GetAttributeComponent() override;
	virtual void SetupCharacterStats(FName Id) override;

protected:
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere)
	class UAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere)
	class UTargetComponent* TargetComponent;

public:
	virtual void Tick(float DeltaTime) override;
};
