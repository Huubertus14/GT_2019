// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Bear_Controller.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"



void AAI_Bear_Controller::BeginPlay() 
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATargetPoint::StaticClass(), waypoints);
	GoToRandomWaypoint();

}

ATargetPoint* AAI_Bear_Controller::GetRandomWaypoint()
{
	auto index = FMath::RandRange(0, waypoints.Num() - 1);
	UE_LOG(LogTemp, Warning, TEXT("GETTING WAYPOINTS"));
	return Cast<ATargetPoint>(waypoints[index]);
}

void AAI_Bear_Controller::GoToRandomWaypoint()
{
	UE_LOG(LogTemp, Warning, TEXT("IM GOING TO MOVE"));
	MoveToActor(GetRandomWaypoint());
}
