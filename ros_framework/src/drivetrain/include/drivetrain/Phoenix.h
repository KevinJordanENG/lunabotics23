#pragma once

/* If you are linking Phoenix on a platform that is *not* the NI RoboRIO, 
 * define Phoenix_No_WPI before the Phoenix.h include.
 * The Phoenix WPI extensions are only available on roboRIO.
 * This is necessary if compiling on RaspberryPi, Jetson, Linux-Desktop, etc.
 */
#ifndef Phoenix_No_WPI
#define Phoenix_WPI
#endif

#include "drivetrain/phoenix/CANifier.h"
#include "drivetrain/phoenix/ErrorCode.h"
#include "drivetrain/phoenix/paramEnum.h"
#include "drivetrain/phoenix/HsvToRgb.h"
#include "drivetrain/phoenix/LinearInterpolation.h"
#include "drivetrain/phoenix/led/CANdle.h"
#include "drivetrain/phoenix/motion/BufferedTrajectoryPointStream.h"
#include "drivetrain/phoenix/motion/MotionProfileStatus.h"
#include "drivetrain/phoenix/motion/TrajectoryPoint.h"
#include "drivetrain/phoenix/motorcontrol/can/TalonFX.h"
#include "drivetrain/phoenix/motorcontrol/can/TalonSRX.h"
#include "drivetrain/phoenix/motorcontrol/can/VictorSPX.h"
#include "drivetrain/phoenix/motorcontrol/DemandType.h"
#include "drivetrain/phoenix/motorcontrol/Faults.h"
#include "drivetrain/phoenix/motorcontrol/FollowerType.h"
#include "drivetrain/phoenix/motorcontrol/IMotorController.h"
#include "drivetrain/phoenix/motorcontrol/IMotorControllerEnhanced.h"
#include "drivetrain/phoenix/motorcontrol/InvertType.h"
#include "drivetrain/phoenix/motorcontrol/SensorCollection.h"
#include "drivetrain/phoenix/music/Orchestra.h"
#include "drivetrain/phoenix/sensors/CANCoder.h"
#include "drivetrain/phoenix/sensors/PigeonIMU.h"
#include "drivetrain/phoenix/sensors/Pigeon2.h"
#include "drivetrain/phoenix/signals/MovingAverage.h"
#include "drivetrain/phoenix/tasking/Schedulers/ConcurrentScheduler.h"
#include "drivetrain/phoenix/tasking/ILoopable.h"
#include "drivetrain/phoenix/tasking/IProcessable.h"
#include "drivetrain/phoenix/Utilities.h"

#ifdef Phoenix_WPI
#endif

/*
 * In general it is bad-practice to include namespaces in a C++ header, as this 
 * can cause a name conflict with other types in other modules.
 * 
 * However doing so allows users to quickly start developing with the Phoenix class library 
 * with a single include "Phoenix.h", without having to learn the various namespaces.
 * This is particularly useful for aspiring student-programmers who may not understand all of the language features yet.
 * 
 * Those who understand the benefits of namespaces can instead include the core headers (above)
 * or modify this header if proper namespace-scoping is required.
 */
using namespace ctre;
using namespace ctre::phoenix;
using namespace ctre::phoenix::led;
using namespace ctre::phoenix::motion;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::music;
using namespace ctre::phoenix::sensors;
using namespace ctre::phoenix::signals;
using namespace ctre::phoenix::tasking;
using namespace ctre::phoenix::tasking::schedulers;
