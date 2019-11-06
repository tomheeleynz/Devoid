// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define OUT

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FPSCameraComponent->SetupAttachment(GetCapsuleComponent());
	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Allow the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Get Player View Point
	FVector ViewPointLocation;
	FRotator ViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation
	);

	//UE_LOG(LogTemp, Warning, TEXT("Location: %s Rotation: %s"), *ViewPointLocation.ToString(), *ViewPointRotation.ToString());

	FVector lineTraceEnd = ViewPointLocation + ViewPointRotation.Vector() * m_fReach;

	DrawDebugLine(
		GetWorld(),
		ViewPointLocation,
		lineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		10.0f
	);
	
	/// Set Up Query Parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());


	/// Line Tracing
	FHitResult LineTraceHit;

	GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHit,
		ViewPointLocation,
		lineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = LineTraceHit.GetActor();

	if (ActorHit)
	{
		m_bIsVisible = true;
	}
	else {
		m_bIsVisible = false;
	}
	
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Setting Up Movememnt Axis
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMainCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMainCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("EnterWorld", IE_Released, this, &AMainCharacter::ChangeLevel);
}

void AMainCharacter::MoveFoward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::ChangeLevel()
{

	if (m_bIsVisible == true)
	{
		FString transferLevel = "Env_Level_Denial";
		UGameplayStatics::OpenLevel(GetWorld(), FName(*transferLevel), false);
		UE_LOG(LogTemp, Warning, TEXT("E Clicked"));
	}
}

