// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "EnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class GASLEARNINGPROJ_API AEnemyBase : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyBase();
	
	virtual void BeginPlay() override;
	/** Enemy Interface **/
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	/** End of Enemy Interface **/
	UPROPERTY(BlueprintReadOnly, Category="Enemy")
	bool bHighlighted = false;
	
};
