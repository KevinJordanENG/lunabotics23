#pragma once

#include "ctre_motors/phoenix/cci/CCI.h"
#include "ctre_motors/phoenix/platform/Platform.h"
#include <stdint.h>

using namespace ctre::phoenix::platform;

extern "C" {
    CCIEXPORT ctre::phoenix::ErrorCode c_SimCreate(DeviceType type, int id);
    CCIEXPORT ctre::phoenix::ErrorCode c_SimDestroy(DeviceType type, int id);
    CCIEXPORT ctre::phoenix::ErrorCode c_SimDestroyAll();
    CCIEXPORT ctre::phoenix::ErrorCode c_SimSetPhysicsInput(DeviceType type, int id, std::string const &physicsType, double value);
    CCIEXPORT ctre::phoenix::ErrorCode c_SimGetPhysicsValue(DeviceType type, int id, std::string const &physicsType, double &value);
    CCIEXPORT ctre::phoenix::ErrorCode c_SimGetLastError(DeviceType type, int id);
}
