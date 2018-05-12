#include "SquareGrid.h"
#include "AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareConstructionTest, "GridTest.SquareGrid.Constructor Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter)
bool FSquareConstructionTest::RunTest(const FString& Parameters)
{

	/*//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Check that the default parameters are correct
	if (SquareTestGrid.GetTileWidth() != 1.0f)
	{
		return false;
	}
	if (SquareTestGrid.GetTileLength() != 1.0f)
	{
		return false;
	}
	if (SquareTestGrid.GetTileHeight() != 1.0f)
	{
		return false;
	}
	if (SquareTestGrid.GetSizeX() != 1)
	{
		return false;
	}
	if (SquareTestGrid.GetSizeY() != 1)
	{
		return false;
	}
	if (SquareTestGrid.GetSizeZ() != 1)
	{
		return false;
	}*/

	/*verify(SquareTestGrid.GetTileWidth() == 1.0f);
	verify(SquareTestGrid.GetTileLength() == 1.0f);
	verify(SquareTestGrid.GetTileHeight() == 1.0f);

	verify(SquareTestGrid.GetSizeX() == 1);
	verify(SquareTestGrid.GetSizeY() == 1);
	verify(SquareTestGrid.GetSizeZ() == 1);*/

	return true;
}

