// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSCardInfoWidget.h"

void UJSCardInfoWidget::ShowCardInfoWidget_Implementation(const FVector2D CurrentMousePosition)
{

}

void UJSCardInfoWidget::InitCardInfoWidget(const FCardInfoData& InCardInfoData, const float MousePositionX,
	const float MousePositionY)
{
	UE_LOG(LogTemp, Log, TEXT("Init Card"));
	CardInfoData = InCardInfoData;
	ShowCardInfoWidget(FVector2D(MousePositionX, MousePositionY));
}
