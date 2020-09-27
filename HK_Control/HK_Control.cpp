#include"pch.h"
#include "HK_Control.h"
#include"HCNetSDK.h"
#include<iostream>
#define MULTI_RECORD_ECP "StartRecord called multi times before EndRecord! Try EndRecord first"


class HKIniter {
public:
	HKIniter() {
		NET_DVR_Init();
	}
	~HKIniter() {
		NET_DVR_Cleanup();
	}
};
//����������Ҳֻ��initһ��
const static HKIniter initer;

HKCAPI HK_Control::HK_Control(std::string ip, int port, std::string user, std::string pwd, long channel)
	:_ip(ip),
	_port(port),
	_user(user),
	_pwd(pwd),
	_channel(channel)
{

}

HKCAPI HK_Control::~HK_Control()
{
	if (_isRecording) 
	{
		EndRecord();
	}
	if (_playID != -1)
	{
		StopPlay();
	}
	if (_loginID != -1)
	{
		Logout();
	}
}

HKCAPI DWORD HK_Control::Login()
{
	NET_DVR_DEVICEINFO info;
	//login
	_loginID = NET_DVR_Login((char*)_ip.c_str(),
		_port,
		(char*)_user.c_str(),
		(char*)_pwd.c_str(),
		&info);
	return GetLastError();
}

HKCAPI DWORD HK_Control::Play(HWND hwnd)
{
	NET_DVR_CLIENTINFO playInfo;
	playInfo.lChannel = 1;
	playInfo.hPlayWnd = hwnd;
	playInfo.sMultiCastIP = 0;
	playInfo.lLinkMode = 0;
	_playID = NET_DVR_RealPlay_V30(_loginID, &playInfo);
	return GetLastError();
}

HKCAPI DWORD HK_Control::CaptureJPG(std::string filename)
{
	NET_DVR_SetCapturePictureMode(JPEG_MODE);
	NET_DVR_CapturePicture(_playID, (char*)filename.c_str());
	return GetLastError();
}

HKCAPI DWORD HK_Control::CaptureBMP(std::string filename)
{
	NET_DVR_CapturePicture(_playID, (char*)filename.c_str());
	return GetLastError();
}
HKCAPI DWORD HK_Control::StartRecord(std::string filename)
{
	if (!_isRecording)
	{
		NET_DVR_SaveRealData(_playID, (char*)filename.c_str());
		_isRecording = true;
	}
	else
	{
		throw std::exception(MULTI_RECORD_ECP);
	}
	return  GetLastError();
}
HKCAPI DWORD HK_Control::EndRecord()
{
	NET_DVR_StopSaveRealData(_playID);
	_isRecording = false;
	return  GetLastError();
}
HKCAPI DWORD HK_Control::StopPlay()
{
	NET_DVR_StopRealPlay(_playID);
	_playID = -1;
	return 0;
}

HKCAPI DWORD HK_Control::Logout()
{
	NET_DVR_Logout(_loginID);
	_loginID = -1;
	return 0;
}

HKCAPI BOOL HK_Control::AddCameraPreset(DWORD dwPresetIndex)
{
	return  NET_DVR_PTZPreset(_playID, SET_PRESET, dwPresetIndex);
}

HKCAPI BOOL HK_Control::MoveCameraToPreset(DWORD dwPresetIndex)
{
	return  NET_DVR_PTZPreset(_playID, GOTO_PRESET, dwPresetIndex);
}

HKCAPI void HK_Control::MoveCameraUpStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, TILT_UP, 0, speed);
}

HKCAPI void HK_Control::MoveCameraUpStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, TILT_UP, 1, speed);
}

HKCAPI void HK_Control::MoveCameraDownStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, TILT_DOWN, 0, speed);
}

HKCAPI void HK_Control::MoveCameraDownStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, TILT_DOWN, 1, speed);
}

HKCAPI void HK_Control::MoveCameraLeftStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, PAN_LEFT, 0, speed);
}

HKCAPI void HK_Control::MoveCameraLeftStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, PAN_LEFT, 1, speed);
}

HKCAPI void HK_Control::MoveCameraRightStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, PAN_RIGHT, 0, speed);
}

HKCAPI void HK_Control::MoveCameraRightStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, PAN_RIGHT, 1, speed);
}

HKCAPI void HK_Control::ZoomInStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, ZOOM_IN, 0, speed);
}

HKCAPI void HK_Control::ZoomInStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, ZOOM_IN, 1, speed);
}

HKCAPI void HK_Control::ZoomOutStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, ZOOM_OUT, 0, speed);
}

HKCAPI void HK_Control::ZoomOutStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, ZOOM_OUT, 1, speed);
}

HKCAPI void HK_Control::FocusNearStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, FOCUS_NEAR, 0, speed);
}

HKCAPI void HK_Control::FocusNearStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, FOCUS_NEAR, 1, speed);
}

HKCAPI void HK_Control::FocusFarStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, FOCUS_FAR, 0, speed);
}

HKCAPI void HK_Control::FocusFarStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, FOCUS_FAR, 1, speed);
}

HKCAPI void HK_Control::IRISOpenStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, IRIS_OPEN, 0, speed);
}

HKCAPI void HK_Control::IRISOpenStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, IRIS_OPEN, 1, speed);
}

HKCAPI void HK_Control::IRISCloseStart(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, IRIS_CLOSE, 0, speed);
}

HKCAPI void HK_Control::IRISCloseStop(DWORD speed)
{
	NET_DVR_PTZControlWithSpeed(_playID, IRIS_CLOSE, 1, speed);
}

DWORD HK_Control::GetLastCameraError()
{
	return GetLastError();
}