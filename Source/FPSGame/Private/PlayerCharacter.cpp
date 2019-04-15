// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine.h"
#include "Arrow.h"

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

	//MeshCharacter
	MeshPit = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	MeshPit->SetupAttachment(CameraComponent);
	MeshPit->CastShadow = false;
	//MeshWeapons
	MeshBow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BowMesh"));
	MeshBow->SetupAttachment(MeshPit);
	MeshBow->CastShadow = false;
	MeshBow->AttachTo(MeshPit, TEXT("WeaponLeft"));

	MeshArrow = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
	MeshArrow->SetupAttachment(MeshPit);
	MeshArrow->CastShadow = false;
	MeshArrow->AttachTo(MeshPit, TEXT("WeaponRight"));

	MeshAxe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AxeMesh"));
	MeshAxe->SetupAttachment(MeshPit);
	MeshAxe->CastShadow = false;
	MeshAxe->AttachTo(MeshPit, TEXT("WeaponRight"));

	MeshPickaxe = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PickaxeMesh"));
	MeshPickaxe->SetupAttachment(MeshPit);
	MeshPickaxe->CastShadow = false;
	MeshPickaxe->AttachTo(MeshPit, TEXT("WeaponRight"));
	

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
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Life = 100;
}

void APlayerCharacter::ServerFire_Implementation()
{
	FVector pos = CameraComponent->GetComponentLocation();
	FVector f = GetActorForwardVector();
	FRotator camera = CameraComponent->GetComponentRotation();

	pos.X += f.X * 50;
	pos.Y += f.Y * 50;

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;


	if (spawnTime < 0) {
		AArrow* newArrow = GetWorld()->SpawnActor<AArrow>(AArrow::StaticClass(), pos, camera, spawnParams);
		//newArrow->speed = power;
		
		spawnTime = 1;
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
		hitTemp = Cast<AOre>(HitResult->Actor);
		if (hitTemp) {
			hitTemp->OreHitSpawn(HitResult->Location);
		}
	}

}

bool APlayerCharacter::PerformMineCast_Validate() {
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

