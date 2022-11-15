//------------------------------------------------------------
//
//弾
//Author;takano
//
//------------------------------------------------------------
#include"bullet.h"
#include"explosion.h"
#include"enemy.h"
#include"effect.h"
#include"time.h"
#include"player.h"
#include"boss.h"
#include"life.h"

//---------------
//グローバル変数
//---------------
LPDIRECT3DTEXTURE9 g_pTextureBullet = NULL;						//テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRunningman = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;				//頂点バッファのポインタ
BULLET g_aBullet[MAX_BULLET];									//弾の情報

//---------------
//弾の初期化
//---------------
void InitBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//デバイスのポインタ
	int nCntBullet;
	pDevice = GetDevice();					//デバイスの取得

	//弾の初期化
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心の位置
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f,0.0f, 0.0f);		//動きの初期化
		g_aBullet[nCntBullet].nCounterTime = 0;							//射出時間
		g_aBullet[nCntBullet].nLife = 200;								//弾のライフ
		g_aBullet[nCntBullet].nCounterAnim = 0;							//アニメーションカウンターの初期化
		g_aBullet[nCntBullet].nPatternAnim = 0;							//アニメーションパターンの初期化
		g_aBullet[nCntBullet].bUse = false;								//使用してない状態にする
		g_aBullet[nCntBullet].nEp = 0;									//爆発の初期化
		g_aBullet[nCntBullet].nTypeBullet = 0;							//特殊弾の初期化
		g_aBullet[nCntBullet].nPattern = 0;								//種類（1.雑魚敵、2.ボス）
	}

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET,				//*の後ろが頂点の個数				
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffBullet,
		NULL);
	
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//bullet000.png", &g_pTextureBullet);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//runningman000.png", &g_pTextureRunningman);
	
	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + 10.0f, g_aBullet[nCntBullet].pos.y + 10.0f, 0.0f);

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
		
		pVtx += 4;				//デデデータが4個分進む
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-------------
//弾の終了
//-------------
void UninitBullet(void)
{
	//テクスチャの破棄
	if (g_pTextureBullet != NULL)
	{
		g_pTextureBullet->Release();
		g_pTextureBullet = NULL;
	}

	//テクスチャの破棄
	if (g_pTextureRunningman != NULL)
	{
		g_pTextureRunningman->Release();
		g_pTextureRunningman = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
}

//-------------
//弾の更新
//-------------
void UpdateBullet(void)
{
	int nCntBullet;

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾が使用されている
			Enemy *pEnemy = GetEnemy();
			Boss *pBoss = GetBoss();
			EFFECT *pEffect = GetEffect();
			Player * pPlayer = GetPlayer();
			int nCntEnemy;
			int nCountBoss = 0;

			VERTEX_2D *pVtx;		//頂点情報へのポインタ

			//頂点バッファをロックし、頂点情報へのポインタを取得
			g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntBullet * 4;						//データに合わせた数値分進む

			for (nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
			{
				if (pEnemy->bUse == true)
				{//エネミーが使用されている
					if (g_aBullet[nCntBullet].nPattern == 0)
					{
						if (g_aBullet[nCntBullet].nTypeBullet == 0)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
							 //エネミーのヒット処理
								HitEnemy(nCntEnemy, 120);

								g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 1)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - RUNNINGMAN_WIDTH &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + RUNNINGMAN_WIDTH &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - RUNNINGMAN_HEIGHT &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + RUNNINGMAN_HEIGHT)
							{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
							 //エネミーのヒット処理
								HitEnemy(nCntEnemy, 45);

								g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 2)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
							 //エネミーのヒット処理
								HitEnemy(nCntEnemy, 100);

								g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

								pEffect->bUse = false;
							}
						}
						else if (g_aBullet[nCntBullet].nTypeBullet == 3)
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
							 //エネミーのヒット処理
								HitEnemy(nCntEnemy, 20);

								g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

								pEffect->bUse = false;
							}
						}
						else
						{
							if (g_aBullet[nCntBullet].pos.x >= pEnemy->pos.x - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.x <= pEnemy->pos.x + ENEMY_SIZE + MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y >= pEnemy->pos.y - ENEMY_SIZE - MYBULLET_SIZE &&
								g_aBullet[nCntBullet].pos.y <= pEnemy->pos.y + ENEMY_SIZE + MYBULLET_SIZE)
							{//エネミーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時

							 //エネミーのヒット処理
								HitEnemy(nCntEnemy, 150);

								g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

								pEffect->bUse = false;
							}
						}
					}
				}
			}

			if (pPlayer->bUse == true)
			{//プレイヤーが使用されている
				if (g_aBullet[nCntBullet].nPattern == 1)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 0)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - HI_PLAYER + MINUS_PLAYERSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + WD_PLAYER - MINUS_PLAYERSIZE + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - HI_PLAYER + MINUS_PLAYERSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + WD_PLAYER - MINUS_PLAYERSIZE + MYBULLET_SIZE)
						{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時

							//プレイヤーのヒット処理
							HitPlayer(1);

							HitLife();

							g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする
						}
					}
				}
			}

			if (pBoss->bUse == true)
			{//プレイヤーが使用されている

				if (g_aBullet[nCntBullet].nPattern == 2)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 0)
					{
						if (g_aBullet[nCntBullet].pos.x >= pPlayer->pos.x - HI_PLAYER - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pPlayer->pos.x + WD_PLAYER + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pPlayer->pos.y - HI_PLAYER - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pPlayer->pos.y + WD_PLAYER + MYBULLET_SIZE)
						{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時

							//プレイヤーのヒット処理
							HitPlayer(1);

							HitLife();

							g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする
						}
					}
				}
				else if (g_aBullet[nCntBullet].nPattern == 0)
				{
					if (g_aBullet[nCntBullet].nTypeBullet == 1)
					{
						if (g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_HISIZE - RUNNINGMAN_WIDTH &&
							g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_HISIZE + RUNNINGMAN_WIDTH &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_WDSIZE - RUNNINGMAN_HEIGHT &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_WDSIZE + RUNNINGMAN_HEIGHT)
						{//プレイヤーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時
						 //エネミーのヒット処理
							HitBoss(nCountBoss, 100);

							g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

							pEffect->bUse = false;
						}
					}
					else
					{
						if (g_aBullet[nCntBullet].pos.x >= pBoss->pos.x - BOSS_HISIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.x <= pBoss->pos.x + BOSS_HISIZE + MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y >= pBoss->pos.y - BOSS_WDSIZE - MYBULLET_SIZE &&
							g_aBullet[nCntBullet].pos.y <= pBoss->pos.y + BOSS_WDSIZE + MYBULLET_SIZE)
						{//エネミーの中心にエネミーと弾のサイズ（各半分）を＋ーした範囲に弾が当たった時

						 //エネミーのヒット処理
							HitBoss(nCountBoss, 5);

							g_aBullet[nCntBullet].bUse = false;			//使用されていない状態にする

							pEffect->bUse = false;
						}
					}
				}
			}
			

			//弾の位置の更新
			g_aBullet[nCntBullet].pos += g_aBullet[nCntBullet].move;

			if (g_aBullet[nCntBullet].nTypeBullet == 0)
			{//特殊弾
				g_aBullet[nCntBullet].nLife--;
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);

			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);

			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 2)
			{
				g_aBullet[nCntBullet].nLife--;
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 3)
			{
				g_aBullet[nCntBullet].nCounterTime++;
				if (g_aBullet[nCntBullet].nCounterTime == 27)
				{
					SetBullet(g_aBullet[nCntBullet].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.75f) * BULLET_SIZE, cosf(D3DX_PI * 0.75f) * BULLET_SIZE, 0.0f), g_aBullet[nCntBullet].nEp, g_aBullet[nCntBullet].nTypeBullet, 0);
					SetBullet(g_aBullet[nCntBullet].pos, D3DXVECTOR3(sinf(D3DX_PI * 0.25f) * BULLET_SIZE, cosf(D3DX_PI * 0.25f) * BULLET_SIZE, 0.0f), g_aBullet[nCntBullet].nEp, g_aBullet[nCntBullet].nTypeBullet, 0);
				}
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 4)
			{
				g_aBullet[nCntBullet].nLife--;
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 5)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				g_aBullet[nCntBullet].nPatternAnim = (g_aBullet[nCntBullet].nPatternAnim + 1) % 8;

				//テキスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 1.0f);
			}
			else
			{
				//テキスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			if (g_aBullet[nCntBullet].pos.y <= 0.0f ||
				g_aBullet[nCntBullet].pos.y >= SCREEN_HEIGHT ||
				g_aBullet[nCntBullet].pos.x >= SCREEN_WIDTH ||
				g_aBullet[nCntBullet].pos.x <= 0.0f)
			{//弾頭が画面端を超えた
				g_aBullet[nCntBullet].bUse = false;				//使用していない状態に戻す
				pEffect->bUse = false;							//使用していない状態に戻す

			}

			//寿命のカウントダウン
			if (g_aBullet[nCntBullet].nLife <= 0)
			{//推進力が尽きた
				g_aBullet[nCntBullet].bUse = false;				//使用してない状態に戻す、つまりアローリ
				pEffect->bUse = false;							//使用していない状態に戻す
			}

			if (g_aBullet[nCntBullet].nPattern == 0)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 1)
				{
					Player * pPlayer = GetPlayer();
					//エフェークトゥのセットアップ
					SetEffect(pPlayer[0].pos, D3DXCOLOR(0.0f, 0.0f, 0.5f, 1.0f), EFFECT_RUNNINGMAN_SIZE, 5);
				}
				else if (g_aBullet[nCntBullet].nTypeBullet == 3)
				{
					//エフェークトゥのセットアップ
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
				else if (g_aBullet[nCntBullet].nTypeBullet == 5)
				{
					//エフェークトゥのセットアップ
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.5f, 0.5f, 0.0f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
				else
				{
					//エフェークトゥのセットアップ
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
			else if (g_aBullet[nCntBullet].nPattern == 1)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 0)
				{
					//エフェークトゥのセットアップ
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
			else if (g_aBullet[nCntBullet].nPattern == 2)
			{
				if (g_aBullet[nCntBullet].nTypeBullet == 0)
				{
					//エフェークトゥのセットアップ
					SetEffect(g_aBullet[nCntBullet].pos, D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f), EFFECTBULLET_SIZE, 10);
				}
			}
		//頂点バッファをアンロックする
		g_pVtxBuffBullet->Unlock();
		}
	}
}


