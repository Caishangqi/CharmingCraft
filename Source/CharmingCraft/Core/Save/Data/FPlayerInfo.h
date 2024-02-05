#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "FPlayerInfo.generated.h"

USTRUCT(BlueprintType)
struct FPlayerInfo : public FTableRowBase
{
	GENERATED_BODY()

	FPlayerInfo(): PlayerNickName(""), CostumeId(0), IsSelected(false)
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerInformation")
	FString PlayerNickName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PlayerInformation")
	int32 CostumeId;
	UPROPERTY(BlueprintReadWrite)
	bool IsSelected;
};
