#ifndef __TESTMOTOR_H__
#define __TESTMOTOR_H__


#include <EV3_Motor.h>
#include <string>


typedef std::string							T_String;


class C_TestMotor
{
public:
	C_TestMotor();

	~C_TestMotor();

public:
	void Test_StartMotor() const;
	void Test_StartMotor_Rotation() const;
	void Test_StartMotor_Time() const;
	void Test_StartMotor_Time2() const;
	void Test_TwoMotors() const;

protected:
	void Show_MotorData(ev3_c_api::E_Motor_Port inPort, ev3_c_api::E_Brick_Layer inLayer, ev3_c_api::E_MotorType inMotorType) const;

	void Show_Title(const char* inTitle) const;

	T_String GetPortName(ev3_c_api::E_Motor_Port inPort) const;
};


#endif	// __TESTMOTOR_H__