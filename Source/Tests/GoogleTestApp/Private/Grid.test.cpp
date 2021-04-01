#include "GoogleTestApp.h"
#include "../../../Plugins/MinesweeperLib/Source/MinesweeperLibCore/Public/Grid.h"
#include "gtest/gtest.h"
#include "NansCoreHelpers/Public/Misc/NansAssertionMacros.h"


class MinesweeperLibCoreGridTest : public ::testing::Test
{
	virtual void SetUp() override {}

	virtual void TearDown() override {}
};

TEST_F(MinesweeperLibCoreGridTest, CreateABasicGrid)
{
	NGrid* Grid = new NGrid(4, 4, 4);
	Grid->Build();
}
