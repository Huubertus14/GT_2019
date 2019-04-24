// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"
#include "Engine.h"
#include "UnrealNetwork.h"

// Sets default values
AResource::AResource()
{
	SetReplicates(true);

}


void AResource::AddAmount(int Number) {
	Amount += Number;
	//Needs to be server validated.
}
void AResource::RemoveAmount(int Number) {
	Amount -= Number;
	//Needs to be server validated.
}

void AResource::ResetAmount() {
	Amount = 0;
	//Needs to be server validated.
}

int AResource::GetAmount() {
	return Amount;
	//Needs to be server validated.
}

void AResource::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AResource, Amount);

}

