#include "Grid.h"
#include "SquareGrid.h"
#include "AutomationTest.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "AutomationEditorCommon.h"

//Latent commands will run until they return true. These are used for waiting on stuff that can happen over many frames, like loading and spawning
DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForWorldToSpawn, UWorld*, Map);
bool FWaitForWorldToSpawn::Update()
{
	return IsValid(Map);
}

DEFINE_LATENT_AUTOMATION_COMMAND_ONE_PARAMETER(FWaitForGridToSpawn, AGrid*, Grid);
bool FWaitForGridToSpawn::Update()
{
	return IsValid(Grid);
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnTest, "GridTest.Grid.Spawn Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSpawnTest::RunTest(const FString& Parameters)
{

	//Set spawning parameters
	FVector MyLocation(0, 0, 0);
	FRotator MyRotation(0, 0, 0);
	FActorSpawnParameters SpawnInfo;

	//Create a blank world to spawn our actor in
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Check the map was created properly
	if (!IsValid(World))
	{
		return false;
	}

	//Construct a AGrid object
	AGrid* TestGrid = World->SpawnActor<AGrid>(MyLocation, MyRotation, SpawnInfo);

	//Check the object was constructed properly
	if (!IsValid(TestGrid))
	{
		return false;
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnTestSquare, "GridTest.SquareGrid.Spawn Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSpawnTestSquare::RunTest(const FString& Parameters)
{

	//Set spawning parameters
	FVector MyLocation(0, 0, 0);
	FRotator MyRotation(0, 0, 0);
	FActorSpawnParameters SpawnInfo;

	//Create a blank world to spawn our actor in
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Check the map was created properly
	if (!IsValid(World))
	{
		return false;
	}

	//Construct a AGrid object
	ASquareGrid* TestGrid = World->SpawnActor<ASquareGrid>(MyLocation, MyRotation, SpawnInfo);

	//Check the object was constructed properly
	if (!IsValid(TestGrid))
	{
		return false;
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddTileTestSquare, "GridTest.SquareGrid.Add Tile Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FAddTileTestSquare::RunTest(const FString& Parameters)
{

	//Set spawning parameters
	FVector MyLocation(0, 0, 0);
	FRotator MyRotation(0, 0, 0);
	FActorSpawnParameters SpawnInfo;

	//Create a blank world to spawn our actor in
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Check the map was created properly
	if (!IsValid(World))
	{
		return false;
	}

	//Construct a AGrid object
	ASquareGrid* TestGrid = World->SpawnActor<ASquareGrid>(MyLocation, MyRotation, SpawnInfo);

	//Check the object was constructed properly
	if (!IsValid(TestGrid))
	{
		return false;
	}

	//Check the parameters of the square grid


	return true;
}