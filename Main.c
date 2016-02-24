#pragma config(Sensor, in1,    autonPot,       sensorPotentiometer)
#pragma config(Sensor, dgtl1,  leftDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  rightDriveEncoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl11, shooterEncoder, sensorQuadEncoder)
#pragma config(Motor,  port1,           liftMotor1,    tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           rightFrontMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftFrontMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           shooterMotor4, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           shooterMotor3, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           shooterMotor1, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           shooterMotor2, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           leftBackMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           rightBackMotor, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port10,          liftMotor2,    tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#include "Utils.h"
#include "DriveSystem.h"
#include "Shooter.h"
#include "Lift.h"
#include "Control.h"
//#include "Debug.h"

/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////

void pre_auton()
{
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.

	bStopTasksBetweenModes = false;

	// All activities that occur before the competition starts
	// Example: clearing encoders, setting servo positions, ...
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task autonomous()
{
	startTask(driveSystemTask, kDefaultTaskPriority);
	startTask(shooterTask, kDefaultTaskPriority);
	startTask(liftTask, kDefaultTaskPriority);
	//startTask(debug, kDefaultTaskPriority);

	shooterPID.requestedSpeed = 100;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////

task usercontrol()
{
	startTask(controlTask, kDefaultTaskPriority);

	// BAD HACK. FIX ASAP.
	while (true) {}
}
