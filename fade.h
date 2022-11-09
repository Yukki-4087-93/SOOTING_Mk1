//--------------------------------------------------------------------
//
//�z���C�g�t�F�U�[����
//Author;takanoooooooooooooooooooooooooooooooooooooooooooooooooooo
//
//-------------------------------------------------------------------
#ifndef _FADE_H_
#define _FADE_H_

#include "main.h"

//----------------
//�t�F�[�_�̏��
//----------------
typedef enum
{
	FADE_NONE = 0,
	FADE_IN,
	FADE_OUT,
	FADE_MAX
}FADE;

//-----------------
//�v���g�^�C�v�錾
//-----------------
void InitFade(MODE modeNext);
void UninitFade(void);
void UpdateFade(void);
void DrawFade(void);

void SetFade(MODE modeNext);

FADE GetFade(void);

#endif // !_FADE_H_

