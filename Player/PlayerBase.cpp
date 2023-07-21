#include "PlayerBase.h"
#include "../Engine/System.h"
#include "../OtherObject/PlayScene/Racket.h"
#include "../OtherObject/PlayScene/Ball.h"
#include "../OtherObject/PlayScene/Referee.h"

////定数
namespace
{
    ///////////////キャラの必要な情報///////////////////

    static const XMFLOAT3 PLAYER_SERVE_ROTATION_ANGLE = { 0,240,0 };   //プレイヤーの開始角度
    static const XMFLOAT3 CAM_TAR_ADD_VALUE = { 0,1,0 };               //カメラの焦点に加算する値
    static const float PLAYER_ANIM_SPEED = 2.0f;   //アニメーションの再生速度
    static const int ANIM_START_FRAME = 1;         //アニメーションの開始フレーム
    static const int ANIM_END_FRAME = 60;		   //アニメーションの終了フレーム

    ///////////////////カメラ///////////////////////

    static const XMFLOAT3 CAM_POS_SERVE_RECEIVE = { -2, 3.67f, 20.17f };     //サーブレシーブ時のカメラの位置
    static const XMFLOAT3 CAM_TAR_SERVE_RECEIVE = { 0, -2.27f, 0 };          //サーブレシーブ時のカメラの焦点

    static const XMFLOAT3 CAM_POS_NORMAL = { 0, 10.67f, 24.17f };   //通常時のカメラの位置
    static const XMFLOAT3 CAM_TAR_NORMAL = { 0, -2.27f, 0 };        //通常時のカメラの焦点
}

//コンストラクタ
PlayerBase::PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name)
    :NormalObject(parent, modelFilePath_, name),

    ///////////////キャラの必要な情報///////////////////

    pRacket_(nullptr),
    pState_(new PlayerStateManager),

    ///////////////////カメラ///////////////////////

    camVec_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    camVec2_(XMVectorSet(ZERO,ZERO,ZERO,ZERO)),
    nowLookNum_(ZERO)

{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void PlayerBase::ChildInitialize()
{
    ///////////////////初期化///////////////////////

    //状態
    ARGUMENT_INITIALIZE(pState_->playerState_ , pState_->playerStanding_);
    pState_->SetPlayerNum(GameManager::SetPlayer(this));

    //サーバーだけ角度修正
    if (GameManager::GetReferee()->GetServer() == this)
        ARGUMENT_INITIALIZE(transform_->rotate_, PLAYER_SERVE_ROTATION_ANGLE);

    //明るさ最大に
    //ModelManager::SetBrightness(hModel_, 1.0f);

    //自身に影を描画しないように
    ModelManager::SetMyShadowApply(hModel_, false);

    //初期位置設定
    ARGUMENT_INITIALIZE(initialPosition_, transform_->position_);

    ///////////////アニメーション設定///////////////////

    //アニメーション
    ModelManager::SetAnimFrame(hModel_, ANIM_START_FRAME, ANIM_END_FRAME, PLAYER_ANIM_SPEED);

    /////////////////ファイル読み込んでパスごとの位置取得///////////////////

    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
        SetData("Data/PathData/GameStartCamera/CamPos1.json");
    else
        SetData("Data/PathData/GameStartCamera/CamPos2.json");

    //開始
    hermiteMoveTable_[nowLookNum_]->Start();

    ///////////////ラケット生成///////////////////

    ARGUMENT_INITIALIZE(pRacket_,Instantiate<Racket>(this));
}


//更新
void PlayerBase::ChildUpdate()
{
    //更新
    pState_->Update3D(this);

    //カメラの処理
    CameraBehavior();
}

//カメラの処理
void PlayerBase::CameraBehavior()
{
    //スタートしていないのなら(スタート開始前のカメラワークをする)
    if (!GameManager::GetReferee()->IsGameStart())
    {
        GameStartCamera();
        return;
    }

    //カメラの挙動(サーブレシーブの時とラリー中の時のカメラを分ける)
    if (GameManager::GetReferee()->GetGameStatus() == GameStatus::NOW_SERVE_RECEIVE)
    {
        ServeReceiveCameraBehavior();
        return;
    }

    vector<float> zPos; //Zの位置を格納する用
    vector<float> xPos; //Xの位置を格納する用

    //ボールを取得
    Ball* pBall = GameManager::GetpBall();
    if (pBall)
    {
        zPos.push_back(pBall->GetComponent<Transform>()->GetPosition().z);
        xPos.push_back(pBall->GetComponent<Transform>()->GetPosition().x);
    }

    //自分以外のプレイヤーを取得
    PlayerBase* pPlayer = GameManager::GetNotMyPlayer(this);
    if (pPlayer)
    {
        zPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().z);
        xPos.push_back(pPlayer->GetComponent<Transform>()->GetPosition().x);
    }

    //自分自身も格納
    zPos.push_back(transform_->position_.z);
    xPos.push_back(transform_->position_.x);

    //最小値最大値を取得
    pair<vector<float>::iterator, vector<float>::iterator> minmax;
    minmax = minmax_element(zPos.begin(), zPos.end());
    float MaxZ = *minmax.second;
    float MinZ = *minmax.first;
    float sum = abs(MaxZ + MinZ);

    //重心求める
    float centerX = 0;
    for (auto i = xPos.begin(); i != xPos.end(); i++)
    {
        centerX += (*i);
    }
    centerX /= xPos.size();
   
    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
    {
        //カメラのベクトル変換
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - CAM_POS_NORMAL));
        ARGUMENT_INITIALIZE(camVec2_, (CAM_TAR_NORMAL - CAM_POS_NORMAL));

        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 tar = Camera::GetTarget();
        XMFLOAT3 nextPos = { centerX, (transform_->position_.y - XMVectorGetY(camVec_)) * 1.0f + (sum * 0.25f), (MaxZ - XMVectorGetZ(camVec_)) * 1.0f + (sum * 0.25f) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.1f));
        XMFLOAT3 nextTar = VectorToFloat3((nextPos + camVec2_));
        nextTar = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&tar), XMLoadFloat3(&nextTar), 0.1f));
        Camera::SetPosition(nextPos);
        Camera::SetTarget(nextTar);
    }
    //2人目のプレイヤーなら
    else
    {
        //カメラのベクトル変換(2人目はカメラが逆なのでX,Zを逆にする)
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(-CAM_POS_NORMAL.x, CAM_POS_NORMAL.y, -CAM_POS_NORMAL.z)));
        ARGUMENT_INITIALIZE(camVec2_, (XMFLOAT3(-CAM_TAR_NORMAL.x, CAM_TAR_NORMAL.y, -CAM_TAR_NORMAL.z) - XMFLOAT3(-CAM_POS_NORMAL.x, CAM_POS_NORMAL.y, -CAM_POS_NORMAL.z)));

        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 tar = Camera::GetTargetTwo();
        XMFLOAT3 nextPos = { centerX, (transform_->position_.y - XMVectorGetY(camVec_)) * 1.0f + (sum * 0.25f), (MinZ - XMVectorGetZ(camVec_)) * 1.0f + (sum * 0.25f) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.1f));
        XMFLOAT3 nextTar = VectorToFloat3((nextPos + camVec2_));
        nextTar = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&tar), XMLoadFloat3(&nextTar), 0.1f));
        Camera::SetPositionTwo(nextPos);
        Camera::SetTargetTwo(nextTar);
    }
}