//--------------
//弾の描画
//--------------
void DrawBullet(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntBullet;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == true)
		{//弾薬が使用されている
		 //テクスチャの設定
			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				pDevice->SetTexture(0, g_pTextureRunningman);
			}
			else
			{
				pDevice->SetTexture(0, g_pTextureBullet);
			}
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntBullet * 4,						//描画する最初の頂点インデックス
				2);									//ポリゴン数
		}
	}
}

//---------------
//弾の設定
//---------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nEp, int nTypeBullet, int nPattern)
{
	int nCntBullet;

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		if (g_aBullet[nCntBullet].bUse == false)
		{//弾が使われていない
			g_aBullet[nCntBullet].pos = pos;			//プレイヤーの中心とマテリアルの中心を同じにする
			g_aBullet[nCntBullet].nTypeBullet = nTypeBullet;
			g_aBullet[nCntBullet].move = move;
			g_aBullet[nCntBullet].nLife = 200;
			g_aBullet[nCntBullet].bUse = true;			//使用している状態にする
			g_aBullet[nCntBullet].nEp = nEp;
			g_aBullet[nCntBullet].nPattern = nPattern;
			pVtx += nCntBullet * 4;						//デデデータに合わせた数値分進む

			if (g_aBullet[nCntBullet].nTypeBullet == 0)
			{//特殊弾
			 //頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y - RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + RUNNINGMAN_WIDTH, g_aBullet[nCntBullet].pos.y + RUNNINGMAN_HEIGHT, 0.0f);

			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 2)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			else if (g_aBullet[nCntBullet].nTypeBullet == 3)
			{
				g_aBullet[nCntBullet].nCounterTime = 0;							//射出時間
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 4)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}
			else if (g_aBullet[nCntBullet].nTypeBullet == 5)
			{
				//頂点座標の更新
				pVtx[0].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[1].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y - BULLET_SIZE, 0.0f);
				pVtx[2].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x - BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
				pVtx[3].pos = D3DXVECTOR3(g_aBullet[nCntBullet].pos.x + BULLET_SIZE, g_aBullet[nCntBullet].pos.y + BULLET_SIZE, 0.0f);
			}

			if (g_aBullet[nCntBullet].nTypeBullet == 1)
			{
				g_aBullet[nCntBullet].nPatternAnim = (g_aBullet[nCntBullet].nPatternAnim + 1) % 8;

				//テキスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aBullet[nCntBullet].nPatternAnim * 0.125f + 0.125f, 1.0f);
			}
			else
			{
				//テキスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
			}

			break;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBullet->Unlock();
}

//-----------------
//ポインタの取得
//-----------------
BULLET *GetBullet(void)
{
	return g_aBullet;
}