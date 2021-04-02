#include "UI/SMineSweeperGrid.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Construct(const FArguments& InArgs)
{
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

void SMineSweeperGrid::ChangeGrid(const FVector2D& Vector2D)
{
	
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMineSweeperGrid::Refresh()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Refresh"), ANSI_TO_TCHAR(__FUNCTION__));
}
