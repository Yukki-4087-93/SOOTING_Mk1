//------------------------------------------------------------
//
//�^�C�����
//Author;takanoooooooooooooooooooooo
//
//------------------------------------------------------------
#include"time.h"

//---------------
//�O���[�o���ϐ�
//---------------
int g_nTime;													//��������
int g_nEnemyTime;
int g_nEnmBulletTime;
int g_nBossTime;
int g_nOpenMyHart;

//---------------------
//�������ނ̏���������
//---------------------
void InitTime(void)
{
	g_nTime = 0;												//�l��������
	g_nEnemyTime = 0;											//�l��������
	g_nEnmBulletTime = 0;
	g_nBossTime = 0;											//�l��������
	g_nOpenMyHart = 0;
}

//-------------
//T�̏I������
//-------------
void UninitTime(void)
{
	
}

//-------------------
//�������ނ̍X�V����
//-------------------
void UpdateTime(void)
{

}

//----------------
//Time�̕`�揈��
//----------------
void DrawTime(void)
{
	
}

//----------------
//taim�̐ݒ菈��
//----------------
void SetTime(int nTime)
{
	g_nTime = nTime;
}

//----------------
//taim�̐ݒ菈��2
//----------------
void SetEnemyTime(int nEnemyTime)
{
	g_nEnemyTime = nEnemyTime;
}

//----------------
//taim�̐ݒ菈��3
//----------------
void SetEnmBulletTime(int nEnmBulletTime)
{
	g_nEnmBulletTime = nEnmBulletTime;
}

//----------------
//taim�̐ݒ菈��4
//----------------
void SetBossTime(int nBossTime)
{
	g_nBossTime = nBossTime;
}

//----------------
//taim�̐ݒ菈��5
//----------------
void SetLastHart(int nOpenMyHart)
{
	g_nOpenMyHart = nOpenMyHart;
}

//----------------
//taim�̉��Z����
//----------------
void AddTime(int nValue)
{
	g_nTime += nValue;
	g_nEnemyTime += nValue;
	g_nEnmBulletTime += nValue;
	g_nBossTime += nValue;
	g_nOpenMyHart += nValue;
}

//------------------
//�^�C���i�Q�b�g
//------------------
int GetTime(void)
{
	return g_nTime;
}

//------------------
//�G�l�~�i�Q�b�g
//------------------
int GetEnenyTime(void)
{
	return g_nEnemyTime;
}

//------------------
//�G�l�~�i�Q�b�g
//------------------
int GetEnmBulletTime(void)
{
	return g_nEnmBulletTime;
}

//------------------
//�{�X�i�Q�b�g
//------------------
int GetBossTime(void)
{
	return g_nBossTime;
}

//--------------------
//���X�g�V���b�g
//--------------------
int GetOpenMyHart(void)
{
	return g_nOpenMyHart;
}