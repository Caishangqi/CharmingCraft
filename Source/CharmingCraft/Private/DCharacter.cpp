// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"


#include "NavigationInvokerComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharmingCraft/Controller/DPlayerAIController.h"
#include "CharmingCraft/Core/Attribute/DAttributeComponent.h"
#include "CharmingCraft/Core/Buff/BuffHandlerComponent.h"
#include "CharmingCraft/Core/Interact/DInteractionComponent.h"
#include "CharmingCraft/Core/Skill/DActionComponent.h"
#include "../Core/Container/Inventory/InventoryComponent.h"
#include "../Core/Container/Inventory/EquipmentComponent.h"
#include "Components/PostProcessComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ADCharacter::ADCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/* Camera Settings */

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //  范形是对象类型，括号内给名字，这个名字会在编辑器显示而已
	SpringArmComp->bUsePawnControlRotation = true; //  使用控制器的位置对Pawn进行操控
	//	确保弹簧和网格体/角色本身相连
	SpringArmComp->SetupAttachment(RootComponent); //  层级中第一个组件,最上面的 (胶囊体组件)
	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//	确保摄像机连接到弹簧上面
	CameraComp->SetupAttachment(SpringArmComp);
	SpringArmComp->bDoCollisionTest = false; //不要让摄像机卡住,我们需要卡住摄像机用透视.
	// SpringArmComp->bEnableCameraRotationLag = true;
	// SpringArmComp->CameraRotationLagSpeed = 0.5f;
	GetCharacterMovement()->bOrientRotationToMovement = true; //  设置相机起始点？
	bUseControllerRotationYaw = false;


	/* Interaction Settings */

	InteractionComp = CreateDefaultSubobject<UDInteractionComponent>("InteractionComp");

	/* Attribute Settings */

	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	BuffHandlerComponent = CreateDefaultSubobject<UBuffHandlerComponent>("BuffHandlerComp");

	/* Movement Settings */

	MovementComponent = CreateDefaultSubobject<
		UCharacterMovementComponent>("MovementComponent");

	/* Ability Component Settings */

	ActionComponent = CreateDefaultSubobject<UDActionComponent>("ActionComponent");

	/* AI Settings */

	AIControllerClass = ADPlayerAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	// Set the auto step
	GetCharacterMovement()->MaxStepHeight = 100.0f;
	GetCharacterMovement()->SetWalkableFloorAngle(90.0f);

	/* 后处理组件 */
	// PostProcessComponent = CreateDefaultSubobject<UPostProcessComponent>("PostProcessComponent");

	/* 物品栏 */
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>("Inventory Component");

	EquipmentComponent = CreateDefaultSubobject<UEquipmentComponent>("Equipment Component");

	// AI navigation
	NavigationInvokerComponent = CreateDefaultSubobject<UNavigationInvokerComponent>("NavigationInvoker Component");
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();

	/* AI Controller Initialization */

	PlayerAIController = GetWorld()->SpawnActor<ADPlayerAIController>(AIControllerClass);
	if (PlayerAIController)
	{
		PlayerAIController->SetPawn(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unable to set player AIController to Pawn"));
	}

	AttributeComp->OnHealthChanged.AddDynamic(this, &ADCharacter::HandleHealthChanged);
	InteractionComp->AIController = PlayerAIController;
}


void ADCharacter::MoveForward(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	ControlRot.Yaw = 0.0f;

	// 先获取角色向前的向量，之后对这个向量进行 0 - 1 的scale
	// 注意键盘只会输入 0 - 1,其本身工作原理就是提供 0 或者 1
	AddMovementInput(ControlRot.Vector(), Value);
}

void ADCharacter::MoveRight(float Value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;
	ControlRot.Yaw = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, Value);
}

void ADCharacter::PrimaryInteract()
{
	//InteractionComp->PrimaryInteract();
}

