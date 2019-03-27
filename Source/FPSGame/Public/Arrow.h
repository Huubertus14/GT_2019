// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"


UCLASS()
class FPSGAME_API AArrow : public AActor
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* arrowMesh;



public:
	// Sets default values for this actor's properties
	AArrow();
	float forward;
	float speed;
	float gravity;
	FVector location;
	int lifeSpan;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerMovement(FVector _pos, FRotator _rot);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* mesh;

	FORCEINLINE class UStaticMeshComponent* GetArrowMesh() const { return arrowMesh; }

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit);

};
