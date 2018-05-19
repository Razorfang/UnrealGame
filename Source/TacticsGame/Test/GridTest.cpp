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
	FVector MyLocation(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	FRotator MyRotation(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
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
	if (TestGrid->GetGridOrigin() != MyLocation)
	{
		return false;
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnTestSquare, "GridTest.SquareGrid.Spawn Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FSpawnTestSquare::RunTest(const FString& Parameters)
{

	//Set spawning parameters
	FVector MyLocation(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	FRotator MyRotation(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
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
	if (TestGrid->GetGridOrigin() != MyLocation)
	{
		return false;
	}

	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddTileTestSquare, "GridTest.SquareGrid.Add Tile Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FAddTileTestSquare::RunTest(const FString& Parameters)
{

	//Set spawning parameters
	FVector MyLocation(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	FRotator MyRotation(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
	FActorSpawnParameters SpawnInfo;

	//Create a blank world to spawn our actor in
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Check the map was created properly
	if (!IsValid(World)) { return false; }

	//Construct a AGrid object
	ASquareGrid* TestGrid = World->SpawnActor<ASquareGrid>(MyLocation, MyRotation, SpawnInfo);

	UE_LOG(LogTemp, Warning, TEXT("Grid Origin is (%f, %f, %f)"), TestGrid->GetGridOrigin().X, TestGrid->GetGridOrigin().Y, TestGrid->GetGridOrigin().Z);

	//Check the object was constructed properly
	if (!IsValid(TestGrid))
	{
		return false;
	}
	if (TestGrid->GetGridOrigin() != MyLocation)
	{
		return false;
	}

	//Add a tile to the grid
	TestGrid->AddTile(0, 0, 1);

	//Check the addition happened properly
	if (TestGrid->GetSizeX() != 1 && TestGrid->GetSizeY() != 1 && TestGrid->GetSizeZ() != 2)
	{
		return false;
	}

	TestGrid->AddTile(1, 1, 0);
	if (TestGrid->GetSizeX() != 2 && TestGrid->GetSizeY() != 2 && TestGrid->GetSizeZ() != 2)
	{
		return false;
	}
	

	return true;
}