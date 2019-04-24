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
// Sets default values
APlayerCharacter::APlayerCharacter()
{
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
	//HitBoxComponent->CastShadow = false;
	HitBoxComponent->AttachTo(MeshPit, TEXT("WeaponRight"));
	HitBoxComponent->SetSphereRadius(7.f);
	//HitBoxComponent->SetSimulatePhysics(true);
	//HitBoxComponent->SetNotifyRigidBodyCollision(true);
	HitBoxComponent->BodyInstance.SetCollisionProfileName("BlockAllDynamic"); //BlockAllDynamic//OverlapAll



	/*HitBoxDetection = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	HitBoxDetection->SetupAttachment(MeshPit);
	HitBoxDetection->AttachTo(MeshPit, TEXT("WeaponRight"));
	HitBoxDetection->bDynamicObstacle = true;
	HitBoxDetection->BodyInstance.SetCollisionProfileName("MyCollisionProfile");
	HitBoxDetection->SetNotifyRigidBodyCollision(true);
	
	FScriptDelegate DelegateBegin;
	DelegateBegin.BindUFunction(this, "OnTestOverlapBegin");
	HitBoxDetection->OnComponentBeginOverlap.Add(DelegateBegin);
	FScriptDelegate DelegateEnd;
	DelegateEnd.BindUFunction(this, "OnTestOverlapEnd");
	HitBoxDetection->OnComponentEndOverlap.Add(DelegateEnd);*/

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
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::PerformHitCast);

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

void APlayerCharacter::EnergizePlayer(float amount)
{
	CurrentMaxStamina += (amount / 4);
	if (CurrentMaxStamina > MaxStamina) {
		CurrentMaxStamina = MaxStamina;
	}
	CurrentStamina += amount;
	if (CurrentStamina > CurrentMaxStamina) {
		CurrentStamina = CurrentMaxStamina;
	}

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Resources.Init(3, 0);
	lifeCap = 100;
	life = 50;
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
		pos += f * 150.f;
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Instigator;

		if (power > 1&& isBow)
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
			power += .7f * DeltaTime;
			CurrentStamina -= 10.f * DeltaTime;
			if (CurrentStamina <= 0) {
				ServerFire();
			}
		}
		else {
			power = 0.f;
			CurrentStamina += 2.5f * DeltaTime;
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

	FString NewString = FString::FromInt(life);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, NewString);

	if (life <= 0) {

			//UE_LOG(LogTemp, Warning, TEXT("Player Die"));
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
	life += heal;
	if (life > lifeCap) {
		life = lifeCap;
	}

	FString NewString = FString::FromInt(life);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, NewString);

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
{		FString VeryCleanString = FString::FromInt(0);
		return FText::FromString(VeryCleanString);
}

FText APlayerCharacter::GetResourceOne()
{
		FString VeryCleanString = FString::FromInt(0);
		return FText::FromString(VeryCleanString);
}

FText APlayerCharacter::GetResourceTwo()
{
		FString VeryCleanString = FString::FromInt(0);
		return FText::FromString(VeryCleanString);
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
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, temp);

		//check if it was a ore.
		AOre* hitTemp = Cast<AOre>(HitResult->Actor);

		if (hitTemp) {
			if (FVector::Dist(hitTemp->GetActorLocation(), GetActorLocation()) > 350.f) {
				hitTemp->OreHitSpawn(HitResult->Location);
			}
			else {

				Resources[hitTemp->resourceID]+= hitTemp->resourceAmount;
				hitTemp->OreEmpty();
			}
		}

		AMeatActor* meattemp = Cast<AMeatActor>(HitResult->Actor);

		if (meattemp)//Check if the raycasted thing is meat
		{
			//Debug tool
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "YAY VLEES!");

			//Increase life and staminarr
			HealPlayer(50);
			EnergizePlayer(20);

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
	isBow = true;
	is2H = false;
}

void APlayerCharacter::WeaponSlot2_Implementation()
{
	WeaponVisibility();
	MeshAxe->SetVisibility(true);
	isBow = false;
	is2H = false;
}
void APlayerCharacter::WeaponSlot3_Implementation()
{
	WeaponVisibility();
	MeshPickaxe->SetVisibility(true);
	isBow = false;
	is2H = false;
}

void APlayerCharacter::WeaponSlot4_Implementation()
{
	WeaponVisibility();
	MeshSword->SetVisibility(true);
	Mesh2HSword->SetVisibility(false);
	isBow = false;
	is2H = false;
}

void APlayerCharacter::WeaponSlot5_Implementation()
{
	WeaponVisibility();
	Mesh2HSword->SetVisibility(true);
	isBow = false;
	is2H = true;
}

bool APlayerCharacter::WeaponSlot1_Validate()
{
	return true;
}
bool APlayerCharacter::WeaponSlot2_Validate()
{
	return true;
}
bool APlayerCharacter::WeaponSlot3_Validate()
{
	return true;
}
bool APlayerCharacter::WeaponSlot4_Validate()
{
	return true;
}
bool APlayerCharacter::WeaponSlot5_Validate()
{
	return true;
}

void APlayerCharacter::PerformHitCast_Implementation() {
	
	
	//resultRaycast
	FHitResult* weaponHitResult = new FHitResult();
	//Startpoint raycast
	FVector StartTrace = CameraComponent->GetComponentLocation();
	//Direction raycast
	FVector ForwardVector = CameraComponent->GetForwardVector();
	//Endpoint raycast
	FVector EndTrace = StartTrace + (ForwardVector * 3000.f);
	//List of items to not collide with.
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams;
	TraceParams->AddIgnoredActor(this);
	//Attempt raycast
	if (GetWorld()->LineTraceSingleByChannel(*weaponHitResult, StartTrace, EndTrace, ECC_Visibility, *TraceParams)) {
		APlayerCharacter* temp = Cast<APlayerCharacter>(weaponHitResult->Actor);

		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0,255, 0), true, 5.f);
		
			if (temp) 
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("You Hit: %s"), "100"));
				temp->HitPlayer(100);
			}
	}

}

bool APlayerCharacter::PerformHitCast_Validate() {
	return true;
}

	
	

void APlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const {

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APlayerCharacter, life);
	DOREPLIFETIME(APlayerCharacter, Resources);
	
	DOREPLIFETIME(APlayerCharacter, hudCountDown);
	DOREPLIFETIME(APlayerCharacter, CurrentMaxStamina);
	DOREPLIFETIME(APlayerCharacter, CurrentStamina);
	DOREPLIFETIME(APlayerCharacter, power);
	DOREPLIFETIME(APlayerCharacter, isDrawn);
}