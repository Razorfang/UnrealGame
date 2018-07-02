#include "SquareGrid.h"
#include "AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareConstructionTest, "GridTest.SquareGrid.Constructor Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareConstructionTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Check that the default parameters are correct

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareInitTest, "GridTest.SquareGrid.Initialization Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareInitTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareSetMeshesTest, "GridTest.SquareGrid.Set Meshes Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareSetMeshesTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	//Set the mesh using SetTilesMesh and verify

	/*verify(SquareTestGrid.GetTileWidth() == 1.0f);*/

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareCoordToWorldTest, "GridTest.SquareGrid.CoordToWorld Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareCoordToWorldTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	//Run coordtoworld on a large set of values, and verify each time

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareSetAllHighlightedTest, "GridTest.SquareGrid.Set All HIghlighted Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareSetAllHighlightedTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	//Run SetTilesHighlighted and verify

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareGetNumSpacesTest, "GridTest.SquareGrid.GetNumSpaces Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareGetNumSpacesTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	//Run GetNumSpaces and verify

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSquareTileIsValidTest, "GridTest.SquareGrid.TileIsValid Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSquareTileIsValidTest::RunTest(const FString& Parameters)
{

	//Construct a ASquareGrid object
	ASquareGrid SquareTestGrid;

	//Initialize the grid with random x,y,z,state, and known mesh

	//Run TileIsValid and verify

	return true;
}