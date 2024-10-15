// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/RC_CarBase.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MaterialParameterCollection.generated.h"
#include "Kismet/KismetMaterialLibrary.h"

ARC_CarBase::ARC_CarBase()
{
	PrimaryActorTick.bCanEverTick = true; // Enable ticking
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 600;
	SpringArm->SetRelativeLocation(FVector(0,0,140));
	SpringArm->SetRelativeRotation(FRotator(-10,0,0));
	SpringArm->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);

	EngineSoundComp = CreateDefaultSubobject<UAudioComponent>("EngineSounds");
	EngineSoundComp->SetupAttachment(GetRootComponent());

}

void ARC_CarBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	
	// Get the vehicle movement component
	UChaosWheeledVehicleMovementComponent* VehicleMovement = Cast<UChaosWheeledVehicleMovementComponent>(GetVehicleMovementComponent());
	if (VehicleMovement)
	{
		// Get the engine rotation speed
		float EngineRotationSpeed = VehicleMovement->GetEngineRotationSpeed();

		EngineSoundComp->SetFloatParameter(TEXT("RPM"),EngineRotationSpeed);
	}
}

void ARC_CarBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Throttle", this, &ARC_CarBase::Throttle);
	PlayerInputComponent->BindAxis("Reverse", this, &ARC_CarBase::Reverse);
	PlayerInputComponent->BindAxis("MoveLR", this, &ARC_CarBase::Steering);
	PlayerInputComponent->BindAxis("LookLR", this, &ARC_CarBase::LookRL);
	PlayerInputComponent->BindAxis("LookUD", this, &ARC_CarBase::LookUpDown);
	
	
	PlayerInputComponent->BindAction("Handbrake", IE_Pressed, this, &ARC_CarBase::HandbrakePressed);
	PlayerInputComponent->BindAction("Handbrake", IE_Released, this, &ARC_CarBase::HandBrakeReleased);

}

void ARC_CarBase::Throttle(float Value)
{
	GetVehicleMovementComponent()->SetThrottleInput(Value);
}

void ARC_CarBase::Reverse(float Value)
{
	GetVehicleMovementComponent()->SetBrakeInput(Value);

}

void ARC_CarBase::Steering(float Value)
{
	GetVehicleMovementComponent()->SetSteeringInput(Value);

}

void ARC_CarBase::HandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
	BrakeLightToggle(true);
}

void ARC_CarBase::HandBrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
	BrakeLightToggle(false);
}

void ARC_CarBase::LookUpDown(float Value)
{
	AddControllerPitchInput(-Value);
}

void ARC_CarBase::LookRL(float Value)
{
	AddControllerYawInput(Value);
}

void ARC_CarBase::BrakeLightToggle(bool bValue)
{
	if(!MPC_Car) { return;}
	if(bValue)
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MPC_Car, FName("EdgeIntensity"),70000);
	}
	else
	{
		UKismetMaterialLibrary::SetScalarParameterValue(GetWorld(), MPC_Car, FName("EdgeIntensity"),1);
	}
}
