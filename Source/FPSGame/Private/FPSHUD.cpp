// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSHUD.h"

#include "Engine/Texture2D.h"
#include "Engine/Font.h"
#include "TextureResource.h"

#include "UObject/ConstructorHelpers.h"


AFPSHUD::AFPSHUD()
{
	// Set the crosshair texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> crosshairTexObj(TEXT("/Game/UI/FirstPersonCrosshair"));
	crosshairTex = crosshairTexObj.Object;
	// Set the coins texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> coinTexObj(TEXT("/Game/UI/coinSP"));
	coinTex = coinTexObj.Object;
	// Set the stone texture
	static ConstructorHelpers::FObjectFinder<UTexture2D> stoneTexObj(TEXT("/Game/UI/stoneSP"));
	stoneTex = stoneTexObj.Object;
	// Set text font
	static ConstructorHelpers::FObjectFinder<UFont> fontObj(TEXT("/Game/UI/HudFont"));
	hudFont = fontObj.Object;
	
}


void AFPSHUD::DrawHUD()
{
	Super::DrawHUD();

	// find center of the Canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const FVector2D sizeCanvas(Canvas->ClipX, Canvas->ClipY);

	//Assign position
	float tempnumberX = 9.f;
	float tempnumberY = 6.f;
	const FVector2D crosshairDrawPosition(  (Center.X),									(Center.Y + 20.0f));
	const FVector2D coinDrawPosition(		(sizeCanvas.X - (sizeCanvas.X / tempnumberX)),				(sizeCanvas.Y / tempnumberY));
	const FVector2D coinTextDrawPosition(	(sizeCanvas.X - (sizeCanvas.X / tempnumberX - 25.f)),		(sizeCanvas.Y / tempnumberY));
	const FVector2D stoneDrawPosition(		(sizeCanvas.X - (sizeCanvas.X / tempnumberX)),				(sizeCanvas.Y / tempnumberY - 20.f));
	const FVector2D stoneTextDrawPosition(	(sizeCanvas.X - (sizeCanvas.X / tempnumberX - 25.f)),		(sizeCanvas.Y / tempnumberY - 20.f));
	const FVector2D woodDrawPosition(		(sizeCanvas.X - (sizeCanvas.X / tempnumberX)),				(sizeCanvas.Y / tempnumberY - 40.f));
	const FVector2D woodTextDrawPosition(	(sizeCanvas.X-(sizeCanvas.X / tempnumberX - 25.f)),			(sizeCanvas.Y / tempnumberY - 40.f));
	const FVector2D healthTextDrawPosition(	(sizeCanvas.X-(sizeCanvas.X / 7)),							(sizeCanvas.Y-(sizeCanvas.Y / 7)));
	// draw texts
	FText temp = FText::FromString("0");
	TileItem2Text = new FCanvasTextItem(coinTextDrawPosition, temp, hudFont, FLinearColor::Black);

	FCanvasTextItem TileItem3Text(stoneTextDrawPosition, temp, hudFont, FLinearColor::Black);

	FCanvasTextItem TileItem4Text(woodTextDrawPosition, temp, hudFont, FLinearColor::Black);

	FText temp4 = FText::FromString("100");
	FCanvasTextItem TileItem5Text(healthTextDrawPosition, temp4, hudFont, FLinearColor::Black);

	// draw  images
	FCanvasTileItem TileItem	( crosshairDrawPosition,	crosshairTex->Resource, FLinearColor::White);
	FCanvasTileItem TileItem2	( coinDrawPosition,	coinTex->Resource,  FVector2D(16.f, 16.f),	FLinearColor::White);
	FCanvasTileItem TileItem3   ( stoneDrawPosition, stoneTex->Resource, FVector2D(16.f, 16.f), FLinearColor::White);

	TileItem.BlendMode  = SE_BLEND_Translucent;
	TileItem2.BlendMode = SE_BLEND_Translucent;
	TileItem3.BlendMode = SE_BLEND_Translucent;

	
	// Tiles for the draw system 
	Canvas->DrawItem( TileItem  );
	Canvas->DrawItem( TileItem2 );
	Canvas->DrawItem( TileItem3 );
	Canvas->DrawItem(*TileItem2Text);
	Canvas->DrawItem(TileItem3Text);
	Canvas->DrawItem(TileItem4Text);
	Canvas->DrawItem(TileItem5Text);
}

void AFPSHUD::BeginPlay() 
{
	Super::BeginPlay();
	
}

void AFPSHUD::UpdateLife(float currentHP, float maxHP, float hpPercent) {

}