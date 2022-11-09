//-----------------------------------------------------------------------------------------------------------
//
//�v���C���[
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#include"main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"
#include"life.h"
#include"time.h"
#include"fade.h"

//---------------
//�}�N����`
//---------------
//#define MAX_LIFE			(20)							//�v���C���[�ő僉�C�t

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//���_�o�b�t�@�̃|�C���^
Player g_aPlayer[MAX_PLAYER];						//�������̏��
int g_nEp;											//����
int g_nTypeBullet;									//����e��
bool g_bTime;										//������
bool g_bHart;

//------------------------
//�h���h�̏���������
//------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	//�f���@�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_pTexturePlayer);

	g_aPlayer[0].pos = D3DXVECTOR3(200.0f, 400.0f, 0.0f);				//�ʒu������������
	g_aPlayer[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�ړ��ʂ�����������
	g_aPlayer[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//�����̏�����
	g_aPlayer[0].state = PLAYERSTATE_NORMAL;							//�X�e�[�^�X���m�[�}���i�ʏ��ԁj�ɐݒ�
	g_aPlayer[0].nCounterState = 0;										//��ԃJ�E���^�[�̏�����
	g_aPlayer[0].nCountTimer = 0;										//�^�C�}�[�̏�����
	g_aPlayer[0].nPlayerLife = 4;										//���C�t
	g_nEp = 0;															//�����̏�����
	g_nTypeBullet = 0;													//����e�̏�����
	g_bTime = false;													//�e�Ɏg�p�����^�C�}�[�̏�����
	g_bHart = false;													//�e�̓���^�C�}�[�i���g�p�j
	g_aPlayer[0].bUse = true;											//�g�p����Ă��邩�ۂ�
	for (int i = 0; i < g_aPlayer[0].nPlayerLife; i++)
	{
		SetLife();
	}

	//�Ίp���̒������Z�o����
	g_aPlayer[0].fLength = sqrtf(HI_PLAYER * HI_PLAYER + WD_PLAYER * WD_PLAYER) / 2.0f;

	//�Ίp���̊p�x���Z�o����
	g_aPlayer[0].fAngle = atan2f(HI_PLAYER, WD_PLAYER);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.z = 0.0f;
	
	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	//�e�L�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//---------------------
//�h���h�̏I������
//---------------------
void UninitPlayer(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//----------------
//�h���h�̍X�V����
//----------------
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;							//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetkeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
	{//A�L�[�������ꂽ
		if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{//������W�L�[���������Ƃ�
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.75f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.75f) * 0.44f;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{//S�L�[�������ꂽ
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.25f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.25f) * 0.44f;
		}
		else
		{
			//�ړ��ʂ̍X�V
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.5f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.5f) * 0.44f;
		}
	}
	else if (GetkeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
	{//D�L�[�������ꂽ
		if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{//�����ɂc�L�[�������ꂽ
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.75f) * 0.44f;			
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.75f) * 0.44f;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{//�ʓ�����S�L�[�������ꂽ							  
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.25f) * 0.44f;
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.25f) * 0.44f;
		}
		else
		{//�c�L�[�R���O�������ꂽ
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.5f) * 0.44f;
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.5f) * 0.44f;
		}
	}
	else if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
	{//W�L�[�������ꂽ
		g_aPlayer[0].move.x += sinf(D3DX_PI) * 0.44f;
		g_aPlayer[0].move.y += cosf(D3DX_PI) * 0.44f;
	}
	else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN))
	{//S�L�[�������ꂽ
		g_aPlayer[0].move.x += sinf(D3DX_PI * 0.0f) * 0.44f;
		g_aPlayer[0].move.y += cosf(D3DX_PI * 0.0f) * 0.44f;
	}

	if (GetkeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_X) == true)
	{// �X�y�[�X�L�[�������ꂽ
		if (g_nTypeBullet == 0)
		{
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 1)
		{//2�Ԗڂ̋ʂ˂�

			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 6.0f, cosf(D3DX_PI * 0.5f) * 6.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 2)
		{//3�Ԓn�̗�
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.54f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.46f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 3)
		{//4�ԏo���̋ʐ�
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 4)
		{//5�ԃz�[���̍�
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 100.0f, cosf(D3DX_PI * 0.5f) * 100.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
	}

	int pTime = GetTime();
	if (pTime >= 1200)
	{
		g_bTime = true;
	}

	if (g_bTime == true)
	{
		if (GetkeyboardPress(DIK_J) == true || GetJoypadPress(JOYKEY_Y) == true)
		{//J�L�[�������ꂽ
			if (g_nTypeBullet == 5)
			{//6�Ԗڂ̗����}�X�^�[�X�p�[�N
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.5f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.52f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.48f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.54f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.46f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.56f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.44f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.51f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.49f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.53f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.47f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.55f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.45f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);

				g_aPlayer[0].nCountTimer++;
				if (g_aPlayer[0].nCountTimer >= 100)
				{
					g_bTime = false;
					SetTime(0);
				}
			}
		}
	}

	if (GetkeyboardTrigger(DIK_K) == true || GetJoypadTrigger(JOYKEY_B) == true)
	{//k�L�[�������ꂽ
		SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 10.0f, cosf(D3DX_PI * 0.5f) * 10.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
	}

	
	else if (GetkeyboardTrigger(DIK_L) == true || GetJoypadTrigger(JOYKEY_R1) == true)
	{//L�L�[�������ꂽ
		//�e�̐؂�ւ�
		g_nTypeBullet = (g_nTypeBullet + 1) % 6;
	}

	//�ʒu���X�V
	g_aPlayer[0].pos.x += g_aPlayer[0].move.x;
	g_aPlayer[0].pos.y += g_aPlayer[0].move.y;

	//�ړ��ʂ��X�V
	g_aPlayer[0].move.x += (0.0f - g_aPlayer[0].move.x) * 0.0793852f;				//������������ׂ���/8���^��
	g_aPlayer[0].move.y += (0.0f - g_aPlayer[0].move.y) * 0.0793852f;				//���[�����܂����[/ 9��29��

	if (g_aPlayer[0].pos.y >= SCREEN_HEIGHT - 20.0f)
	{//����(��ʉ�����ʒ[)
		g_aPlayer[0].pos.y = SCREEN_HEIGHT - 20.0f;
	}
	else if (g_aPlayer[0].pos.y <= 0 + 20.0f)
	{//�㋴(��ʏ㌓��ʒ[)
		g_aPlayer[0].pos.y = 0 + 20.0f;
	}

	if (g_aPlayer[0].pos.x >= SCREEN_WIDTH - 800.0f)
	{//�~�M�[��(��ʉE����ʒ[)
		g_aPlayer[0].pos.x = SCREEN_WIDTH - 800.0f;
	}
	else if (g_aPlayer[0].pos.x <= 0 + 25.0f)
	{//����(��ʍ�����ʒ[)
		g_aPlayer[0].pos.x = 0 + 25.0f;
	}

	
