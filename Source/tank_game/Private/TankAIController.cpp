// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("TankAIController not possesing a tank"));
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("TankAIPlayController possessing:%s"), *(ControlledTank->GetName()));
	}
}
//获取控制者(AI or Player)
ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
//获取第一个玩家控制者(Player)
ATank* ATankAIController::GetPlayerTank() const
{
	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}


// Called every frame
void ATankAIController::Tick(float DeltaTime)
{
	FVector Location;
	return;
	GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
}



