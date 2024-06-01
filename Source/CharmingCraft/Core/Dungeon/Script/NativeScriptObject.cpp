// Fill out your copyright notice in the Description page of Project Settings.


#include "NativeScriptObject.h"

#include "ScriptActorInterface.h"

bool UNativeScriptObject::StopScript_Implementation(UObject* InstigatorObject)
{
	// Make ParentScriptActor to stop the Script Object Instance
	IScriptActorInterface::Execute_RemoveRunningScriptObject(ParentScriptActor, this);
	// It should mark this Object state as "Remove"

	return true;
}

void UNativeScriptObject::OnScriptTick_Implementation(UObject* InstigatorObject)
{
}

bool UNativeScriptObject::StartScript_Implementation(UObject* InstigatorObject)
{
	return true;
}
