// Fill out your copyright notice in the Description page of Project Settings.


#include "DInventoryComponent.h"
#include "ItemStack.h"
#include "CharmingCraft/Entity/Item/DropItem.h"
#include "CharmingCraft/Interface/DItemInteractInterface.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UDInventoryComponent::UDInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


#if WITH_EDITOR
void UDInventoryComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	// 检查更改的属性是否是我们关心的属性
	if (PropertyChangedEvent.Property && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(
		UDInventoryComponent, Inventory))
	{
		for (UItemStack* & ItemStack : Inventory)
		{
			// 如果元素是nullptr，为其分配默认的UItem对象
			if (!ItemStack)
			{
				ItemStack = NewObject<UItemStack>(this, UItemStack::StaticClass());
				ItemStack->Initialize(EMaterial::APPLE, 32);
			}
		}
	}
}
#endif
UDInventoryComponent::FReturnSuccessRemainQuantity UDInventoryComponent::AddToInventory(UItemStack* ItemStack)
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::AddToInventory %s | %d"),
	       *ItemStack->GetItemClass()->DisplayName.ToString(),
	       ItemStack->Amount);
	FReturnSuccessRemainQuantity Result;
	UItemStack* CopiedItemStack = DuplicateObject<UItemStack>(ItemStack, this);
	int32 LocalQuantity = CopiedItemStack->Amount;
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::AddToInventory LocalQuantity: %d bLocalHasFailed: %d"),
	       LocalQuantity,
	       bLocalHasFailed);
	while (LocalQuantity > 0 && !bLocalHasFailed)
	{
		int32 SlotIndex = FindSlot(CopiedItemStack);
		UE_LOG(LogTemp, Warning, TEXT("FindSlot: %d"), SlotIndex);
		if (SlotIndex != -1)
		{
			AddToStack(SlotIndex, 1, CopiedItemStack);
			LocalQuantity--;
			UE_LOG(LogTemp, Warning, TEXT("AddToStack(%d, 1) LocalQuantity = %d"), SlotIndex, LocalQuantity);
		}
		else if (IsEmptySlotAvailable().Result)
		{
			if (CreateNewStack(CopiedItemStack, 1))
			{
				LocalQuantity--;
			}
			else
			{
				bLocalHasFailed = true;
			}
		}
		else
		{
			bLocalHasFailed = true;
		}
	}
	Result.bIsSuccess = !bLocalHasFailed;
	Result.RemainQuantity = LocalQuantity;

	return Result;
}

/*!
 * @param Index 移除物品栏序号位置
 * @param RemoveWholeStack 是否移除整组物品还只是一个
 * @param IsConsumed 是否是消耗物品
 */
void UDInventoryComponent::RemoveInventory(int32 Index, bool RemoveWholeStack, bool IsConsumed)
{
	LocalItemStack = Inventory[Index];
	if (LocalItemStack->Amount == 1 || RemoveWholeStack)
	{
		Inventory[Index] = nullptr;
		if (IsConsumed)
		{
		}
		else
		{
			Drop(LocalItemStack, LocalItemStack->Amount);
		}
	}
	else
	{
		Inventory[Index]->Amount = Inventory[Index]->Amount - 1;
		if (IsConsumed)
		{
		}
		else
		{
			Drop(LocalItemStack, 1);
		}
	}
	OnInventoryUpdate.Broadcast();
}


