//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BATTLEBAN = 0,				// BGM0
	SOUND_LABEL_LAST_MEETING,				// BGM1
	SOUND_LABEL_RESULT_BGM,					// BGM2
	SOUND_LABEL_OP,							// BGM3
	SOUND_LABEL_BATTLEMEETING_VER_2,		// BGM4  challenge_to_tomorrow
	SOUND_LABEL_NO_NAME,					// BGM5
	SOUND_LABEL_CHALLENGE_TO_TOMORROW,		// BGM6
	SOUND_LABEL_BATTLEMEETING,				// BGM7
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
