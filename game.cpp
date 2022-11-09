//-----------------------------------------------------------------------------------------
//
//	�Q�[�����
//	Author;takanoooooooooooooooooooooooooooooooooooooooo
//
//-----------------------------------------------------------------------------------------
#include"input.h"
#include"player.h"
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"score.h"
#include"sound.h"
#include"time.h"
#include"bg.h"
#include"fade.h"
#include"effect.h"
#include"pause.h"
#include"pop.h"
#include"boss.h"
#include"life.h"

//---------------------------
//�O���[�o���ϐ�
//---------------------------
bool g_bPause = false;

//---------------------------
//�Q�[����ʂ̏�����
//---------------------------
void InitGame(void)
{
	InitBG();					//�w�i�̏�����
	InitPause();				//�|�[�Y�̏�����
	InitEffect();
	InitTime();					//�^�C���̏���������
	SetTime(0);					//�����ނ�����
	SetEnemyTime(0);			//�����ސޓ�
	SetEnmBulletTime(0);
	SetBossTime(0);
	SetLastHart(0);
	InitScore();				//�X�R�A�̏���������
	SetScore(0);				//�X�R�A������
	InitBullet();				//�e�̏���������
	InitLife();
	InitPlayer();				//�v���C���[�̏���������
	InitEnemy();				//�G�����̏�����
	InitBoss();
	InitPop();
	InitExplosion();			//�����̏�����
	g_bPause = false;
//	PlaySound(SOUND_LABEL_BATTLEMEETING_VER_2);
}

//---------------------------
//�Q�[����ʂ̏I������
//---------------------------
void UninitGame(void)
{
	//StopSound();
	UninitBG();				//�I������(�w�i)
	UninitScore();			//�I������(�X�R�A)
	UninitBullet();			//�I�������i�e�j
	UninitEffect();
	UninitEnemy();			//�I�������i�G�����j
	UninitBoss();
	UninitLife();
	UninitPlayer();			//�I�������i�v���C���[�j
	UninitExplosion();		//�I�������i�����j
	UninitPause();
}

//---------------------------
//�Q�[����ʂ̍X�V����
//---------------------------
void UpdateGame(void)
{
	if (GetkeyboardTrigger(DIK_P) == true || GetJoypadTrigger(JOYKEY_STRTE) == true || GetJoypadTrigger(JOYKEY_BACK) == true)
	{//P�L�[�Ƃ��̑�������낪�����ꂽ
		g_bPause = g_bPause ? false : true;
	}

	if (g_bPause == false)
	{
		UpdateBG();					//BackGround�̍X�V����
		UpdateScore();				//Score�̍X�V����
		UpdateLife();
		UpdatePlayer();				//player�̍X�V����
		UpdateEnemy();				//Enemy�̍X�V����
		UpdateBoss();				//�{�X�̍X�V
		UpdatePop();				//�G�o���̍X�V
		UpdateExplosion();			//Explosion�̍X�V����
		UpdateBullet();				//Bullet�̍X�V����
		UpdateEffect();
		AddTime(1);					//Time�̉��Z����
		int pTime = GetTime();		//�^�C���̂�����������������
		/*if (pTime >= 9360)
		{
			SetFade(MODE_RESULT);
		}*/
	}

	else if (g_bPause == true)
	{
		UpdatePause();
	}
}

//---------------------------
//�Q�[����ʂ̕`��
//---------------------------
void DrawGame(void)
{
	DrawBG();					//�w�i�̕`�揈��
	DrawScore();				//�X�R�A�̕`�揈��
	DrawEnemy();				//�G�����̕`�揈��
	DrawBoss();
	DrawPlayer();				//�v���C���[�̕`�揈��
	DrawLife();
	DrawBullet();				//�e�̕`�揈��
	DrawEffect();
	DrawExplosion();			//�����`�揈��
	if (g_bPause == true)
	{//�|�[�Y�Ȃ�
		DrawPause();
	}
}

//---------------------------
//�|�[�Y�̗L�����ۂ���ݒ�
//---------------------------
void SetEnablePause(bool bPause)
{
	g_bPause = bPause;
}