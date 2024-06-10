// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeDilationSlider.h"

#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UTimeDilationSlider::NativeConstruct()
{
	Super::NativeConstruct();

	if (TimeSlider)
	{
		TimeSlider->OnValueChanged.AddDynamic(this, &UTimeDilationSlider::OnTimeSliderValueChanged);
	}
}

void UTimeDilationSlider::OnTimeSliderValueChanged(float NewValue)
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), NewValue);
	CurrentTimeDilationText->SetText(FText::FromString(FString::SanitizeFloat(NewValue)));
}
