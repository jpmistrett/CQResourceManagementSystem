#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuantumPlayerController.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "ResourceManagement.generated.h"

UCLASS()
class MOON_API UResourceManagement : public UUserWidget
{
	GENERATED_BODY()

	UResourceManagement(const FObjectInitializer& ObjectInitializer);

	virtual bool Initialize();

public:

	UFUNCTION(BlueprintCallable)
	void SetStartValues();

	UFUNCTION(BlueprintCallable)
	void UpdateResourcePool(int value);

	UFUNCTION(BlueprintCallable)
	void UpdateRepairAllocation(int value);

	UFUNCTION(BlueprintCallable)
	void UpdateScavengeAllocation(int value);

	UFUNCTION(BlueprintCallable)
	void UpdateRescueAllocation(int value);

	UFUNCTION(BlueprintCallable)
	void CompleteResourceManagement();

	float BaseShieldValue;

private:

	void SetShieldRepairValue();

	void UpdateResourcesVisual();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ResourceManagementGlobals)
	float MaxShieldValue = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ResourceManagementGlobals)
	float MaxResourcePoolValue = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ResourceManagementGlobals)
	float ShieldRepairsPerAllocation = 10;

	UPROPERTY(BlueprintReadWrite)
	float CurrentResourcePool = 10.0f;

	UPROPERTY(BlueprintReadOnly)
	float CurrentShieldValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScavengeValues)
	float ScavengeSuccessRate = 45.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScavengeValues)
	float WeaponDamageIncreasePerAllocation = 0.4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RescueValues)
	float RescueSuccessRate = 65.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = RescueValues)
	float PercentIncreasePerAllocation = 2.0f;

	UPROPERTY(BlueprintReadWrite, Category = ResourceManagement)
	float RepairAllocation = 0;

	UPROPERTY(BlueprintReadWrite, Category = ResourceManagement)
	float ScavengeAllocation = 0;

	UPROPERTY(BlueprintReadWrite, Category = ResourceManagement)
	float RescueAllocation = 0;
	
	AQuantumPlayerController* QuantumController;

	//essentially require these UMG elements

	UPROPERTY(meta = (BindWidget))
	UButton* RepairMinus;

	UPROPERTY(meta = (BindWidget))
	UButton* RepairAdd;

	UPROPERTY(meta = (BindWidget))
	UButton* ScavengeMinus;

	UPROPERTY(meta = (BindWidget))
	UButton* ScavengeAdd;

	UPROPERTY(meta = (BindWidget))
	UButton* RescueMinus;

	UPROPERTY(meta = (BindWidget))
	UButton* RescueAdd;

	UPROPERTY(meta = (BindWidget))
	UButton* CompleteManagement;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ResourcesVisual;
};
