// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Drive.h"

Drive::Drive(SwerveChassis* swerveChassis, frc::XboxController* controller) :
	m_swerveChassis(swerveChassis), joystick(controller) {
	// Use addRequirements() here to declare subsystem dependencies.
	AddRequirements(m_swerveChassis);
}

// Called when the command is initially scheduled.
void Drive::Initialize() {}

// Called repeatedly when this Command is scheduled to run
void Drive::Execute() {

	if (joystick->GetRightBumper()) {
		kMaxSpeed = 2;
		kMaxAngularSpeed = 3.5;
	} else {
		kMaxSpeed = 5.0;
		kMaxAngularSpeed = 9.0;
	}

	units::meters_per_second_t xInput{ Utils::ApplyAxisFilter(-joystick->GetLeftY()) * kMaxSpeed };
	units::meters_per_second_t yInput{ Utils::ApplyAxisFilter(-joystick->GetLeftX()) * kMaxSpeed };
	units::radians_per_second_t rInput{ Utils::ApplyAxisFilter(-joystick->GetRightX()) * kMaxAngularSpeed };

	frc::ChassisSpeeds chassisSpeeds = frc::ChassisSpeeds::Discretize(frc::ChassisSpeeds::FromFieldRelativeSpeeds(
		xLimiter.Calculate(xInput),
		yLimiter.Calculate(yInput),
		rLimiter.Calculate(rInput),
		m_swerveChassis->getOdometry().Rotation()), 0.2_s);

	m_swerveChassis->setSpeed(chassisSpeeds);
}

// Called once the command ends or is interrupted.
void Drive::End(bool interrupted) {}

// Returns true when the command should end.
bool Drive::IsFinished() {
	return false;
}
