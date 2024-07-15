// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EnemyBase.h"

#include "GASLearningProj/GASLearningProj.h"

void AEnemyBase::HighlightActor()
{
	//bHighlighted = true;

	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	
}

void AEnemyBase::UnHighlightActor()
{
	//bHighlighted = false;
	GetMesh()->SetRenderCustomDepth(false);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_DEFAULT);

	Weapon->SetRenderCustomDepth(false);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_DEFAULT);
}
