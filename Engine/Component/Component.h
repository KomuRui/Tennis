#pragma once

class GameObject;

//コンポーネント基底クラス
class Component
{
private:
    
    //コンストラクタ
    Component() {}

    //デストラクタ
    virtual ~Component() {}

public:
   
    //親
    GameObject* parent;

    //最初の一回だけ呼ばれる
    virtual void Start() {}

    //更新
    virtual void Update() {}

    //描画
    virtual void Draw() {}
};