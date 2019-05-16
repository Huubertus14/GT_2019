// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "MeatActor.h"
#include "Arrow.h"
#include "UnrealNetwork.h"


#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green,text)

APlayerCharacter::APlayerCharacter()
{
	for (int i = 0; i < 3; ++i)
	{
		m_r_resources.Add(0);
	}

	// Create a CameraComponent	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	cameraComponent->SetupAttachment(GetCapsuleComponent());
	cameraComponent->RelativeLocation = FVector(0, 0, BaseEyeHeight); // Position the camera
	cameraComponent->bUsePawnControlRotation = true;
  
	//MeshCharacter
	MeshPit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	MeshPit->SetupAttachment(RootComponent);
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
	
	MeshShield = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldMesh"));
	MeshShield->SetupAttachment(MeshPit);
	MeshShield->CastShadow = false;
	MeshShield->AttachTo(MeshPit, TEXT("WeaponLeft"));
	MeshShield->SetVisibility(false);

	MeshDagger = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DaggerMesh"));
	MeshDagger->SetupAttachment(MeshPit);
	MeshDagger->CastShadow = false;
	MeshDagger->AttachTo(MeshPit, TEXT("WeaponRight"));
	MeshDagger->SetVisibility(false);


	//Collision mesh
	HitBoxComponent = CreateDefaultSubobject<USphereComponent>(TEXT("HitComp"));
	HitBoxComponent->SetupAttachment(MeshPit);
	HitBoxComponent->AttachTo(MeshPit, TEXT("WeaponRight"));
	HitBoxComponent->SetSphereRadius(7.f);
	HitBoxComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic"); 


	PrimaryActorTick.bCanEverTick = true;

	//SetReplicateMovement(true);
	SetReplicates(true);
	bReplicates = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	m_lifeCap = 100;
	m_r_life = 50;
	m_maxStamina = 200;
	m_r_currentMaxStamina = 100;
	m_r_currentStamina = m_r_currentMaxStamina;
	bowEquiped = true;
	twoHanderEquiped = false;
	currentWeaponID = 0;
	r_equipedWeapon = 1;
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::ServerPerformMineCast);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::ServerPerformHitCast);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::ServerDrawArrow);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::ServerFire);

	PlayerInputComponent->BindAction("ServerPickupThrow", IE_Released, this, &APlayerCharacter::ServerPickupThrow);

	// WeaponSlots
	PlayerInputComponent->BindAction("WeaponSlot1", IE_Pressed, this, &APlayerCharacter::WeaponSlot1);
	PlayerInputComponent->BindAction("WeaponSlot2", IE_Pressed, this, &APlayerCharacter::WeaponSlot2);
	PlayerInputComponent->BindAction("WeaponSlot3", IE_Pressed, this, &APlayerCharacter::WeaponSlot3);
	PlayerInputComponent->BindAction("WeaponSlot4", IE_Pressed, this, &APlayerCharacter::WeaponSlot4);
	PlayerInputComponent->BindAction("WeaponSlot5", IE_Pressed, this, &APlayerCharacter::WeaponSlot5);
}


// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bowEquiped) 
	{
		if (m_r_isDrawn) 
		{
			if (UpdateBowTension(DeltaTime)) 
			{
				ServerFire();
			}
		}
		else 
		{
			RegainEnergy(DeltaTime);
		}
	}

	UpdateLifeStatus();

	SharePlayerPitch();
}

bool APlayerCharacter::UpdateBowTension(float DeltaTime)
{
	m_r_power += .7f * DeltaTime;
	m_r_currentStamina -= 10.f * DeltaTime;

	if (m_r_currentStamina <= 0) {
		return true;
	}
	else {
		return false;
	}
}

void APlayerCharacter::RegainEnergy(float DeltaTime)
{
	m_r_power = 0.f;
	m_r_currentStamina += 2.5f * DeltaTime;
	if (m_r_currentStamina > m_r_currentMaxStamina)
	{
		m_r_currentStamina = m_r_currentMaxStamina;
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

void APlayerCharacter::SharePlayerPitch()
{
	
	if (!IsLocallyControlled())
	{
		FRotator newRot = cameraComponent->RelativeRotation;
		newRot.Pitch = RemoteViewPitch * 360.0f / 255.0f;

		cameraComponent->SetRelativeRotation(newRot);
	}
}

void APlayerCharacter::UpdateLifeStatus()
{
	if (m_r_life < 0) {
		DestroyPlayer();
	}
}

void APlayerCharacter::HitPlayer(float damage)
{
	if (damage <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't damage negative!\n Use heal instead!"));
		return;
	}
	m_r_life -= damage;

	FString NewString = FString::FromInt(m_r_life);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, NewString);

	if (m_r_life <= 0) {

			UE_LOG(LogTemp, Warning, TEXT("Player Die"));
			DestroyPlayer();
	}
}

void APlayerCharacter::HealPlayer(float heal)
{
	if (heal<= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't heal negative!\n Use damage instead!"));
		return;
	}
	m_r_life += heal;
	if (m_r_life > m_lifeCap) {
		m_r_life = m_lifeCap;
	}

	FString NewString = FString::FromInt(m_r_life);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, NewString);

}

