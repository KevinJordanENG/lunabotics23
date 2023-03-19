#pragma once

/* If you are linking Phoenix on a platform that is *not* the NI RoboRIO, 
 * define Phoenix_No_WPI before the Phoenix.h include.
 * The Phoenix WPI extensions are only available on roboRIO.
 * This is necessary if compiling on RaspberryPi, Jetson, Linux-Desktop, etc.
 */
#ifndef Phoenix_No_WPI
#define Phoenix_WPI
#endif

#include "mining_and_hopper/phoenix/CANifier.h"
#include "mining_and_hopper/phoenix/ErrorCode.h"
#include "mining_and_hopper/phoenix/paramEnum.h"
#include "mining_and_hopper/phoenix/HsvToRgb.h"
#include "mining_and_hopper/phoenix/LinearInterpolation.h"
#include "mining_and_hopper/phoenix/led/CANdle.h"
#include "mining_and_hopper/phoenix/motion/BufferedTrajectoryPointStream.h"
#include "mining_and_hopper/phoenix/motion/MotionProfileStatus.h"
#include "mining_and_hopper/phoenix/motion/TrajectoryPoint.h"
#include "mining_and_hopper/phoenix/motorcontrol/can/TalonFX.h"
#include "mining_and_hopper/phoenix/motorcontrol/can/TalonSRX.h"
#include "mining_and_hopper/phoenix/motorcontrol/can/VictorSPX.h"
#include "mining_and_hopper/phoenix/motorcontrol/DemandType.h"
#include "mining_and_hopper/phoenix/motorcontrol/Faults.h"
#include "mining_and_hopper/phoenix/motorcontrol/FollowerType.h"
#include "mining_and_hopper/phoenix/motorcontrol/IMotorController.h"
#include "mining_and_hopper/phoenix/motorcontrol/IMotorControllerEnhanced.h"
#include "mining_and_hopper/phoenix/motorcontrol/InvertType.h"
#include "mining_and_hopper/phoenix/motorcontrol/SensorCollection.h"
#include "mining_and_hopper/phoenix/music/Orchestra.h"
#include "mining_and_hopper/phoenix/sensors/CANCoder.h"
#include "mining_and_hopper/phoenix/sensors/PigeonIMU.h"
#include "mining_and_hopper/phoenix/sensors/Pigeon2.h"
#include "mining_and_hopper/phoenix/signals/MovingAverage.h"
#include "mining_and_hopper/phoenix/tasking/Schedulers/ConcurrentScheduler.h"
#include "mining_and_hopper/phoenix/tasking/ILoopable.h"
#include "mining_and_hopper/phoenix/tasking/IProcessable.h"
#include "mining_and_hopper/phoenix/Utilities.h"

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
