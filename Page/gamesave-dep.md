# 操作不当引起的游戏内 DEP

## 主要原因

- 使用引用类型和指针类型的 Struct 未标注 `UPROPERTY()` 宏
- 由于未标注 `UPROPERTY()` 则被垃圾回收, 导致空指针和 DEP

**注意**: Struct 如果是 **指针类型** 不可以被标记 `UPROPERTY()`

## 解决方案

### 非引用类型Struct

#### 优点

- 可以直接避免出现这类问题，让数据全程由 Unreal Engine 反射系统管理
- 若Struct内有指针类型的变量，可以标注 `UPROPERTY()` 让资源系统管理，可能需要重写` = 操作符`
- 若Struct内有指针类型的变量并且该数据结构存放在 LinkList，则需要重写 `== 操作符` 来支持LinkList相关功能

```c++
USTRUCT(BlueprintType)
struct FSaveSlotInfo
{
	GENERATED_BODY()
	FSaveSlotInfo(): SaveSlotID(0), SaveSlotPath(""), SaveSlotRelativePath(""), SaveSlotName(""), bPrepareDelete(false),
	                 IsIndicateBound(false), PlayerData(nullptr), RealmData(nullptr),
	                 ProgressData(nullptr), LevelData(nullptr)
	{
	}

public:
	// 存档的唯一标识符
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "SaveData")
	FGuid UniqueID;

	UPROPERTY(BlueprintReadWrite)
	int32 SaveSlotID;
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotPath;
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotRelativePath; // Player View
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotName;
	UPROPERTY(BlueprintReadWrite)
	bool bPrepareDelete;
	UPROPERTY(BlueprintReadWrite)
	bool IsIndicateBound;
	UPROPERTY(BlueprintReadWrite)
	UPlayerData* PlayerData;
	UPROPERTY(BlueprintReadWrite)
	URealmData* RealmData;
	UPROPERTY(BlueprintReadWrite)
	UProgressData* ProgressData;
	UPROPERTY(BlueprintReadWrite)
	ULevelData* LevelData;

    // 需要重写 == 来判断存档指针地址 PlayerData, RealmData, ProgressData, LevelData 是否一致
	friend bool operator==(const FSaveSlotInfo& Lhs, const FSaveSlotInfo& RHS)
	{
		return Lhs.SaveSlotID == RHS.SaveSlotID
			&& Lhs.SaveSlotPath == RHS.SaveSlotPath
			&& Lhs.SaveSlotRelativePath == RHS.SaveSlotRelativePath
			&& Lhs.SaveSlotName == RHS.SaveSlotName
			&& Lhs.bPrepareDelete == RHS.bPrepareDelete
			&& Lhs.IsIndicateBound == RHS.IsIndicateBound
			&& Lhs.PlayerData == RHS.PlayerData
			&& Lhs.RealmData == RHS.RealmData
			&& Lhs.ProgressData == RHS.ProgressData
			&& Lhs.LevelData == RHS.LevelData;
	}

	friend bool operator!=(const FSaveSlotInfo& Lhs, const FSaveSlotInfo& RHS)
	{
		return !(Lhs == RHS);
	}
};
```

#### 缺点

- 若Struct内数据庞大，则会影响读写效率增加性能开销。
- 由于存档Struct包含了4个子存档，主要数据集中在指针类型的 PlayerData, RealmData, ProgressData, LevelData, 故直接拷贝即可。



## 注意事项

在 Unreal Engine中，对存档对象执行任何读写操作前，若你不能保证数据合法性，你最好先加载该 `USaveGame` 修改后在进行保存，Debugger不能很好地显示游戏保存对象的有效性，`IsValid()` 也不能。
```c++
Cast<YouSaveGame>(UGameplayStatics::LoadGameFromSlot()
```
```c++
UGameplayStatics::SaveGameToSlot(YouSaveGame)
```