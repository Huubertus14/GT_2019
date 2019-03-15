// Fill out your copyright notice in the Description page of Project Settings.

#include "Resource.h"

Resource::Resource()
{
}

Resource::~Resource()
{
}

bool Resource::AddAmount(int Number) {
	Amount += Number;
	//Needs to be server validation;
	return true;
}
bool Resource::RemoveAmount(int Number) {
	Amount -= Number;
	//Needs to be server validation;
	return true;
}

