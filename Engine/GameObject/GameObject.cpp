#include "gameObject.h"
#include <assert.h>
#include "../ResourceManager/Global.h"
#include "Camera.h"
#include "../Component/Transform/Transform.h"
#include "../Component/Collider/Collider.h"

//コンストラクタ（親も名前もなし）
GameObject::GameObject(void) :
	GameObject(nullptr, "")
{

}

//コンストラクタ（名前なし）
GameObject::GameObject(GameObject * parent) :
	GameObject(parent, "")
{
}

//コンストラクタ（標準）
GameObject::GameObject(GameObject * parent, const std::string& name)
	: pParent_(parent),pathName_(""),



	objectName_(name)
{
	childList_.clear();
	state_ = { 0, 1, 1, 0 };
}

//デストラクタ
GameObject::~GameObject()
{
	//コンポーネント解放
	for (auto it = ComponentList_.begin(); it != ComponentList_.end(); it++)
	{
		if ((*it))
			SAFE_DELETE(*it);
	}
	ComponentList_.clear();
}

// 削除するかどうか
bool GameObject::IsDead()
{
	return (state_.dead != 0);
}

// 自分を削除する
void GameObject::KillMe()
{
	state_.dead = 1;
}

// Updateを許可
void GameObject::Enter()
{
	state_.entered = 1;
}

// Updateを拒否
void GameObject::Leave()
{
	state_.entered = 0;
}

// Drawを許可
void GameObject::Visible()
{
	state_.visible = 1;
}

// Drawを拒否
void GameObject::Invisible()
{
	state_.visible = 0;
}

// 初期化済みかどうか
bool GameObject::IsInitialized()
{
	return (state_.initialized != 0);
}

// 初期化済みにする
void GameObject::SetInitialized()
{
	state_.initialized = 1;
}

// Update実行していいか
bool GameObject::IsEntered()
{
	return (state_.entered != 0);
}

// Draw実行していいか
bool GameObject::IsVisibled()
{
	return (state_.visible != 0);
}

void GameObject::SetStartUpdate()
{
	state_.startUpdate = 1;
}

bool GameObject::IsStartUpdate()
{
	return (state_.startUpdate != 1);
}

void GameObject::SetEmission(bool flag)
{
	state_.emission = flag;
}

bool GameObject::GetEmission()
{
	return (state_.emission != 0);
}

void GameObject::SetShadow(bool flag)
{
	state_.shadow = flag;
}

bool GameObject::GetShadow()
{
	return (state_.shadow != 0);
}

//時間メソッドを使用しているに設定
void GameObject::SetTimeMethod(float time)
{
	//時間メソッドを使用している
	state_.timeMethod = 1;

	//時間を保存
	time_ = (int)(time * 60.0f);
}

//時間メソッドを使用しているかどうか
bool GameObject::GetTimeMethod()
{
	return (state_.timeMethod != 0);
}

//子オブジェクトリストを取得
std::list<GameObject*>* GameObject::GetChildList()
{
	return &childList_;
}

//親オブジェクトを取得
GameObject * GameObject::GetParent()
{
	return pParent_;
}

//名前でオブジェクトを検索（対象は自分の子供以下）
GameObject * GameObject::FindChildObject(const std::string & name)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return nullptr;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトから探す
	while (it != end) {
		//同じ名前のオブジェクトを見つけたらそれを返す
		if ((*it)->GetObjectName() == name)
			return *it;

		//その子供（孫）以降にいないか探す
		GameObject* obj = (*it)->FindChildObject(name);
		if (obj != nullptr)
		{
			return obj;
		}

		//次の子へ
		it++;
	}

	//見つからなかった
	return nullptr;
}

//オブジェクトの名前を取得
const std::string& GameObject::GetObjectName(void) const
{
	return objectName_;
}

//子オブジェクトを追加（リストの最後へ）
void GameObject::PushBackChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_back(obj);
}

//子オブジェクトを追加（リストの先頭へ）
void GameObject::PushFrontChild(GameObject * obj)
{
	assert(obj != nullptr);

	obj->pParent_ = this;
	childList_.push_front(obj);
}

//子オブジェクトを全て削除
void GameObject::KillAllChildren(void)
{
	//子供がいないなら終わり
	if (childList_.empty())
		return;

	//イテレータ
	auto it = childList_.begin();	//先頭
	auto end = childList_.end();	//末尾

	//子オブジェクトを1個ずつ削除
	while (it != end)
	{
		KillObjectSub(*it);
		delete *it;
		it = childList_.erase(it);
	}

	//リストをクリア
	childList_.clear();
}

//オブジェクト削除（再帰）
void GameObject::KillObjectSub(GameObject * obj)
{
	if (!childList_.empty())
	{
		auto list = obj->GetChildList();
		auto it = list->begin();
		auto end = list->end();
		while (it != end)
		{
			KillObjectSub(*it);
			delete *it;
			it = list->erase(it);
		}
		list->clear();
	}
	obj->Release();
}

//RootJobを取得
GameObject * GameObject::GetRootJob()
{
	if (GetParent() == nullptr)
	{
		return this;
	}
	else return GetParent()->GetRootJob();
}

