//------------------------------------------------------------
//
//スコア表示
//Author;takano
//
//------------------------------------------------------------
#include"score.h"

//------------------
//スタティック変数
//------------------
static LPDIRECT3DTEXTURE9 s_pTexture = NULL;							//テクスチャのポインタ
static LPDIRECT3DVERTEXBUFFER9 s_pVtxBuff = NULL;						//頂点バッファのポインタ
static D3DXVECTOR3 s_posScore;												//スコアの位置
static int s_nScore;														//スコアの値

//-------------------
//スコアの初期化処理
//-------------------
void InitScore(void)
{
	LPDIRECT3DDEVICE9 pDevice;				//デバイスのポインタ
	pDevice = GetDevice();					//デバイスの取得
	
	//テクスチャの読み込み処理
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//number000.png", &s_pTexture);
	
	//スコアの初期化
	s_posScore = D3DXVECTOR3(0.0f,0.0f,0.0f);					//位置の初期化
	s_nScore = 0;												//値を初期化

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE,				//*の後ろが個数
		D3DUSAGE_WRITEONLY, 
		FVF_VERTEX_2D, 
		D3DPOOL_MANAGED,
		&s_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(s_posScore.x + (SCORE_WIDTH * nCountRank), s_posScore.y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(s_posScore.x + SCORE_WIDTH + (SCORE_WIDTH * nCountRank), s_posScore.y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(s_posScore.x + (SCORE_WIDTH * nCountRank), s_posScore.y + SCORE_HEIGHT, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(s_posScore.x + SCORE_WIDTH + (SCORE_WIDTH * nCountRank), s_posScore.y + SCORE_HEIGHT, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f; 
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

		pVtx += 4;				//データが4個分進む
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//-----------------
//スコアの終了処理
//-----------------
void UninitScore(void)
{
	//テクスチャの破棄
	if (s_pTexture != NULL)
	{
		s_pTexture->Release();
		s_pTexture = NULL;
	}

	//頂点バッファの破棄
	if (s_pVtxBuff != NULL)
	{
		s_pVtxBuff->Release();
		s_pVtxBuff = NULL;
	}
}

//-------------------
//スコアのの更新処理
//-------------------
void UpdateScore(void)
{

}

//-----------------
//スコアの描画処理
//-----------------
void DrawScore(void)
{
	//デバイスのポインタ
	LPDIRECT3DDEVICE9 pDevice;
	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, s_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, s_pTexture);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,
			nCountRank * 4,								//描画する最初の頂点インデックス
			2);											//ポリゴン数
	}
}

//----------------
//スコアの設定処理
//----------------
void SetScore(int nScore)
{
	int aPosTexU[MAX_SCORE];
	int nCountRank;

	s_nScore = nScore;

	aPosTexU[0] = s_nScore % 100000 / 10000;
	aPosTexU[1] = s_nScore % 10000 / 1000;
	aPosTexU[2] = s_nScore % 1000 / 100;
	aPosTexU[3] = s_nScore % 100 / 10;
	aPosTexU[4] = s_nScore % 10;

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 1.0f);

		pVtx += 4;				//デデデータが4個分進む
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//----------------
//スコアの加算処理
//----------------
void AddScore(int nValue)
{
	int aPosTexU[MAX_SCORE];

	s_nScore += nValue;

	aPosTexU[0] = s_nScore % 100000 / 10000;
	aPosTexU[1] = s_nScore % 10000 / 1000;
	aPosTexU[2] = s_nScore % 1000 / 100;
	aPosTexU[3] = s_nScore % 100 / 10;
	aPosTexU[4] = s_nScore % 10;

	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	s_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCountRank = 0; nCountRank < MAX_SCORE; nCountRank++)
	{
		//テクスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f + (aPosTexU[nCountRank] * 0.1f), 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f + (aPosTexU[nCountRank] * 0.1f), 1.0f);

		pVtx += 4;				//データが4個分進む
	}

	//頂点バッファをアンロックする
	s_pVtxBuff->Unlock();
}

//----------------------
//スコア情報の取得
//----------------------
int GetScore(void)
{
	return s_nScore;
}