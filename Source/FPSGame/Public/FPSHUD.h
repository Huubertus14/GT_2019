// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"


class UTexture2D;

UCLASS()
class AFPSHUD : public AHUD
{
	GENERATED_BODY()

protected:

	/** Crosshair asset pointer */
	UTexture2D* crosshairTex;

	/** Coin asset pointer		*/
	UTexture2D* coinTex;

	/** Stone asset pointer		*/
	UTexture2D* stoneTex;

	/** Wood asset pointer		*/
	UTexture2D* woodTex;

	UFont* hudFont;


public:

	FCanvasTextItem* TileItem2Text;

	AFPSHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void UpdateLife(float currentHP, float maxHp, float hpPercent);
};

