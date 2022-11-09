//------------------------------------------------------------------------------------------
//
//�|�[�Y���j���[
//Author;takano
//
//------------------------------------------------------------------------------------------
#include"pause.h"
#include"input.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//----------------------
//�}�N����`
//----------------------
#define MAX_W				(256)							//����
#define MAX_H				(30)							//�c��

//-----------------------
//�O���[�o���ϐ�
//-----------------------
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu[POUSE_MENU_MAX] = {NULL,NULL,NULL};					//�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;													//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;												//���_�o�b�t�@�̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;											//���_�o�b�t�@�̃|�C���^
PAUSE_MENU g_pauseMenu;																		//�|�[�Y���j�D�[�\���̂̏��
PAUSE g_aPause[POUSE_MENU_MAX];																//�|�[�Y�\���̂̏��

//---------------------
//�|�[�Y�̏���������
//---------------------
void InitPause(void)
{
	int nCountPause;

	LPDIRECT3DDEVICE9 pDevice;																//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause, NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * POUSE_MENU_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause000.png", &g_pTexturePauseMenu[0]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause001.png", &g_pTexturePauseMenu[1]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause002.png", &g_pTexturePauseMenu[2]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pouse_now.png", &g_pTexturePause);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//�l�̏�����
		g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.2f,170.0f + (MAX_H * 7.0f * nCountPause), 0.0f);
		g_aPause[nCountPause].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	}

	//�|�[�Y���̏�����
	g_pauseMenu = POUSE_MENU_COUNTINUE;
	
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.26f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.26f);

	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPause->Unlock();

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_W, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_W, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_W, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_W, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aPause[nCountPause].col;
		pVtx[1].col = g_aPause[nCountPause].col;
		pVtx[2].col = g_aPause[nCountPause].col;
		pVtx[3].col = g_aPause[nCountPause].col;

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPauseMenu->Unlock();
}

//---------------------
//�|�[�Y�̏I������
//---------------------
void UninitPause(void)
{
	for (int nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//�e�N�X�`���̔j��
		if (g_pTexturePauseMenu[nCountPause] != NULL)
		{
			g_pTexturePauseMenu[nCountPause]->Release();
			g_pTexturePauseMenu[nCountPause] = NULL;
		}
	}

	//�e�N�X�`���̔j��
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//---------------------
//�|�[�Y�̍X�V����
//---------------------
void UpdatePause(void)
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP) == true  || GetJoypadTrigger(JOYKEY_UP) == true)
		{//W�L�[���������Ƃ�
			g_aPause[g_pauseMenu].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_pauseMenu;			//�Ł[����

												//���_�J���[�̐ݒ�
			pVtx[0].col = g_aPause[g_pauseMenu].col;
			pVtx[1].col = g_aPause[g_pauseMenu].col;
			pVtx[2].col = g_aPause[g_pauseMenu].col;
			pVtx[3].col = g_aPause[g_pauseMenu].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPauseMenu->Unlock();

			g_pauseMenu = (PAUSE_MENU)((g_pauseMenu - 1 + 3) % 3);
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)
		{//S�L�[�������ꂽ
			g_aPause[g_pauseMenu].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_pauseMenu;			//�Ł[����

												//���_�J���[�̐ݒ�
			pVtx[0].col = g_aPause[g_pauseMenu].col;
			pVtx[1].col = g_aPause[g_pauseMenu].col;
			pVtx[2].col = g_aPause[g_pauseMenu].col;
			pVtx[3].col = g_aPause[g_pauseMenu].col;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffPauseMenu->Unlock();

			g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1 + 3) % 3);

		}
		g_aPause[g_pauseMenu].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * g_pauseMenu;			//�Ł[����

		//���_�J���[�̐ݒ�
		pVtx[0].col = g_aPause[g_pauseMenu].col;
		pVtx[1].col = g_aPause[g_pauseMenu].col;
		pVtx[2].col = g_aPause[g_pauseMenu].col;
		pVtx[3].col = g_aPause[g_pauseMenu].col;

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPauseMenu->Unlock();

		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			if (g_pauseMenu == POUSE_MENU_COUNTINUE)
			{
				SetEnablePause(false);
			}
			else if (g_pauseMenu == POUSE_MENU_RETRY)
			{
				SetFade(MODE_GAME);
			}
			else if (g_pauseMenu == POUSE_MENU_QUIT)
			{
				SetFade(MODE_TITLE);
			}
		}
	}
}

//---------------------
//�|�[�Y�̕`�揈��
//---------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	int nCountPause = 0;

	//�f���@�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePause);

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTexturePauseMenu[nCountPause]);

		//�|���S���̕`��
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			nCountPause * 4,
			2);
	}
}