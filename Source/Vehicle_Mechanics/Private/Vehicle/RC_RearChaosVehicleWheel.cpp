// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicle/RC_RearChaosVehicleWheel.h"

URC_RearChaosVehicleWheel::URC_RearChaosVehicleWheel()
{
	AxleType = EAxleType::Rear;
	/*WheelRadius = 40;
	WheelMass = 1000;*/
	bAffectedByBrake = true;
	bAffectedByEngine = true;
	bAffectedByHandbrake = true;
	bAffectedBySteering = false;
	
}
