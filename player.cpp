//-----------------------------------------------------------------------------------------------------------
//
//プレイヤー
//Author;takanoooooooooooooooo
//
//-----------------------------------------------------------------------------------------------------------
#include"main.h"
#include"player.h"
#include"input.h"
#include"bullet.h"
#include"explosion.h"
#include"life.h"
#include"time.h"
#include"fade.h"

//---------------
//マクロ定義
//---------------
//#define MAX_LIFE			(20)							//プレイヤー最大ライフ

//---------------
//グローバル変数
//---------------
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点バッファのポインタ
Player g_aPlayer[MAX_PLAYER];						//俺たちの情報
int g_nEp;											//爆発
int g_nTypeBullet;									//特殊弾頭
bool g_bTime;										//お時間
bool g_bHart;

//------------------------
//”俺”の初期化処理
//------------------------
void InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	//デヴァイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_pTexturePlayer);

	g_aPlayer[0].pos = D3DXVECTOR3(200.0f, 400.0f, 0.0f);				//位置を初期化する
	g_aPlayer[0].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//移動量を初期化する
	g_aPlayer[0].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					//向きの初期化
	g_aPlayer[0].state = PLAYERSTATE_NORMAL;							//ステータスをノーマル（通常状態）に設定
	g_aPlayer[0].nCounterState = 0;										//状態カウンターの初期化
	g_aPlayer[0].nCountTimer = 0;										//タイマーの初期化
	g_aPlayer[0].nPlayerLife = 4;										//ライフ
	g_nEp = 0;															//爆発の初期化
	g_nTypeBullet = 0;													//特殊弾の初期化
	g_bTime = false;													//弾に使用されるタイマーの初期化
	g_bHart = false;													//弾の特殊タイマー（未使用）
	g_aPlayer[0].bUse = true;											//使用されているか否か
	for (int i = 0; i < g_aPlayer[0].nPlayerLife; i++)
	{
		SetLife();
	}

	//対角線の長さを算出する
	g_aPlayer[0].fLength = sqrtf(HI_PLAYER * HI_PLAYER + WD_PLAYER * WD_PLAYER) / 2.0f;

	//対角線の角度を算出する
	g_aPlayer[0].fAngle = atan2f(HI_PLAYER, WD_PLAYER);

	//頂点座標の設定
	pVtx[0].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.z = 0.0f;
	
	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	
	//テキスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//---------------------
//”俺”の終了処理
//---------------------
void UninitPlayer(void)
{
	//テクスチャの破棄
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}
}

//----------------
//”俺”の更新処理
//----------------
void UpdatePlayer(void)
{
	VERTEX_2D*pVtx;							//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (GetkeyboardPress(DIK_A) == true || GetJoypadPress(JOYKEY_LEFT) == true)
	{//Aキーが押された
		if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{//同時にWキーも押したとき
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.75f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.75f) * 0.44f;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{//Sキーが押された
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.25f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.25f) * 0.44f;
		}
		else
		{
			//移動量の更新
			g_aPlayer[0].move.x += sinf(-D3DX_PI * 0.5f) * 0.44f;
			g_aPlayer[0].move.y += cosf(-D3DX_PI * 0.5f) * 0.44f;
		}
	}
	else if (GetkeyboardPress(DIK_D) == true || GetJoypadPress(JOYKEY_RIGHT) == true)
	{//Dキーが押された
		if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
		{//同時にＤキーも押された
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.75f) * 0.44f;			
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.75f) * 0.44f;
		}
		else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN) == true)
		{//別同時にSキーも押された							  
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.25f) * 0.44f;
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.25f) * 0.44f;
		}
		else
		{//Ｄキーコングが押された
			g_aPlayer[0].move.x += sinf(D3DX_PI * 0.5f) * 0.44f;
			g_aPlayer[0].move.y += cosf(D3DX_PI * 0.5f) * 0.44f;
		}
	}
	else if (GetkeyboardPress(DIK_W) == true || GetJoypadPress(JOYKEY_UP) == true)
	{//Wキーが押された
		g_aPlayer[0].move.x += sinf(D3DX_PI) * 0.44f;
		g_aPlayer[0].move.y += cosf(D3DX_PI) * 0.44f;
	}
	else if (GetkeyboardPress(DIK_S) == true || GetJoypadPress(JOYKEY_DOWN))
	{//Sキーが押された
		g_aPlayer[0].move.x += sinf(D3DX_PI * 0.0f) * 0.44f;
		g_aPlayer[0].move.y += cosf(D3DX_PI * 0.0f) * 0.44f;
	}

	if (GetkeyboardTrigger(DIK_SPACE) == true || GetJoypadTrigger(JOYKEY_X) == true)
	{// スペースキーが押された
		if (g_nTypeBullet == 0)
		{
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 1)
		{//2番目の玉ねぎ

			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 6.0f, cosf(D3DX_PI * 0.5f) * 6.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 2)
		{//3番地の卵
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.54f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.46f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 3)
		{//4番出口の玉川
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 20.0f, cosf(D3DX_PI * 0.5f) * 20.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
		else if (g_nTypeBullet == 4)
		{//5番ホールの魂
			SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 100.0f, cosf(D3DX_PI * 0.5f) * 100.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
		}
	}

	int pTime = GetTime();
	if (pTime >= 1200)
	{
		g_bTime = true;
	}

	if (g_bTime == true)
	{
		if (GetkeyboardPress(DIK_J) == true || GetJoypadPress(JOYKEY_Y) == true)
		{//Jキーが押された
			if (g_nTypeBullet == 5)
			{//6番目の恋符マスタースパーク
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.5f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.52f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.48f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.54f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.46f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.56f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.44f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.51f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.49f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.53f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.47f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.55f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
				SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 30.0f, cosf(D3DX_PI * 0.45f) * 30.0f, 0.0f), g_nEp, g_nTypeBullet, 0);

				g_aPlayer[0].nCountTimer++;
				if (g_aPlayer[0].nCountTimer >= 100)
				{
					g_bTime = false;
					SetTime(0);
				}
			}
		}
	}

	if (GetkeyboardTrigger(DIK_K) == true || GetJoypadTrigger(JOYKEY_B) == true)
	{//kキーが押された
		SetBullet(g_aPlayer[0].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.5f) * 10.0f, cosf(D3DX_PI * 0.5f) * 10.0f, 0.0f), g_nEp, g_nTypeBullet, 0);
	}

	
	else if (GetkeyboardTrigger(DIK_L) == true || GetJoypadTrigger(JOYKEY_R1) == true)
	{//Lキーが押された
		//弾の切り替え
		g_nTypeBullet = (g_nTypeBullet + 1) % 6;
	}

	//位置を更新
	g_aPlayer[0].pos.x += g_aPlayer[0].move.x;
	g_aPlayer[0].pos.y += g_aPlayer[0].move.y;

	//移動量を更新
	g_aPlayer[0].move.x += (0.0f - g_aPlayer[0].move.x) * 0.0793852f;				//未完成だから細かく/8月某日
	g_aPlayer[0].move.y += (0.0f - g_aPlayer[0].move.y) * 0.0793852f;				//↑納得しましたー/ 9月29日

	if (g_aPlayer[0].pos.y >= SCREEN_HEIGHT - 20.0f)
	{//下橋(画面下兼画面端)
		g_aPlayer[0].pos.y = SCREEN_HEIGHT - 20.0f;
	}
	else if (g_aPlayer[0].pos.y <= 0 + 20.0f)
	{//上橋(画面上兼画面端)
		g_aPlayer[0].pos.y = 0 + 20.0f;
	}

	if (g_aPlayer[0].pos.x >= SCREEN_WIDTH - 800.0f)
	{//ミギー橋(画面右兼画面端)
		g_aPlayer[0].pos.x = SCREEN_WIDTH - 800.0f;
	}
	else if (g_aPlayer[0].pos.x <= 0 + 25.0f)
	{//左橋(画面左兼画面端)
		g_aPlayer[0].pos.x = 0 + 25.0f;
	}

	
