// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeDilationSlider.generated.h"

class UTextBlock;
class USlider;
/**
 * 
 */
UCLASS()
class SBSP_API UTimeDilationSlider : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	USlider* TimeSlider;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentTimeDilationText;

protected:
	virtual void NativeConstruct() override;
	UFUNCTION()
	void OnTimeSliderValueChanged(float NewValue);
	
	
};
