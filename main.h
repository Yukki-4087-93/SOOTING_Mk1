//-----------------------------------------------------------------------------------------------------------
//
//���������C��������hwwwww
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _MAIN_H_																	//���̃}�N����`���Ȃ���Ȃ�������
#define _MAIN_H_																	//��d�C���N���[�h�h�~�̃}�N����`

#include<Windows.h>
#include"d3dx9.h"
#define DIRECTINPUT_VERSION		(0X0800)											//�r���h���̌x���Ή��p�}�N��
#include"dinput.h"
#include"xaudio2.h"
#include"xinput.h"

//-----------------------------
//���C�u�����̃����N�X�����O�X
//-----------------------------
#pragma comment(lib,"d3d9.lib")														//�`�揈���ɕK�{
#pragma comment(lib,"d3dx9.lib")													//d3d9.lib�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")													//DirectX�R���|�[�l���g�g�p�ɕK�{
#pragma comment(lib,"winmm.lib")													//�V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")													//���͏����ɕK�{
#pragma comment(lib,"xinput.lib")

//-----------
//�}�N����`
//-----------
#define SCREEN_WIDTH		(1280)													//�E�B���h�E�̕�
#define SCREEN_HEIGHT		(720)													//�E�B���h�E�̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				//���_���W�ƒ��_�L�����[																	//�~������

//-------------------------
//���_���W[2D]�̍\���̒�`
//-------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//���_���W
	float rhw;				//���W�����p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;			//���_�J���[
	D3DXVECTOR2 tex;		//�e�N�X�`���̍��W
}VERTEX_2D;

//--------------------------
//���(���[�h)�̎��
//--------------------------
typedef enum 
{
	MODE_TITLE = 0,				//�Q�[���^�C�g��
	MODE_GAME,					//�Q�[�����
	MODE_RESULT,				//���U���g���
	MODE_RANKING,				//�����L���O���
	MODE_MAX
}MODE;

//-----------------
//�v���g�^�C�v�錾
//-----------------
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif // !_MAIN_H_
