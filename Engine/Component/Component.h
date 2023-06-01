#pragma once

class GameObject;

//コンポーネント基底クラス
class Component
{
public:
   
    //親
    GameObject* parent;

    //コンストラクタ
    Component() :parent(nullptr) {}

    //デストラクタ
    virtual ~Component() {}

    //最初の一回だけ呼ばれる
    virtual void Start() {}

    //更新
    virtual void Update() {}

    //描画
    virtual void Draw() {}
};