#include "./TestMotor.h"
#include <EV3_LCDDisplay.h>
#include <EV3_Timer.h>
#include <EV3_Thread.h>
#include <EV3_BrickUI.h>


using namespace ev3_c_api;


C_TestMotor::C_TestMotor()
{
}

C_TestMotor::~C_TestMotor()
{
}

void C_TestMotor::Test_StartMotor() const
{
	this->Show_Title("Start Motor");

	const E_Brick_Layer layer = E_Layer_1;
	const E_Motor_Port port = E_Port_A;
	const E_MotorType motorType = E_MotorType_Large;
	const signed char speed = 10;

	for (unsigned int i = 0; i < 1; i++)
	{
		Clear_Display();

		bool bVal = ResetMotor(port, layer);
		Draw_Text(0, E_Font_Normal, false, "ResetMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(2));

		bVal = SpeedMotor(port, speed, layer);
		Draw_Text(1, E_Font_Normal, false, "SpeedMotor(%d)", speed);

		Timer_Start(1);
		while (1)
		{
			this->Show_MotorData(port, layer, motorType);

			if (Timer_GetTime(1) > SEC(5))
				break;

			EV3_Sleep(100);
		}
		Timer_Destroy(1);

		Draw_Text(2, E_Font_Normal, false, "StopMotor");
		bVal = StopMotor(port, true, layer);

		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(4));
	}
}

