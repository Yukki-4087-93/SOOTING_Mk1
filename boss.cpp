//------------------------------------------------------
//
//BOSS
//Author;takano
//
//------------------------------------------------------
#include"boss.h"
#include"bullet.h"
#include"time.h"
#include"score.h"
#include"explosion.h"
#include"fade.h"
#include"sound.h"

//---------------
//グローバル変数
//---------------
LPDIRECT3DTEXTURE9 g_apTextureBoss = NULL;						//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBoss = NULL;											//頂点バッファのポインタ
Boss g_aBoss[MAX_BOSS];
int g_nAliveBoss;

//---------------------
//BOSSの初期化
//---------------------
void InitBoss(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_BOSS,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBoss, NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//AGE.png", &g_apTextureBoss);
	
	//ボスの初期化
	for (int nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		g_aBoss[nCntBoss].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心の位置
		g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBoss[nCntBoss].nType = 0;
		g_aBoss[nCntBoss].nPattern = 0;
		g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;
		g_aBoss[nCntBoss].nCounterState = 0;
		g_aBoss[nCntBoss].nLife = 2500;
		g_aBoss[nCntBoss].bUse = false;								//使用してない状態にする
	}

	for (int nCnt = 0; nCnt < MAX_BOSS; nCnt++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x - BOSS_HISIZE, g_aBoss[nCnt].pos.y - BOSS_WDSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x + BOSS_HISIZE, g_aBoss[nCnt].pos.y - BOSS_WDSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x - BOSS_HISIZE, g_aBoss[nCnt].pos.y + BOSS_WDSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCnt].pos.x + BOSS_HISIZE, g_aBoss[nCnt].pos.y + BOSS_WDSIZE, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBoss->Unlock();
}

//---------------------
//BOSSの終了処理
//---------------------
void UninitBoss(void)
{

	//テクスチャの破棄
	if (g_apTextureBoss != NULL)
	{
		g_apTextureBoss->Release();
		g_apTextureBoss = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBoss != NULL)
	{
		g_pVtxBuffBoss->Release();
		g_pVtxBuffBoss = NULL;
	}
}

//---------------------
//BOSSの更新
//---------------------
void UpdateBoss(void)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == true)
		{
			int pTime = GetBossTime();
			g_aBoss[nCntBoss].pos += g_aBoss[nCntBoss].move;
			if (g_aBoss[nCntBoss].pos.x <= 230.0f)
			{
				g_aBoss[nCntBoss].pos.x = 1030.0f;
				g_aBoss[nCntBoss].move.x = 0.0f;
			}

			if (pTime % 60 == 0)
			{
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.54f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.46f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.51f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.49f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.53f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.47f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.55f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.45f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.59f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.39f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.58f) * 10.0f, 0.0f), 0, 0, 2);
				SetBullet(g_aBoss[nCntBoss].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.38f) * 10.0f, 0.0f), 0, 0, 2);

			}
			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBoss * 4;						//デデデータに合わせた数値分進む

														//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);

			switch (g_aBoss[nCntBoss].state)
			{
			case BOSSSTATE_NORMAL:

				break;

			case BOSSSTATE_DAMAGE:

				g_aBoss[nCntBoss].nCounterState--;

				if (g_aBoss[nCntBoss].nCounterState <= 0)
				{//BOSSの体力が0以上のとき
					g_aBoss[nCntBoss].state = BOSSSTATE_NORMAL;						//敵ちゃんを通常状態にする

																					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffBoss->Unlock();
		}
	}
}

//---------------------
//BOSSの描画処理
//---------------------
void DrawBoss(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	for (int i = 0; i < MAX_BOSS; i++)
	{
		if (g_aBoss[i].bUse == true)
		{//BOSSが使用されている

			//頂点バッファをデータストリームに設定
			pDevice->SetStreamSource(0, g_pVtxBuffBoss, 0, sizeof(VERTEX_2D));

			//頂点フォーマット
			pDevice->SetFVF(FVF_VERTEX_2D);


			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureBoss);
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				i * 4,						//描画する最初の頂点インデックス
				2);									//ポリゴン数
		}
	}
	
}

//---------------------
//BOSSの置き場所
//---------------------
void SetBoss(D3DXVECTOR3 pos, int nType, int nPattern)
{
	int nCntBoss;

	for (nCntBoss = 0; nCntBoss < MAX_BOSS; nCntBoss++)
	{
		if (g_aBoss[nCntBoss].bUse == false)
		{//BOSSが使われていない
			g_aBoss[nCntBoss].pos = pos;				//BOSSの中心とマテリアルの中心を同じにする
			g_aBoss[nCntBoss].nType = nType;
			g_aBoss[nCntBoss].nPattern = nPattern;

			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBoss * 4;						//データに合わせた数値分進む

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y - BOSS_WDSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x - BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aBoss[nCntBoss].pos.x + BOSS_HISIZE, g_aBoss[nCntBoss].pos.y + BOSS_WDSIZE, 0.0f);

			if (nPattern == 0)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 1)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-20.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 2)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			}
			else if (nPattern == 3)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			}
			else if (nPattern == 4)
			{
				g_aBoss[nCntBoss].move = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			}

			g_aBoss[nCntBoss].nLife = 2500;
			g_aBoss[nCntBoss].bUse = true;			//使用している状態にする

			//頂点バッファをアンロックする
			g_pVtxBuffBoss->Unlock();
			break;
		}
	}
}

//---------------------
//BOSSのヒット
//---------------------
void HitBoss(int nCntBoss, int nDamage)
{
	g_aBoss[nCntBoss].nLife -= nDamage;
	if (g_aBoss[nCntBoss].nLife <= 0)
	{//BOSSの体力がなくなったとき
		SetExplosion(g_aBoss[nCntBoss].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_nAliveBoss--;
		FADE pFade = GetFade();
		if (g_nAliveBoss <= 0 && pFade == FADE_NONE)
		{
		SetFade(MODE_RESULT);
		}
		AddScore(10000);
		g_aBoss[nCntBoss].bUse = false;			//使用されていない状態にする
	}
	else
	{
		VERTEX_2D*pVtx;			//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffBoss->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntBoss * 4;						//データに合わせた数値分進む

		g_aBoss[nCntBoss].state = BOSSSTATE_DAMAGE;
		g_aBoss[nCntBoss].nCounterState = 5;				//ダメージ状態を保つ時間

															//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffBoss->Unlock();
	}

}

//--------------------
//BOSSの情報取得
//--------------------
Boss *GetBoss(void)
{
	return g_aBoss;
}

//--------------------
//BOSSの情報取得
//--------------------
int GetAliveBoss(void)
{
	return g_nAliveBoss;
}