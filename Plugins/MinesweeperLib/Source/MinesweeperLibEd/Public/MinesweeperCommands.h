#pragma once

#include "CoreMinimal.h"
#include "EditorStyleSet.h"
#include "MinesweeperLibEditorStyle.h"
#include "Framework/Commands/Commands.h"

/**
 * 
 */
class FMinesweeperCommands : public TCommands<FMinesweeperCommands>
{
public:
	FMinesweeperCommands() : TCommands<FMinesweeperCommands>(
		FName(TEXT("Minesweeper")),
		FText::FromString("Minesweeper Commands"),
		NAME_None,
		FMinesweeperLibEditorStyle::GetStyleSetName()
	) { }

	TSharedPtr<FUICommandInfo> MyButton;
	TSharedPtr<FUICommandInfo> MyMenuButton;
	virtual void RegisterCommands() override;
};
