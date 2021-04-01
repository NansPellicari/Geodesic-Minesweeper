#include "GoogleTestApp.h"
#include "gtest/gtest.h"
#include "NansCoreHelpers/Public/Misc/NansAssertionMacros.h"


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	GIsGGTests = true;

	return RUN_ALL_TESTS();
}
