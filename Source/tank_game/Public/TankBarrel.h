// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_GAME_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	void Elevate(float DegressPreSecond);

private:
	UPROPERTY(EditAnywhere)
	float MaxDepreesPerSecond = 20;//每秒最大移動角度
	UPROPERTY(EditAnywhere)
		float MaxElevationDegrees = 40;//最大轉角
	UPROPERTY(EditAnywhere)
		float MinElevationDegrees = -1;//最小轉角
	
};
