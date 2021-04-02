#include <iostream>

#include "GoogleTestApp.h"
#include "Grid.h"
#include "gtest/gtest.h"
#include "NansCoreHelpers/Public/Misc/NansAssertionMacros.h"


class MinesweeperLibCoreGridTest : public ::testing::Test
{
	virtual void SetUp() override {}

	virtual void TearDown() override {}
};

TEST_F(MinesweeperLibCoreGridTest, CreateABasicGrid)
{
	FGridData Grid(4, 4);
	Grid.BombsAmount = 4;
	try
	{
		NGrid::Build(Grid);
		int32 SlotNum = 0;
		for (int32 Row = 0; Row < Grid.Rows; ++Row)
		{
			for (int32 Col = 0; Col < Grid.Columns; ++Col)
			{
				FGridSlot Slot = Grid.GetSlot(Row, Col);
				std::cout << "Slot: " << SlotNum << "\n";
				std::cout << " - Row " << Row;
				std::cout << " - Col " << Col;
				std::cout << " - is bomb " << Slot.bIsBomb;
				std::cout << " - bombs aside " << Slot.AsideBombsNumber << "\n";
				SlotNum++;
			}
		}
	}
	catch (const TCHAR* e)
	{
		std::cout << "Error occured: " << TCHAR_TO_ANSI(e) << "\n";
	}
}
