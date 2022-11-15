//------------------------------------------------------------
//
//�e
//Author;takano
//
//------------------------------------------------------------
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"
#include"time.h"
#include"player.h"
#include"boss.h"
#include"life.h"

//---------------
//�O���[�o���ϐ�
//---------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;						//�e�N�X�`���̃|�C���^
LPDIRECT3DTEXTURE9 g_pTextureRunningman = NULL;					//�e�N�X�`���̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;				//���_�o�b�t�@�̃|�C���^
BULLET g_aBullet[MAX_BULLET];									//�e�̏��

//---------------
//�e�̏�����
//---------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//�f�o�C�X�̃|�C���^
	int nCntBullet;
	pDevice = GetDevice();					//�f�o�C�X�̎擾

	//�e�̏�����
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//���S�̈ʒu
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f,0.0f, 0.0f);		//�����̏�����
		g_aBullet[nCntBullet].nCounterTime = 0;							//�ˏo����
		g_aBullet[nCntBullet].nLife = 200;								//�e�̃��C�t
		g_aBullet[nCntBullet].nCounterAnim = 0;							//�A�j���[�V�����J�E���^�[�̏�����
		g_aBullet[nCntBullet].nPatternAnim = 0;							//�A�j���[�V�����p�^�[���̏�����
		g_aBullet[nCntBullet].bUse = false;								//�g�p���ĂȂ���Ԃɂ���
		g_aBullet[nCntBullet].nEp = 0;									//�����̏�����
		g_aBullet[nCntBullet].nTypeBullet = 0;							//����e�̏�����
		g_aBullet[nCntBullet].nPattern = 0;								//��ށi1.�G���G�A2.�{�X�j
	}

	//���_�o�b�t�@
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,				//*�̌�낪���_�̌�				
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̓ǂݍ��ݏ���
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTextureBullet);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//runningman000.png", &g_pTextureRunningman);
	
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);

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
	g_pVtxBuffBullet->Unlock();
}

