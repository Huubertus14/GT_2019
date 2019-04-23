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

	//UE_LOG(LogTemp, Warning, TEXT("Total amount of Resources: %i"), Resources.Num());
	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	CameraComponent->bUsePawnControlRotation = true;
  
	//MeshCharacter
	MeshPit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	MeshPit->SetupAttachment(CameraComponent);
	MeshPit->CastShadow = false;
	
	//MeshWeapons
	MeshBow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowMesh"));
	MeshBow->SetupAttachment(MeshPit);
	MeshBow->CastShadow = false;
	MeshBow->AttachTo(MeshPit, TEXT("WeaponLeft"));
	MeshBow->SetVisibility(true);

	MeshArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	MeshArrow->SetupAttachment(MeshPit);
	MeshArrow->CastShadow = false;
	MeshArrow->AttachTo(MeshPit, TEXT("WeaponRight"));
	MeshArrow->SetVisibility(true);

	MeshAxe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	MeshAxe->SetupAttachment(MeshPit);
	MeshAxe->CastShadow = false;
	MeshAxe->AttachTo(MeshPit, TEXT("WeaponRight"));
	MeshAxe->SetVisibility(false);

	MeshPickaxe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickaxeMesh"));
	MeshPickaxe->SetupAttachment(MeshPit);
	MeshPickaxe->CastShadow = false;
	MeshPickaxe->AttachTo(MeshPit, TEXT("WeaponRight"));
	MeshPickaxe->SetVisibility(false);

	MeshSword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SwordMesh"));
	MeshSword->SetupAttachment(MeshPit);
	MeshSword->CastShadow = false;
	MeshSword->AttachTo(MeshPit, TEXT("WeaponRight"));
	MeshSword->SetVisibility(false);

	Mesh2HSword = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("2HSwordMesh"));
	Mesh2HSword->SetupAttachment(MeshPit);
	Mesh2HSword->CastShadow = false;
	Mesh2HSword->AttachTo(MeshPit, TEXT("WeaponRight"));
	Mesh2HSword->SetVisibility(false);
	
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

	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::RightMouseClick);

	// WeaponSlots
	PlayerInputComponent->BindAction("WeaponSlot1", IE_Pressed, this, &APlayerCharacter::WeaponSlot1);
	PlayerInputComponent->BindAction("WeaponSlot2", IE_Pressed, this, &APlayerCharacter::WeaponSlot2);
	PlayerInputComponent->BindAction("WeaponSlot3", IE_Pressed, this, &APlayerCharacter::WeaponSlot3);
	PlayerInputComponent->BindAction("WeaponSlot4", IE_Pressed, this, &APlayerCharacter::WeaponSlot4);
	PlayerInputComponent->BindAction("WeaponSlot5", IE_Pressed, this, &APlayerCharacter::WeaponSlot5);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	lifeCap = 100;
	life = lifeCap;
	MaxStamina = 200;
	CurrentMaxStamina = 100;
	CurrentStamina = CurrentMaxStamina;
	isBow = true;
	is2H = false;
	currentWeaponID = 0;
}

void APlayerCharacter::DropWeapon_Implementation()
{
	//Get current weapon ID

	//Loop through weapon array
	for (int i = 0; i < dropWeapons.Num(); i++)
	{
		APickUpItem* item = dropWeapons[i].GetDefaultObject();
		if (item->GetID() == currentWeaponID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Dropped a weapon");

			//Drop weapon
			FVector f = CameraComponent->GetForwardVector();
			FRotator camera = CameraComponent->GetComponentRotation();
			FVector pos = CameraComponent->GetComponentLocation();
			pos += f * 100.f;
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			//Spawn new weapon in the world
			APickUpItem* newArrow = GetWorld()->SpawnActor<APickUpItem>(dropWeapons[i], pos, camera, spawnParams);
			
			//Set current weapon

			return;
		}
	}

}

bool APlayerCharacter::DropWeapon_Validate()
{
	return true;
}

