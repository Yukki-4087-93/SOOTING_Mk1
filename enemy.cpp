//------------------------------------------------------
//
//エネミー
//Author;takano
//
//------------------------------------------------------
#include"explosion.h"
#include"enemy.h"
#include"score.h"
#include"fade.h"
#include"time.h"
#include"bullet.h"
#include"effect.h"

//---------------
//グローバル変数
//---------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[NUM_ENEMY] = { NULL, NULL, NULL, NULL };					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;													//頂点バッファのポインタ
Enemy g_aEnemy[MAX_ENEMY];																		//エネミーの情報
int g_nAliveEnemy;

//---------------------
//エネミーの初期化処理
//---------------------
void InitEnemy(void)
{
	LPDIRECT3DDEVICE9 pDevice;			//デバイスのポインタ

	int nCntEnemy;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_ENEMY,
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D, 
		D3DPOOL_MANAGED,
		&g_pVtxBuffEnemy, NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_apTextureEnemy[2]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//llllllll.png", &g_apTextureEnemy[3]);

	//エネミーのの初期化
	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心の位置
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].nPattern = 0;
		g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;
		g_aEnemy[nCntEnemy].nCounterState = 0;
		g_aEnemy[nCntEnemy].nLife = 0;
		g_aEnemy[nCntEnemy].bUse = false;								//使用してない状態にする
	}

	g_nAliveEnemy = 4;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);

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
	g_pVtxBuffEnemy->Unlock();
}

//---------------------
//エネミーのオワタ処理
//---------------------
void UninitEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < NUM_ENEMY; nCntEnemy++)
	{
		//テクスチャの破棄
		if (g_apTextureEnemy[nCntEnemy] != NULL)
		{
			g_apTextureEnemy[nCntEnemy]->Release();
			g_apTextureEnemy[nCntEnemy] = NULL;
		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
}

//-------------------
//エネミーの更新処理
//-------------------
void UpdateEnemy(void)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			g_aEnemy[nCntEnemy].pos += g_aEnemy[nCntEnemy].move;
			if (g_aEnemy[nCntEnemy].nPattern == 3)
			{
				int pEnmTime = GetEnenyTime();
				if (pEnmTime >= 460)
				{
					g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-5.0f, 0.0f, 0.0f);
					SetEnemyTime(0);
				}
			}
			else if (g_aEnemy[nCntEnemy].nPattern == 4)
			{
				int pTime = GetEnmBulletTime();
				if (pTime % 60 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f),0,0,1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.75f) * 10.0f, cosf(D3DX_PI * -0.75f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.25f) * 10.0f, cosf(D3DX_PI * -0.25f) * 10.0f, 0.0f), 0, 0, 1);
					
				}
				if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT * 0.68f)
				{//画面下の当たり判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
				else if (g_aEnemy[nCntEnemy].pos.y <= SCREEN_HEIGHT * 0.34f)
				{//画面上の当たり判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
			}
			else if (g_aEnemy[nCntEnemy].nPattern == 5)
			{
				int pTime = GetEnmBulletTime();
				if (pTime % 60 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 1);
				}
				if (g_aEnemy[nCntEnemy].pos.y <= 0 + ENEMY_SIZE)
				{//画面上の判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
				else if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - ENEMY_SIZE)
				{//画面下の判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
			}
			else if (g_aEnemy[nCntEnemy].nPattern == 6)
			{
				int pTime = GetEnmBulletTime();
				if (pTime % 60 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 1);

				}
				if (g_aEnemy[nCntEnemy].pos.y <= 0 + ENEMY_SIZE)
				{//画面上に当たったときの判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
				else if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - ENEMY_SIZE)
				{//画面下に当たったときの判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
			}
			else if (g_aEnemy[nCntEnemy].nPattern == 7)
			{
				int pTime = GetEnmBulletTime();
				if (pTime % 120 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.75f) * 10.0f, cosf(D3DX_PI * -0.75f) * 10.0f, 0.0f),0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.25f) * 10.0f, cosf(D3DX_PI * -0.25f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.625f) * 10.0f, cosf(D3DX_PI *  -0.625f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.375f) * 10.0f, cosf(D3DX_PI * -0.375f) * 10.0f, 0.0f), 0, 0, 1);

				}
				if (g_aEnemy[nCntEnemy].pos.y <= 0 + ENEMY_SIZE)
				{//画面上に当たったときの判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
				else if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - ENEMY_SIZE)
				{//画面下に当たったときの判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
			}
			else if (g_aEnemy[nCntEnemy].nPattern == 8)
			{
				int pTime = GetEnmBulletTime();
				if (pTime % 120 == 0)
				{
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.5f) * 10.0f, cosf(D3DX_PI * -0.5f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.75f) * 10.0f, cosf(D3DX_PI * -0.75f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.25f) * 10.0f, cosf(D3DX_PI * -0.25f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.625f) * 10.0f, cosf(D3DX_PI *  -0.625f) * 10.0f, 0.0f), 0, 0, 1);
					SetBullet(g_aEnemy[nCntEnemy].pos, D3DXVECTOR3(sinf(D3DX_PI * -0.375f) * 10.0f, cosf(D3DX_PI * -0.375f) * 10.0f, 0.0f), 0, 0, 1);
					//エフェクトのセットアップ
					SetEffect(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
				if (g_aEnemy[nCntEnemy].pos.y <= 0 + ENEMY_SIZE)
				{//画面上の当たり判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
				else if (g_aEnemy[nCntEnemy].pos.y >= SCREEN_HEIGHT - ENEMY_SIZE)
				{//画面下に当たったときの判定
					g_aEnemy[nCntEnemy].move.y *= -1.0f;
				}
			}

			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEnemy * 4;						//データに合わせた数値分進む

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);


			switch (g_aEnemy[nCntEnemy].state)
			{
			case ENEMYSTATE_NORMAL:


				break;

			case ENEMYSTATE_DAMAGE:

				g_aEnemy[nCntEnemy].nCounterState--;

				if (g_aEnemy[nCntEnemy].nCounterState <= 0)
				{//エネミーの体力が0以上のとき
					g_aEnemy[nCntEnemy].state = ENEMYSTATE_NORMAL;					//エネミーを通常状態にする

					//頂点カラーの設定
					pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
					pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				}
				break;
			}
			//頂点バッファをアンロックする
			g_pVtxBuffEnemy->Unlock();
		}
	}
}

