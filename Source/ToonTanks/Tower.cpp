// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle, 
		this, 
		&ATower::CheckFireCondition, 
		FireRate, 
		true
	);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank) 
	{
		//distance Tank-Tower
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		
		//if Tank in range
		if (Distance <= FireRange) 
		{
			//rotate Turret to Tank
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{
	if (!Tank) 
	{ 
		return; 
	}

	if (InFireRange() && Tank->bAlive)
	{
		//fire Projectile
		Fire();
	}
}

bool ATower::InFireRange() 
{
	if (Tank)
	{
		//distance Tank-Tower
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		//if Tank in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
