// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"


UCLASS()
class FPSGAME_API AArrow : public AActor
{
	GENERATED_BODY()

public:
	AArrow();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, Category = "Projectile Damage")
		int arrowDamage;

	UPROPERTY(EditAnywhere, Category = "Projectile Mesh")
		UStaticMeshComponent* meshComponent;

	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit);

private:
	float m_lifeSpan;

};
