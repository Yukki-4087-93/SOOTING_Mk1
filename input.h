//-----------------------------------------------------------------------------------------------------------
//
//�{�^���d�r����
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//-----------------
//�L�[�̎��
//-----------------
typedef enum
{
	JOYKEY_UP = 0,			//�\���L�[��
	JOYKEY_DOWN,			//"""""��
	JOYKEY_LEFT,			//��������
	JOYKEY_RIGHT,			//��������
	JOYKEY_STRTE,			//�X�^-�g�ڂ�����
	JOYKEY_BACK,			//BLACKRX
	JOYKEY_LPUSH,			//L�g���K��
	JOYKEY_RPUSH,			//���C�g�Ȍ{�K��
	JOYKEY_L1,				//L1
	JOYKEY_R1,				//R1
	JOYKEY_L2,				//L2
	JOYKEY_R2,				//R2
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�o�g���[
	MAX_KEY
}JOYkey;

//-----------------
//�v���g�^�C�v�錾
//-----------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard(void);
void Updatekeyboard(void);
bool GetkeyboardPress(int nkey);
bool GetkeyboardTrigger(int nkey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYkey key);
bool GetJoypadTrigger(JOYkey key);

#endif // !_INPUT_H_

