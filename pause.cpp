//------------------------------------------------------------------------------------------
//
//ポーズメニュー
//Author;takano
//
//------------------------------------------------------------------------------------------
#include"pause.h"
#include"input.h"
#include"game.h"
#include"fade.h"
#include"sound.h"

//----------------------
//マクロ定義
//----------------------
#define MAX_W				(256)							//横幅
#define MAX_H				(30)							//縦幅

//-----------------------
//グローバル変数
//-----------------------
LPDIRECT3DTEXTURE9 g_pTexturePauseMenu[POUSE_MENU_MAX] = {NULL,NULL,NULL};					//テクスチャのポインタ
LPDIRECT3DTEXTURE9 g_pTexturePause = NULL;													//テクスチャのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPause = NULL;												//頂点バッファのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPauseMenu = NULL;											//頂点バッファのポインタ
PAUSE_MENU g_pauseMenu;																		//ポーズメニゥー構造体の情報
PAUSE g_aPause[POUSE_MENU_MAX];																//ポーズ構造体の情報

//---------------------
//ポーズの初期化処理
//---------------------
void InitPause(void)
{
	int nCountPause;

	LPDIRECT3DDEVICE9 pDevice;																//デバイスのポインタ

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPause, NULL);

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * POUSE_MENU_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPauseMenu, NULL);

	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause000.png", &g_pTexturePauseMenu[0]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause001.png", &g_pTexturePauseMenu[1]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pause002.png", &g_pTexturePauseMenu[2]);
	D3DXCreateTextureFromFile(pDevice, "Data//TEXTURE//pouse_now.png", &g_pTexturePause);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//値の初期化
		g_aPause[nCountPause].pos = D3DXVECTOR3(SCREEN_WIDTH * 0.2f,170.0f + (MAX_H * 7.0f * nCountPause), 0.0f);
		g_aPause[nCountPause].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	}

	//ポーズ情報の初期化
	g_pauseMenu = POUSE_MENU_COUNTINUE;
	
	VERTEX_2D*pVtx;			//頂点情報へのポインタ

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPause->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.26f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.26f);

	//テキスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPause->Unlock();

	//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
	g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//頂点座標の設定
		pVtx[0].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_W, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_W, g_aPause[nCountPause].pos.y - MAX_H, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x - MAX_W, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aPause[nCountPause].pos.x + MAX_W, g_aPause[nCountPause].pos.y + MAX_H, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点カラーの設定
		pVtx[0].col = g_aPause[nCountPause].col;
		pVtx[1].col = g_aPause[nCountPause].col;
		pVtx[2].col = g_aPause[nCountPause].col;
		pVtx[3].col = g_aPause[nCountPause].col;

		//テキスチャの座標設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffPauseMenu->Unlock();
}

//---------------------
//ポーズの終了処理
//---------------------
void UninitPause(void)
{
	for (int nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//テクスチャの破棄
		if (g_pTexturePauseMenu[nCountPause] != NULL)
		{
			g_pTexturePauseMenu[nCountPause]->Release();
			g_pTexturePauseMenu[nCountPause] = NULL;
		}
	}

	//テクスチャの破棄
	if (g_pTexturePause != NULL)
	{
		g_pTexturePause->Release();
		g_pTexturePause = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPause != NULL)
	{
		g_pVtxBuffPause->Release();
		g_pVtxBuffPause = NULL;
	}

	//頂点バッファの破棄
	if (g_pVtxBuffPauseMenu != NULL)
	{
		g_pVtxBuffPauseMenu->Release();
		g_pVtxBuffPauseMenu = NULL;
	}
}

//---------------------
//ポーズの更新処理
//---------------------
void UpdatePause(void)
{
	FADE pFade = GetFade();
	if (pFade == FADE_NONE)
	{
		VERTEX_2D*pVtx;			//頂点情報へのポインタ

		if (GetkeyboardTrigger(DIK_W) == true || GetkeyboardTrigger(DIK_UP) == true  || GetJoypadTrigger(JOYKEY_UP) == true)
		{//Wキーを押したとき
			g_aPause[g_pauseMenu].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
			g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_pauseMenu;			//でーたよ

												//頂点カラーの設定
			pVtx[0].col = g_aPause[g_pauseMenu].col;
			pVtx[1].col = g_aPause[g_pauseMenu].col;
			pVtx[2].col = g_aPause[g_pauseMenu].col;
			pVtx[3].col = g_aPause[g_pauseMenu].col;

			//頂点バッファをアンロックする
			g_pVtxBuffPauseMenu->Unlock();

			g_pauseMenu = (PAUSE_MENU)((g_pauseMenu - 1 + 3) % 3);
		}
		else if (GetkeyboardTrigger(DIK_S) == true || GetkeyboardTrigger(DIK_DOWN) == true || GetJoypadTrigger(JOYKEY_DOWN) == true)
		{//Sキーが押された
			g_aPause[g_pauseMenu].col = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
			//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
			g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

			pVtx += 4 * g_pauseMenu;			//でーたよ

												//頂点カラーの設定
			pVtx[0].col = g_aPause[g_pauseMenu].col;
			pVtx[1].col = g_aPause[g_pauseMenu].col;
			pVtx[2].col = g_aPause[g_pauseMenu].col;
			pVtx[3].col = g_aPause[g_pauseMenu].col;

			//頂点バッファをアンロックする
			g_pVtxBuffPauseMenu->Unlock();

			g_pauseMenu = (PAUSE_MENU)((g_pauseMenu + 1 + 3) % 3);

		}
		g_aPause[g_pauseMenu].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
		//頂点バッファをコック＆ロックし、頂点情報へのポインタを取得
		g_pVtxBuffPauseMenu->Lock(0, 0, (void**)&pVtx, 0);

		pVtx += 4 * g_pauseMenu;			//でーたよ

		//頂点カラーの設定
		pVtx[0].col = g_aPause[g_pauseMenu].col;
		pVtx[1].col = g_aPause[g_pauseMenu].col;
		pVtx[2].col = g_aPause[g_pauseMenu].col;
		pVtx[3].col = g_aPause[g_pauseMenu].col;

		//頂点バッファをアンロックする
		g_pVtxBuffPauseMenu->Unlock();

		//決定キー(ENTER)が押されたかどうか
		if (GetkeyboardTrigger(DIK_RETURN) == true || GetJoypadTrigger(JOYKEY_A) == true)
		{
			if (g_pauseMenu == POUSE_MENU_COUNTINUE)
			{
				SetEnablePause(false);
			}
			else if (g_pauseMenu == POUSE_MENU_RETRY)
			{
				SetFade(MODE_GAME);
			}
			else if (g_pauseMenu == POUSE_MENU_QUIT)
			{
				SetFade(MODE_TITLE);
			}
		}
	}
}

//---------------------
//ポーズの描画処理
//---------------------
void DrawPause(void)
{
	LPDIRECT3DDEVICE9 pDevice;						//デバイスのポインタ

	int nCountPause = 0;

	//デヴァイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPause, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTexturePause);

	//ポリゴンの描画
	pDevice->DrawPrimitive
	(D3DPT_TRIANGLESTRIP,
		0,
		2);

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPauseMenu, 0, sizeof(VERTEX_2D));

	//頂点フォーマット
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (nCountPause = 0; nCountPause < POUSE_MENU_MAX; nCountPause++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTexturePauseMenu[nCountPause]);

		//ポリゴンの描画
		pDevice->DrawPrimitive
		(D3DPT_TRIANGLESTRIP,
			nCountPause * 4,
			2);
	}
}