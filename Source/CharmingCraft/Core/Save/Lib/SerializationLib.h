// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SerializationLib.generated.h"

#define CREATE_JSON_OBJECT(JsonObjectName) \
TSharedPtr<FJsonObject> JsonObjectName = MakeShareable(new FJsonObject); \
if (this->GetClass()) \
{ \
FString ClassName = this->GetClass()->GetName(); \
JsonObjectName->SetStringField(TEXT("Class"), ClassName); \
}

#define CREATE_JSON_OBJECT_FROM_STRING(JsonObjectName, InputString) \
TSharedPtr<FJsonObject> JsonObjectName;\
TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(InputString);\
FJsonSerializer::Deserialize(Reader, JsonObjectName)


#define SET_JSON_FIELD_STRING(JsonObjectVariable, FieldName, FieldValue) \
JsonObjectVariable->SetStringField(TEXT(#FieldName), FieldValue)

#define GET_JSON_FIELD_STRING(JsonObjectVariable, FieldName) \
JsonObjectVariable->GetStringField(TEXT(#FieldName))

#define SET_JSON_FIELD_OBJECT(JsonObjectVariable, FieldName, FieldValue) \
JsonObjectVariable->SetObjectField(TEXT(#FieldName), FieldValue)

#define SET_JSON_FIELD_OBJECT(JsonObjectVariable, FieldName) \
JsonObjectVariable->GetObjectField(TEXT(#FieldName))

#define SET_JSON_FIELD_NUMBER(JsonObjectVariable, FieldName, FieldValue) \
JsonObjectVariable->SetNumberField(TEXT(#FieldName), FieldValue)

#define GET_JSON_FIELD_NUMBER(JsonObjectVariable, FieldName) \
JsonObjectVariable->GetNumberField(TEXT(#FieldName))

#define SET_JSON_FIELD_ARRAY(JsonObjectVariable, FieldName, FieldValue) \
JsonObjectVariable->SetArrayField(TEXT(#FieldName), FieldValue)

#define SET_JSON_FIELD_ARRAY(JsonObjectVariable, FieldName) \
JsonObjectVariable->GetArrayField(TEXT(#FieldName))

#define SET_JSON_FIELD_BOOL(JsonObjectVariable, FieldName, FieldValue) \
JsonObjectVariable->SetBoolField(TEXT(#FieldName), FieldValue)

#define SET_JSON_FIELD_BOOL(JsonObjectVariable, FieldName) \
JsonObjectVariable->GetBoolField(TEXT(#FieldName))

#define SET_JSON_FIELD_ENUM(JsonObjectVariable, FieldName, EnumType, FieldValue) \
GET_ENUM_AS_STRING(FieldValue, EnumType, EnumString);\
SET_JSON_FIELD_STRING(JsonObjectVariable, FieldName, EnumString)

#define INJECT_JSON_FIELD_ENUM(JsonObjectVariable, FieldName, EnumType, OutPutValue) \
GET_ENUM_FROM_STRING(GET_JSON_FIELD_STRING(JsonObjectVariable,FieldName),EnumType,OutPutValue)

#define EXPORT_JSON_OBJECT_AND_SERIALIZE(JsonObjectName, OutputStringName) \
FString OutputStringName; \
TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputStringName); \
FJsonSerializer::Serialize(JsonObjectName.ToSharedRef(), Writer);


#define GET_ENUM_AS_STRING(EnumValue, EnumType, OutputString) \
FString OutputString;\
do \
{ \
UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT(#EnumType), true); \
if(EnumPtr != nullptr) \
{ \
OutputString = EnumPtr->GetNameStringByValue((int64)EnumValue); \
} \
else \
{ \
OutputString = TEXT("Unknown"); \
} \
} while(false)

#define GET_ENUM_FROM_STRING(InputString, EnumType, OutputEnum) \
do \
{ \
UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT(#EnumType), true); \
if(EnumPtr != nullptr) \
{ \
int64 EnumValue = EnumPtr->GetValueByName(FName(*InputString)); \
if(EnumValue != INDEX_NONE) \
{ \
OutputEnum = (EnumType)EnumValue; \
} \
} \
} while(false)


/**
 * 
 */
UCLASS(meta=(BlueprintThreadSafe, ScriptName = "SerializationLibarary"))
class CHARMINGCRAFT_API USerializationLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
};
