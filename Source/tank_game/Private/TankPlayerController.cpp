// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	auto ControlledTank = GetControlledTank();
		if (!ControlledTank) 
		{
			UE_LOG(LogTemp, Warning, TEXT("PlayController not possesing a tank"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("PlayController possessing:%s"), *(ControlledTank->GetName()));
		}
}

//获取玩家对象，强转为ATank对象
ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}


// Called every frame
void ATankPlayerController::Tick(float DeltaTime)
{	
	
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation)) {
		GetControlledTank()->AimAt(HitLocation);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("not hit"));
	}
	
	
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation)const
{
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	//获取屏幕尺寸
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	//根据屏幕尺寸计算白点的平面坐标位置
	auto ScreenLocation = FVector2D(ViewportSizeX*CrosshairXLocation, ViewportSizeY*CrosshairYLocation);
	UE_LOG(LogTemp, Warning, TEXT("Look ScreenLocation :%s"), *ScreenLocation.ToString());
	
	
	FVector WorldDirection;
	//根据平面坐标转换为世界中的空间坐标
	if (GetLookDirection(ScreenLocation, WorldDirection)) {
		if (GetLookVectorHitLocation(WorldDirection, HitLocation))
		{
			return true;
		}
			
	}
	return false;
}

//根据平面坐标返回世界空间3维坐标
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector WorldLocation; //to be discarded
	return DeprojectScreenPositionToWorld(
		ScreenLocation.X,
		ScreenLocation.Y, 
		WorldLocation,
		LookDirection);

}
bool ATankPlayerController::GetLookVectorHitLocation(FVector& LookDirection,FVector& HitLocation)const
{
	FHitResult HitResult;

	//玩家相机视角
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	//获取终点
	FVector EndLocation = StartLocation + (LookDirection*LineTraceRange);
	//判断start-end距离之间是否有对象被击中（遮挡），从而得到第一个可被击中的目标位置HitResult
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility)
	)
	{	
		HitLocation = HitResult.Location;
		return true;
	}
	else {
		
	}
	return false;
}