#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"

/**
 * 
 */
class MINESWEEPERLIBUE4_API SMineSweeperGrid : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SMineSweeperGrid) : _Rows(32), _Columns(32) {}
		SLATE_ARGUMENT(uint32, Rows)
		SLATE_ARGUMENT(uint32, Columns)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void ChangeGrid(const FVector2D& InSize);
	void Refresh();
	FReply OnReplayClicked();
private:
	TSharedPtr<SUniformGridPanel> Grid;
	uint32 Rows;
	uint32 Columns;
	FReply HandleButtonClicked(uint32 Position);
};
