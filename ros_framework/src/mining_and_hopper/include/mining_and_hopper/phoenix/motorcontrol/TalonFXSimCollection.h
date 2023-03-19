#pragma once

#include "mining_and_hopper/phoenix/ErrorCode.h"

/* forward proto's */
namespace ctre {
	namespace phoenix {
		namespace motorcontrol {
			namespace can {
				class BaseTalon;
			}
		}
	}
}

namespace ctre {
	namespace phoenix {
		namespace motorcontrol {

			/**
			  * Collection of simulation commands available to a TalonFX motor controller.
			  *
			  * Use the getSimCollection() routine inside your motor controller to create the respective sim collection.
			  */
			class TalonFXSimCollection {
			public:
				/**
				 * Constructor for TalonFXSimCollection
				 * @param motorController TalonFX Motor Controller to connect Collection to
				 */
				TalonFXSimCollection(ctre::phoenix::motorcontrol::can::BaseTalon& motorController);

				/**
				 * Gets the last error generated by this object. Not all functions return an
				 * error code but can potentially report errors. This function can be used
				 * to retrieve those error codes.
				 *
				 * @return Last Error Code generated by a function.
				 */
				ErrorCode GetLastError();

				/**
				 * Gets the simulated output voltage across M+ and M- for the motor.
				 * 
				 * @return applied voltage to the motor in volts
				 */
				double GetMotorOutputLeadVoltage();

				/**
				 * Sets the simulated bus voltage of the TalonFX.
				 * 
				 * The minimum allowed bus voltage is 4 V - values 
				 * below this will be promoted to 4 V.
				 * 
				 * @param vbat the bus voltage in volts
				 *
				 * @return  error code
				 */
				ErrorCode SetBusVoltage(double vbat);

				/**
				 * Sets the simulated supply current of the TalonFX.
				 * 
				 * @param currA the supply current in amps
				 *
				 * @return  error code
				 */
				ErrorCode SetSupplyCurrent(double currA);

				/**
				 * Sets the simulated stator current of the TalonFX.
				 * 
				 * @param currA the stator current in amps
				 *
				 * @return  error code
				 */
				ErrorCode SetStatorCurrent(double currA);

				/**
				 * Sets the simulated forward limit switch of the TalonFX.
				 * 
				 * @param isClosed true if the limit switch is closed
				 *
				 * @return  error code
				 */
				ErrorCode SetLimitFwd(bool isClosed);

				/**
				 * Sets the simulated reverse limit switch of the TalonFX.
				 * 
				 * @param isClosed true if the limit switch is closed
				 *
				 * @return  error code
				 */
				ErrorCode SetLimitRev(bool isClosed);

				/**
				 * Sets the simulated raw integrated sensor position of the TalonFX. 
				 *
				 * The TalonFX integrates this to calculate the true reported integrated sensor 
				 * position. 
				 *
				 * When using the WPI Sim GUI, you will notice a readonly 'position' and 
				 * settable 'rawPositionInput'.  The readonly signal is the emulated position 
				 * which will match self-test in Tuner and the hardware API.  Changes to 
				 * 'rawPositionInput' will be integrated into the emulated position.  This way 
				 * a simulator can modify the position without overriding your 
				 * hardware API calls for home-ing your sensor. 
				 *
				 * Inputs to this function over time should be continuous, 
				 * as user calls of SetSelectedSensorPosition() and SetIntegratedSensorPosition() 
				 * will be accounted for in the calculation.
				 * 
				 * @param newPos the new raw position in native units
				 *
				 * @return  error code
				 */
				ErrorCode SetIntegratedSensorRawPosition(int newPos);

				/**
				 * Adds to the simulated integrated sensor position of the TalonFX.
				 * 
				 * @param dPos the change in position in native units
				 *
				 * @return  error code
				 */
				ErrorCode AddIntegratedSensorPosition(int dPos);

				/**
				 * Sets the simulated integrated sensor velocity of the TalonFX.
				 * 
				 * @param newVel the new velocity in native units per 100ms
				 *
				 * @return  error code
				 */
				ErrorCode SetIntegratedSensorVelocity(int newVel);

			private:
				int _id;

			};

		} // namespace motorcontrol
	} // namespace phoenix
} // namespace ctre
