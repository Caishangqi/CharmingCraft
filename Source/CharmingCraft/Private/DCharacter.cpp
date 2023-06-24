// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
ADCharacter::ADCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //范形是对象类型，括号内给名字，这个名字会在编辑器显示而已
	SpringArmComp->bUsePawnControlRotation = true; //使用控制器的位置对Pawn进行操控
	//确保弹簧和网格体/角色本身相连
	SpringArmComp->SetupAttachment(RootComponent); //层级中第一个组件,最上面的 (胶囊体组件)

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//确保摄像机连接到弹簧上面
	CameraComp->SetupAttachment(SpringArmComp);

	GetCharacterMovement()->bOrientRotationToMovement = true; //设置相机起始点？
	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}


void ADCharacter::MoveForward(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// 先获取角色向前的向量，之后对这个向量进行 0 - 1 的scale
	// 注意键盘只会输入 0 - 1,其本身工作原理就是提供 0 或者 1
	AddMovementInput(ControlRot.Vector(), value);
}

void ADCharacter::MoveRight(float value)
{
	FRotator ControlRot = GetControlRotation();
	ControlRot.Pitch = 0.0f;
	ControlRot.Roll = 0.0f;

	// X = Forward (Red)
	// Y = Right (Green)
	// Z = Up (Blue)

	FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	AddMovementInput(RightVector, value);
}

void ADCharacter::PrimaryAttack()
{
	/*!
	 *	GetControlRotation() 得到玩家控制器的朝向, 就是对准方向
	 */
	FTransform SpawnTM = FTransform(GetControlRotation(), GetActorLocation());
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	//先从世界生成投射物
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
}

// Called every frame
void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ADCharacter::PrimaryAttack);
}
