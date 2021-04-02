#pragma once

#include "CoreMinimal.h"

#include "Grid.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"

enum class EGameStatus : uint8
{
	Fail,
	Success,
	Running,
};

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
	static FLinearColor GetCellColor(const int32 BombsNumber);
	bool GameIsOver() const;

private:
	EGameStatus GameStatus = EGameStatus::Running;
	bool bCheatMode = false;
	TSharedPtr<SUniformGridPanel> Grid;
	FGridData GridData;

	FReply OnReplayClicked();
	EVisibility HandleButtonDetailsVisibility(uint32 Position) const;
	bool IsButtonEnable(uint32 Position) const;
	FReply OnCheatModeClicked();
	FReply HandleButtonClicked(uint32 Position);
};
