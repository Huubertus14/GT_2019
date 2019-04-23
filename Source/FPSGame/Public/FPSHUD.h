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

	UFont* hudFont;


public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PlayerHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;

	FCanvasTextItem* TileItem2Text;

	AFPSHUD();

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

};