void C_TestMotor::Test_StartMotor_Rotation() const
{
	this->Show_Title("StartMotor Rotation");

	const E_Brick_Layer layer = E_Layer_1;
	const E_Motor_Port port = E_Port_A;
	const E_MotorType motorType = E_MotorType_Large;
	const signed char speed = 20;
	const int angle = 1800;

	for (unsigned int i = 0; i < 1; i++)
	{
		Clear_Display();

		ResetMotor(port, layer);
		Draw_Text(0, E_Font_Normal, false, "ResetMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(2));

		SpeedMotor_RotationAngle(port, speed, angle, layer);
		Draw_Text(1, E_Font_Normal, false, "SpeedMotor_RotationAngle");

		while (1)
		{
			if ( !isMotorBusy(port, motorType, layer) )
				break;

			this->Show_MotorData(port, layer, motorType);
			EV3_Sleep(100);
		}

		Draw_Text(2, E_Font_Normal, false, "StopMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(4));
	}
}

void C_TestMotor::Test_StartMotor_Time() const
{
	this->Show_Title("StartMotor Time");

	const E_Brick_Layer layer = E_Layer_1;
	const E_Motor_Port port = E_Port_A;
	const E_MotorType motorType = E_MotorType_Large;
	const signed char power = 10;
	const unsigned int time = 5;		// seconds

	for (unsigned int i = 0; i < 1; i++)
	{
		Clear_Display();

		ResetMotor(port);
		Draw_Text(0, E_Font_Normal, false, "ResetMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(2));

		Draw_Text(1, E_Font_Normal, false, "PowerMotor_Time");
		PowerMotor_Time(port, power, SEC(time), layer);

		while (1)
		{
			if ( !isMotorBusy(port, motorType, layer) )
				break;

			this->Show_MotorData(port, layer, motorType);
			EV3_Sleep(100);
		}

		Draw_Text(2, E_Font_Normal, false, "StopMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(4));
	}
}

void C_TestMotor::Test_StartMotor_Time2() const
{
	this->Show_Title("StartMotor Time2");

	const E_Brick_Layer layer = E_Layer_1;
	const E_Motor_Port port = E_Port_A;
	const E_MotorType motorType = E_MotorType_Large;
	const signed char speed = -10;
	const unsigned int time = 10;		// seconds

	for (unsigned int i = 0; i < 1; i++)
	{
		Clear_Display();

		ResetMotor(port);
		Draw_Text(0, E_Font_Normal, false, "ResetMotor");
		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(2));

		Draw_Text(1, E_Font_Normal, false, "SpeedMotor_Time");
		SpeedMotor_Time(port, speed, SEC(time), layer);

		Timer_Start(1);
		while (1)
		{
			if ( !isMotorBusy(port, motorType, layer) )
				break;

			if (Timer_GetTime(1) > SEC(4))
			{
				Draw_Text(2, E_Font_Normal, false, "StopMotor");
				StopMotor(port, true, layer);
			}

			this->Show_MotorData(port, layer, motorType);
			EV3_Sleep(100);
		}
		Timer_Destroy(1);

		this->Show_MotorData(port, layer, motorType);
		EV3_Sleep(SEC(4));
	}
}

void C_TestMotor::Test_TwoMotors() const
{
	this->Show_Title("Start Two Motors");

	const E_Brick_Layer layer = E_Layer_1;
	const E_Motor_Port port1 = E_Port_A;
	const E_Motor_Port port2 = E_Port_D;
	const E_MotorType motorType1 = E_MotorType_Large;
	const E_MotorType motorType2 = E_MotorType_Large;
	const signed char speed1 = 10;
	const signed char speed2 = -20;
	const unsigned int time = 10;				// seconds

	Clear_Display();

	ResetMotor(port1);
	ResetMotor(port2);
	Draw_Text(0, E_Font_Normal, false, "ResetMotor");
	this->Show_MotorData(port1, layer, motorType1);
	EV3_Sleep(SEC(2));
	this->Show_MotorData(port2, layer, motorType2);
	EV3_Sleep(SEC(2));

	SpeedTwoMotors_Time(port1, speed1, port2, speed2, SEC(time), layer);
	Draw_Text(1, E_Font_Normal, false, "SpeedTwoMotors_Time");

	Timer_Start(1);
	while (1)
	{
		if ( !isMotorBusy(port1, motorType1, layer) )
			break;

		this->Show_MotorData(port1, layer, motorType1);

		if ( Timer_GetTime(1) > SEC(4) )
			break;

		EV3_Sleep(100);
	}
	Timer_Destroy(1);

	Draw_Text(2, E_Font_Normal, false, "Stop Motors");
	StopMotor(E_Port_AD, true, layer);

	this->Show_MotorData(port1, layer, motorType1);
	EV3_Sleep(SEC(2));
	this->Show_MotorData(port2, layer, motorType2);
	EV3_Sleep(SEC(2));
}

void C_TestMotor::Show_MotorData(E_Motor_Port inPort, E_Brick_Layer inLayer, E_MotorType inMotorType) const
{
	unsigned int uiLine = 4;

	Clear_Text(uiLine, E_Font_Normal);
	Draw_Text(uiLine, E_Font_Normal, false, "Port : %s", this->GetPortName(inPort).c_str());
	uiLine++;

	Clear_Text(uiLine, E_Font_Normal);
	Draw_Text(uiLine, E_Font_Normal, false, "Tacho Counts : %ld", GetMotor_TachoCounts(inPort, inMotorType, inLayer));
	uiLine++;

	Clear_Text(uiLine, E_Font_Normal);
	Draw_Text(uiLine, E_Font_Normal, false, "Rotation : %ld", GetMotor_RotationCount(inPort, inMotorType, inLayer));
	uiLine++;

	Clear_Text(uiLine, E_Font_Normal);
	Draw_Text(uiLine, E_Font_Normal, false, "Speed : %ld", GetMotor_Speed(inPort, inMotorType, inLayer));
	uiLine++;

	Clear_Text(uiLine, E_Font_Normal);
	if (isMotorBusy(inPort, inMotorType, inLayer))
		Draw_Text(uiLine, E_Font_Normal, false, "Busy : Yes");
	else
		Draw_Text(uiLine, E_Font_Normal, false, "Busy : No");
}

void C_TestMotor::Show_Title(const char* inTitle) const
{
	Clear_Display();
	Draw_Text(0, E_Font_Normal, false, inTitle);
	Draw_Text(2, E_Font_Normal, false, "Press button Down...");
	WaitBrickButtonPress(E_BTN_DOWN);
	Clear_Display();
}

T_String C_TestMotor::GetPortName(E_Motor_Port inPort) const
{
	switch ( inPort )
	{
		case E_Port_A:
			return "A";

		case E_Port_B:
			return "B";

		case E_Port_C:
			return "C";

		case E_Port_D:
			return "D";

		default:
			return "Unknown";
	}

	return "Unknown";
}