void APlayerCharacter::EnergizePlayer(float amount)
{
	m_r_currentMaxStamina += (amount / 4);
	if (m_r_currentMaxStamina > m_maxStamina) {
		m_r_currentMaxStamina = m_maxStamina;
	}
	m_r_currentStamina += amount;
	if (m_r_currentStamina > m_r_currentMaxStamina) {
		m_r_currentStamina = m_r_currentMaxStamina;
	}

}

float APlayerCharacter::GetCurrentStam()
{
	return m_r_currentStamina;
}

float APlayerCharacter::GetCurrentMaxStam()
{
	return m_r_currentMaxStamina;
}

float APlayerCharacter::GetCurrentLife()
{
	return m_r_life;
}

FText APlayerCharacter::GetResourceZero()
{		
		FString veryCleanString = FString::FromInt(m_r_resources[0]);
		return FText::FromString(veryCleanString);
}

FText APlayerCharacter::GetResourceOne()
{
		FString veryCleanString = FString::FromInt(m_r_resources[1]);
		return FText::FromString(veryCleanString);
}

FText APlayerCharacter::GetResourceTwo()
{
		FString veryCleanString = FString::FromInt(m_r_resources[2]);
		return FText::FromString(veryCleanString);
}

void APlayerCharacter::ServerPickupThrow_Implementation()
{
	//resultRaycast
	m_hitResult = new FHitResult();
	//Startpoint raycast
	FVector StartTrace = cameraComponent->GetComponentLocation();
	//Direction raycast
	FVector ForwardVector = cameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector EndTrace = StartTrace + (ForwardVector * 1000.f);
	//List of items to not collide with.
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);

	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*m_hitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)) {

		//Info of jus cast raycast
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), true, 5.f);
		FString temp = m_hitResult->Location.ToString();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp);

		APickUpItem* tempPickUp = Cast<APickUpItem>(m_hitResult->Actor);

		if (tempPickUp)
		{
			ServerDropWeapon();
			currentWeaponID = tempPickUp->GetWeaponID();
			tempPickUp->Pickup();
		}
	}
}

bool APlayerCharacter::ServerPickupThrow_Validate()
{
	return true;
}

void APlayerCharacter::ServerDropWeapon_Implementation()
{
	//Get current weapon ID

	//Loop through weapon array
	for (int i = 0; i < dropWeapons.Num(); ++i)
	{
		APickUpItem* actualWeapon = dropWeapons[i].GetDefaultObject();

		if (actualWeapon->GetWeaponID() == currentWeaponID)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "Dropped a weapon");

			//Drop weapon
			FVector forwardVector = cameraComponent->GetForwardVector();
			FRotator cameraRotation = cameraComponent->GetComponentRotation();
			FVector cameraPosition = cameraComponent->GetComponentLocation();
			cameraPosition += forwardVector * 100.f;
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			//Spawn new weapon in the world
			APickUpItem* dropedWeapon = GetWorld()->SpawnActor<APickUpItem>(dropWeapons[i], cameraPosition, cameraRotation, spawnParams);

			//Set current weapon

			return;
		}
	}
}

bool APlayerCharacter::ServerDropWeapon_Validate()
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
		ServerLeaveGame();

		UGameplayStatics::OpenLevel(this, FName(TEXT("FirstPersonExampleMap")));
	}
}

void APlayerCharacter::ServerLeaveGame_Implementation()
{
	Destroy();
}

bool APlayerCharacter::ServerLeaveGame_Validate()
{
	return true;
}

void APlayerCharacter::WeaponVisibility()
{
	MeshBow->SetVisibility(false);
	MeshArrow->SetVisibility(false);
	MeshAxe->SetVisibility(false);
	MeshPickaxe->SetVisibility(false);
	MeshSword->SetVisibility(false);
	Mesh2HSword->SetVisibility(false);
	MeshShield->SetVisibility(false);
	MeshDagger->SetVisibility(false);
}

void APlayerCharacter::WeaponSlot1_Implementation()
{
	WeaponVisibility();
	MeshBow->SetVisibility(true);
	MeshArrow->SetVisibility(true);
	bowEquiped = true;
	twoHanderEquiped = false;
	r_equipedWeapon = 1;
}

bool APlayerCharacter::WeaponSlot1_Validate()
{
	return true;
}

void APlayerCharacter::WeaponSlot2_Implementation()
{
	WeaponVisibility();
	MeshAxe->SetVisibility(true);
	bowEquiped = false;
	twoHanderEquiped = false;
	r_equipedWeapon = 2;
}

bool APlayerCharacter::WeaponSlot2_Validate()
{
	return true;
}

void APlayerCharacter::WeaponSlot3_Implementation()
{
	WeaponVisibility();
	MeshPickaxe->SetVisibility(true);
	bowEquiped = false;
	twoHanderEquiped = false;
	r_equipedWeapon = 3;
}

bool APlayerCharacter::WeaponSlot3_Validate()
{
	return true;
}

