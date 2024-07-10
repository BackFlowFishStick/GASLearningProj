// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "GASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNINGPROJ_API AGASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGASPlayerController();
	
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> GasContext;
};
