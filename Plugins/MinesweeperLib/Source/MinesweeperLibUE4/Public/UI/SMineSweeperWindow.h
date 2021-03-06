#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class SMineSweeperGrid;

struct FMinesweeperGridSize
{
	static const FVector2D Beginner;
	static const FVector2D Advanced;
	static const FVector2D Expert;
};

/**
 * 
 */
class MINESWEEPERLIBUE4_API SMineSweeperWindow : public SCompoundWidget
{
public:
SLATE_BEGIN_ARGS(SMineSweeperWindow) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	bool bIsCustom = false;
	FVector2D ChosenConfig;
	TSharedPtr<SMineSweeperGrid> Grid;

	void ChangeGridConfig(const FVector2D& GridSize);
	void WidthChanged(int32 NewValue, ETextCommit::Type);
	void HeightChanged(int32 NewValue, ETextCommit::Type);

	FReply OnLevelClicked(const FVector2D GridSize);
	FReply OnCustomClicked();
	TOptional<int32> OnGetPreviewWidthValue() const { return ChosenConfig.X; }
	TOptional<int32> OnGetPreviewHeightValue() const { return ChosenConfig.Y; }
};
