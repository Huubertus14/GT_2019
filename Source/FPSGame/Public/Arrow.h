// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Arrow.generated.h"
//!The class of the arrow
/*!
 *This holds all the info of a arrow
 *Like damage, rotation etc
 */
UCLASS()
class FPSGAME_API AArrow : public AActor
{
	GENERATED_BODY()

public:
	AArrow();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** How much damage an arrow will do on collision */
	UPROPERTY(EditAnywhere, Category = "Projectile Damage")
		int arrowDamage;

	UPROPERTY(EditAnywhere, Category = "Projectile Mesh")
		UStaticMeshComponent* meshComponent;

	/**This mehtod is called when the arrow hits something */
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& hit);

private:
	float m_lifeSpan;

};
