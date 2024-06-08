#include "CraftWorldWarpPoint.h"
#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "CharmingCraft/Core/World/NativeCraftWorld.h"
#include "CharmingCraft/Core/World/WorldManager.h"

ACraftWorldWarpPoint::ACraftWorldWarpPoint()
{
	// Ensure we can control the load of LevelWarp by datalayer
	bIsSpatiallyLoaded = false;
}

void ACraftWorldWarpPoint::BeginPlay()
{
	Super::BeginPlay();
	bIsInitialized = false;
	// UE_LOG(LogChamingCraftWorld, Warning,
	//        TEXT("[❕] Warp Point [%s] is initialized at: %s"
	//        ), *TargetName, *UCoreComponents::GetWorldManager(this)->GetShownWorld()->GetCraftWorldName());;
	SynchronizeDataToCraftWords();
}

bool ACraftWorldWarpPoint::SynchronizeDataToCraftWords()
{
	TObjectPtr<UNativeCraftWorld> CraftWorld = UCoreComponents::GetWorldManager(this)->GetShownWorld();
	// UE_LOG(LogChamingCraftWorld, Warning,
	//        TEXT("[❕] Current Shown World is [%s] "
	//        ), *CraftWorld->GetCraftWorldName());
	if (CraftWorld)
	{
		CraftWorld->GetLoadedWarpPoints().Add(this);
		// Call normal
		CraftWorld->OnWarpDataUpdateInternal.AddLambda([CraftWorld,this](UNativeCraftWorld*, ACraftWorldWarpPoint*)
		{
			CraftWorld->OnWarpDataUpdate.Broadcast(CraftWorld, this);
		});
		CraftWorld->OnWarpDataUpdateInternal.Broadcast(CraftWorld, this);
		if (TargetName == "Spawn")
		{
			// Double Delegate brodcast that compatible both Blueprint and C++

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
		// UE_LOG(LogChamingCraftWorld, Warning,
		//        TEXT("[❕] OnWarpDataUpdate is brodcast in world [%s] by [%s]"
		//        ), *CraftWorld->GetName(), *this->TargetName);
		return true;
	}
	else
	{
		return false;
	}
}
