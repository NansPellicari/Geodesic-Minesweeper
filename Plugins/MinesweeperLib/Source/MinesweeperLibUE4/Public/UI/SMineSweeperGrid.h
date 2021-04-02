#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SUniformGridPanel.h"

/**
 * 
 */
class MINESWEEPERLIBUE4_API SMineSweeperGrid : public SUniformGridPanel
{
public:
SLATE_BEGIN_ARGS(SMineSweeperGrid) {}
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);
	void ChangeGrid(const FVector2D& Vector2D);
	void Refresh();
};
