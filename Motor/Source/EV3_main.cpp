#include "./TestMotor.h"


int EV3_main()
{
	C_TestMotor motor;

	motor.Test_StartMotor();
	motor.Test_StartMotor_Rotation();
	motor.Test_StartMotor_Time();
	motor.Test_StartMotor_Time2();
	motor.Test_TwoMotors();

	return 0;
}
