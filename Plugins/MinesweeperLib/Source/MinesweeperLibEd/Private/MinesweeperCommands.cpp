#include "MinesweeperCommands.h"

#define LOCTEXT_NAMESPACE "MinesweeperEditor"

void FMinesweeperCommands::RegisterCommands()
{
	// @formatter:off
	UI_COMMAND(MyButton, "MineSweeper", "Launch the MineSweeper game", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(MyMenuButton, "MineSweeper", "Launch the MineSweeper game", EUserInterfaceActionType::Button, FInputChord());
	// @formatter:on
}

#undef LOCTEXT_NAMESPACE
