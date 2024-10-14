// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widget/GASUserWidget.h"

void UGASUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;

	WidgetControllerSet();
}
