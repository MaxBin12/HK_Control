#pragma once

#ifdef HKCONTROL_EXPORTS
#define HKCAPI  __declspec(dllexport)
#else
#define HKCAPI __declspec(dllimport)
#endif // HKCONTROL_EXPORTS
//Ĭ����̨�ٶ�
#define DEFAULTSPEED 3

#include<Windows.h>
#include<string>
#include<vector>


 /**
  * @brief �Ժ������������API�򵥷�װ���������
  * ע��ʹ��Dll�������ֶ�NET_DVR_Init��NET_DVR_Cleanup����Dll�ڵ�һ����̬ȫ�ֶ����Զ�Init��Cleanup
 */
 class HK_Control
{
private:
	//ip
	std::string _ip;
	//�˿�
	int _port = 8000;
	//�û���
	std::string _user;
	//����
	std::string _pwd;
	//���Ŵ���hwnd
	HWND _hwnd = NULL;
	//��¼�ɹ����id
	long _loginID = -1;
	//����ͨ��
	long _channel = 1;
	//����id
	long _playID = -1;
	//����¼��
	bool _isRecording = false;
public:
	/**
	 * @brief ��¼�벥�Ų�����ʼ��
	 * @param ip ip
	 * @param port �˿�
	 * @param user �û���
	 * @param pwd ����
	 * @param channel ����ͨ����Ĭ��Ϊ 1
	 * @return  
	*/
	HKCAPI HK_Control(std::string ip, int port, std::string user, std::string pwd, long channel = 1);
	/**
	 * @brief ������������Ƿ��˳���¼��ֹͣ���ŵ�
	 * @return 
	*/
	HKCAPI ~HK_Control();
	/**
	 * @brief ��¼
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD Login();
	/**
	 * @brief �Ƿ��Ѿ���½��δ�˳�
	 * @return true�Ѿ���½��δ�˳���false���˳�
	*/
	HKCAPI bool IsLogin();
	/**
	 * @brief ���ڲ���
	 * @return true���ڲ��ţ�fasleδ���ڲ���
	*/
	HKCAPI bool IsPlay();
	/**
	 * @brief �Ƿ����ڲ���
	 * @return 
	*/
	HKCAPI bool IsRecording();
	/**
	 * @brief ����Ԥ��
	 * @param hwnd Ԥ����������Ⱦ��hwnd
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD Play(HWND hwnd);
	/**
	 * @brief ����һ��ץͼ����ʽΪjpg
	 * @param filename ץͼ�ļ���
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD CaptureJPG(std::string filename);
	/**
	 * @brief ����һ��ץͼ����ʽΪbpm
	 * @param filename ץͼ�ļ���
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD CaptureBMP(std::string filename);
	/**
	 * @brief ��ʼ¼��
	 * @exception std::exception ���������ʼ¼�񣬶�δֹͣ��һ��¼�񣬻��׳��ظ�¼���쳣��
	 * @param filename ¼���ļ��� 
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD StartRecord(std::string filename);
	/**
	 * @brief ֹͣ¼��
	 * @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	HKCAPI DWORD EndRecord();

	/**
	 * @brief ֹͣ����
	 * @return 
	*/
	HKCAPI DWORD StopPlay();
	/**
	 * @brief ע����¼
	 * @return 
	*/
	HKCAPI DWORD Logout();
	/**
	 * @brief ���Ŀǰλ�õ�Ԥ��λ
	 * @param dwPresetIndex Ԥ��λ���
	 * @return 
	*/
	HKCAPI BOOL AddCameraPreset( DWORD dwPresetIndex);
	/**
	 * @brief ����ƶ���Ԥ��λ
	 * @param dwPresetIndex Ԥ��λ���
	 * @return 
	*/
	HKCAPI BOOL MoveCameraToPreset( DWORD dwPresetIndex);
	//��������̨����
	//up static
	HKCAPI void MoveCameraUpStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraUpStop(DWORD speed = DEFAULTSPEED);
	//down static
	HKCAPI void MoveCameraDownStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraDownStop(DWORD speed = DEFAULTSPEED);
	//left static
	HKCAPI void MoveCameraLeftStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraLeftStop(DWORD speed = DEFAULTSPEED);
	//right static
	HKCAPI void MoveCameraRightStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void MoveCameraRightStop(DWORD speed = DEFAULTSPEED);
	//Zoom in
	HKCAPI void ZoomInStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void ZoomInStop(DWORD speed = DEFAULTSPEED);
	//Zoom out
	HKCAPI void ZoomOutStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void ZoomOutStop(DWORD speed = DEFAULTSPEED);
	//Focus near
	HKCAPI void FocusNearStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void FocusNearStop(DWORD speed = DEFAULTSPEED);
	//Focus far
	HKCAPI void FocusFarStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void FocusFarStop(DWORD speed = DEFAULTSPEED);
	//IRIS open
	HKCAPI void IRISOpenStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void IRISOpenStop(DWORD speed = DEFAULTSPEED);
	//IRIS close
	HKCAPI void IRISCloseStart(DWORD speed = DEFAULTSPEED);
	HKCAPI void IRISCloseStop(DWORD speed = DEFAULTSPEED);

	HKCAPI DWORD GetLastCameraError();
};

