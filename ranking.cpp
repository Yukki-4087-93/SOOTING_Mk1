//----------------------------------------------------------------------------------------
//
//�����L���O
//Author;takano
//
//----------------------------------------------------------------------------------------
#include"ranking.h"
#include"score.h"
#include"fade.h"
#include"input.h"
#include"sound.h"

//----------------------
//�}�N����`
//----------------------
#define RANK_H				(80)								//�c��
#define RANK_WD				(50)								//����

//--------------------------
//�O���[�o���ϐ�
//--------------------------
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;						//�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;					//���_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;				//���_�o�b�t�@�ւ̃|�C���^
RankScore g_aRankScore[MAX_RANK];								//�����L���O�X�R�A���
int g_nRankUpdate = -1;											//�X�V�����NNo.
int g_nCountState = 0;											//�����L���O�X�R�A�̏�ԃJ�E���^�[
int g_nScoreState = 0;											//�����L���O�X�R�A�̏�ԏ��

//------------------------
//�����L���O�̏���������
//------------------------
void InitRanking(void)
{
	int nCountRank,nRankScore;

	LPDIRECT3DDEVICE9 pDevice;						//�f�o�C�X�̃|�C���^

	int aPosTexU[MAX_RANK][MAX_SCORE];

	//�f���@�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank, NULL);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//ranking_rank.png", &g_pTextureRank);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//number000.png", &g_pTextureRankScore);

	for (nCountRank = 0; nCountRank < MAX_RANK ; nCountRank++)
	{
		g_aRankScore[nCountRank].pos.x = 350.0f;
		g_aRankScore[nCountRank].pos.y = 200.0f;
		g_aRankScore[nCountRank].pos.z = 0.0f;
		g_aRankScore[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankScore = 0; nRankScore < MAX_RANK; nRankScore++)
	{
		for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
		{
			//���_���W�̐ݒ�
			pVtx[0].pos.x = g_aRankScore[nRankScore].pos.x + (RANK_WD * nCountRank);
			pVtx[0].pos.y = g_aRankScore[nRankScore].pos.y + (RANK_H * nRankScore);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankScore[nRankScore].pos.x + RANK_WD + (RANK_WD * nCountRank);
			pVtx[1].pos.y = g_aRankScore[nRankScore].pos.y + (RANK_H * nRankScore);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankScore[nRankScore].pos.x + (RANK_WD * nCountRank);
			pVtx[2].pos.y = g_aRankScore[nRankScore].pos.y + RANK_H +(RANK_H * nRankScore);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankScore[nRankScore].pos.x + RANK_WD + (RANK_WD * nCountRank);
			pVtx[3].pos.y = g_aRankScore[nRankScore].pos.y + RANK_H + (RANK_H * nRankScore);
			pVtx[3].pos.z = 0.0f;

			//rhw�̐ݒ�
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aRankScore[nRankScore].col;
			pVtx[1].col = g_aRankScore[nRankScore].col;
			pVtx[2].col = g_aRankScore[nRankScore].col;
			pVtx[3].col = g_aRankScore[nRankScore].col;

			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 1.0f);

			pVtx += 4;				//�f�f�f�[�^��4���i��
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(100.0f,200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(200.0f,200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f,600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(200.0f,600.0f, 0.0f);

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
	
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRank->Unlock();

	//�T�E���h�̍Đ�
	PlaySound(SOUND_LABEL_OP);

}

//------------------------
//�����L���O�̏I������
//------------------------
void UninitRanking(void)
{
	//�T�E���h�̒�~
	StopSound();

	//�e�N�X�`���̔j��
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}


	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}

//------------------------
//�����L���O�̍X�V����
//------------------------
void UpdateRanking(void)
{
	int nCountRank;
	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	if (g_nRankUpdate != -1)
	{
		g_aRankScore[g_nRankUpdate].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_nCountState++;
		if (g_nCountState % 4 == 0)
		{
			g_nScoreState ^= 1;
			g_aRankScore[g_nRankUpdate].col.a = (1.0f * g_nScoreState);
		}
		pVtx += MAX_SCORE * g_nRankUpdate * 4;				//�f�f�f�[�^��4���i��

		for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
		{
			//���_�J���[�̐ݒ�
			pVtx[0].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[1].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[2].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[3].col = g_aRankScore[g_nRankUpdate].col;

			pVtx += 4;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();

	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//����L�[(ENTER)�������ꂽ���ǂ���
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//���[�h�̐ݒ�
			SetFade(MODE_TITLE);
		}
	}
}

//------------------------
//�����L���O�̕`�揈��
//------------------------
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCountRank;//, nRankScore;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRank);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,								//�`�悷��ŏ��̒��_�C���f�b�N�X
		2);											//�|���S����

//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureRankScore);
	for (nCountRank = 0; nCountRank < MAX_SCORE * MAX_RANK; nCountRank++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);											//�|���S����
	}
}

//------------------------
//�����L���O�̃��Z�}��
//------------------------
void ResetRanking(void)
{
	//�����L���O�̏����X�R�A
	g_aRankScore[0].nScore = 16500;

	g_aRankScore[1].nScore = 10200;

	g_aRankScore[2].nScore = 9500;

	g_aRankScore[3].nScore = 8100;

	g_aRankScore[4].nScore = 4300;
}

//---------------------------
//�����L���O�̃Z�b�g
//---------------------------
void SetRanking(int nScore)
{
	int aPosTexU[MAX_SCORE];
	int nRankScore,nCountRankScore;
	int nScore1, nScore2, nScore3 = 0;

	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		for (nScore1 = 0; nScore1 < MAX_RANK -1; nScore1++)
		{
			for (nScore2 = nScore1 + 1; nScore2 < MAX_RANK; nScore2++)
			{
				if (g_aRankScore[nScore1].nScore > g_aRankScore[nScore2].nScore)
				{
					nScore3 = g_aRankScore[nScore1].nScore;
					g_aRankScore[nScore1].nScore = g_aRankScore[nScore2].nScore;
					g_aRankScore[nScore2].nScore = nScore3;
				}
			}
		}
		
	}

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankScore = 0; nRankScore < MAX_RANK; nRankScore++)
	{
		aPosTexU[0] = g_aRankScore[nRankScore].nScore % 100000 / 10000;
		aPosTexU[1] = g_aRankScore[nRankScore].nScore % 10000 / 1000;
		aPosTexU[2] = g_aRankScore[nRankScore].nScore % 1000 / 100;
		aPosTexU[3] = g_aRankScore[nRankScore].nScore % 100 / 10;
		aPosTexU[4] = g_aRankScore[nRankScore].nScore % 10;

		for (nCountRankScore = 0; nCountRankScore < MAX_SCORE; nCountRankScore++)
		{
			//�e�N�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRankScore] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRankScore] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRankScore] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRankScore] * 0.1f), 1.0f);

			pVtx += 4;				//�f�f�f�[�^��4���i��
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffRankScore->Unlock();
}

//---------------------------
//�����L���O�̏��擾
//---------------------------
int GetRanking(void)
{
	return g_nRankUpdate;
}