void APlayerCharacter::ServerFire_Implementation()
{
	if (isDrawn) {
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
}

bool APlayerCharacter::ServerFire_Validate()
{
	return true;
}

void APlayerCharacter::DrawArrow_Implementation()
{
	if (CurrentStamina > 20.f) {
		isDrawn = true;
	}
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
			power += .75f * DeltaTime;
			CurrentStamina -= 10.f * DeltaTime;
			if (CurrentStamina <= 0) {
				ServerFire();
			}
		}
		else {
			power = 0.f;
			CurrentStamina += 0.5f * DeltaTime;
			if (CurrentStamina > CurrentMaxStamina) {
				CurrentStamina = CurrentMaxStamina;
			}
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

void APlayerCharacter::HitPlayer(float damage)
{
	if (damage <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't damage negative!\n Use heal instead!"));
		return;
	}
	life -= damage;


	if (life <= 0) {

		if (IsLocallyControlled()) // cannot destroy the host
		{
			//UE_LOG(LogTemp, Warning, TEXT("Player Die"));
			DestroyPlayer();
		}

	}
}

void APlayerCharacter::HealPlayer(float heal)
{
	if (heal<= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't heal negative!\n Use damage instead!"));
		return;
	}
	life += heal;

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


float APlayerCharacter::GetCurrentStam()
{
	return CurrentStamina;
}

float APlayerCharacter::GetCurrentMaxStam()
{
	return CurrentMaxStamina;
}

float APlayerCharacter::GetCurrentLife()
{
	return life;
}

FText APlayerCharacter::GetResourceZero()
{
	FString VeryCleanString = FString::SanitizeFloat(Resources[0]->GetAmount());
	return FText::FromString(VeryCleanString);
}

FText APlayerCharacter::GetResourceTwo()
{
	return FText();
}

FText APlayerCharacter::GetResourceThree()
{
	return FText();
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
			HealPlayer(50);

			//destroy meat object
			meattemp->EatMeat();
		}
	}

}

bool APlayerCharacter::PerformMineCast_Validate() {
	return true;
}

void APlayerCharacter::RightMouseClick_Implementation()
{
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

		APickUpItem* tempPickUp = Cast<APickUpItem>(HitResult->Actor);
		if (tempPickUp)
		{
			DropWeapon();
			currentWeaponID = tempPickUp->GetID();
			tempPickUp->Pickup();
		}
	}
}

bool APlayerCharacter::RightMouseClick_Validate()
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

void APlayerCharacter::LeaveGame_Implementation()
{
	Destroy();
}

bool APlayerCharacter::LeaveGame_Validate()
{
	return true;
}

void APlayerCharacter::WeaponSlot1()
{
	MeshBow->SetVisibility(true);
	MeshArrow->SetVisibility(true);
	MeshAxe->SetVisibility(false);
	MeshPickaxe->SetVisibility(false);
	MeshSword->SetVisibility(false);
	Mesh2HSword->SetVisibility(false);
	isBow = true;
	is2H = false;
}
void APlayerCharacter::WeaponSlot2()
{
	MeshBow->SetVisibility(false);
	MeshArrow->SetVisibility(false);
	MeshAxe->SetVisibility(true);
	MeshPickaxe->SetVisibility(false);
	MeshSword->SetVisibility(false);
	Mesh2HSword->SetVisibility(false);
	isBow = false;
	is2H = false;
}
void APlayerCharacter::WeaponSlot3()
{
	MeshBow->SetVisibility(false);
	MeshArrow->SetVisibility(false);
	MeshAxe->SetVisibility(false);
	MeshPickaxe->SetVisibility(true);
	MeshSword->SetVisibility(false);
	Mesh2HSword->SetVisibility(false);
	isBow = false;
	is2H = false;
}
void APlayerCharacter::WeaponSlot4()
{
	MeshBow->SetVisibility(false);
	MeshArrow->SetVisibility(false);
	MeshAxe->SetVisibility(false);
	MeshPickaxe->SetVisibility(false);
	MeshSword->SetVisibility(true);
	Mesh2HSword->SetVisibility(false);
	isBow = false;
	is2H = false;
}
void APlayerCharacter::WeaponSlot5()
{
	MeshBow->SetVisibility(false);
	MeshArrow->SetVisibility(false);
	MeshAxe->SetVisibility(false);
	MeshPickaxe->SetVisibility(false);
	MeshSword->SetVisibility(false);
	Mesh2HSword->SetVisibility(true);
	isBow = false;
	is2H = true;
}

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerCharacter, power);
	DOREPLIFETIME(APlayerCharacter, isDrawn);
}