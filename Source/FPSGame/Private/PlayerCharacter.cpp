// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "DrawDebugHelpers.h"
#include "MotionControllerComponent.h"
#include "Arrow.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;

	MeshCube = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshCubeCharacter"));
	MeshCube->SetOnlyOwnerSee(true);
	MeshCube->SetupAttachment(CameraComponent);
	MeshCube->bCastDynamicShadow = false;
	MeshCube->CastShadow = false;
	MeshCube->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	MeshCube->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);


	KnifeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Knife_Mesh"));

	AxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Axe_Mesh"));
	// Weapon grip test purpose
	//WeaponGrip = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GripTrick"));
	//WeaponGrip->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	//WeaponGrip->bCastDynamicShadow = false;
	//WeaponGrip->CastShadow = false;
	//WeaponGrip->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(WeaponGrip);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	//Creating the HoldingComponent
	HoldingComponent = CreateDefaultSubobject<USceneComponent>(TEXT("HoldingComponent"));
	HoldingComponent->RelativeLocation.X = 50.0f;
	HoldingComponent->SetupAttachment(FP_MuzzleLocation);

	CurrentItem = NULL;
	bCanMove = true;

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


	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);

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
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::FireArrow);

	PlayerInputComponent->BindAction("PickupThrow", IE_Pressed, this, &APlayerCharacter::OnAction);

	PlayerInputComponent->BindAction("RightClick", IE_Pressed, this, &APlayerCharacter::PerformRightClickCast);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Life = 100;

	//WeaponGrip->AttachToComponent(MeshCube, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("WeaponGripPoint"));

	MeshCube->SetHiddenInGame(false, true);
	currentWeapon = NULL;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	{
		if (!IsLocallyControlled())
		{
			arrowRotation = CameraComponent->RelativeRotation;
			arrowRotation.Pitch = RemoteViewPitch * 360.0f / 255.0f; // convert to right Uint8

			CameraComponent->SetRelativeRotation(arrowRotation);
		}
		if (isDrawn) {
			power += .5f;
		}
		else {
			power = 0;
		}
		spawnTime--;
	}
}

void APlayerCharacter::ServerFire_Implementation()
{
	FVector pos = GetActorLocation();
	FVector f = GetActorForwardVector();
	FRotator camera = CameraComponent->GetComponentRotation();

	pos.X += f.X * 100;
	pos.Y += f.Y * 100;
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;


	if (spawnTime < 0) {
		AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), pos, camera, spawnParams);
		//newArrow->speed = power;
		spawnTime = 60;
		power = 0;
	}
	isDrawn = false;
}


void APlayerCharacter::LeaveGame_Implementation()
{
	Destroy();
}
bool APlayerCharacter::LeaveGame_Validate()
{
	return true;
}

bool APlayerCharacter::ServerFire_Validate()
{
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
	FVector StartTrace = GetActorLocation();
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
		hitTemp = Cast<AOre>(HitResult->Actor);
		if (hitTemp) {
			hitTemp->OreHitSpawn(HitResult->Location);
		}
	}

}

bool APlayerCharacter::PerformMineCast_Validate() {
	return true;
}

void APlayerCharacter::PerformRightClickCast_Implementation()
{
	//resultRaycast
	HitResult = new FHitResult();
	//Startpoint raycast
	FVector StartTrace = GetActorLocation();
	//Direction raycast
	FVector ForwardVector = CameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector EndTrace = StartTrace + (ForwardVector * 1000.f);
	//List of items to not collide with.
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);

	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)) {

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0, 255, 0), true, 5.f);
		FString temp = HitResult->Location.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp);

		pickUp = Cast<APickUpThrow>(HitResult->Actor);
		if (pickUp)
		{ 
			APickUpThrow* temp = currentWeapon;
			
			//TrowItem = currentWeapon;
			if (pickUp->GetID() == 1)
			{
				UE_LOG(LogTemp, Warning, TEXT("Weapon 1 selected"));
				
				//Drop current weapon
				//currentweapos
				
			}
			if (pickUp->GetID() == 2)
			{
				UE_LOG(LogTemp, Warning, TEXT("Weapon 2 selected"));
			}
			ServerDropWeapon();
			pickUp->Pickup();
		}
	}
}

bool  APlayerCharacter::PerformRightClickCast_Validate()
{
	return true;
}

void APlayerCharacter::ServerDropWeapon_Implementation()
{
	FVector pos = GetActorLocation();
	FVector f = GetActorForwardVector();
	FRotator camera = CameraComponent->GetComponentRotation();

	pos.X += f.X * 100;
	pos.Y += f.Y * 100;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;

	APickUpThrow* newitem = GetWorld()->SpawnActor<APickUpThrow>(TrowItem, pos, camera, spawnParams);
}

bool APlayerCharacter::ServerDropWeapon_Validate()
{
	return true;
}

void APlayerCharacter::DrawArrow()
{
	isDrawn = true;
}

void APlayerCharacter::FireArrow()
{
	ServerFire();
}

void APlayerCharacter::OnAction()
{
	if (CurrentItem)
	{
		ToggleItemPickup();
	}
}

void APlayerCharacter::ToggleItemPickup()
{
	if (CurrentItem)
	{
		bHoldingItem = !bHoldingItem;
		CurrentItem->Pickup();

		if (!bHoldingItem)
		{
			CurrentItem = NULL;
		}
	}
}
