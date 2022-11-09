//------------------------------------------------------------
//
//�X�R�A�\��
//Author;takano
//
//------------------------------------------------------------
#include"score.h"

//------------------
//�X�^�e�B�b�N�ϐ�
//------------------
static LPDIRECT3DTEXTURE9 s_pTexture = NULL;							//�e�N�X�`���̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;						//���_�o�b�t�@�̃|�C���^
static D3DXVECTOR3 s_posScore;												//�X�R�A�̈ʒu
static int s_nScore;														//�X�R�A�̒l

//-------------------
//�X�R�A�̏���������
//-------------------
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//�f�o�C�X�̃|�C���^
	pDevice = GetDevice();					//�f�o�C�X�̎擾
	
	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//number000.png", &s_pTexture);
	
	//�X�R�A�̏�����
	s_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);					//�ʒu�̏�����
	s_nScore = 0;												//�l��������

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,				//*�̌�낪��
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D, 
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(s_posScore.x + (SCORE_WIDTH * nCountRank), s_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_posScore.x + SCORE_WIDTH + (SCORE_WIDTH * nCountRank), s_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(s_posScore.x + (SCORE_WIDTH * nCountRank), s_posScore.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_posScore.x + SCORE_WIDTH + (SCORE_WIDTH * nCountRank), s_posScore.y + SCORE_HEIGHT, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f; 
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//�f�[�^��4���i��
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//-----------------
//�X�R�A�̏I������
//-----------------
void UninitScore(void)
{
	//�e�N�X�`���̔j��
	if (s_pTexture != NULL)
	{
		s_pTexture->Release();
		s_pTexture = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//-------------------
//�X�R�A�̂̍X�V����
//-------------------
void UpdateScore(void)
{

}

//-----------------
//�X�R�A�̕`�揈��
//-----------------
void DrawScore(void)
{
	//�f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice;
	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, s_pTexture);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,								//�`�悷��ŏ��̒��_�C���f�b�N�X
			2);											//�|���S����
	}
}

//----------------
//�X�R�A�̐ݒ菈��
//----------------
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE];
	int nCountRank;

	s_nScore = nScore;

	aPosTexU[0] = s_nScore % 100000 / 10000;
	aPosTexU[1] = s_nScore % 10000 / 1000;
	aPosTexU[2] = s_nScore % 1000 / 100;
	aPosTexU[3] = s_nScore % 100 / 10;
	aPosTexU[4] = s_nScore % 10;

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 1.0f);

		pVtx += 4;				//�f�f�f�[�^��4���i��
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//----------------
//�X�R�A�̉��Z����
//----------------
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE];

	s_nScore += nValue;

	aPosTexU[0] = s_nScore % 100000 / 10000;
	aPosTexU[1] = s_nScore % 10000 / 1000;
	aPosTexU[2] = s_nScore % 1000 / 100;
	aPosTexU[3] = s_nScore % 100 / 10;
	aPosTexU[4] = s_nScore % 10;

	VERTEX_2D*pVtx;			//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//�e�N�X�`���̍��W�ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 1.0f);

		pVtx += 4;				//�f�[�^��4���i��
	}

	//���_�o�b�t�@���A�����b�N����
	s_pVtxBuff->Unlock();
}

//----------------------
//�X�R�A���̎擾
//----------------------
int GetScore(void)
{
	return s_nScore;
}