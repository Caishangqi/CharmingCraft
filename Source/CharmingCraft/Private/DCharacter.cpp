// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ADCharacter::ADCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp"); //范形是对象类型，括号内给名字，这个名字会在编辑器显示而已
	//确保弹簧和网格体/角色本身相连
	SpringArmComp->SetupAttachment(RootComponent); //层级中第一个组件,最上面的 (胶囊体组件)

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	//确保摄像机连接到弹簧上面
	CameraComp-> SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
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
}