//-------------------
//エネミーの描画処理
//-------------------
void DrawEnemy(void)
{
	//デバイスへのポインタ
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();
	int nCntEnemy;

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == true)
		{//弾薬が使用されている
		 //テクスチャの設定
			pDevice->SetTexture(0, g_apTextureEnemy[g_aEnemy[nCntEnemy].nType]);
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntEnemy * 4,						//描画する最初の頂点インデックス
				2);									//ポリゴン数
		}
	}
}

//----------------
//エネミーセット
//----------------
void SetEnemy(D3DXVECTOR3 pos, int nType, int nPattern)
{
	int nCntEnemy;

	for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		if (g_aEnemy[nCntEnemy].bUse == false)
		{//弾が使われていない
			g_aEnemy[nCntEnemy].pos = pos;				//プレイヤーの中心とマテリアルの中心を同じにする
			g_aEnemy[nCntEnemy].nType = nType;
			g_aEnemy[nCntEnemy].nPattern = nPattern;

			VERTEX_2D *pVtx;

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntEnemy * 4;						//デデデータに合わせた数値分進む

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y - ENEMY_MAXSIZE, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x - ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nCntEnemy].pos.x + ENEMY_MAXSIZE, g_aEnemy[nCntEnemy].pos.y + ENEMY_MAXSIZE, 0.0f);

			if (nPattern == 0)
			{
				g_aEnemy[nCntEnemy].nLife = 120;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 1)
			{
				g_aEnemy[nCntEnemy].nLife = 120;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-0.1f, 0.0f, 0.0f);
			}
			else if (nPattern == 2)
			{
				g_aEnemy[nCntEnemy].nLife = 120;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-2.0f, 0.0f, 0.0f);
			}
			else if (nPattern == 3)
			{
				g_aEnemy[nCntEnemy].nLife = 120;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-0.1f, 0.0f, 0.0f);
			}
			else if (nPattern == 4)
			{
				g_aEnemy[nCntEnemy].nLife = 120;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			}
			else if (nPattern == 5)
			{
				g_aEnemy[nCntEnemy].nLife = 200;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			}
			else if (nPattern == 6)
			{
				g_aEnemy[nCntEnemy].nLife = 200;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			}
			else if (nPattern == 7)
			{
				g_aEnemy[nCntEnemy].nLife = 200;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			}
			else if (nPattern == 8)
			{
				g_aEnemy[nCntEnemy].nLife = 200;
				g_aEnemy[nCntEnemy].move = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			}


			g_aEnemy[nCntEnemy].bUse = true;			//使用している状態にする

			//頂点バッファをアンロックする
			g_pVtxBuffEnemy->Unlock();
			break;
		}
	}
}

//---------------------
//エネミーのヒット処理
//---------------------
void HitEnemy(int nCntEnemy, int nDamage)
{
	g_aEnemy[nCntEnemy].nLife -= nDamage;
	if (g_aEnemy[nCntEnemy].nLife <= 0)
	{//エネミーの体力がなくなったとき
		SetExplosion(g_aEnemy[nCntEnemy].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		g_nAliveEnemy--;
		AddScore(100);
		g_aEnemy[nCntEnemy].bUse = false;			//使用されていない状態にする
	}
	else
	{
		VERTEX_2D*pVtx;			//頂点情報へのポインタ

		//頂点バッファをロックし、頂点情報へのポインタを取得
		g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += nCntEnemy * 4;						//データに合わせた数値分進む

		g_aEnemy[nCntEnemy].state = ENEMYSTATE_DAMAGE;
		g_aEnemy[nCntEnemy].nCounterState = 5;				//ダメージ状態を保つ時間
		
		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffEnemy->Unlock();
	}
	
}

//---------------
//デバイスの取得
//---------------
Enemy *GetEnemy(void)
{
	return &g_aEnemy[0];
}

//---------------
//デバイスの取得
//---------------
int GetAliveEnemy(void)
{
	return g_nAliveEnemy;
}