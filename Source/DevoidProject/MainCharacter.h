// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "MainCharacter.generated.h"

UCLASS()
class DEVOIDPROJECT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	// Input Functions
	UFUNCTION()
		void MoveFoward(float Value);
	UFUNCTION()
		void MoveRight(float Value);
	UFUNCTION()
		void ChangeLevel();

		void Jump();

		void StopJump();

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=UIBoolean)
		bool m_bIsVisible = false;
	

	FString LevelChangeName;
private:
	float m_fReach = 200.0f;
};