int32 UDInventoryComponent::FindSlot(UItemStack* ItemStack)
{
	for (int32 Index = 0; Index < Inventory.Num(); ++Index)
	{
		if (Inventory[Index] != nullptr)
		{
			UItemStack* CacheItemStack = Inventory[Index];
			bool bIDEqual = CacheItemStack->Material == ItemStack->Material;
			bool bQuantityValid = CacheItemStack->Amount < GetMaxStackSize(ItemStack);
			if (bIDEqual && bQuantityValid)
			{
				bLocalHasFailed = false;
				UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot %d"), Index);
				return Index; // 返回找到的Index
			}
		}
		else
		{
			return Index;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::FindSlot =  FALSE"));
	return -1; // 如果没有找到合适的Slot，返回-1或其他指示值
}


int32 UDInventoryComponent::GetMaxStackSize(UItemStack* ItemStack)
{
	if (MaterialData)
	{
	} // TODO
	if (ItemStack->GetItemClass()->MaxStackSize)
	{
		return ItemStack->GetItemClass()->MaxStackSize;
	}
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::GetMaxStackSize NO ITEM DATA FOUND"));
	return -1;
}

/* 这个方法还是可以改进的 */
void UDInventoryComponent::AddToStack(int32 Index, int32 Quantity, UItemStack* ItemStack)
{
	if (Inventory.IsValidIndex(Index))
	{
		/* 处理空指针, 如果找到空槽得把空槽传一个初始的ItemStack,设置成 1 */
		if (Inventory[Index] == nullptr)
		{
			Inventory[Index] = ItemStack; // 待改进,这样先放一个属实有点呆
			Inventory[Index]->Amount = 1;
		}
		else
		{
			Inventory[Index]->Amount = Inventory[Index]->Amount + Quantity;
		}
	}
}


UDInventoryComponent::FReturnValue UDInventoryComponent::IsEmptySlotAvailable()
{
	FReturnValue Result;
	for (int32 Index = 0; Index < Inventory.Num(); ++Index)
	{
		if (Inventory[Index] == nullptr)
		{
			Result.Index = Index;
			Result.Result = true;
			return Result;
		}
	}
	Result.Index = -1;
	Result.Result = false;
	return Result;
}


bool UDInventoryComponent::CreateNewStack(UItemStack* ItemStack, int32 Quantity)
{
	if (IsEmptySlotAvailable().Result)
	{
		// UItemStack* NewItemStack = NewObject<UItemStack>();
		// NewItemStack->Amount = ItemStack->Amount;
		// NewItemStack->Material = ItemStack->Material;
		// NewItemStack->ItemMeta = ItemStack->ItemMeta;
		// NewItemStack->ItemMeta->Durability = ItemStack->ItemMeta->Durability;

		Inventory[IsEmptySlotAvailable().Index] = ItemStack;
		return true;
	}
	else
	{
		return false;
	}
}

void UDInventoryComponent::TransferSlots(int32 SourceIndex, UDInventoryComponent* SourceInventory,
                                         int32 DestinationIndex)
{
	LocalItemStack = SourceInventory->Inventory[SourceIndex];
	if (DestinationIndex < 0)
	{
	}
	else
	{
		// 发出者的背包Index
		/* 备注: 这里真的好丑陋,应当实现Minecraft 空气逻辑 */
		if (Inventory[DestinationIndex] != nullptr && Inventory[DestinationIndex]->Material == LocalItemStack->Material)
		{
			// Content 是箱子, Source 是玩家的背包 TODO
			int32 MaxStackSize = GetMaxStackSize(Inventory[DestinationIndex]);
			UE_LOG(LogTemp, Warning,
			       TEXT(
				       "UDInventoryComponent::TransferSlots -> LocalItemStack: %d Inventory[DestinationIndex]: %d MaxStackSize: %d"
			       ),
			       LocalItemStack->Amount, Inventory[DestinationIndex]->Amount, MaxStackSize);
			if (LocalItemStack->Amount + Inventory[DestinationIndex]->Amount > MaxStackSize)
			{
				// 优先算出背包剩余物品, 如果鼠标悬浮物品为 32 箱子里 64,则先计算背包
				// 计算如下 光标物品 - (最大堆叠数 - 同Index下的相同物品数量)
				// 32- (64 - 48) = 16
				SourceInventory->Inventory[SourceIndex]->Amount = LocalItemStack->Amount - (MaxStackSize - Inventory[
					DestinationIndex]->Amount);
				Inventory[DestinationIndex]->Amount = MaxStackSize;
			}
			else if (LocalItemStack->Amount + Inventory[DestinationIndex]->Amount <= MaxStackSize)
			{
				Inventory[DestinationIndex]->Amount = LocalItemStack->Amount + Inventory[
					DestinationIndex]->Amount;
				SourceInventory->Inventory[SourceIndex] = nullptr;
			}
			OnInventoryUpdate.Broadcast();
			SourceInventory->OnInventoryUpdate.Broadcast();
		}
		else
		{
			SourceInventory->Inventory[SourceIndex] = Inventory[DestinationIndex];
			Inventory[DestinationIndex] = LocalItemStack;
			//
			OnInventoryUpdate.Broadcast();
			SourceInventory->OnInventoryUpdate.Broadcast();
		}
	}
}


void UDInventoryComponent::Drop(UItemStack* ItemStack, int32 Quantity)
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::Drop"));
	FVector Location = GetDropLocation();
	FTransform SpawnTransform(Location);

	// 使用SpawnActorDeferred创建ADropItem对象，但它还不在世界中
	ADropItem* Drop = Cast<ADropItem>(
		UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ADropItem::StaticClass(), SpawnTransform));
	UItemStack* CopiedItemStack = DuplicateObject<UItemStack>(ItemStack, this);
	CopiedItemStack->Amount = Quantity;
	if (Drop)
	{
		Drop->Initialize(CopiedItemStack);

		// 使用FinishSpawningActor将Drop对象放入世界中
		UGameplayStatics::FinishSpawningActor(Drop, SpawnTransform);
	}
}

FVector UDInventoryComponent::GetDropLocation()
{
	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	//
	FVector TraceStart = GetOwner()->GetActorLocation() + RandomUnitVectorInConeInDegrees(
		GetOwner()->GetActorForwardVector(), 30) * 150;
	FVector TraceEnd = TraceStart - FVector(0.0, 0.0, 500.0);
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECC_Visibility, QueryParams);
	return Hit.Location;
}


void UDInventoryComponent::PrintDebugMessage()
{
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::PrintDebugMessage"));
	UE_LOG(LogTemp, Warning, TEXT("Content Size is %d"), Inventory.Num());
	for (int32 Index = 0; Index < Inventory.Num(); ++Index)
	{
		if (Inventory[Index] != nullptr)
		{
			UItemStack* ItemStack = Inventory[Index];
			FString DebugMessage = FString::Printf(
				TEXT("Index: %d | ItemID: %s | Quantity: %d"), Index,
				*ItemStack->GetItemClass()->DisplayName.ToString(),
				ItemStack->Amount);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);
		}
	}
}

