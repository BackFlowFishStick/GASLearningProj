// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GASPlayerState.h"

#include "AbilitySystem/GASAttributeSet.h"
#include "AbilitySystem/GASComponentBase.h"

AGASPlayerState::AGASPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UGASComponentBase>("GASComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGASAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
