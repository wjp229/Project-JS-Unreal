// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/JSEventWidget.h"
#include "Data/JSEventData.h"
#include "Event/JSEventAction.h"

void UJSEventWidget::InitEventInfoWidget_Implementation(UJSEventData* InEventData)
{
	EventData = InEventData;
}

void UJSEventWidget::ActivateEventAction(int32 InButtonNum)
{
	if(nullptr != EventData || nullptr != EventData->EventActions[InButtonNum])
	{
		UJSEventAction* Action = NewObject<UJSEventAction>(this, EventData->EventActions[InButtonNum]);
		Action->ActivateEvent();
	}
}
