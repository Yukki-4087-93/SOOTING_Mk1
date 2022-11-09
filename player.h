//-----------------------------------------------------------------------------------------------------------
//
//動かないでくれ・P処理
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#ifndef _PLAYER_H_													//このマクロ定義がなされなっかたら
#define _PLAYER_H_													//二重インクルード防止のマクロ定義

#include"main.h"

//-----------
//マクロ定義
//-----------
#define MAX_PLAYER			(1)							//プレイヤーの最大人数
#define HI_PLAYER			(35)						//プレイヤーの高さ
#define WD_PLAYER			(35)						//プレイヤーの幅
#define MINUS_PLAYERSIZE	(30)						//プレイヤーの当たり判定の際に引くプレイヤーのサイズ

//-----------------------
//敵ちゃんの状態
//-----------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,				//通常状態
	PLAYERSTATE_DAMAGE,					//ダメージ状態
	PLAYERSTATE_MAX
}PLAYERSTATE;

//-----------------------
//俺の構造体の定義
//-----------------------
typedef struct
{
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 move;							//移動量
	D3DXVECTOR3 rot;							//プレイヤー向き
	PLAYERSTATE state;							//状態
	int nCounterState;							//状態管理カウンター
	int nCountTimer;							//魂射出！時間
	int nPlayerLife;							//ライフ
	float fLength;								//対角線のロングレンジ
	float fAngle;								//対角線のティンダロスの猟犬
	bool bUse;									//わたしゃが使用中か否か
}Player;


//-----------------
//プロトタイプ宣言
//-----------------
void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
void AddPlayer(int nAdd);
void HitPlayer(int nDamage);
Player *GetPlayer(void);

#endif // !PLAYER_H_