void APlayerCharacter::WeaponSlot4_Implementation()
{
	WeaponVisibility();
	MeshSword->SetVisibility(true);
	bowEquiped = false;
	twoHanderEquiped = false;
	r_equipedWeapon = 4;
}

bool APlayerCharacter::WeaponSlot4_Validate()
{
	return true;
}

void APlayerCharacter::WeaponSlot5_Implementation()
{
	WeaponVisibility();
	Mesh2HSword->SetVisibility(true);
	bowEquiped = false;
	twoHanderEquiped = true;
	r_equipedWeapon = 5;
}

bool APlayerCharacter::WeaponSlot5_Validate()
{
	return true;
}


void APlayerCharacter::ServerPerformMineCast_Implementation() {

	//resultRaycast
	m_hitResult = new FHitResult();
	//Startpoint raycast
	FVector startTrace = cameraComponent->GetComponentLocation();
	//Direction raycast
	FVector forwardVector = cameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector endTrace = startTrace + (forwardVector * 1000.f);
	//List of items to not collide with.
	FCollisionQueryParams* traceParams = new FCollisionQueryParams;
	traceParams->AddIgnoredActor(this);

	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*m_hitResult, startTrace, endTrace, ECC_Visibility, *traceParams)) {

		//check if it was a ore.
		AOre* hitTemp = Cast<AOre>(m_hitResult->Actor);

		//if it was a ore check how close you are. if to close just add to player else spawn a item.
		if ((hitTemp && r_equipedWeapon == 2) || (hitTemp && r_equipedWeapon == 3)) 
		{
			if (FVector::Dist(hitTemp->GetActorLocation(), GetActorLocation()) > 350.f) 
			{
				hitTemp->OreHitSpawn(m_hitResult->Location);
			}
			else 
			{

				m_r_resources[hitTemp->GetResourceID()] += hitTemp->GetResourceAmount();
				hitTemp->OreEmpty();
			}
		}

		//check if it was a meat item.
		AMeatActor* meattemp = Cast<AMeatActor>(m_hitResult->Actor);

		if (meattemp)
		{
			//Increase life and stamina
			HealPlayer(50);
			EnergizePlayer(20);

			//destroy meat object
			meattemp->EatMeat();
		}
	}

}

bool APlayerCharacter::ServerPerformMineCast_Validate() {
	return true;
}

void APlayerCharacter::ServerFire_Implementation()
{
	if (m_r_isDrawn)
	{
		FVector forwardVector = cameraComponent->GetForwardVector();
		FRotator cameraRot = cameraComponent->GetComponentRotation();
		FVector position = cameraComponent->GetComponentLocation();
		position += forwardVector * 150.f;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		if (m_r_power > 1 && bowEquiped)
		{
			AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(arrowToCreate, position, cameraRot, spawnParams);
			UStaticMeshComponent* meshComp = Cast<UStaticMeshComponent>(newArrow->GetRootComponent());
			if (meshComp) {
				meshComp->AddForce(forwardVector*100000.f*meshComp->GetMass()*m_r_power);
			}
		}
		m_r_isDrawn = false;
	}
}


bool APlayerCharacter::ServerFire_Validate()
{
	return true;
}

void APlayerCharacter::ServerDrawArrow_Implementation()
{
	if (m_r_currentStamina > 20.f && bowEquiped) {
		m_r_isDrawn = true;
	}
}

bool APlayerCharacter::ServerDrawArrow_Validate()
{
	return true;
}

void APlayerCharacter::ServerPerformHitCast_Implementation() {
	
	
	/**resultRaycast*/
	FHitResult* weaponHitResult = new FHitResult();
	//Startpoint raycast
	FVector StartTrace = cameraComponent->GetComponentLocation();
	//Direction raycast
	FVector ForwardVector = cameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector EndTrace = StartTrace + (ForwardVector * 1000.f);
	//List of items to not collide with.
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);
	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*weaponHitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams))
	{
		// Checking if it is PlayerCharacter it hits
		APlayerCharacter* temp = Cast<APlayerCharacter>(weaponHitResult->Actor);
		if (temp) 
		{
			//checking which weapon your holding to give the correct damage
			if(currentWeaponID == 2)
				temp->HitPlayer(axeDamage);
			if (currentWeaponID == 3)
				temp->HitPlayer(pickAxeDamage);
			if (currentWeaponID == 4)
				temp->HitPlayer(swordDamage);
			if (currentWeaponID == 5)
				temp->HitPlayer(sword2HDamage);
		}
	}

}

bool APlayerCharacter::ServerPerformHitCast_Validate() {
	return true;
}
	
void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacter, m_r_life);
	DOREPLIFETIME(APlayerCharacter, m_r_resources);

	DOREPLIFETIME(APlayerCharacter, m_r_currentMaxStamina);
	DOREPLIFETIME(APlayerCharacter, m_r_currentStamina);
	DOREPLIFETIME(APlayerCharacter, m_r_power);
	DOREPLIFETIME(APlayerCharacter, m_r_isDrawn);
}