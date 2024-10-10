// Radek Cehak | Interview Task | Grip Digital

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DraggableWidgetDragDropOperations.generated.h"

/**
 * 
 */
UCLASS()
class GRIPTASK_API UDraggableWidgetDragDropOperations : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category= "DragDrop")
	FVector2D DragOffset;
};
