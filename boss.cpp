//------------------------------------------------------
//
//BOSS
//Author;takano
//
//------------------------------------------------------
#include"boss.h"
#include"bullet.h"
#include"time.h"
#include"score.h"
#include"explosion.h"
#include"fade.h"
#include"sound.h"

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_apTextureBoss = NULL;						//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;											//���_�o�b�t�@�̃|�C���^
Boss g_aBoss[MAX_BOSS];
int g_nAliveBoss;

//---------------------
//BOSS�̏�����
//---------------------
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//�f�o�C�X�̃|�C���^

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss, NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//AGE.png", &g_apTextureBoss);
	
	//�{�X�̏�����
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�̈ʒu
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].nPattern = 0;
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = 2500;
		g_aBoss[nCntBoss].bUse = false;								//�g�p���ĂȂ���Ԃɂ���
	}

	for (int nCnt = 0; nCnt < MAX_BOSS; nCnt++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x - BOSS_HISIZE, g_aBoss[nCnt].pos.y - BOSS_WDSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x + BOSS_HISIZE, g_aBoss[nCnt].pos.y - BOSS_WDSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x - BOSS_HISIZE, g_aBoss[nCnt].pos.y + BOSS_WDSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x + BOSS_HISIZE, g_aBoss[nCnt].pos.y + BOSS_WDSIZE, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//�e�L�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBoss->Unlock();
}

//---------------------
//BOSS�̏I������
//---------------------
void UninitBoss(void)
{

	//�e�N�X�`���̔j��
	if (g_apTextureBoss != NULL)
	{
		g_apTextureBoss->Release();
		g_apTextureBoss = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//---------------------
//BOSS�̍X�V
//---------------------
void UpdateBoss(void)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			int pTime = GetBossTime();
			g_aBoss[nCntBoss].pos += g_aBoss[nCntBoss].move;
			if (g_aBoss[nCntBoss].pos.x <= 230.0f)
			{
				g_aBoss[nCntBoss].pos.x = 1030.0f;
				g_aBoss[nCntBoss].move.x = 0.0f;
			}

			if (pTime % 60 == 0)
			{
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.54f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.46f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.51f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.49f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.53f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.47f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.55f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.45f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.59f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.39f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.58f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.38f) * 10.0f, 0.0f), 0, 0, 2);

			}
			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBoss * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

														//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);

			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:

				break;

			case BOSSSTATE_DAMAGE:

				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{//BOSS�̗̑͂�0�ȏ�̂Ƃ�
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;						//�G������ʏ��Ԃɂ���

																					//���_�J���[�̐ݒ�
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}
			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBoss->Unlock();
		}
	}
}

//---------------------
//BOSS�̕`�揈��
//---------------------
void DrawBoss(void)
{
	//�f�o�C�X�ւ̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	for (int i = 0; i < MAX_BOSS; i++)
	{
		if (g_aBoss[i].bUse == true)
		{//BOSS���g�p����Ă���

			//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
			pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

			//���_�t�H�[�}�b�g
			pDevice->SetFVF(FVF_VERTEX_2D);


			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureBoss);
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				i * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�|���S����
		}
	}
	
}

//---------------------
//BOSS�̒u���ꏊ
//---------------------
void SetBoss(D3DXVECTOR3 pos, int nType, int nPattern)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)
		{//BOSS���g���Ă��Ȃ�
			g_aBoss[nCntBoss].pos = pos;				//BOSS�̒��S�ƃ}�e���A���̒��S�𓯂��ɂ���
			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].nPattern = nPattern;

			VERTEX_2D *pVtx;

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBoss * 4;						//�f�[�^�ɍ��킹�����l���i��

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);

			if (nPattern == 0)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 1)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 2)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			}
			else if (nPattern == 3)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			}
			else if (nPattern == 4)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}

			g_aBoss[nCntBoss].nLife = 2500;
			g_aBoss[nCntBoss].bUse = true;			//�g�p���Ă����Ԃɂ���

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffBoss->Unlock();
			break;
		}
	}
}

//---------------------
//BOSS�̃q�b�g
//---------------------
void HitBoss(int nCntBoss, int nDamage)
{
	g_aBoss[nCntBoss].nLife -= nDamage;
	if (g_aBoss[nCntBoss].nLife <= 0)
	{//BOSS�̗̑͂��Ȃ��Ȃ����Ƃ�
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_nAliveBoss--;
		FADE pFade = GetFade();
		if (g_nAliveBoss <= 0 && pFade == FADE_NONE)
		{
		SetFade(MODE_RESULT);
		}
		AddScore(10000);
		g_aBoss[nCntBoss].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
	}
	else
	{
		VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntBoss * 4;						//�f�[�^�ɍ��킹�����l���i��

		g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
		g_aBoss[nCntBoss].nCounterState = 5;				//�_���[�W��Ԃ�ۂ���

															//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBoss->Unlock();
	}

}

//--------------------
//BOSS�̏��擾
//--------------------
Boss *GetBoss(void)
{
	return g_aBoss;
}

//--------------------
//BOSS�̏��擾
//--------------------
int GetAliveBoss(void)
{
	return g_nAliveBoss;
}