//ゲームスタート時のカメラ 
void PlayerBase::GameStartCamera()
{
    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
    {
        Camera::SetPosition(hermiteMoveTable_[nowLookNum_]->Updata());
        Camera::SetTarget(VectorToFloat3(GetComponent<Transform>()->GetPosition() + CAM_TAR_ADD_VALUE));
    }
    else
    {
        Camera::SetPositionTwo(hermiteMoveTable_[nowLookNum_]->Updata());
        Camera::SetTargetTwo(VectorToFloat3(GetComponent<Transform>()->GetPosition() + CAM_TAR_ADD_VALUE));
    }

    //動きが終わったのなら
    if (hermiteMoveTable_[nowLookNum_]->IsFinish())
    {
        nowLookNum_++;

        //サイズオーバーしていたなら
        if (hermiteMoveTable_.size() == nowLookNum_)
            ARGUMENT_INITIALIZE(nowLookNum_, ZERO);

        //開始
        hermiteMoveTable_[nowLookNum_]->ReStart();
    }
}


//サーブレシーブ時のカメラの処理
void PlayerBase::ServeReceiveCameraBehavior()
{
    //1人目のプレイヤーなら
    if (pState_->GetPlayerNum() == 0)
    {
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(transform_->position_.x / 2, CAM_POS_SERVE_RECEIVE.y, CAM_POS_SERVE_RECEIVE.z)));
        XMFLOAT3 pos = Camera::GetPosition();
        XMFLOAT3 nextPos = { (transform_->position_.x - XMVectorGetX(camVec_)), (transform_->position_.y - XMVectorGetY(camVec_)), (transform_->position_.z - XMVectorGetZ(camVec_)) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.05f));
        Camera::SetPosition(nextPos);

        if (GameManager::GetReferee()->GetServer() == this)
            Camera::SetTarget(GameManager::GetReferee()->GetReceiverPosition());
        else
            Camera::SetTarget(GameManager::GetReferee()->GetServerPosition());
    }
    else
    {
        ARGUMENT_INITIALIZE(camVec_, (initialPosition_ - XMFLOAT3(transform_->position_.x / 2, CAM_POS_SERVE_RECEIVE.y, -CAM_POS_SERVE_RECEIVE.z)));
        XMFLOAT3 pos = Camera::GetPositionTwo();
        XMFLOAT3 nextPos = { (transform_->position_.x - XMVectorGetX(camVec_)), (transform_->position_.y - XMVectorGetY(camVec_)), (transform_->position_.z - XMVectorGetZ(camVec_)) };
        nextPos = VectorToFloat3(XMVectorLerp(XMLoadFloat3(&pos), XMLoadFloat3(&nextPos), 0.05f));
        Camera::SetPositionTwo(nextPos);

        if (GameManager::GetReferee()->GetServer() == this)
            Camera::SetTargetTwo(GameManager::GetReferee()->GetReceiverPosition());
        else
            Camera::SetTargetTwo(GameManager::GetReferee()->GetServerPosition());
    }
        
}

//データセット
void PlayerBase::SetData(string posFileName)
{
    //新しく追加
    hermiteMoveTable_.push_back(std::make_unique<HermiteSplineMove>());

    //読み込み
    ifstream ifsPos(posFileName);
    json json_object_Pos;
    ifsPos >> json_object_Pos;

    //各値取得
    for (auto it = json_object_Pos.begin(); it != json_object_Pos.end(); it++) {

        hermiteMoveTable_[hermiteMoveTable_.size() - 1]->AddPath(XMFLOAT3(json_object_Pos[it.key()]["Position"][0], json_object_Pos[it.key()]["Position"][1], json_object_Pos[it.key()]["Position"][2]), XMFLOAT3(50, ZERO, ZERO));
    }
}