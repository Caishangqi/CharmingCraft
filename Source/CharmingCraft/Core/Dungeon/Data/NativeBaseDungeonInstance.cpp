// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeBaseDungeonInstance.h"

#include "CharmingCraft/Core/Libarary/CoreComponents.h"
#include "GameFramework/Character.h"

bool ANativeBaseDungeonInstance::IsDungeonWorldLoaded(int TargetChildDungeon)
{
	if (ChildDungeonsWorldsInstance.IsEmpty())
	{
		return false;
	}
	FCharmingCraftWorld* DungeonWorld = ChildDungeonsWorldsInstance.Find(TargetChildDungeon);
	if (DungeonWorld)
	{
		if (DungeonWorld->GamePlayWorld)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

ANativeBaseDungeonInstance::ANativeBaseDungeonInstance()
{
}

bool ANativeBaseDungeonInstance::JoinPlayerToDungeon(ACharacter* Player, int32 TargetChildDungeon)
{
	if (IsDungeonWorldLoaded(TargetChildDungeon))
	{
		// Should Unload Player Current Level
		FCharmingCraftWorld PlayerCurrentWorld = UCoreComponents::GetWorldManager(Player)->GetPlayerCurrentLevel(Player);
		//UCoreComponents::GetWorldManager(Player)->Un
		// Let Player Join Dungeon world
	}
	return false;
}

bool ANativeBaseDungeonInstance::LeavePlayerFromDungeon(ACharacter* Player, int32 TargetChildDungeon)
{
	return false;
}

bool ANativeBaseDungeonInstance::ExitPlayerFromDungeon(ACharacter* Player)
{
	return false;
}
