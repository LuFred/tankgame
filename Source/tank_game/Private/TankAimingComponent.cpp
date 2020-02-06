// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation,float LaunchSpeed)const
{
	if (!Barrel)
	{
		return;
	}	
	FVector	OutLaunchVelocity;//速度矢量(有大小和方向)
	auto OutTankName = GetOwner()->GetName();
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	UE_LOG(LogTemp, Warning, TEXT("tank[%s] hitlocation=%s  StartLocation: %f %f %f"), *OutTankName, *HitLocation.ToString(), StartLocation.X, StartLocation.Y, StartLocation.Z);
	//做抛物运动时,在已知起点,目标点,速度大小时,求出其初始抛射的方向
	bool HaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (HaveAimSolution)
	{

		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("tank [%s] Aim firing: %s"), *OutTankName, *AimDirection.ToString());
		//旋转炮筒角度
		MoveBarrelTowards(AimDirection);
	}
}
//移动炮台
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) const
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();//獲取對象當前向量
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;//目標向量減去當前向量 即爲差值向量
	auto OutTankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("tank [%s] MoveBarrelTowards: %s"), *OutTankName, *DeltaRotator.ToString());
	//移動抛光上下幅度，向量度數
	Barrel->Elevate(DeltaRotator.Pitch);
	//移動炮臺
	Turret->Rotation(DeltaRotator.Yaw);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}
void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	Turret = TurretToSet;
}