// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/RC_FrontChaosVehicleWheel.h"

URC_FrontChaosVehicleWheel::URC_FrontChaosVehicleWheel()
{
	AxleType = EAxleType::Front;
	/*WheelRadius = 40;
	WheelMass = 1000;*/
	bAffectedByBrake = true;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = true;
	MaxSteerAngle = 45;
}
