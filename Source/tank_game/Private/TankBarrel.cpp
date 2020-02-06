// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	
	auto OutTankName = GetOwner()->GetName();
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	//向量角度*每秒最大移動角度*每幀需要的時間
	auto ElevationChange=RelativeSpeed*MaxDepreesPerSecond*GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange,MinElevationDegrees,MaxElevationDegrees);
	//UE_LOG(LogTemp, Warning, TEXT("tank [%s]wxx RelativeSpeed %f Elevate: %f  delta=%f"), *OutTankName, RelativeSpeed, RawNewElevation, GetWorld()->DeltaTimeSeconds);
	
	SetRelativeRotation(FRotator(RawNewElevation,0,0));
	
	//
}