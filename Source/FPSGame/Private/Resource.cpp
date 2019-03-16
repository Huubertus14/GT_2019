// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"

// Sets default values
AResource::AResource()
{
	SetReplicates(true);
	ResetAmount();
}


void AResource::AddAmount(int Number) {
		Amount += Number;
	//Needs to be server validation;
}
void AResource::RemoveAmount(int Number) {
	Amount -= Number;
	//Needs to be server validation;
}

void AResource::ResetAmount() {
	Amount = 0;
}

int AResource::GetAmount() {
	return Amount;
}