//-------------
//�e�̏I��
//-------------
void UninitBullet(void)
{
	//�e�N�X�`���̔j��
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//�e�N�X�`���̔j��
	if (g_pTextureRunningman != NULL)
	{
		g_pTextureRunningman->Release();
		g_pTextureRunningman = NULL;
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//-------------
//�e�̍X�V
//-------------
void UpdateBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e���g�p����Ă���
			Enemy *pEnemy = GetEnemy();
			Boss *pBoss = GetBoss();
			EFFECT *pEffect = GetEffect();
			Player * pPlayer = GetPlayer();
			int nCntEnemy;
			int nCountBoss = 0;

			VERTEX_2D *pVtx;		//���_���ւ̃|�C���^

			//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBullet * 4;						//�f�[�^�ɍ��킹�����l���i��

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{//�G�l�~�[���g�p����Ă���
					if (g_aBullet[nCntBullet].nPattern == 0)
					{
						if (g_aBullet[nCntBullet].nTypeBullet == 0)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
							 //�G�l�~�[�̃q�b�g����
								HitEnemy(nCntEnemy, 120);

								g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 1)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - RUNNINGMAN_WIDTH &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + RUNNINGMAN_WIDTH &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - RUNNINGMAN_HEIGHT &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + RUNNINGMAN_HEIGHT)
							{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
							 //�G�l�~�[�̃q�b�g����
								HitEnemy(nCntEnemy, 45);

								g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 2)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
							 //�G�l�~�[�̃q�b�g����
								HitEnemy(nCntEnemy, 100);

								g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 3)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
							 //�G�l�~�[�̃q�b�g����
								HitEnemy(nCntEnemy, 20);

								g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

								pEffect->bUse = false;
							}
						}
						else
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//�G�l�~�[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������

							 //�G�l�~�[�̃q�b�g����
								HitEnemy(nCntEnemy, 150);

								g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

								pEffect->bUse = false;
							}
						}
					}
				}
			}

			if (pPlayer->bUse == true)
			{//�v���C���[���g�p����Ă���
				if (g_aBullet[nCntBullet].nPattern == 1)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 0)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - HI_PLAYER + MINUS_PLAYERSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + WD_PLAYER - MINUS_PLAYERSIZE + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - HI_PLAYER + MINUS_PLAYERSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + WD_PLAYER - MINUS_PLAYERSIZE + MYBULLET_SIZE)
						{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������

							//�v���C���[�̃q�b�g����
							HitPlayer(1);

							HitLife();

							g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
						}
					}
				}
			}

			if (pBoss->bUse == true)
			{//�v���C���[���g�p����Ă���

				if (g_aBullet[nCntBullet].nPattern == 2)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 0)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - HI_PLAYER - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + WD_PLAYER + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - HI_PLAYER - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + WD_PLAYER + MYBULLET_SIZE)
						{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������

							//�v���C���[�̃q�b�g����
							HitPlayer(1);

							HitLife();

							g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���
						}
					}
				}
				else if (g_aBullet[nCntBullet].nPattern == 0)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 1)
					{
						if (g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_HISIZE - RUNNINGMAN_WIDTH &&
							g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_HISIZE + RUNNINGMAN_WIDTH &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_WDSIZE - RUNNINGMAN_HEIGHT &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_WDSIZE + RUNNINGMAN_HEIGHT)
						{//�v���C���[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������
						 //�G�l�~�[�̃q�b�g����
							HitBoss(nCountBoss, 100);

							g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

							pEffect->bUse = false;
						}
					}
					else
					{
						if (g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_HISIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_HISIZE + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_WDSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_WDSIZE + MYBULLET_SIZE)
						{//�G�l�~�[�̒��S�ɃG�l�~�[�ƒe�̃T�C�Y�i�e�����j���{�[�����͈͂ɒe������������

						 //�G�l�~�[�̃q�b�g����
							HitBoss(nCountBoss, 5);

							g_aBullet[nCntBullet].bUse = false;			//�g�p����Ă��Ȃ���Ԃɂ���

							pEffect->bUse = false;
						}
					}
				}
			}
			

			//�e�̈ʒu�̍X�V
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].nTypeBullet == 0)
			{//����e
				g_aBullet[nCntBullet].nLife--;
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);

			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 2)
			{
				g_aBullet[nCntBullet].nLife--;
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 3)
			{
				g_aBullet[nCntBullet].nCounterTime++;
				if (g_aBullet[nCntBullet].nCounterTime == 27)
				{
					SetBullet(g_aBullet[nCntBullet].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * BULLET_SIZE, cosf(D3DX_PI * 0.75f) * BULLET_SIZE, 0.0f), g_aBullet[nCntBullet].nEp, g_aBullet[nCntBullet].nTypeBullet, 0);
					SetBullet(g_aBullet[nCntBullet].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * BULLET_SIZE, cosf(D3DX_PI * 0.25f) * BULLET_SIZE, 0.0f), g_aBullet[nCntBullet].nEp, g_aBullet[nCntBullet].nTypeBullet, 0);
				}
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 4)
			{
				g_aBullet[nCntBullet].nLife--;
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 5)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				g_aBullet[nCntBullet].nPatternAnim = (g_aBullet[nCntBullet].nPatternAnim + 1) % 8;

				//�e�L�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 1.0f);
			}
			else
			{
				//�e�L�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			if (g_aBullet[nCntBullet].pos.y <= 0.0f ||
				g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT ||
				g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH ||
				g_aBullet[nCntBullet].pos.x <= 0.0f)
			{//�e������ʒ[�𒴂���
				g_aBullet[nCntBullet].bUse = false;				//�g�p���Ă��Ȃ���Ԃɖ߂�
				pEffect->bUse = false;							//�g�p���Ă��Ȃ���Ԃɖ߂�

			}

			//�����̃J�E���g�_�E��
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//���i�͂��s����
				g_aBullet[nCntBullet].bUse = false;				//�g�p���ĂȂ���Ԃɖ߂��A�܂�A���[��
				pEffect->bUse = false;							//�g�p���Ă��Ȃ���Ԃɖ߂�
			}

			if (g_aBullet[nCntBullet].nPattern == 0)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 1)
				{
					Player * pPlayer = GetPlayer();
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(pPlayer[0].pos, D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f), EFFECT_RUNNINGMAN_SIZE, 5);
				}
				else if (g_aBullet[nCntBullet].nTypeBullet == 3)
				{
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
				else if (g_aBullet[nCntBullet].nTypeBullet == 5)
				{
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
				else
				{
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
			else if (g_aBullet[nCntBullet].nPattern == 1)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 0)
				{
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
			else if (g_aBullet[nCntBullet].nPattern == 2)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 0)
				{
					//�G�t�F�[�N�g�D�̃Z�b�g�A�b�v
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffBullet->Unlock();
		}
	}
}


//--------------
//�e�̕`��
//--------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//�e�򂪎g�p����Ă���
		 //�e�N�X�`���̐ݒ�
			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				pDevice->SetTexture(0, g_pTextureRunningman);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureBullet);
			}
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,						//�`�悷��ŏ��̒��_�C���f�b�N�X
				2);									//�|���S����
		}
	}
}

//---------------
//�e�̐ݒ�
//---------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nEp, int nTypeBullet, int nPattern)
{
	int nCntBullet;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//�e���g���Ă��Ȃ�
			g_aBullet[nCntBullet].pos = pos;			//�v���C���[�̒��S�ƃ}�e���A���̒��S�𓯂��ɂ���
			g_aBullet[nCntBullet].nTypeBullet = nTypeBullet;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 200;
			g_aBullet[nCntBullet].bUse = true;			//�g�p���Ă����Ԃɂ���
			g_aBullet[nCntBullet].nEp = nEp;
			g_aBullet[nCntBullet].nPattern = nPattern;
			pVtx += nCntBullet * 4;						//�f�f�f�[�^�ɍ��킹�����l���i��

			if (g_aBullet[nCntBullet].nTypeBullet == 0)
			{//����e
			 //���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);

			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 2)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 3)
			{
				g_aBullet[nCntBullet].nCounterTime = 0;							//�ˏo����
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 4)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 5)
			{
				//���_���W�̍X�V
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				g_aBullet[nCntBullet].nPatternAnim = (g_aBullet[nCntBullet].nPatternAnim + 1) % 8;

				//�e�L�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 1.0f);
			}
			else
			{
				//�e�L�X�`���̍��W�ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			break;
		}
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-----------------
//�|�C���^�̎擾
//-----------------
BULLET *GetBullet(void)
{
	return g_aBullet;
}