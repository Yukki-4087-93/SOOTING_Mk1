//----------------------------------------------------------------------------------------
//
//ランキング
//Author;takano
//
//----------------------------------------------------------------------------------------
#include"ranking.h"
#include"score.h"
#include"fade.h"
#include"input.h"
#include"sound.h"

//----------------------
//マクロ定義
//----------------------
#define RANK_H				(80)								//縦幅
#define RANK_WD				(50)								//横幅

//--------------------------
//グローバル変数
//--------------------------
LPDIRECT3DTEXTURE9 g_pTextureRank = NULL;						//テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTextureRankScore = NULL;					//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRank = NULL;					//頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffRankScore = NULL;				//頂点バッファへのポインタ
RankScore g_aRankScore[MAX_RANK];								//ランキングスコア情報
int g_nRankUpdate = -1;											//更新ランクNo.
int g_nCountState = 0;											//ランキングスコアの状態カウンター
int g_nScoreState = 0;											//ランキングスコアの状態情報

//------------------------
//ランキングの初期化処理
//------------------------
void InitRanking(void)
{
	int nCountRank,nRankScore;

	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	int aPosTexU[MAX_RANK][MAX_SCORE];

	//デヴァイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRank, NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * MAX_SCORE * MAX_RANK,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffRankScore, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//ranking_rank.png", &g_pTextureRank);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//number000.png", &g_pTextureRankScore);

	for (nCountRank = 0; nCountRank < MAX_RANK ; nCountRank++)
	{
		g_aRankScore[nCountRank].pos.x = 350.0f;
		g_aRankScore[nCountRank].pos.y = 200.0f;
		g_aRankScore[nCountRank].pos.z = 0.0f;
		g_aRankScore[nCountRank].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankScore = 0; nRankScore < MAX_RANK; nRankScore++)
	{
		for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
		{
			//頂点座標の設定
			pVtx[0].pos.x = g_aRankScore[nRankScore].pos.x + (RANK_WD * nCountRank);
			pVtx[0].pos.y = g_aRankScore[nRankScore].pos.y + (RANK_H * nRankScore);
			pVtx[0].pos.z = 0.0f;

			pVtx[1].pos.x = g_aRankScore[nRankScore].pos.x + RANK_WD + (RANK_WD * nCountRank);
			pVtx[1].pos.y = g_aRankScore[nRankScore].pos.y + (RANK_H * nRankScore);
			pVtx[1].pos.z = 0.0f;

			pVtx[2].pos.x = g_aRankScore[nRankScore].pos.x + (RANK_WD * nCountRank);
			pVtx[2].pos.y = g_aRankScore[nRankScore].pos.y + RANK_H +(RANK_H * nRankScore);
			pVtx[2].pos.z = 0.0f;

			pVtx[3].pos.x = g_aRankScore[nRankScore].pos.x + RANK_WD + (RANK_WD * nCountRank);
			pVtx[3].pos.y = g_aRankScore[nRankScore].pos.y + RANK_H + (RANK_H * nRankScore);
			pVtx[3].pos.z = 0.0f;

			//rhwの設定
			pVtx[0].rhw = 1.0f;
			pVtx[1].rhw = 1.0f;
			pVtx[2].rhw = 1.0f;
			pVtx[3].rhw = 1.0f;

			//頂点カラーの設定
			pVtx[0].col = g_aRankScore[nRankScore].col;
			pVtx[1].col = g_aRankScore[nRankScore].col;
			pVtx[2].col = g_aRankScore[nRankScore].col;
			pVtx[3].col = g_aRankScore[nRankScore].col;

			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nRankScore][nCountRank] * 0.1f), 1.0f);

			pVtx += 4;				//デデデータが4個分進む
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffRank->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(100.0f,200.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(200.0f,200.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(100.0f,600.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(200.0f,600.0f, 0.0f);

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
	
	//頂点バッファをアンロックする
	g_pVtxBuffRank->Unlock();

	//サウンドの再生
	PlaySound(SOUND_LABEL_OP);

}

//------------------------
//ランキングの終了処理
//------------------------
void UninitRanking(void)
{
	//サウンドの停止
	StopSound();

	//テクスチャの破棄
	if (g_pTextureRank != NULL)
	{
		g_pTextureRank->Release();
		g_pTextureRank = NULL;
	}

	if (g_pTextureRankScore != NULL)
	{
		g_pTextureRankScore->Release();
		g_pTextureRankScore = NULL;
	}


	//頂点バッファの破棄
	if (g_pVtxBuffRank != NULL)
	{
		g_pVtxBuffRank->Release();
		g_pVtxBuffRank = NULL;
	}

	if (g_pVtxBuffRankScore != NULL)
	{
		g_pVtxBuffRankScore->Release();
		g_pVtxBuffRankScore = NULL;
	}
}

//------------------------
//ランキングの更新処理
//------------------------
void UpdateRanking(void)
{
	int nCountRank;
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);
	if (g_nRankUpdate != -1)
	{
		g_aRankScore[g_nRankUpdate].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
		g_nCountState++;
		if (g_nCountState % 4 == 0)
		{
			g_nScoreState ^= 1;
			g_aRankScore[g_nRankUpdate].col.a = (1.0f * g_nScoreState);
		}
		pVtx += MAX_SCORE * g_nRankUpdate * 4;				//デデデータが4個分進む

		for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
		{
			//頂点カラーの設定
			pVtx[0].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[1].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[2].col = g_aRankScore[g_nRankUpdate].col;
			pVtx[3].col = g_aRankScore[g_nRankUpdate].col;

			pVtx += 4;
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();

	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{//モードの設定
			SetFade(MODE_TITLE);
		}
	}
}

//------------------------
//ランキングの描画処理
//------------------------
void DrawRanking(void)
{
	LPDIRECT3DDEVICE9 pDevice;
	int nCountRank;//, nRankScore;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRank, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRank);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
		0,								//描画する最初の頂点インデックス
		2);											//ポリゴン数

//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffRankScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureRankScore);
	for (nCountRank = 0; nCountRank < MAX_SCORE * MAX_RANK; nCountRank++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,								//描画する最初の頂点インデックス
			2);											//ポリゴン数
	}
}