#ifdef _DEBUG
	//FPSの表示
	if (GetkeyboardTrigger(DIK_RETURN) == true)
	{
		HitPlayer(1);
		
		HitLife();
	}
	if (GetkeyboardTrigger(DIK_Y) == true)
	{
		AddPlayer(1);
		
		SetLife();
	}
#endif

	//頂点座標の設定
	pVtx[0].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (-D3DX_PI + g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (D3DX_PI - g_aPlayer[0].fAngle)) * g_aPlayer[0].fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * -1.0f)) * g_aPlayer[0].fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = g_aPlayer[0].pos.x + sinf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.y = g_aPlayer[0].pos.y + cosf(g_aPlayer[0].rot.z + (g_aPlayer[0].fAngle * 1.0f)) * g_aPlayer[0].fLength;
	pVtx[3].pos.z = 0.0f;

	switch (g_aPlayer[0].state)
	{
	case PLAYERSTATE_NORMAL:

		/*変更なし*/

		break;

	case PLAYERSTATE_DAMAGE:

		g_aPlayer[0].nCounterState--;

		if (g_aPlayer[0].nCounterState <= 0)
		{//敵ちゃんの体力が0以上のとき
			g_aPlayer[0].state = PLAYERSTATE_NORMAL;					//敵ちゃんを通常状態にする

			//頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		}
		break;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();
}

//-----------------
//”俺”の描画処理
//-----------------
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	//デヴァイスの取得
	pDevice = GetDevice();
	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePlayer);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);
}

//---------------------
//ライフの増える処理
//---------------------
void AddPlayer(int nAdd)
{
	g_aPlayer[0].nPlayerLife += nAdd;
}

//---------------------
//オレのヒット処理
//---------------------
void HitPlayer(int nDamage)
{
	int nCountPlayer = 0;
	g_aPlayer[0].nPlayerLife -= nDamage;
	if (g_aPlayer[0].nPlayerLife <= 0)
	{//プレイヤーの体力がなくなったとき
		SetExplosion(g_aPlayer[0].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_aPlayer[0].bUse = false;			//使用されていない状態にする
		FADE pFade = GetFade();
		if (g_aPlayer[0].nPlayerLife <= 0 && pFade == FADE_NONE)
		{
			SetFade(MODE_RESULT);
		}
	}
	else
	{
		VERTEX_2D*pVtx;			//頂点情報へのポインタ

		//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
		g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCountPlayer * 4;						//データに合わせた数値分進む

		g_aPlayer[0].state = PLAYERSTATE_DAMAGE;
		g_aPlayer[0].nCounterState = 5;					//ダメージ状態を保つ時間

															//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffPlayer->Unlock();
	}
}

//-----------------
//げってぃんぐP
//-----------------
Player *GetPlayer(void)
{
	return &g_aPlayer[0];
}