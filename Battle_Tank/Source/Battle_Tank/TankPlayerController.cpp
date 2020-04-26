// Fill out your copyright notice in the Description page of Project Settings.

#include "Battle_Tank.h"
#include "Engine/World.h"
#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) 
	{
		UE_LOG(LogTemp, Warning, TEXT("No possesion"));
	}

	else 
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessed: %s"), *(ControlledTank->GetName()));
	}
	UE_LOG(LogTemp, Warning, TEXT("PlayerController begin play"));
}

void ATankPlayerController::Tick(float DeltaTime) 
{
	Super::Tick(DeltaTime);

	
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() 
{
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out Parameter
	if (GetSightRayHitLocation(HitLocation)) //Ray traces
	{
		
			// TODO point towards hitLocation

		GetControlledTank()->AimAt(HitLocation);
	}
}

// if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const 
{
	//find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//deproject screen positon of crosshair to world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection)) 
	{
		//line trace along that look direction, get what is hit up to max range

		GetVectorHitLocation(LookDirection, OutHitLocation);
	}
	
	return true;
}

bool ATankPlayerController::GetVectorHitLocation(FVector LookDirection, FVector& HitLocation)const 
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if(GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	else 
	{
		HitLocation = FVector(0);
		return false;
	}


}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CamerWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CamerWorldLocation, LookDirection);
}