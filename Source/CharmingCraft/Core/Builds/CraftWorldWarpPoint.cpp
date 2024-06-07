#include "CraftWorldWarpPoint.h"

#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "CharmingCraft/Core/Log/Logging.h"
#include "CharmingCraft/Core/World/NativeCraftWorld.h"
#include "CharmingCraft/Core/World/WorldManager.h"
#include "Engine/LevelStreamingDynamic.h"

ACraftWorldWarpPoint::ACraftWorldWarpPoint()
{
	// Ensure we can control the load of LevelWarp by datalayer
	bIsSpatiallyLoaded = false;
}

void ACraftWorldWarpPoint::BeginPlay()
{
	Super::BeginPlay();
	bIsInitialized = false;
	UE_LOG(LogChamingCraftWorld, Warning,
	       TEXT("[❕] Warp Point [%s] is initialized at: %s"
	       ), *TargetName, *UCoreComponents::GetWorldManager(this)->GetShownWorld()->GetCraftWorldName());;
	SynchronizeDataToCraftWords();
}

bool ACraftWorldWarpPoint::SynchronizeDataToCraftWords()
{
	TObjectPtr<UNativeCraftWorld> CraftWorld = UCoreComponents::GetWorldManager(this)->GetShownWorld();
	if (CraftWorld)
	{
		CraftWorld->GetLoadedWarpPoints().Add(this);

		// Double Delegate brodcast that compatible both Blueprint and C++
		if (TargetName == "Spawn")
		{
			// Bind C++ version of event
			CraftWorld->OnCraftWorldPrepareInternal.AddLambda([CraftWorld]
			{
				// When triggerd by OnCraftWorldPrepareInternal brodcast Blueprint
				// version of event
				CraftWorld->OnCraftWorldPrepare.Broadcast();
			});
			// Brodcast C++ version of event
			CraftWorld->OnCraftWorldPrepareInternal.Broadcast();
		}
		return true;
	}
	else
	{
		return false;
	}
}
