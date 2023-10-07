// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorGenerator.h"
UActorGenerator* UActorGenerator::Instance = nullptr;

UActorGenerator* UActorGenerator::Get()
{
	if (!Instance)
	{
		Instance = NewObject<UActorGenerator>();
		Instance->AddToRoot(); // 防止垃圾回收
	}
	return Instance;
}

template <class T>
T* UActorGenerator::Generate(T Class)
{
	return nullptr;
}
