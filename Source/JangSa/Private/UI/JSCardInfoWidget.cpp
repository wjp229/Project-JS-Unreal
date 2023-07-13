// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSCardInfoWidget.h"

void UJSCardInfoWidget::ShowCardInfoWidget_Implementation()
{

}

void UJSCardInfoWidget::InitCardInfoWidget(const FCardInfoData& InCardInfoData)
{
	CardInfoData = InCardInfoData;
	ShowCardInfoWidget();
}