// Radek Cehak | Interview Task | Grip Digital


#include "TargetDummyActor.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "GripTask/Components/AttributeComponent.h"
#include "GripTask/Components/TargetComponent.h"
#include "GripTask/Core/DebugMacros.h"
#include "GripTask/GameModes/GripTaskGameplayMode.h"
#include "GripTask/UI/Widgets/Nameplate.h"

ATargetDummyActor::ATargetDummyActor()
{
	struct FConstructorStatics
	{
		FName ID_Characters;
		FText NAME_Characters;

		FConstructorStatics()
			: ID_Characters(TEXT("Characters"))
			  , NAME_Characters(NSLOCTEXT("SpriteCategory", "Characters", "Characters"))
		{
		}
	};

	static FConstructorStatics ConstructorStatics;

	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(ACharacter::CapsuleComponentName);
	CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

	CapsuleComponent->CanCharacterStepUpOn = ECB_No;
	CapsuleComponent->SetShouldUpdatePhysicsVolume(true);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	CapsuleComponent->bDynamicObstacle = true;
	RootComponent = CapsuleComponent;

	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SpriteInfo.Category = ConstructorStatics.ID_Characters;
		ArrowComponent->SpriteInfo.DisplayName = ConstructorStatics.NAME_Characters;
		ArrowComponent->SetupAttachment(CapsuleComponent);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}

	Mesh = CreateOptionalDefaultSubobject<USkeletalMeshComponent>(ACharacter::MeshComponentName);
	if (Mesh)
	{
		Mesh->AlwaysLoadOnClient = true;
		Mesh->AlwaysLoadOnServer = true;
		Mesh->bOwnerNoSee = false;
		Mesh->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPose;
		Mesh->bCastDynamicShadow = true;
		Mesh->bAffectDynamicIndirectLighting = true;
		Mesh->PrimaryComponentTick.TickGroup = TG_PrePhysics;
		Mesh->SetupAttachment(CapsuleComponent);
		static FName MeshCollisionProfileName(TEXT("CharacterMesh"));
		Mesh->SetCollisionProfileName(MeshCollisionProfileName);
		Mesh->SetGenerateOverlapEvents(false);
		Mesh->SetCanEverAffectNavigation(false);
	}

	AttributeComponent = CreateDefaultSubobject<UAttributeComponent>(TEXT("AttributeComponent"));
	TargetComponent = CreateDefaultSubobject<UTargetComponent>(TEXT("TargetComponent"));

	NameplateComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("NameplateWidgetComponent"));
	NameplateComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	NameplateComponent->SetWidgetSpace(EWidgetSpace::Screen);
	NameplateComponent->SetDrawAtDesiredSize(true);
	NameplateComponent->SetVisibility(true);
	NameplateComponent->SetRelativeLocation(FVector(0, 0, 120));
	NameplateComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	// NameplateComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1);
}

bool ATargetDummyActor::IsTarget()
{
	return true;
}

UTargetComponent* ATargetDummyActor::GetActorTargetComponent()
{
	return TargetComponent;
}

UAttributeComponent* ATargetDummyActor::GetAttributeComponent()
{
	return AttributeComponent;
}

void ATargetDummyActor::BeginPlay()
{
	Super::BeginPlay();
	if (!AttributeComponent)
	{
		DEBUG_PRINT("AttributeComponent not set");
	}
	else
	{
		SetupCharacterStats(AttributeComponent->GetCharacterStatsId());
	}
}

void ATargetDummyActor::SetupCharacterStats(FName Id)
{
	if (const AGripTaskGameplayMode* GameMode = Cast<AGripTaskGameplayMode>(GetWorld()->GetAuthGameMode()))
	{
		if (FCharacterStats* Stats = GameMode->GetCharacterStats(Id))
		{
			AttributeComponent->SetBaseStats(Stats);
			UNameplate* NameplateWidget = Cast<UNameplate>(NameplateComponent->GetUserWidgetObject());
			if (!NameplateWidget)
			{
				DEBUG_PRINT("NameplateWidget not set");
				return;
			}
			TScriptInterface<ITargetInterface> TargetInterface;
			TargetInterface.SetObject(this);
			TargetInterface.SetInterface(Cast<ITargetInterface>(this));
			NameplateWidget->InitTarget(TargetInterface);
		}
	}
}

void ATargetDummyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
