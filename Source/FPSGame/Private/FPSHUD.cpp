// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSHUD.h"

#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "TextureResource.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"


AFPSHUD::AFPSHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> crosshairTexObj(TEXT("/Game/UI/FirstPersonCrosshair"));
	crosshairTex = crosshairTexObj.Object;
}


void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

	const FVector2D crosshairDrawPosition((Center.X), (Center.Y));

	// draw static images
	FCanvasTileItem TileItem(crosshairDrawPosition, crosshairTex->Resource, FLinearColor::White);

	TileItem.BlendMode  = SE_BLEND_Translucent;
	
	// Tiles for the draw system 
	Canvas->DrawItem(TileItem);
}

void AFPSHUD::BeginPlay() 
{
	Super::BeginPlay();	
	//assign the correct hud
	if (PlayerHUDClass != nullptr) {
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);

		if (CurrentWidget != nullptr) {
			CurrentWidget->AddToViewport();
		}
	}
}
