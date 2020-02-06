// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"

void UTankTurret::Rotation(float RelativeSpeed)
{
	auto OutTankName = GetOwner()->GetName();

	
	UE_LOG(LogTemp, Warning, TEXT("tank [%s] turret=============c=%f"), *OutTankName, RelativeSpeed);
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	//向量角度*每秒最大移動角度*每幀需要的時間
	auto RotationChange = RelativeSpeed * MaxDepreesPerSecond * GetWorld()->DeltaTimeSeconds;

	/*auto Rotation = FMath::Clamp(RelativeRotation.Yaw + RotationChange, MinElevationDegrees, MaxElevationDegrees);*/
	auto Rotation =RelativeRotation.Yaw + RotationChange;

	UE_LOG(LogTemp, Warning, TEXT("tank [%s] turret a=%f  b=%f   c=%f"), *OutTankName, Rotation,RotationChange, RelativeRotation.Yaw);

	SetRelativeRotation(FRotator(0, Rotation, 0));

	//
}