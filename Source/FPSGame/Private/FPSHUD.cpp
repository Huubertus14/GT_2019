// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSHUD.h"

#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "TextureResource.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


AFPSHUD::AFPSHUD()
{
	//! Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> crosshairTexObj(TEXT("/Game/UI/FirstPersonCrosshair"));
	crosshairTex = crosshairTexObj.Object;
}


void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	//! Find center of the Canvas
	const FVector2D center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	//! Draw static images
	FCanvasTileItem tileItem(center, crosshairTex->Resource, FLinearColor::White);
	
	//! Make them just their image with no background
	tileItem.BlendMode  = SE_BLEND_Translucent;
	
	//! Tiles for the draw system 
	Canvas->DrawItem(tileItem);
}

void AFPSHUD::BeginPlay() 
{
	Super::BeginPlay();	
	//! Assign the correct hud in the future there could be more huds such as inventory
	if (playerHUDClass != nullptr) {
		
		//assign non static part of the hud
		currentWidget = CreateWidget<UUserWidget>(GetWorld(), playerHUDClass);
		craftingWidget = CreateWidget<UUserWidget>(GetWorld(), playerCraftingHudClass);
		
		if (currentWidget != nullptr) {
			currentWidget->AddToViewport();
			mainWidgetWorking = true;
		}

	}
}

void AFPSHUD::SwitchCraftingHud() {

	if (mainWidgetWorking) {
		craftingWidget->AddToViewport();
		currentWidget->RemoveFromViewport();
		mainWidgetWorking = false;
	}
	else {
		currentWidget->AddToViewport();
		craftingWidget->RemoveFromViewport();
		mainWidgetWorking = true;
	}

}

