// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "MeatActor.h"
#include "Arrow.h"
#include "UnrealNetwork.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)
// Sets default values
APlayerCharacter::APlayerCharacter()
{
	//Finds the resource bp.
	static ConstructorHelpers::FClassFinder<AResource> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Resource"));
	toCreate = PlayerPawnClassFinder.Class;

	for (int i = 0; i < 3; i++)
	{
		//creates 3 resources for this player.
		if (Spawn()) {
			//UE_LOG(LogTemp, Warning, TEXT("Made a Resource"));
		}
	}

	//Adds a small amount to resource 0
	if (Resources.Num() > 0) {
		Resources[0]->AddAmount(10);
		//UE_LOG(LogTemp, Warning, TEXT("Total amount of cash: %i"), Resources[0]->GetAmount());
	}

	//UE_LOG(LogTemp, Warning, TEXT("Total amount of Resources: %i"), Resources.Num());
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SetReplicateMovement(true);
	SetReplicates(true);
	bReplicates = true;


}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::PerformMineCast);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::DrawArrow);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::ServerFire);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	life = 100;
}

void APlayerCharacter::ServerFire_Implementation()
{
		FVector f = CameraComponent->GetForwardVector();
		FRotator camera = CameraComponent->GetComponentRotation();
		FVector pos = CameraComponent->GetComponentLocation();
		pos += f * 100.f;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		if (power > 1)
		{
			AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(arrowToCreate, pos, camera, spawnParams);
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(newArrow->GetRootComponent());
			if (meshComp) {
				meshComp->AddForce(f*100000.f*meshComp->GetMass()*power);
			}
		}
		isDrawn = false;
}


bool APlayerCharacter::ServerFire_Validate()
{
	return true;
}



void APlayerCharacter::DrawArrow_Implementation()
{
	isDrawn = true;
}

bool APlayerCharacter::DrawArrow_Validate()
{
	return true;
}



// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
		if (isDrawn) {
			power += .05f;
		}
		else {
			power = 0.f;
		}

		if (!IsLocallyControlled()) {
			FRotator newRot = CameraComponent->RelativeRotation;
			newRot.Pitch = RemoteViewPitch * 360.0f / 255.0f;

			CameraComponent->SetRelativeRotation(newRot);
		}

}

void APlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in horizontal direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void APlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in horizontal direction
		AddMovementInput(GetActorRightVector(), Value);

	}
}

//Spawns the 3 resources a player can stack.
bool APlayerCharacter::Spawn() {
	if (toCreate) {
		UWorld* world = GetWorld();
		if (world) {
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;

			FRotator rotator = FRotator(0, 0, 0);
			FVector spawnLocation = FVector(0, 0, 0);
			Resources.Emplace(world->SpawnActor<AResource>(toCreate, spawnLocation, rotator, spawnParams));
			return true;
		}
	}
	return false;
}

void APlayerCharacter::PerformMineCast_Implementation() {

	//resultRaycast
	HitResult = new FHitResult();
	//Startpoint raycast
	FVector StartTrace = CameraComponent->GetComponentLocation();
	//Direction raycast
	FVector ForwardVector = CameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector EndTrace = StartTrace + (ForwardVector * 1000.f);
	//List of items to not collide with.
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);

	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)) {

		//Info of jus cast raycast
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true, 5.f);
		FString temp = HitResult->Location.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp);

		//check if it was a ore.
		AOre* hitTemp = Cast<AOre>(HitResult->Actor);

		if (hitTemp) {
			hitTemp->OreHitSpawn(HitResult->Location);
		}

		AMeatActor* meattemp = Cast<AMeatActor>(HitResult->Actor);

		if (meattemp)//Check if the raycasted thing is meat
		{
			//Debug tool
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "YAY VLEES!");

			//Increase life and stamina
			life += 50;

			//destroy meat object
			meattemp->EatMeat();
		}
	}

}

bool APlayerCharacter::PerformMineCast_Validate() {
	return true;
}

void APlayerCharacter::DestroyPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Player left"));

	if (GetNetMode() != ENetMode::NM_ListenServer)
	{
		UWorld* TheWorld = GetWorld();
		FString CurrentLevel = TheWorld->GetMapName();

		if (CurrentLevel == "Map2") // player is in a session
		{
			//Change to the main menu
			UGameplayStatics::OpenLevel(GetWorld(), "FirstPersonExampleMap");
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("WTF... Which lvl are you playing"));
		}
		//Destroy();
		LeaveGame();

		UGameplayStatics::OpenLevel(this, FName(TEXT("FirstPersonExampleMap")));
	}
}

void APlayerCharacter::LeaveGame_Implementation()
{
	Destroy();
}

bool APlayerCharacter::LeaveGame_Validate()
{
	return true;
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, power);
	DOREPLIFETIME(APlayerCharacter, isDrawn);
}