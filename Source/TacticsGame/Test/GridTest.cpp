#include "Grid.h"
#include "AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FConstructionTest, "GridTest.Grid.Constructor Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::SmokeFilter)
bool FConstructionTest::RunTest(const FString& Parameters)
{

	//Construct a AGrid object
	//AGrid TestGrid;

	//TODO: Stuff

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPlaceholderTest, "GridTest.Placeholder Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
bool FPlaceholderTest::RunTest(const FString& Parameters)
{
	// Make the test pass by returning true, or fail by returning false.
	return true;
}