//-----------------------------------------------------------------------------------------------------------
//
//���C��
//Author;takano
//
//-----------------------------------------------------------------------------------------------------------
#include"main.h"
#include"input.h"
#include"title.h"
#include"game.h"
#include"sound.h"
#include"result.h"
#include"fade.h"
#include"ranking.h"
#include"score.h"

//-----------
//�}�N����`
//-----------
#define CLASS_NAME			"WindowClass"			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME			"�E�B���h�E����"		//�E�B���h�E�̖��O

//-----------------
//�v���g�^�C�v�錾
//-----------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT InIt(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);
void DrawFPS(void);

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3D9 g_pD3D = NULL;							//Direct3D�I�u�W�F�N�g�̃|�C���^
LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;				//Direct3D�f�o�C�X�̃|�C���^
LPD3DXFONT g_pFont = NULL;
int g_nCountFPS = 0;
MODE g_mode = MODE_TITLE;							//���݂̃��[�h

//------------
//���C���֐�
//------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),						//WINDCLASSEX�̃������T�C�Y
		CS_CLASSDC,								//�E�B���h�E�X�^�C��
		WindowProc,							    //�E�B���h�E�v���[�V��
		0,										//0�ɂ���
		0,										//�O�ɂ���
		hInstance,								//�C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),			//�^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),				//�}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),				//�N���C�A���g�̈�̔w�i
		NULL,									//���j���[�o�[
		CLASS_NAME,								//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)			//�t�@�C���A�C�R��
	};

	HWND hWnd;									//�E�B���h�E�n���h��
	MSG msg;									//���b�Z�[�W�����[����\����

	//��ʍ\����
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�N���C�A���g�̈���w��̃T�C�Y�ɒ���
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	//�E�B���h�E����
	hWnd = CreateWindowEx(0,						//�g���E�B���h�X�^�C��
		CLASS_NAME,									//�E�B���h�N���X�̃X�^�C��
		WINDOW_NAME,								//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,						//�E�B���h�X�^�C��			
		CW_USEDEFAULT,								//�E�B���h�E�̍��゘���W
		CW_USEDEFAULT,								//�E�B���h�E�̍��゙���W
		(rect.right - rect.left),					//�E�B���h�E�̕�
		(rect.bottom - rect.top),					//�E�B���h�E�̍���
		NULL,										//�e�E�B���h�E�̃n���h��
		NULL,										//���j���[�n���h��or�q�E�B���h�E�h�c
		hInstance,									//�C���X�^���X�n���h��
		NULL);										//�E�B���h�E�̍쐬�f�[�^

	DWORD dwFrameCount;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;			//���ݎ���
	DWORD dwExecLastTime;			//�Ō�ɏ�����������

	//����������
	if (FAILED(InIt(hInstance, hWnd, TRUE)))
	{//�����������s�����ꍇ
		return -1;
	}

	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;							//������
	dwExecLastTime = timeGetTime();				//���ݎ������擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();;

	//�E�B���h�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{//windows�̏���
			if (msg.message == WM_QUIT)
			{//MW_QUIT���b�Z�[�W���󂯎�����烁�b�Z�[�W���[�v���ʂ���
				break;
			}
			else
			{
				//���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);

				DispatchMessage(&msg);
			}
		}
		else
		{//DirctX�̏���
			dwCurrentTime = timeGetTime();				//���ݎ������擾
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{//0.5�b�o��
				//FPS���v��
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				//FPS�̌v��������ۑ�
				dwFPSLastTime = dwCurrentTime;

				//�t���[���J�E���g���N���A
				dwFrameCount = 0;
			}
			if (dwCurrentTime - dwExecLastTime >=(1000/60))
			{
				dwExecLastTime = dwCurrentTime;			//�����J�n�̎����ƌ��ݎ������擾
				//�X�V����
				Update();
				//�`�揈��
				Draw();
				//�t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}
	//�I������
	Uninit();

	//����\��߂�
	timeEndPeriod(1);

	//�E�B���h�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//---------------------
//�E�B���h�E�v���[�W��
//---------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;  
	switch (uMsg)
	{
	case WM_DESTROY:		//�E�B���h�E�j�����b�Z�[�W

		//WM_QUIT���b�Z�[�W�ő���
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:				//ESC�L�[�������ꂽ
			//�E�B���h�E��j������
			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO | MB_TOPMOST);

			if (nID == IDYES)
			{
				//�E�B���h�E��j�󂷂�
				DestroyWindow(hWnd);
			}
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------
//����������
//-----------
HRESULT InIt(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;					//�f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;			//�v���[���e�[�V�����p�����[�^�[

	//Dirct3d�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	//�f�o�C�X�̃v���[���e�[�V�����̃p�����[�^�[�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));														//�p�����[�^�[�̃[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;													//�Q�[����ʃT�C�Y�i���j
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;													//�Q�[����ʃT�C�Y�i�����j
	d3dpp.BackBufferFormat = d3ddm.Format;													//�o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferCount = 1;																//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;												//�_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;													//�f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@�̐���
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;												//�f�v�X�o�b�t�@�Ƃ��āA16bit���g��
	d3dpp.Windowed = bWindow;																//�E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;								//�C���^�[�o��

	//Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�A���_��CPU)
	if (FAILED(g_pD3D->CreateDevice
		(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_HARDWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))

	{
		//Direct3D�f�o�C�X�̐���(�`�揈�����n�[�h�A���_��CPU)
		if (FAILED(g_pD3D->CreateDevice
			(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_HAL,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))

		{//Direct3D�f�o�C�X�̐���(�`�揈����CPU�A���_��CPU)
			if (FAILED(g_pD3D->CreateDevice
				(D3DADAPTER_DEFAULT,
					D3DDEVTYPE_REF,
					hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp,
					&g_pD3DDevice)))
			{
				return E_FAIL;
			}
		}

	}
	//�����_�[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);


	//�T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	//�e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	//�f�o�b�N�\���p�̃t�H�g���X�g���[���𐶐�
	D3DXCreateFont(g_pD3DDevice, 18, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH,
		"Terminal", &g_pFont);

	//�L�[�{�[�h�̏���������
	if (FAILED(Initkeyboard(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	//�Q�[���p�b�g�̏�����
	InitJoypad();

	//�����L���O�̃��Z�b�g
	ResetRanking();
	
	//�T�E���h�̏���������
	InitSound(hWnd);

	//���[�h�̐ݒ�
	InitFade(g_mode);

	return S_OK;
}

//---------
//�I������
//---------
void Uninit(void)
{
	//�t�F�[�h�̏I������
	UninitFade();

	//�^�C�g����ʂ̏I������
	UninitTitle();

	//�Q�[����ʂ̏I������
	UninitGame();

	//���U���g��ʂ̏I������
	UninitResult();

	//�L�[�{�[�h�̏I������
	Uninitkeyboard();

	//�W���C�p�b�h�̏I������
	UninitJoypad();

	//�����L���O�̏I������
	UninitRanking();

	//�T�E���h�̏I������
	UninitSound();

	//�f�o�b�N�p�t�H�g���̔j��
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	//Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	//Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//---------
//�X�V����
//---------
void Update(void)
{

	Updatekeyboard();				//keyboard�̍X�V����

	UpdateJoypad();					//Joypad�̍X�V����

	switch (g_mode)
	{
	case MODE_TITLE:
		UpdateTitle();				//titlescreen�̍X�V����
		break;

	case MODE_GAME:
		UpdateGame();				//gamescreen�̍X�V����
		break;

	case MODE_RESULT:
		UpdateResult();				//resultscreen�̍X�V����
		break;

	case MODE_RANKING:
		UpdateRanking();			//resultscreen�̍X�V����
		break;
	}

	//�t�F�[�h�̍X�V����
	UpdateFade();
}

//---------
//�`�揈��
//---------
void Draw(void)
{
	//��ʃN���A�i�o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A�j
	g_pD3DDevice->Clear(
		0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	//�`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{//�`��J�n�����������ꍇ

		switch (g_mode)
		{
		case MODE_TITLE:
			DrawTitle();
			break;

		case MODE_GAME:
			DrawGame();
			break;

		case MODE_RESULT:
			DrawResult();
			break;

		case MODE_RANKING:
			DrawRanking();
			break;
		}

		//�t�F�[�h�̕`�揈��
		DrawFade();
		#ifdef _DEBUG
			//FPS�̕\��
			DrawFPS();
		#endif


		//�`��I��
		g_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//-----------------
//FPS�̐ݒ�
//-----------------
void DrawFPS(void)
{
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	int pRanking = GetRanking();

	char aStr[256];

	//������ɑ��
	wsprintf(&aStr[0], "FPS:%d\n", g_nCountFPS);
	wsprintf(&aStr[7], "Ranking:%d\n", pRanking);

	//�e�L�X�g�̕`��
	g_pFont->DrawText(NULL, &aStr[0], -1, &rect, DT_LEFT, D3DCOLOR_RGBA(255, 255, 255, 255));
}

//-----------------
//���[�h�̐ݒ�
//-----------------
void SetMode(MODE mode)
{
	//���݂̃��[�h�̏I������
	switch (g_mode)
	{
	case MODE_TITLE:
		UninitTitle();
		break;

	case MODE_GAME:
		UninitGame();
		break;

	case MODE_RESULT:
		UninitResult();
		break;

	case MODE_RANKING:
		UninitRanking();
		break;
	}

	//�V�������[�h�̐ݒ�
	switch (mode)
	{
	case MODE_TITLE:
		InitTitle();
		break;

	case MODE_GAME:
		InitGame();
		break;

	case MODE_RESULT:
		InitResult();
		break;

	case MODE_RANKING:
		InitRanking();
		SetRanking(GetScore());
		break;
	}
	g_mode = mode;
}

//---------------
//�f�o�C�X�̎擾
//---------------
LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pD3DDevice;
}

//---------------
//���[�h�̎擾
//---------------
MODE GetMode(void)
{
	return g_mode;
}