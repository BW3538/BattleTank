// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerTank = GetPlayerTank();
	if (!PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("No possesion"));
	}

	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Found: %s"), *(PlayerTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("AIController begin play"));
}

void ATankAIController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);
	
	if (GetPlayerTank()) 
	{
		

		//TODO Move towards player

		//Aim towards the player

		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());

		//Fire if ready
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());


}

ATank* ATankAIController::GetPlayerTank() const 
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!PlayerPawn) { return nullptr; }
	return Cast<ATank>(PlayerPawn);
}