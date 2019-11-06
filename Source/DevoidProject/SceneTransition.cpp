// Fill out your copyright notice in the Description page of Project Settings.


#include "SceneTransition.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"


// Sets default values for this component's properties
USceneTransition::USceneTransition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


FString USceneTransition::GetLevelName()
{
	return m_strLevelName;
}


// Called when the game starts
void USceneTransition::BeginPlay()
{
	Super::BeginPlay();

	// UE_LOG(LogTemp, Warning, TEXT("Component Loaded %s in level %s"), *name, *levelName);
	
}


// Called every frame
void USceneTransition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

