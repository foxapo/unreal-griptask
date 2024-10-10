#include "DraggableWidgetBase.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "GripTask/Classes/DraggableWidgetDragDropOperations.h"
#include "GripTask/Core/DebugMacros.h"

void UDraggableWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	bIsDragging = false;
}

FReply UDraggableWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		bIsDragging = true;
		DragOffset = InGeometry.AbsoluteToLocal(InMouseEvent.GetScreenSpacePosition()); // Store the relative offset
		return FReply::Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	return Reply;
}

void UDraggableWidgetBase::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	UDraggableWidgetDragDropOperations* DragDropOperation = NewObject<UDraggableWidgetDragDropOperations>();
	DragDropOperation->DragOffset = DragOffset;
	DragDropOperation->Payload = this;
	DragDropOperation->DefaultDragVisual = this;
	DragDropOperation->Pivot = EDragPivot::MouseDown;

	OutOperation = DragDropOperation;
}

bool UDraggableWidgetBase::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{

	DEBUG_PRINT("UDraggableWidgetBase::NativeOnDrop");
	
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}
