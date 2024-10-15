// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TGBasePawn.generated.h"

UCLASS()
class VEHICLE_MECHANICS_API ATGBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATGBasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY()
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY()
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY()
	UStaticMeshComponent* TurretMesh;

	UPROPERTY()
	class USceneComponent* ProjectileSpawnPoint;

	
	
};