void ADCharacter::SpawnProjectile(TSubclassOf<AActor> ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		// Ignore Player collision
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);

		FVector TraceStart = CameraComp->GetComponentLocation();
		// endpoint far into the look-at distance (not too far, still adjust somewhat towards cross hair on a miss)
		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);

		FHitResult Hit;
		// Return true if we go to a blocking hit
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Overwrite trace end with impact point in the world
			TraceEnd = Hit.ImpactPoint;
		}

		// Find new direction/rotation from Hand pointing to impact point in world
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);
	}
}

void ADCharacter::Dash_TimeElapsed()
{
	//SpawnProjectile(ADDashProjectile);
}

void ADCharacter::SprintStart()
{
	ActionComponent->StartActionByName(this, "Sprint");
}

void ADCharacter::SprintStop()
{
	ActionComponent->StopActionByName(this, "Sprint");
}

void ADCharacter::PrintDebugMessage()
{
	// /* 测试背包 */
	// UE_LOG(LogTemp, Warning, TEXT("should print something"));
	// UInventoryComponent->PrintDebugMessage();
}

void ADCharacter::PrimaryAttack_TimeElapsed()
{
	UE_LOG(LogTemp, Warning, TEXT("Enter PrimaryAttack_TimeElapsed"));
	/*!
	 *	GetControlRotation() 得到玩家控制器的朝向, 就是对准方向
	 */

	// 人物骨架上可以有插槽 socket
	const FVector GunLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	const FTransform SpawnTM = FTransform(GetControlRotation(), GunLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//指定发射 Instigator 是玩家自己
	SpawnParams.Instigator = this;
	//先从世界生成投射物
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	constexpr float DrawScale = 100.0f;
	constexpr float Tickness = 5.0f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of spawn
	LineStart += GetActorRightVector() * 100.0f;
	// Set Line end in direction of the actor's forward
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.0f, 0,
	                          Tickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.0f);
	// Draw Controller's Rotation {'PlayerController' that 'possessed' this character}
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.0f,
	                          0, Tickness);
}


// Called to bind functionality to input
void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//绑定游戏内的轴，第一个参数是名字, 第二个参数是目标, 第三个参数是触发后激活的函数
	PlayerInputComponent->BindAxis("MoveForward", this, &ADCharacter::MoveForward);

	//绑定水平旋转, yaw是水平, pitch是垂直旋转, 这里用的Pawn上的方法
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	/*
	 * 这个方法本质上移动的是Controller的位置，但是UE的人物蓝图有一个属性 Pawn.Use Controller Rotation
	 * 开启这个会让角色基于控制器进行旋转
	 */
	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ADCharacter::Jump);

	PlayerInputComponent->BindAction("PrintDebug", IE_Pressed, this, &ADCharacter::PrintDebugMessage);
}

void ADCharacter::HandleHealthChanged_Implementation(APawn* InstigatorPawn, UDAttributeComponent* OwningComp,
                                                     float Health, float HealthDelta)
{
	IDamageable::HandleHealthChanged_Implementation(InstigatorPawn, OwningComp, Health, HealthDelta);
}

void ADCharacter::HandleDeath_Implementation(APawn* InstigatorPawn)
{
	IDamageable::HandleDeath_Implementation(InstigatorPawn);
}

void ADCharacter::OnActionHit_Implementation(APawn* InstigatorPawn, FHitData HitData)
{
	if (!AttributeComp->IsDead)
	{
		AttributeComp->SubmitHitData(HitData);
	}
}

UDAttributeComponent* ADCharacter::GetAttributeComponent_Implementation()
{
	return AttributeComp;
}

UCharmingCraftInstance* ADCharacter::GetGameInstance_Implementation()
{
	return Cast<UCharmingCraftInstance>(UGameplayStatics::GetGameInstance(this));
}

UWorldManager* ADCharacter::GetWorldManager_Implementation()
{
	return GetGameInstance_Implementation()->GetWorldManager();
}

UGameEventHandler* ADCharacter::GetGameEventHandler_Implementation()
{
	return GetGameInstance_Implementation()->GetGameEventHandler();
}
