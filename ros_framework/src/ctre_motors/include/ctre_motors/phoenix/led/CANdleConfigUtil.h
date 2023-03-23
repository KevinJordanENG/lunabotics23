#pragma once

#include "ctre_motors/phoenix/led/CANdleConfiguration.h"
#include "ctre_motors/phoenix/CustomParamConfiguration.h"
#include "ctre_motors/phoenix/Utilities.h"

namespace ctre{ namespace phoenix{ namespace led{

/**
 * Util class to help with configuring CANifier
 */
class CANdleConfigUtil : public CustomParamConfigUtil{
	static CANdleConfiguration _default;
public:

	static bool StripTypeDifferent (CANdleConfiguration settings);
	static bool BrightnessScalarDifferent (CANdleConfiguration settings);
	static bool DisableWhenLOSDifferent (CANdleConfiguration settings);
	static bool StatusLedOffWhenActiveDifferent (CANdleConfiguration settings);
	static bool VBatOutputModeDifferent (CANdleConfiguration settings);
	static bool V5EnabledDifferent (CANdleConfiguration settings);
};

} // namespace led
} // namespace phoenix
} // namespace ctre
