// Fill out your copyright notice in the Description page of Project Settings.

#include "ResourceManagement.h"
#include "Math/UnrealMathUtility.h"
#include <cstdlib>
#include <ctime>

UResourceManagement::UResourceManagement(const FObjectInitializer& ObjectInitializer): UUserWidget(ObjectInitializer)
{
	//constructor, empty for now
}

bool UResourceManagement::Initialize()
{
	Super::Initialize();

	QuantumController = Cast<AQuantumPlayerController>(GetWorld()->GetFirstPlayerController());

	if (QuantumController != nullptr)
	{
		QuantumController->SetRMSReference(this);
	}

	if (CompleteManagement != nullptr) 
	{
		CompleteManagement->OnClicked.AddDynamic(this, &UResourceManagement::CompleteResourceManagement);
	}

	SetStartValues();

	return true;
}

//call from UMG on add to viewport
void UResourceManagement::SetStartValues()
{
	BaseShieldValue = QuantumController->GetShieldHealth();
	CurrentShieldValue = BaseShieldValue;

	RepairAllocation = 0.0f;
	ScavengeAllocation = 0.0f;
	RescueAllocation = 0.0f;

	CurrentResourcePool = MaxResourcePoolValue;
	ResourcesVisual->SetPercent(1);
}

//update functions called via UMG on button click events

void UResourceManagement::UpdateResourcePool(int value)
{
	CurrentResourcePool += value;
	
	CurrentResourcePool = FMath::Clamp(CurrentResourcePool, 0.0f, MaxResourcePoolValue);

	UpdateResourcesVisual();
}

void UResourceManagement::UpdateRepairAllocation(int value)
{
	if (value > 0)
	{
		if (CurrentResourcePool > 0 && CurrentShieldValue < MaxShieldValue)
		{
			RepairAllocation += value;

			RepairAllocation = FMath::Clamp(RepairAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}
	else
	{
		if (RepairAllocation > 0)
		{
			RepairAllocation += value;

			RepairAllocation = FMath::Clamp(RepairAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}

	SetShieldRepairValue();
}

void UResourceManagement::UpdateScavengeAllocation(int value)
{
	if (value > 0)
	{
		if (CurrentResourcePool > 0)
		{
			ScavengeAllocation += value;

			ScavengeAllocation = FMath::Clamp(ScavengeAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}
	else
	{
		if (ScavengeAllocation > 0)
		{
			ScavengeAllocation += value;

			ScavengeAllocation = FMath::Clamp(ScavengeAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}
}

void UResourceManagement::UpdateRescueAllocation(int value)
{
	if (value > 0)
	{
		if (CurrentResourcePool > 0)
		{
			RescueAllocation += value;

			RescueAllocation = FMath::Clamp(RescueAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}
	else
	{
		if (RescueAllocation > 0)
		{
			RescueAllocation += value;

			RescueAllocation = FMath::Clamp(RescueAllocation, 0.0f, MaxResourcePoolValue);

			UpdateResourcePool(-value);
		}
	}
}

void UResourceManagement::SetShieldRepairValue()
{
	CurrentShieldValue = (BaseShieldValue + (RepairAllocation * ShieldRepairsPerAllocation));

	CurrentShieldValue = FMath::Clamp(CurrentShieldValue, 0.0f, MaxShieldValue);
}

void UResourceManagement::UpdateResourcesVisual()
{
	ResourcesVisual->SetPercent(CurrentResourcePool / MaxResourcePoolValue);
}

void UResourceManagement::CompleteResourceManagement()
{
	srand(time(0));

	float scavengeRoll = rand() % 100;
	float rescueRoll = rand() % 100;

	if (scavengeRoll <= ScavengeSuccessRate)
	{
		float damageIncrease = ScavengeAllocation * WeaponDamageIncreasePerAllocation;
		QuantumController->IncreasePlayerDamage(damageIncrease);
	}

	if (rescueRoll <= RescueSuccessRate)
	{
		float percentSuccessIncrease = RescueAllocation * PercentIncreasePerAllocation;
		QuantumController->IncreasePlayerDamage(percentSuccessIncrease);
	}

	SetStartValues();

	QuantumController->ShowAllocationResults();

	RemoveFromParent();

}
