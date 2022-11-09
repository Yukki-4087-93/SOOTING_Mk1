//------------------------------------------------------------
//
//����
//Author;takano
//
//------------------------------------------------------------
#include"explosion.h"

//-----------
//�}�N����`
//-----------
#define	MAX_EXPLOSION			(128)									//���e�̍ő吔

//---------------
//�e�\���̂̒�`
//---------------
typedef struct
{
	D3DXVECTOR3 pos;													//�ʒu
	D3DXCOLOR col;														//�F����
	int nCounterAnim;													//�A�j���[�V�����J�E���^�[
	int nPatternAnim;													//�A�j���[�V�����J�E���^�[
	bool bUse;															//�������g�p�����ۂ�
}Explosion;

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_pTexExplosion = NULL;							//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;						//���_�o�b�t�@�̃|�C���^
Explosion g_aExplosion[MAX_EXPLOSION];									//�����̏��

//---------------
//�����̏�����
//---------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//�f�o�C�X�̃|�C���^
	int nCntExplosion;
	pDevice = GetDevice();					//�f�o�C�X�̎擾

	//�{�}�[�̏�����
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�̈ʒu
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);		//�F�̏�����
		g_aExplosion[nCntExplosion].nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[
		g_aExplosion[nCntExplosion].nPatternAnim = 0;							//�A�j���[�V�����p�^�[��
		g_aExplosion[nCntExplosion].bUse = false;								//�g�p���ĂȂ���Ԃɂ���
	}

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,				//*�̌�낪���_�̌�				
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//explosion000.png", &g_pTexExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;				//�f�f�f�[�^��4���i��
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffExplosion->Unlock();
}

//---------------------
//�����̏I��
//---------------------
void UninitExplosion(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexExplosion != NULL)
	{
		g_pTexExplosion->Release();
		g_pTexExplosion = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//----------------
//�����̍X�V
//----------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if (g_aExplosion[nCntExplosion].nCounterAnim % 8 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;

				VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

				//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
				g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += nCntExplosion * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

				//�e�L�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
				//���_�o�b�t�@���A�����b�N����
				g_pVtxBuffExplosion->Unlock();
			}

		}
	}
}

//-----------------------
//�����̕`��
//-----------------------
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//�|�p���g�p����Ă���
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�|���S����
		}
	}
}

//---------------
//�����̐ݒ�
//---------------
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//�e���g���Ă��Ȃ�
			g_aExplosion[nCntExplosion].pos = pos;									//�v���C���[�̒��S�ƃ}�e���A���̒��S�𓯂��ɂ���
			g_aExplosion[nCntExplosion].col = col;									//�����̐F
			g_aExplosion[nCntExplosion].nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[
			g_aExplosion[nCntExplosion].nPatternAnim = 0;							//�A�j���[�V�����p�^�[��

			VERTEX_2D *pVtx;

			//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntExplosion * 4;						//�f�[�^�ɍ��킹�����l���i��

			//���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 100.0f, g_aExplosion[nCntExplosion].pos.y - 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 100.0f, g_aExplosion[nCntExplosion].pos.y - 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 100.0f, g_aExplosion[nCntExplosion].pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 100.0f, g_aExplosion[nCntExplosion].pos.y + 100.0f, 0.0f);

			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aExplosion[nCntExplosion].bUse = true;			//�g�p���Ă����Ԃɂ���

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffExplosion->Unlock();
			break;
		}
	}
}