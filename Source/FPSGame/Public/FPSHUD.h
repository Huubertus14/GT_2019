// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CanvasItem.h"
#include "Engine/Canvas.h"
#include "FPSHUD.generated.h"


class UTexture2D;

//! The HUD of the player
/*!
 *This class hold all the values and function of the player HUD
 *This class will also draw it on the screen of the player
 **/
UCLASS()
class AFPSHUD : public AHUD
{
	GENERATED_BODY()

protected:

	/** Crosshair asset pointer */
	UTexture2D* crosshairTex;

public:

	AFPSHUD();

	/**This method will draw the static parts of the HUD on the players screen */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;
	
	UFUNCTION()
	void SwitchCraftingHud();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Huds", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> playerHUDClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Huds", Meta = (BlueprintProtected = "true"))
		TSubclassOf<class UUserWidget> playerCraftingHudClass;

	UPROPERTY()
		bool mainWidgetWorking;

	UPROPERTY()
		class UUserWidget* currentWidget;
	UPROPERTY()
		class UUserWidget* craftingWidget;

};