/*
 * 随机圆锥方向向量生成
 */
FVector UDInventoryComponent::RandomUnitVectorInConeInDegrees(const FVector& ConeDir, float ConeHalfAngleInDegrees)
{
	// 随机生成一个角度和方位角
	float RandAngle = FMath::RandRange(0.f, FMath::DegreesToRadians(ConeHalfAngleInDegrees));
	float RandAzimuth = FMath::RandRange(0.f, 2.f * PI);

	// 使用球坐标系生成随机向量
	FVector RandVector;
	RandVector.X = FMath::Sin(RandAngle) * FMath::Cos(RandAzimuth);
	RandVector.Y = FMath::Sin(RandAngle) * FMath::Sin(RandAzimuth);
	RandVector.Z = FMath::Cos(RandAngle);

	// 创建一个旋转，使Z轴对齐到指定的ConeDir
	FQuat AlignQuat = FQuat::FindBetweenNormals(FVector::UpVector, ConeDir);

	// 将随机向量旋转到指定的圆锥方向上
	FVector ResultVector = AlignQuat.RotateVector(RandVector);

	return ResultVector;
}

void UDInventoryComponent::OnItemInteract(TWeakObjectPtr<AActor> TargetActor, APawn* Instigator)
{
	// 修复普通交互方块触发物品掉落类的逻辑 -> 只有时掉落物类型才执行物品交互
	// 这里的判断符合逻辑应为InteractComponent触发了所有接触到的Actor实现的接口
	if (TargetActor.Get() != nullptr && TargetActor->IsA(ADropItem::StaticClass()))
	{
		IDItemInteractInterface::Execute_Interact(
			TargetActor.Get(), Instigator);
	}

	// TODO 更好的解决方案是把判断抽象出来，Handler基于接触Actor类型再分配调用
	UE_LOG(LogTemp, Warning, TEXT("Call Back from UDInventoryComponent::OnItemInteract"));
}

// Called when the game starts
void UDInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// 设置背包大小
	Inventory.SetNum(8);
	// 启用ActionBar UI组件 不是很美观,暂时封印

	// TODO 有点蠢, 可以优化为另一个世界生成，这个世界优先加载
	for (UItemStack* Items : Inventory)
	{
		if (Items != nullptr && Items->ItemMeta->bIsRenderItem)
		{
			Items->ItemMeta->UpdateRender(GetWorld());
		}
	}
}

/*
* 很好，你已经找到了解决方法。从你提供的代码中，我可以看出，你首先确保UDInventoryComponent::PostInitProperties()被调
* 用来初始化Inventory数组，然后再在UDInventoryComponent::OnRegister()中添加物品。这样的调用顺序使得你能够保证在添加物品之前，Inventory数组已经被正确地初始化。
* 在UE4中，生命周期的理解是很关键的。特定的函数会在特定的时间点被调用，这会影响到对象的初始化和其他逻辑。例如：
* PostInitProperties()：这个函数在属性被初始化之后调用。这是初始化默认属性值的好地方。
* OnRegister()：当一个对象被注册到游戏的逻辑中时，这个函数被调用。这通常发生在物件已经创建和初始化，但在它开始交互或更新之前。
* 确保正确地初始化和设置你的数据是非常重要的，这样可以防止未定义的行为和潜在的崩溃。
*/

void UDInventoryComponent::OnRegister()
{
	Super::OnRegister();
	UE_LOG(LogTemp, Warning, TEXT("UDInventoryComponent::OnRegister()"));
	// 默认物品
	UItemStack* ItemStack = NewObject<UItemStack>(this, UItemStack::StaticClass())->Initialize(EMaterial::APPLE, 64);
	// 默认物品 - 头盔
	UItemStack* ItemStackHelmet = NewObject<UItemStack>(this, UItemStack::StaticClass())->Initialize(
		EMaterial::HELMET, 1);
	// 默认物品 - 铜矿石
	UItemStack* ItemCopper = NewObject<UItemStack>(this, UItemStack::StaticClass())->Initialize(EMaterial::COPPER, 64);
	// 默认物品 - 铅矿石
	UItemStack* ItemLead = NewObject<UItemStack>(this, UItemStack::StaticClass())->Initialize(EMaterial::LEAD, 64);
	// 默认物品 - 钴矿石
	UItemStack* ItemCobalt = NewObject<UItemStack>(this, UItemStack::StaticClass())->Initialize(EMaterial::COBALT, 64);

	Inventory.Add(ItemStack);
	Inventory.Add(ItemStackHelmet);
	Inventory.Add(ItemCopper);
	Inventory.Add(ItemLead);
	Inventory.Add(ItemCobalt);
}

void UDInventoryComponent::PostInitProperties()
{
	Super::PostInitProperties();
	Inventory.SetNum(InventorySize);
}


// Called every frame
void UDInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}
