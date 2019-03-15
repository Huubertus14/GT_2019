// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FPSGAME_API Resource
{

public:
	
	Resource();
	~Resource();

	bool AddAmount(int Number);

	bool RemoveAmount(int Number);

private:
	int Amount;
};
