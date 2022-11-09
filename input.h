//-----------------------------------------------------------------------------------------------------------
//
//ボタン電池処理
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

#include "main.h"

//-----------------
//キーの種類
//-----------------
typedef enum
{
	JOYKEY_UP = 0,			//十字キー↑
	JOYKEY_DOWN,			//"""""↓
	JOYKEY_LEFT,			//＞＞＞←
	JOYKEY_RIGHT,			//＜＜＜→
	JOYKEY_STRTE,			//スタ-トぼったん
	JOYKEY_BACK,			//BLACKRX
	JOYKEY_LPUSH,			//Lトリガラ
	JOYKEY_RPUSH,			//ライトな鶏ガラ
	JOYKEY_L1,				//L1
	JOYKEY_R1,				//R1
	JOYKEY_L2,				//L2
	JOYKEY_R2,				//R2
	JOYKEY_A,				//Aボタン
	JOYKEY_B,				//Bボタン
	JOYKEY_X,				//Xボタン
	JOYKEY_Y,				//Yバトラー
	MAX_KEY
}JOYkey;

//-----------------
//プロトタイプ宣言
//-----------------
HRESULT Initkeyboard(HINSTANCE hInstance, HWND hWnd);
void Uninitkeyboard(void);
void Updatekeyboard(void);
bool GetkeyboardPress(int nkey);
bool GetkeyboardTrigger(int nkey);
HRESULT InitJoypad(void);
void UninitJoypad(void);
void UpdateJoypad(void);
bool GetJoypadPress(JOYkey key);
bool GetJoypadTrigger(JOYkey key);

#endif // !_INPUT_H_

