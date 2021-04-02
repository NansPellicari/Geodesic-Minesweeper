#pragma once

#include "CoreMinimal.h"

#include "Grid.h"
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
	static FLinearColor GetCellColor(const int32 BombsNumber);
	void ChangeGrid(const FVector2D& InSize);
	void Refresh();
	FReply OnReplayClicked();
	FGridData GridData;
private:
	TSharedPtr<SUniformGridPanel> Grid;
	FReply HandleButtonClicked(uint32 Position);
	bool bGameIsOver = false;
};
