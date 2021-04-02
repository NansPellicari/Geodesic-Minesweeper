#include <iostream>

#include "GoogleTestApp.h"
#include "Grid.h"
#include "gtest/gtest.h"
#include "NansCoreHelpers/Public/Misc/NansAssertionMacros.h"


class MinesweeperLibCoreGridTest : public ::testing::Test
{
	virtual void SetUp() override {}

	virtual void TearDown() override {}

public:
	void Debug(FGridData& Data)
	{
		int32 SlotNum = 0;
		for (int32 Row = 0; Row < Data.Rows; ++Row)
		{
			for (int32 Col = 0; Col < Data.Columns; ++Col)
			{
				const FGridSlot& Slot = Data.GetSlot(Row, Col);
				std::cout << "Slot: " << SlotNum << "\n";
				std::cout << " - Row " << Row;
				std::cout << " - Col " << Col;
				std::cout << " - is bomb " << Slot.bIsBomb;
				std::cout << " - bombs aside " << Slot.AsideBombsNumber << "\n";
				SlotNum++;
			}
		}
	}
};

TEST_F(MinesweeperLibCoreGridTest, CreateABasicGrid)
{
	FGridData Grid(4, 4);
	Grid.BombsAmount = 4;
	try
	{
		NGrid::Build(Grid);
		// Debug(Grid);
		ASSERT_EQ(Grid.Num(), 16);
	}
	catch (const TCHAR* e)
	{
		std::cout << "Error occured: " << TCHAR_TO_ANSI(e) << "\n";
	}
}

TEST_F(MinesweeperLibCoreGridTest, ShouldAssertWhenAskASlotWithWrongValue)
{
	FGridData Grid(4, 4);
	Grid.BombsAmount = 4;
	NGrid::Build(Grid);

	try
	{
		Grid.GetSlot(-1, 4);
	}
	catch (const TCHAR* e)
	{
		EXPECT_STREQ(TCHAR_TO_ANSI(e), "Data.IsValidIndex(Row)");
	}

	try
	{
		Grid.GetSlot(0, 5);
	}
	catch (const TCHAR* e)
	{
		EXPECT_STREQ(TCHAR_TO_ANSI(e), "Data[Row].IsValidIndex(Column)");
	}

	try
	{
		Grid.GetSlot(-1);
	}
	catch (const TCHAR* e)
	{
		EXPECT_STREQ(TCHAR_TO_ANSI(e), "Position < Num() && Position >= 0");
	}

	try
	{
		Grid.GetSlot(16);
	}
	catch (const TCHAR* e)
	{
		EXPECT_STREQ(TCHAR_TO_ANSI(e), "Position < Num() && Position >= 0");
	}
}
