#include "SceneWarpPoint.h"

ASceneWarpPoint::ASceneWarpPoint()
{
	// Ensure we can control the load of LevelWarp by datalayer
	bIsSpatiallyLoaded = false;
}

void ASceneWarpPoint::BeginPlay()
{
	Super::BeginPlay();
	bIsInitialized = true;
}
