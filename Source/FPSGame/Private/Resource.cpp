// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"
#include "Engine.h"
#include "UnrealNetwork.h"

AResource::AResource()
{
	SetReplicates(true);

}


void AResource::BeginPlay()
{
	Super::BeginPlay();
	m_r_amount = 0;
}

void AResource::AddAmount(int Number) {
	m_r_amount += Number;

}
void AResource::RemoveAmount(int Number) {
	m_r_amount -= Number;

}

void AResource::ResetAmount() {
	m_r_amount = 0;
}

int AResource::GetAmount() {
	return m_r_amount;
}

void AResource::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AResource, m_r_amount);

}