//------------------------
//ランキングのリセマラ
//------------------------
void ResetRanking(void)
{
	//ランキングの初期スコア
	g_aRankScore[0].nScore = 16500;

	g_aRankScore[1].nScore = 10200;

	g_aRankScore[2].nScore = 9500;

	g_aRankScore[3].nScore = 8100;

	g_aRankScore[4].nScore = 4300;
}

//---------------------------
//ランキングのセット
//---------------------------
void SetRanking(int nScore)
{
	int aPosTexU[MAX_SCORE];
	int nRankScore,nCountRankScore;
	int nScore1, nScore2, nScore3 = 0;

	if (g_aRankScore[MAX_RANK - 1].nScore < nScore)
	{
		g_aRankScore[MAX_RANK - 1].nScore = nScore;
		for (nScore1 = 0; nScore1 < MAX_RANK -1; nScore1++)
		{
			for (nScore2 = nScore1 + 1; nScore2 < MAX_RANK; nScore2++)
			{
				if (g_aRankScore[nScore1].nScore > g_aRankScore[nScore2].nScore)
				{
					nScore3 = g_aRankScore[nScore1].nScore;
					g_aRankScore[nScore1].nScore = g_aRankScore[nScore2].nScore;
					g_aRankScore[nScore2].nScore = nScore3;
				}
			}
		}
		
	}

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffRankScore->Lock(0, 0, (void**)&pVtx, 0);

	for (nRankScore = 0; nRankScore < MAX_RANK; nRankScore++)
	{
		aPosTexU[0] = g_aRankScore[nRankScore].nScore % 100000 / 10000;
		aPosTexU[1] = g_aRankScore[nRankScore].nScore % 10000 / 1000;
		aPosTexU[2] = g_aRankScore[nRankScore].nScore % 1000 / 100;
		aPosTexU[3] = g_aRankScore[nRankScore].nScore % 100 / 10;
		aPosTexU[4] = g_aRankScore[nRankScore].nScore % 10;

		for (nCountRankScore = 0; nCountRankScore < MAX_SCORE; nCountRankScore++)
		{
			//テクスチャの座標設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRankScore] * 0.1f), 0.0f);
			pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRankScore] * 0.1f), 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRankScore] * 0.1f), 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRankScore] * 0.1f), 1.0f);

			pVtx += 4;				//デデデータが4個分進む
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffRankScore->Unlock();
}

//---------------------------
//ランキングの情報取得
//---------------------------
int GetRanking(void)
{
	return g_nRankUpdate;
}