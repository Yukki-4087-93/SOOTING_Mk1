//------------------------------------------------------------
//
//爆発
//Author;takano
//
//------------------------------------------------------------
#include"explosion.h"

//-----------
//マクロ定義
//-----------
#define	MAX_EXPLOSION			(128)									//爆弾の最大数

//---------------
//弾構造体の定義
//---------------
typedef struct
{
	D3DXVECTOR3 pos;													//位置
	D3DXCOLOR col;														//色だよ
	int nCounterAnim;													//アニメーションカウンター
	int nPatternAnim;													//アニメーションカウンター
	bool bUse;															//爆発が使用中か否か
}Explosion;

//---------------
//グローバル変数
//---------------
LPDIRECT3DTEXTURE9 g_pTexExplosion = NULL;							//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffExplosion = NULL;						//頂点バッファのポインタ
Explosion g_aExplosion[MAX_EXPLOSION];									//爆発の情報

//---------------
//爆発の初期化
//---------------
void InitExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//デバイスのポインタ
	int nCntExplosion;
	pDevice = GetDevice();					//デバイスの取得

	//ボマーの初期化
	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		g_aExplosion[nCntExplosion].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//中心の位置
		g_aExplosion[nCntExplosion].col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);		//色の初期化
		g_aExplosion[nCntExplosion].nCounterAnim = 0;							//アニメーションカウンター
		g_aExplosion[nCntExplosion].nPatternAnim = 0;							//アニメーションパターン
		g_aExplosion[nCntExplosion].bUse = false;								//使用してない状態にする
	}

	//頂点バッファ
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_EXPLOSION,				//*の後ろが頂点の個数				
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffExplosion,
		NULL);

	VERTEX_2D *pVtx;

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//explosion000.png", &g_pTexExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y - 10.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 10.0f, g_aExplosion[nCntExplosion].pos.y + 10.0f, 0.0f);

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
		pVtx[1].tex = D3DXVECTOR2(0.125f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.125f, 1.0f);

		pVtx += 4;				//デデデータが4個分進む
	}
	//頂点バッファをアンロックする
	g_pVtxBuffExplosion->Unlock();
}

//---------------------
//爆発の終了
//---------------------
void UninitExplosion(void)
{
	//テクスチャの破棄
	if (g_pTexExplosion != NULL)
	{
		g_pTexExplosion->Release();
		g_pTexExplosion = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffExplosion != NULL)
	{
		g_pVtxBuffExplosion->Release();
		g_pVtxBuffExplosion = NULL;
	}
}

//----------------
//爆発の更新
//----------------
void UpdateExplosion(void)
{
	int nCntExplosion;

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{
			g_aExplosion[nCntExplosion].nCounterAnim++;

			if (g_aExplosion[nCntExplosion].nCounterAnim % 8 == 0)
			{
				g_aExplosion[nCntExplosion].nPatternAnim++;

				VERTEX_2D *pVtx;		//頂点情報へのポインタ

				//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
				g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
				pVtx += nCntExplosion * 4;						//デデデータに合わせた数値分進む

				//テキスチャの座標設定
				pVtx[0].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 0.0f);
				pVtx[1].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(g_aExplosion[nCntExplosion].nPatternAnim * 0.125f + 0.125f, 1.0f);

				if (g_aExplosion[nCntExplosion].nPatternAnim >= 8)
				{
					g_aExplosion[nCntExplosion].bUse = false;
				}
				//頂点バッファをアンロックする
				g_pVtxBuffExplosion->Unlock();
			}

		}
	}
}

//-----------------------
//爆発の描画
//-----------------------
void DrawExplosion(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCntExplosion;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffExplosion, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexExplosion);

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == true)
		{//芸術が使用されている
		 //ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
				nCntExplosion * 4,						//描画する最初の頂点インデックス
				2);										//ポリゴン数
		}
	}
}

//---------------
//爆発の設定
//---------------
void SetExplosion(D3DXVECTOR3 pos, D3DXCOLOR col)
{
	int nCntExplosion;

	for (nCntExplosion = 0; nCntExplosion < MAX_EXPLOSION; nCntExplosion++)
	{
		if (g_aExplosion[nCntExplosion].bUse == false)
		{//弾が使われていない
			g_aExplosion[nCntExplosion].pos = pos;									//プレイヤーの中心とマテリアルの中心を同じにする
			g_aExplosion[nCntExplosion].col = col;									//爆発の色
			g_aExplosion[nCntExplosion].nCounterAnim = 0;							//アニメーションカウンター
			g_aExplosion[nCntExplosion].nPatternAnim = 0;							//アニメーションパターン

			VERTEX_2D *pVtx;

			//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
			g_pVtxBuffExplosion->Lock(0, 0, (void**)&pVtx, 0);
			pVtx += nCntExplosion * 4;						//データに合わせた数値分進む

			//頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 100.0f, g_aExplosion[nCntExplosion].pos.y - 100.0f, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 100.0f, g_aExplosion[nCntExplosion].pos.y - 100.0f, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x - 100.0f, g_aExplosion[nCntExplosion].pos.y + 100.0f, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(g_aExplosion[nCntExplosion].pos.x + 100.0f, g_aExplosion[nCntExplosion].pos.y + 100.0f, 0.0f);

			pVtx[0].col = col;
			pVtx[1].col = col;
			pVtx[2].col = col;
			pVtx[3].col = col;

			g_aExplosion[nCntExplosion].bUse = true;			//使用している状態にする

			//頂点バッファをアンロックする
			g_pVtxBuffExplosion->Unlock();
			break;
		}
	}
}