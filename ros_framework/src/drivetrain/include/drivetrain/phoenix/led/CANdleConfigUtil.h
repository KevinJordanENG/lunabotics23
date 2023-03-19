#pragma once

#include "drivetrain/phoenix/led/CANdleConfiguration.h"
#include "drivetrain/phoenix/CustomParamConfiguration.h"
#include "drivetrain/phoenix/Utilities.h"

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
