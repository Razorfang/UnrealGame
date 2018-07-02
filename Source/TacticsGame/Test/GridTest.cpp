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

	//Set random spawning parameters
	FVector MyLocation(FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f), FMath::RandRange(0.0f, 1.0f));
	FRotator MyRotation(FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f), FMath::RandRange(0.0f, 360.0f));
	FActorSpawnParameters SpawnInfo;

	//Create a blank world to spawn our actor in
	UWorld* World = FAutomationEditorCommonUtils::CreateNewMap();

	//Check the map was created properly
	if (!IsValid(World))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot create new map"));
		return false;
	}

	//Construct a AGrid object
	AGrid* TestGrid = World->SpawnActor<AGrid>(MyLocation, MyRotation, SpawnInfo);

	//Check the object was constructed properly
	if (!IsValid(TestGrid))
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot construct AGrid object"));
		return false;
	}

	//Make sure grid type is Unknown
	if (TestGrid->GetGridType() != EGridType::EUnknown)
	{
		UE_LOG(LogTemp, Warning, TEXT("GridType is incorrect"));
		return false;
	}

	//Make sure origin is set properly
	if (TestGrid->GetGridOrigin() != MyLocation)
	{
		UE_LOG(LogTemp, Warning, TEXT("Origin is incorrect"));
		return false;
	}

	return true;
}


/*IMPLEMENT_SIMPLE_AUTOMATION_TEST(FInitTest, "GridTest.SquareGrid.Initialisation Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FInitTest::RunTest(const FString& Parameters)
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


	//Do the initialization, and check if it makes the right number of tiles, and also that they are in the correct spot (TODO). Use random numbers between 0 and 9
	int randX = FMath::Rand() % 10;
	int randY = FMath::Rand() % 10;
	int randZ = FMath::Rand() % 10;

	TestGrid->InitTiles(randX, randY, randZ);

	if (TestGrid->GetNumSpaces() != (randX * randY * randZ))
	{
		return false;
	}

	return true;
}*/


/*IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSpawnTestSquare, "GridTest.SquareGrid.Spawn Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
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
}*/

/*IMPLEMENT_SIMPLE_AUTOMATION_TEST(FAddTileTestSquare, "GridTest.SquareGrid.Add Tile Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
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
	}*/

	//Add 27 tiles one at a time to fill a 3x3x3 cube
	/*for (int i = 0; i < 27; i++)
	{
		TestGrid->AddTile(i % 3, (i / 3) % 3, (i / 9) % 3);
	}*/


	/*if (TestGrid->GetSizeX() != 3 && TestGrid->GetSizeY() != 3 && TestGrid->GetSizeZ() != 3 && TestGrid->GetNumSpaces() != 27)
	{
		return false;
	}*/
	

	//return true;
//}

/*IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRemoveTileTestSquare, "GridTest.SquareGrid.Remove Tile Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FRemoveTileTestSquare::RunTest(const FString& Parameters)
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

	//Add 27 tiles one at a time to fill a 3x3x3 cube
	for (int i = 0; i < 27; i++)
	{
		TestGrid->AddTile(i % 3, (i / 3) % 3, (i / 9) % 3);
	}

	//if (TestGrid->GetSizeX() != 3 && TestGrid->GetSizeY() != 3 && TestGrid->GetSizeZ() != 3 && TestGrid->GetNumSpaces() != 27)
	//{
	//	return false;
	//}

	//Remove these tiles one at a time, starting from the end
	for (int i = 26; i >= 0; i--)
	{
		TestGrid->RemoveTile(i % 3, (i / 3) % 3, (i / 9) % 3);
	}

	//if (TestGrid->GetSizeX() != 0 && TestGrid->GetSizeY() != 0 && TestGrid->GetSizeZ() != 0 && TestGrid->GetNumSpaces() != 0)
	//{
	//	return false;
	//}

	return true;

}*/

/*IMPLEMENT_SIMPLE_AUTOMATION_TEST(FNullifyTileTestSquare, "GridTest.SquareGrid.Nullify Tile Test", EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter | EAutomationTestFlags::HighPriority)
bool FNullifyTileTestSquare::RunTest(const FString& Parameters)
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
	}*/

	//Add 27 tiles one at a time to fill a 3x3x3 cube
	//TestGrid->InitTiles(3, 3, 3);

	/*if (TestGrid->GetSizeX() != 3 && TestGrid->GetSizeY() != 3 && TestGrid->GetSizeZ() != 3 && TestGrid->GetNumSpaces() != 27)
	{
		return false;
	}*/

	//Nullify each tile, until everything is gone. This should have the same effect as removing since we are nullifying the end
	/*for (int i = 26; i >= 0; i--)
	{
		TestGrid->NullifyTile(i % 3, (i / 3) % 3, (i / 9) % 3);
	}*/

	/*if (TestGrid->GetSizeX() != 0 && TestGrid->GetSizeY() != 0 && TestGrid->GetSizeZ() != 0 && TestGrid->GetNumSpaces() != 0)
	{
		return false;
	}*/

	/*TestGrid->InitTiles(3, 3, 2);
	TestGrid->NullifyTile(1, 0, 0);

	return true;

}*/