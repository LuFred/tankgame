// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TANK_GAME_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Rotation(float DegressPreSecond);

private:
	UPROPERTY(EditAnywhere)
		float MaxDepreesPerSecond = 60;//每秒最大移動角度
	UPROPERTY(EditAnywhere)
		float MaxElevationDegrees = 90;//最大轉角
	UPROPERTY(EditAnywhere)
		float MinElevationDegrees =-90;//最小轉角
};
