#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "../ResourceManager/Global.h"
#include "../DirectX/Input.h"
#include "../Component/Component.h"

using namespace DirectX;

//-----------------------------------------------------------
//全てのゲームオブジェクト（シーンも含めて）が継承するインターフェース
// ゲームオブジェクトは、親子構造になっていて、
// マトリクスの影響を受けることになる
//-----------------------------------------------------------
class GameObject
{
protected:

	//オブジェクトの名前
	std::string				objectName_;

	//モデルや画像のパス名を保存しておく
	std::string					pathName_;

public:
	//コンストラクタ
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);

	//デストラクタ
	virtual ~GameObject();

	//各オブジェクトで必ず作る関数
	virtual void Initialize(void) {};
	virtual void Update(void) {};
	virtual void StartUpdate(void) {};
	virtual void Draw() {};
	virtual void Release(void){};

	//自分の該当関数を読んだ後、子供の関数も呼ぶ
	void UpdateSub();
	void StartUpdateSub();
	void DrawSub();
	void ReleaseSub();

	//二つ目のウィンドウ用
	virtual void TwoWindowDraw() {};
	void TwoWindowDrawSub();

	//透明・半透明なオブジェクト用
	virtual void TransparentDraw() {};
	void TransparentDrawSub();

	//Emissionを適用させたいオブジェクトの描画
	void EmissionDraw();

	//影を描画するときに呼ぶ
	void ShadowDraw();

	//ワールド行列の取得（親の影響を受けた最終的な行列）
	//戻値：ワールド行列
	XMMATRIX GetWorldMatrix();



	//各フラグの制御
	bool IsDead();					// 削除するかどうか
	void KillMe();					// 自分を削除する
	void Enter();					// Updateを許可
	void Leave();					// Updateを拒否
	void Visible();					// Drawを許可
	void Invisible();				// Drawを拒否
	bool IsInitialized();			// 初期化済みかどうか
	void SetInitialized();			// 初期化済みにする
	bool IsEntered();				// Update実行していいか
	bool IsVisibled();				// Draw実行していいか
	void SetStartUpdate();			// StartUpdate済みにする
	bool IsStartUpdate();			// StartUpdate実行していいか
	void SetEmission(bool flag);    // Emissionをセットする
	bool GetEmission();				// Emissionゲット
	void SetShadow(bool flag);      // 影をセットする
	bool GetShadow();				// 影を適用するかどうか
	void SetTimeMethod(float time); // 時間メソッドを使用しているに変更
	bool GetTimeMethod();		    // 時間メソッドを使用しているかどうか

	//子オブジェクトリストを取得
	//戻値：子オブジェクトリスト
	std::list<GameObject*>* GetChildList();

	//親オブジェクトを取得
	//戻値：親オブジェクトのアドレス
	GameObject* GetParent();

	//名前でオブジェクトを検索（対象は自分の子供以下）
	//引数：name	検索する名前
	//戻値：見つけたオブジェクトのアドレス（見つからなければnullptr）
	GameObject* FindChildObject(const std::string& name);

	//名前でオブジェクトを検索（対象は全体）
	//引数：検索する名前
	//戻値：見つけたオブジェクトのアドレス
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//オブジェクトの名前を取得
	//戻値：名前
	const std::string& GetObjectName(void) const;

	/// <summary>
	/// オブジェクトの名前セット
	/// </summary>
	void SetObjectName(std::string s) { objectName_ = s; }

	//子オブジェクトを追加（リストの最後へ）
	//引数：追加するオブジェクト
	void PushBackChild(GameObject* obj);

	//子オブジェクトを追加（リストの先頭へ）
	//引数：obj 追加するオブジェクト
	void PushFrontChild(GameObject* obj);

	//子オブジェクトを全て削除
	void KillAllChildren();

	//指定した時間で呼ばれるメソッド
	virtual void TimeMethod() {};

    //引数でもらったtargetの方を向く
	void LookObject(XMFLOAT3 target,XMVECTOR up);

	//RootJobを取得
	GameObject* GetRootJob();

	//自身を親のリストの最後にプッシュする
	void MyObjectParentListEndPush();

	//オブジェクトが持っているコンポーネントを取得
	template<class T>
	T* GetComponent()
	{
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				return buff;
		}
		return nullptr;
	}

	//オブジェクトが持っている同じコンポーネントを複数Listで取得
	template<class T>
	list<T*> GetComponentList()
	{
		list<T*> l;
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);
			if (buff != nullptr)
				l.push_back(buff);
		}
		return l;
	}

	//オブジェクトが持っているコンポーネントを削除
	template<class T>
	T* DeleteComponent()
	{
		for (auto com : ComponentList_) {
			T* buff = dynamic_cast<T*>(com);

			//見つかれば削除
			if (buff != nullptr)
			{
				ComponentList_.remove(buff);
				delete buff;
			}
		}
		return nullptr;
	}

	//コンポーネント追加
	template<class T>
	T* AddComponent()
	{
		T* buff = new T();
		buff->parent = this;
		ComponentList_.push_back(buff);
		buff->Start();
		return buff;
	}

	//各アクセス関数
	std::string GetPathName() { return pathName_; }
	
private:

	//オブジェクト削除（再帰）
	//引数：obj　削除するオブジェクト
	void KillObjectSub(GameObject* obj);


	//フラグ
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
		unsigned startUpdate : 1;   //最初の更新しているか
		unsigned emission : 1;      //Emission表示
		unsigned shadow : 1;        //影表示
		unsigned timeMethod : 1;    //タイムメソッドを使用しているかどうか
	};
	OBJECT_STATE state_;

	//時間メソッドを呼び出すために必要な時間変数たち
	int time_;
	int timeCount_;

	//親オブジェクト
	GameObject* pParent_;

	//子オブジェクトリスト
	std::list<GameObject*> childList_;

	//コンポーネントリスト
	std::list<Component*> ComponentList_;
};


//オブジェクトを作成するテンプレート(看板用)
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, std::string Name)
{
	T* pNewObject = new T(pParent,fileName, Name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//オブジェクトを作成するテンプレート
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//オブジェクトを作成するテンプレート
template <class T>
T* InstantiateFront(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushFrontChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//オブジェクトを作成するテンプレート
template <class T>
T* InstantiateParentFront(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->GetParent()->PushFrontChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//オブジェクトを作成するテンプレート
template <class T>
T* InstantiateParentPush(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->GetParent()->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

