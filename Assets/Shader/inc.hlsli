//───────────────────────────────────────
 // コンスタントバッファ
// DirectX 側から送信されてくる、ポリゴン頂点以外の諸情報の定義
//───────────────────────────────────────
cbuffer global
{
	float4x4	g_matWVP;			  // ワールド・ビュー・プロジェクションの合成行列
	float4x4	g_matNormalTrans;	  // 法線の変換行列（回転行列と拡大の逆行列）
	float4x4	g_matWorld;			  // ワールド変換行列
	float4x4	g_mWLP;				  //ワールド・”ライトビュー”・プロジェクションの合成 
	float4x4	g_mWLPT;			  //ワールド・”ライトビュー”・プロジェクション・UV 行列の合成 
	float4		g_vecLightDir;		  // ライトの方向ベクトル
	float4		g_vecDiffuse;		  // ディフューズカラー（マテリアルの色）
	float4		g_vecAmbient;		  // アンビエントカラー（影の色）
	float4		g_vecSpeculer;		  // スペキュラーカラー（ハイライトの色）
	float4      g_isSpeculerColor;    // 任意で決めれるスペキュラーカラー
	float4		g_vecCameraPosition;  // 視点（カメラの位置）
	float4      g_vecLightPosition;   // ライトの位置
	float4      g_LightPosition[15];  // ライトの個数分の位置
	float4      g_LightIntensity[15]; // ライトの個数分の強さ
	float4      g_isAmbient;          // アンビエントの力の大きさ 
	float4		g_outLineColor;		  // アウトラインの色
	float		g_shuniness;		  // ハイライトの強さ（テカリ具合）
	bool		g_isTexture;		  // テクスチャ貼ってあるかどうか
	bool        g_isShadowApply;      // 自分自身に影を適用するか
	float 		g_isDiffuse;		  // 透明にするか
	float       g_isBrightness;       // 明るさ
};