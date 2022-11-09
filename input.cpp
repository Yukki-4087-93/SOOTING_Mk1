//-----------------------------------------------------------------------------------------------------------
//
//�L�[�{�[�h�A�Q�[���p�b�h���͏���
//Author;Takano
//
//-----------------------------------------------------------------------------------------------------------
#include"input.h"

//--------------------------------
//�}�N����`
//--------------------------------
#define NUM_KEY_MAX			(256)						//�L�[�̍ő吔

//--------------------------------
//�O���[�o���ϐ�
//--------------------------------
LPDIRECTINPUT8 g_pInput = NULL;							//�_�C���N�g�C���v�b�g�I�u�W�F�N�g�̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevkeyboard = NULL;				//���̓f�o�C�X�i�L�[�{�[�h�j�̃|�C���^
BYTE g_akeyState[NUM_KEY_MAX];							//�L�[�{�[�h�̃v���X���
BYTE g_akeyStateTrigger[NUM_KEY_MAX];					//�L�[�{�[�h�̃g���K�[���
XINPUT_STATE g_JoykeyState;								//�Q�[���p�b�h�̃v���X���
XINPUT_STATE g_JoykeyStateTrigger;						//�Q�[���p�b�h�̃g���K�[���

//--------------------------------
//�L�[�{�[�h�̏�����
//--------------------------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd)
{
	//Directinput�̐���
	if (FAILED(DirectInput8Create(hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)& g_pInput,NULL)))
	{
		return E_FAIL;
	}

	//���̓f�o�C�X�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard,&g_pDevkeyboard,NULL)))
	{
		return E_FAIL;
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevkeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	//�������[�h�̐ݒ�
	if (FAILED(g_pDevkeyboard->SetCooperativeLevel(hWnd,(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����l��
	g_pDevkeyboard->Acquire();

	return S_OK;
}

//--------------------------------
//�Q�[���p�b�h�̏�����
//--------------------------------
HRESULT InitJoypad(void)
{
	//�������̃N���A
	memset(&g_JoykeyState, 0, sizeof(XINPUT_STATE));

	//Xinput�̃X�e�[�g�̐ݒ�i�L�����p�j
	XInputEnable(true);

	return S_OK;
}

//--------------------------------
//�L�[�{�[�h�̏I��
//--------------------------------
void Uninitkeyboard(void)
{
	//���̓f�o�C�X�̔j��
	if (g_pDevkeyboard != NULL)
	{
		g_pDevkeyboard->Unacquire();
		g_pDevkeyboard->Release();
		g_pDevkeyboard = NULL;
	}

	//DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL)
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//--------------------------------
//�Q�[���p�b�h�̏I��
//--------------------------------
void UninitJoypad(void)
{
	//Xinput�̃X�e�[�g�̐ݒ�
	XInputEnable(false);
}

//--------------------------------
//�L�[�{�[�h�̍X�V
//--------------------------------
void Updatekeyboard(void)
{
	BYTE akeystate[NUM_KEY_MAX];				//�L�[�{�[�h�̓��͏��
	int nCntkey;

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevkeyboard->GetDeviceState(sizeof(akeystate), &akeystate[0])))
	{
			for (nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
			{
				g_akeyStateTrigger[nCntkey] = (g_akeyState[nCntkey] & akeystate[nCntkey]) ^ akeystate[nCntkey];			//�g���K�[����						//�L�[�{�[�h�̃g���K�[�����擾
				g_akeyState[nCntkey] = akeystate[nCntkey];																//�v���X����																					//�L�[�{�[�h�̃v���X�����擾
			}
	}
	else
	{
		g_pDevkeyboard->Acquire();					//�L�[�{�[�h�̃A�N�Z�X�����l��
	}
}

//--------------------------------
//�Q�[���p�b�h�X�V
//--------------------------------
void UpdateJoypad(void)
{
	XINPUT_STATE joykeystate;

	//�V���C�p�b�g�̏�Ԃ��擾
	if (XInputGetState(0,&joykeystate) == ERROR_SUCCESS)
	{
		g_JoykeyStateTrigger.Gamepad.wButtons = (g_JoykeyState.Gamepad.wButtons & joykeystate.Gamepad.wButtons) ^ joykeystate.Gamepad.wButtons;			//�g���K�[����	
		g_JoykeyState = joykeystate;
	}
}

//--------------------------------
//�L�[�{�[�h�̏����擾(����)
//--------------------------------
bool GetkeyboardPress(int nkey)
{
	return(g_akeyState[nkey] & 0x80) ? true : false;
}

//--------------------------------
//�L�[�{�[�h�̏����擾
//--------------------------------
bool GetkeyboardTrigger(int nkey)
{
	return(g_akeyStateTrigger[nkey] & 0x80) ? true : false;
}

//--------------------------------
//�Q�[���p�b�h�̏����擾(����)
//--------------------------------
bool GetJoypadPress(JOYkey key)
{
	return (g_JoykeyState.Gamepad.wButtons & (0x01 << key)) ? true : false;
}

//--------------------------------
//�Q�[���p�b�h�̏����擾
//--------------------------------
bool GetJoypadTrigger(JOYkey key)
{
	return (g_JoykeyStateTrigger.Gamepad.wButtons & (0x01 << key)) ? true : false;
}
