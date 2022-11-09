//------------------------------------------------------------
//
//�����Ⴂ�扽����Ă�̏���
//Author;takanoooooooooooooooooooooo
//
//------------------------------------------------------------
#include"effect.h"
#include"bullet.h"

//-----------
//�}�N����`
//-----------
#define	MAX_EFFECT			(6000)							//�u�̌��̉̎�

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_pTexEffect = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEffect = NULL;			//���_�o�b�t�@�̃|�C���^
EFFECT g_aEffect[MAX_EFFECT];								//�C�[�\�C�\�C�̏��

//-------------------------
//DNA�X�p�[�N�̏���������
//-------------------------
void InitEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//�f�o�C�X�̃|�C���^
	int nCntEffect;
	pDevice = GetDevice();					//�f���@�C�X�̎擾

	//���f�̏�����
	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		g_aEffect[nCntEffect].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�̈ʒu
		g_aEffect[nCntEffect].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����Ȃ��_P
		g_aEffect[nCntEffect].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//�F�̏�����
		g_aEffect[nCntEffect].fRadius = 0.0f;
		g_aEffect[nCntEffect].nLife = 0;
		g_aEffect[nCntEffect].bUse = false;								//�g�p���ĂȂ���Ԃɂ���
	}

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EFFECT,				//*�̌�낪���_�̌�				
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffEffect,
		NULL);

	VERTEX_2D *pVtx;

	//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//runningman000.png", &g_pTexEffect);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

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

		pVtx += 4;				//�f�f�f�[�^��4���i��
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffEffect->Unlock();
}

//---------------------
//�I�^�_�̏I������
//---------------------
void UninitEffect(void)
{
	//�e�N�X�`���̔j��
	if (g_pTexEffect != NULL)
	{
		g_pTexEffect->Release();
		g_pTexEffect = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffEffect != NULL)
	{
		g_pVtxBuffEffect->Release();
		g_pVtxBuffEffect = NULL;
	}
}

//----------------
//�M���̍X�V����
//----------------
void UpdateEffect(void)
{
	int nCntEffect;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//�G�t�F�N�g���g���Ă����Ƃ�

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

			//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEffect * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

			g_aEffect[nCntEffect].col += D3DXCOLOR(0.005f, 0.005f, 0.005f, 0.0f);

			pVtx[0].col = g_aEffect[nCntEffect].col;
			pVtx[1].col = g_aEffect[nCntEffect].col;
			pVtx[2].col = g_aEffect[nCntEffect].col;
			pVtx[3].col = g_aEffect[nCntEffect].col;

			//���a�̌��炷��
			g_aEffect[nCntEffect].fRadius -= 0.7891f;

			//���_���W�̐ݒ�
			
			pVtx[0].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y - g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x - g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEffect[nCntEffect].pos.x + g_aEffect[nCntEffect].fRadius, g_aEffect[nCntEffect].pos.y + g_aEffect[nCntEffect].fRadius, 0.0f);

			g_aEffect[nCntEffect].nPatternAnim = (g_aEffect[nCntEffect].nPatternAnim + 1) % 8;

			//�e�L�X�`���̍��W�ݒ�
			pVtx[0].tex = D3DXVECTOR2(g_aEffect[nCntEffect].nPatternAnim * 0.125f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(g_aEffect[nCntEffect].nPatternAnim * 0.125f + 0.125f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(g_aEffect[nCntEffect].nPatternAnim * 0.125f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(g_aEffect[nCntEffect].nPatternAnim * 0.125f + 0.125f, 1.0f);

			//���_�o�b�t�@���A�����b�N����

			g_pVtxBuffEffect->Unlock();

			g_aEffect[nCntEffect].nLife--;
			if (g_aEffect[nCntEffect].nLife <= 0)
			{//�G�t�F�N�g�̗̑͂��s����
				g_aEffect[nCntEffect].bUse = false;
			}
		}

	}
}

//--------------------------------
//Mr.���C�g�j���O�{���g�̕`�揈��
//--------------------------------
void DrawEffect(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntEffect;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffEffect, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTexEffect);

	//A�u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == true)
		{//���d���g�p����Ă���
		 //�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEffect * 4,							//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);										//�|���S����
		}
	}

	//A�u�����f�B���O�����ɖ߂�ze��
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//-------------------
//�G�W�\���̐ݒ菈��
//-------------------
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col, float fRadius, int nLife)
{
	int nCntEffect;

	for (nCntEffect = 0; nCntEffect < MAX_EFFECT; nCntEffect++)
	{
		if (g_aEffect[nCntEffect].bUse == false)
		{
			g_aEffect[nCntEffect].pos = pos;									//�v���C���[�̒��S�ƃ}�e���A���̒��S�𓯂��ɂ���
			g_aEffect[nCntEffect].col = col;									//�t�@�C�o�[�̐F
			g_aEffect[nCntEffect].fRadius = fRadius;
			g_aEffect[nCntEffect].nLife = nLife;
			g_aEffect[nCntEffect].bUse = true;

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

			//���_�o�b�t�@���R�b�N�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffEffect->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += nCntEffect * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			//���_���W�̐ݒ�
			pVtx[0].pos = pos;
			pVtx[1].pos = pos;
			pVtx[2].pos = pos;
			pVtx[3].pos = pos;

			//���_�o�b�t�@���A�����b�N����
			g_pVtxBuffEffect->Unlock();

			break;
		}
	}
}

//----------------------
//�G�t�F�N�g�̏��擾
//----------------------
EFFECT *GetEffect(void)
{
	return g_aEffect;
}