//自身を親のリストの最後にプッシュする
void GameObject::MyObjectParentListEndPush()
{
	// オブジェクトのイテレータを検索
	auto it = std::find(GetParent()->GetChildList()->begin(), GetParent()->GetChildList()->end(), this);

	if (it != GetParent()->GetChildList()->end()) {

		// オブジェクトが見つかった場合、リストから削除
		GetParent()->GetChildList()->erase(it);

		// オブジェクトをリストの末尾に追加
		GetParent()->GetChildList()->push_back(this);
	}
}

void GameObject::UpdateSub()
{
	//nullならこの先処理しない
	if (this == nullptr) return;

	//時間メソッドを使用しているなら
	if (this->state_.timeMethod)
	{
		//タイム加算
		timeCount_++;

		//指定された時間よりタイムが大きいのなら
		if (time_ < timeCount_)
		{
			//使った各変数初期化
			ZERO_INITIALIZE(this->state_.timeMethod);
			ZERO_INITIALIZE(time_);
			ZERO_INITIALIZE(timeCount_);

			//メソッド呼び出す
			TimeMethod();
		}
	}

	//Updateを許可するなら
	if (this->state_.entered && !IsStartUpdate())
	{
		//更新
		Update();

		//コンポーネント更新
		for (auto it = ComponentList_.begin(); it != ComponentList_.end(); it++)
		{
			(*it)->Update();
		}
	}

	//子供の更新処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->UpdateSub();
	}

	for (auto it = childList_.begin(); it != childList_.end();)
	{
		//死んでいるのなら削除
		if ((*it)->IsDead() == true)
		{
			(*it)->ReleaseSub();
			SAFE_DELETE(*it);
			it = childList_.erase(it);
		}
		else
		{
			//当たり判定コンポーネントが存在するのならば接触計算
			if((*it)->GetComponent<Collider>())
				(*it)->GetComponent<Collider>()->Collision(GetParent());
			
			it++;
		}
	}
}

void GameObject::StartUpdateSub()
{
	//nullならこの先処理しない
	if (this == nullptr) return;

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->StartUpdateSub();
	}

	if (IsStartUpdate())
	{
		this->StartUpdate();
		SetStartUpdate();
	}
}

void GameObject::DrawSub()
{
	//nullならこの先処理しない
	if (this == nullptr) return;

	//シェーダをSHADER_3Dにセットしておく
	Direct3D::SetShader(Direct3D::SHADER_3D);

	//もし描画が許可されているのなら
	if (this->IsVisibled())
	{
		//描画
		Draw();

		//コンポーネント描画
		for (auto it = ComponentList_.begin(); it != ComponentList_.end(); it++)
		{
			(*it)->Draw();
		}
	}
	
	//その子オブジェクトの描画処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->DrawSub();
	}
}

void GameObject::TwoWindowDrawSub()
{
	//nullならこの先処理しない
	if (this == nullptr) return;

	//シェーダをSHADER_3Dにセットしておく
	Direct3D::SetShader(Direct3D::SHADER_3D);

	//もし描画が許可されているのなら
	if (this->IsVisibled())
	{
		//描画
		TwoWindowDraw();
	}

	//その子オブジェクトの描画処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->TwoWindowDrawSub();
	}
}

void GameObject::TransparentDrawSub()
{
	//nullならこの先処理しない
	if (this == nullptr) return;

	//シェーダをSHADER_3Dにセットしておく
	Direct3D::SetShader(Direct3D::SHADER_3D);

	//もし描画が許可されているのなら
	if (this->IsVisibled())
	{
		//描画
		TransparentDraw();
	}

	//その子オブジェクトの描画処理
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->TransparentDrawSub();
	}
}

void GameObject::EmissionDraw()
{
	if(this->GetEmission() && this->IsVisibled())
		Draw();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->EmissionDraw();
	}
}

void GameObject::ShadowDraw()
{
	if (this->GetShadow() && this->IsVisibled())
		Draw();

	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ShadowDraw();
	}
}

void GameObject::ReleaseSub()
{
	//コンポーネント解放
	for (auto it = ComponentList_.begin(); it != ComponentList_.end(); it++)
	{
		if((*it))
			SAFE_DELETE(*it);
	}

	//ゲームオブジェクト解放
	for (auto it = childList_.begin(); it != childList_.end(); it++)
	{
		(*it)->ReleaseSub();
		SAFE_DELETE(*it);
	}

	Release();
}

//引数でもらったtargetの方を向く
void GameObject::LookObject(XMFLOAT3 target, XMVECTOR up)
{
	//target.y += 2;
	//transform_.mmRotate_ = XMMatrixInverse(nullptr, XMMatrixLookAtLH(XMVectorSet(ZERO,ZERO,ZERO,ZERO), XMLoadFloat3(&target) - XMLoadFloat3(&transform_.position_), up));
}

//ワールド行列の取得（親の影響を受けた最終的な行列）
XMMATRIX GameObject::GetWorldMatrix(void)
{
	return GetComponent<Transform>()->GetWorldMatrix();
}


