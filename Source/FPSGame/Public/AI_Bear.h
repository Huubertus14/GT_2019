// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AI_Bear.generated.h"

UCLASS()
class FPSGAME_API AAI_Bear : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAI_Bear();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent*  MeshComp;

	int currentState;
	float life;
	FVector location;
	float speed;
	float damage;
	double tOut;

	typedef enum {
		BE_WALK,
		BE_RUN,
		BE_ATTACK,
		BE_DIE
	} bearStates;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeState(int nextState, float TO);
	void Thinking();
	void Walk();
	void Run();
	void Attack();
	void Die();


	double CurrentTime();
	float GetCurrentTime();
	bool TimeOut();
};