#ifdef _DEBUG
	//FPS�̕\��
	if (GetkeyboardTrigger(DIK_RETURN) == true)
	{
		HitPlayer(1);
		
		HitLife();
	}
	if (GetkeyboardTrigger(DIK_Y) == true)
	{
		AddPlayer(1);
		
		SetLife();
	}
#endif

	//���_���W�̐ݒ�
	pVtx[0].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.z = 0.0f;

	switch (g_aPlayer[0].state)
	{
	case PLAYERSTATE_NORMAL:

		/*�ύX�Ȃ�*/

		break;

	case PLAYERSTATE_DAMAGE:

		g_aPlayer[0].nCounterState--;

		if (g_aPlayer[0].nCounterState <= 0)
		{//�G�����̗̑͂�0�ȏ�̂Ƃ�
			g_aPlayer[0].state = PLAYERSTATE_NORMAL;					//�G������ʏ��Ԃɂ���

			//���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}
		break;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPlayer->Unlock();
}

//-----------------
//�h���h�̕`�揈��
//-----------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	//�f���@�C�X�̎擾
	pDevice = GetDevice();
	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexturePlayer);

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//�|���S���̕`��
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//---------------------
//���C�t�̑����鏈��
//---------------------
void AddPlayer(int nAdd)
{
	g_aPlayer[0].nPlayerLife += nAdd;
}

//---------------------
//�I���̃q�b�g����
//---------------------
void HitPlayer(int nDamage)
{
	int nCountPlayer = 0;
	g_aPlayer[0].nPlayerLife -= nDamage;
	if (g_aPlayer[0].nPlayerLife <= 0)
	{//�v���C���[�̗̑͂��Ȃ��Ȃ����Ƃ�
		SetExplosion(g_aPlayer[0].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aPlayer[0].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
		FADE pFade = GetFade();
		if (g_aPlayer[0].nPlayerLife <= 0 && pFade == FADE_NONE)
		{
			SetFade(MODE_RESULT);
		}
	}
	else
	{
		VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCountPlayer * 4;						//�f�[�^�ɍ��킹�����l���i��

		g_aPlayer[0].state = PLAYERSTATE_DAMAGE;
		g_aPlayer[0].nCounterState = 5;					//�_���[�W��Ԃ�ۂ���

															//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffPlayer->Unlock();
	}
}

//-----------------
//�����Ă���P
//-----------------
Player *GetPlayer(void)
{
	return &g_aPlayer[0];
}