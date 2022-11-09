//-----------------------------------------------------------------------------------------------------------
//
//�C���v�b�g
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
	JOYKEY_DOWN,			//�\���L�[��
	JOYKEY_LEFT,			//�\���L�[��
	JOYKEY_RIGHT,			//�\���L�[�E
	JOYKEY_STRTE,			//�X�^-�g
	JOYKEY_BACK,			//�o�b�N
	JOYKEY_LPUSH,			//L�g���K�[
	JOYKEY_RPUSH,			//R�g���K�[
	JOYKEY_L1,				//L1�{�^��
	JOYKEY_R1,				//R1�{�^��
	JOYKEY_L2,				//L2�{�^��
	JOYKEY_R2,				//R2�{�^��
	JOYKEY_A,				//A�{�^��
	JOYKEY_B,				//B�{�^��
	JOYKEY_X,				//X�{�^��
	JOYKEY_Y,				//Y�{�^��
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

