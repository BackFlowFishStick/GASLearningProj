// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

void AEnemyBase::HighlightActor()
{
	bHighlighted = true;
}

void AEnemyBase::UnHighlightActor()
{
	bHighlighted = false;
}
