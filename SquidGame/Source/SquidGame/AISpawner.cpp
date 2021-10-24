// @Copyright 


#include "AISpawner.h"

// Sets default values
AAISpawner::AAISpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAISpawner::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	NextTransform = GetActorTransform();
	FVector DefaultLocation = NextTransform.GetLocation();	
	FVector Location = DefaultLocation;
	for (int32 i = 0; i < Row; i++)
	{		
		for (int32 j = 0; j < Column; j++)
		{			
			GetWorld()->SpawnActor<AActor>(SpawningClass, NextTransform, SpawnParams);
			Location.Y += ColumnGap;
			NextTransform.SetLocation(Location);
		}

		Location.Y = DefaultLocation.Y;
		Location.X += RowGap;
		NextTransform.SetLocation(Location);
	}
}

// Called every frame
void AAISpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

