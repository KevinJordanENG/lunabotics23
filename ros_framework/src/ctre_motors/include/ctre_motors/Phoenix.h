#pragma once

/* If you are linking Phoenix on a platform that is *not* the NI RoboRIO, 
 * define Phoenix_No_WPI before the Phoenix.h include.
 * The Phoenix WPI extensions are only available on roboRIO.
 * This is necessary if compiling on RaspberryPi, Jetson, Linux-Desktop, etc.
 */
#ifndef Phoenix_No_WPI
#define Phoenix_WPI
#endif

#include "ctre_motors/phoenix/CANifier.h"
#include "ctre_motors/phoenix/ErrorCode.h"
#include "ctre_motors/phoenix/paramEnum.h"
#include "ctre_motors/phoenix/HsvToRgb.h"
#include "ctre_motors/phoenix/LinearInterpolation.h"
#include "ctre_motors/phoenix/led/CANdle.h"
#include "ctre_motors/phoenix/motion/BufferedTrajectoryPointStream.h"
#include "ctre_motors/phoenix/motion/MotionProfileStatus.h"
#include "ctre_motors/phoenix/motion/TrajectoryPoint.h"
#include "ctre_motors/phoenix/motorcontrol/can/TalonFX.h"
#include "ctre_motors/phoenix/motorcontrol/can/TalonSRX.h"
#include "ctre_motors/phoenix/motorcontrol/can/VictorSPX.h"
#include "ctre_motors/phoenix/motorcontrol/DemandType.h"
#include "ctre_motors/phoenix/motorcontrol/Faults.h"
#include "ctre_motors/phoenix/motorcontrol/FollowerType.h"
#include "ctre_motors/phoenix/motorcontrol/IMotorController.h"
#include "ctre_motors/phoenix/motorcontrol/IMotorControllerEnhanced.h"
#include "ctre_motors/phoenix/motorcontrol/InvertType.h"
#include "ctre_motors/phoenix/motorcontrol/SensorCollection.h"
#include "ctre_motors/phoenix/music/Orchestra.h"
#include "ctre_motors/phoenix/sensors/CANCoder.h"
#include "ctre_motors/phoenix/sensors/PigeonIMU.h"
#include "ctre_motors/phoenix/sensors/Pigeon2.h"
#include "ctre_motors/phoenix/signals/MovingAverage.h"
#include "ctre_motors/phoenix/tasking/Schedulers/ConcurrentScheduler.h"
#include "ctre_motors/phoenix/tasking/ILoopable.h"
#include "ctre_motors/phoenix/tasking/IProcessable.h"
#include "ctre_motors/phoenix/Utilities.h"

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
