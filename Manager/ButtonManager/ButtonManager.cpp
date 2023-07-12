#include "ButtonManager.h"
#include "../../UI/Button/ButtonBase.h"
#include "../../Engine/ResourceManager/Global.h"
#include "../AudioManager/OtherAudioManager/OtherAudioManager.h"
#include <vector>
#include<algorithm>


//定数
namespace
{
	static const float PAD_STICK_SLOPE_RIGHT = 0.8f;  //パッドのLスティックの右の傾き
	static const float PAD_STICK_SLOPE_LEFT  = -0.8f; //パッドのLスティックの左の傾き
	static const float PAD_STICK_SLOPE_UP    = 0.8f;  //パッドのLスティックの上の傾き
	static const float PAD_STICK_SLOPE_DOWN  = -0.8f; //パッドのLスティックの下の傾き
}


//画面に表示されているボタンを管理する
namespace ButtonManager
{

	//現在使われているボタンを格納する変数
	std::vector<ButtonBase*> nowUseButton;

	//XとYの前回入力保存用
	float beforeXSlope[2] = { ZERO,ZERO };
	float beforeYSlope[2] = { ZERO,ZERO };

	//XとYの現在の入力保存用
	float NowXSlope[2] = { ZERO,ZERO };
	float NowYSlope[2] = { ZERO,ZERO };

	//更新
	void Update()
	{
		//もしボタンが使われていなかったらこの先は処理しない
		if (nowUseButton.empty()) return;

		//各コントローラーで選択されているボタン格納用
		ButtonBase* pButtonController0 = nullptr;
		ButtonBase* pButtonController1 = nullptr;

		//最後まで回してnullptrのものは削除・選択されているボタンを見つける
		for (auto i = nowUseButton.begin(); i != nowUseButton.end();)
		{
			//nullptrだったら削除
			if ((*i) == nullptr)
				i = nowUseButton.erase(i);
			else
			{
				//選択されていたら格納
				if ((*i)->IsSelect() && (*i)->GetControllerNum() == 0) pButtonController0 = (*i);
				if ((*i)->IsSelect() && (*i)->GetControllerNum() == 1) pButtonController1 = (*i);

				//次に進める
				i++;
			}
		}

		//nullじゃないのなら入力処理
		if (pButtonController0 != nullptr) Input(pButtonController0);
		if (pButtonController1 != nullptr) Input(pButtonController1,1);
	}

	//入力
	void Input(ButtonBase* button, int numController)
	{

		//選択されているボタンのxとyを保存
		float x = button->GetComponent<Transform>()->GetPosition().x;
		float y = button->GetComponent<Transform>()->GetPosition().y;

		//前回の傾きを取得
		ARGUMENT_INITIALIZE(beforeXSlope[numController], NowXSlope[numController]);
		ARGUMENT_INITIALIZE(beforeYSlope[numController], NowYSlope[numController]);

		//PadLスティックの傾きを保存
		ARGUMENT_INITIALIZE(NowXSlope[numController],Input::GetPadStickL(numController).x);
		ARGUMENT_INITIALIZE(NowYSlope[numController],Input::GetPadStickL(numController).y);

		//保存用
		std::vector<std::pair<float, ButtonBase*>> date;

		//傾きが定数より大きければ
		if (NowXSlope[numController] >= PAD_STICK_SLOPE_RIGHT && beforeXSlope[numController] <= PAD_STICK_SLOPE_RIGHT)
		{

			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも大きければ
				if ((*i)->GetComponent<Transform>()->GetPosition().x > x)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().x,(*i)});
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{

			//選択されているボタンも追加
			date.push_back({ x,button });

			//ソート(昇順)
			sort(date.begin(), date.end());

			//すでに選択されているのならこの先処理しない
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//選択解除
			button->SetSelect(false, numController);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする(前回のボタンの位置を格納)
			button->SetBeforeButtonSelectPos((*(date.begin())).second->GetComponent<Transform>()->GetPosition());
			button->SetSelect(true, numController);

			return;
		}

		//傾きが定数より小さければ
		if (NowXSlope[numController] <= PAD_STICK_SLOPE_LEFT && beforeXSlope[numController] >= PAD_STICK_SLOPE_LEFT)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも小さければ
				if ((*i)->GetComponent<Transform>()->GetPosition().x < x)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().x,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{

			//選択されているボタンも追加
			date.push_back({ x,button });

			//ソート(降順)
			sort(date.rbegin(), date.rend());

			//すでに選択されているのならこの先処理しない
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//選択解除
			button->SetSelect(false, numController);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true, numController);

			return;
		}

		//傾きが定数より大きければ
		if (NowYSlope[numController] >= PAD_STICK_SLOPE_UP && beforeYSlope[numController] <= PAD_STICK_SLOPE_UP)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Yの座標が選択されていたボタンをよりも大きければ
				if ((*i)->GetComponent<Transform>()->GetPosition().y > y)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().y,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{

			//選択されているボタンも追加
			date.push_back({ y,button });

			//ソート(昇順)
			sort(date.begin(), date.end());

			//すでに選択されているのならこの先処理しない
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//選択解除
			button->SetSelect(false, numController);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true, numController);

			return;
		}

		//傾きが定数より小さければ
		if (NowYSlope[numController] <= PAD_STICK_SLOPE_DOWN && beforeYSlope[numController] >= PAD_STICK_SLOPE_DOWN)
		{
			for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
			{
				//Xの座標が選択されていたボタンをよりも小さければ
				if ((*i)->GetComponent<Transform>()->GetPosition().y < y)
				{
					date.push_back({ (*i)->GetComponent<Transform>()->GetPosition().y,(*i) });
				}
			}
		}

		//もし空じゃなければ
		if (!date.empty())
		{

			//選択されているボタンも追加
			date.push_back({ y,button });

			//ソート(降順)
			sort(date.rbegin(), date.rend());

			//すでに選択されているのならこの先処理しない
			if ((*(date.begin() + 1)).second->IsSelect()) return;

			//選択解除
			button->SetSelect(false, numController);

			//ボタン格納
			ARGUMENT_INITIALIZE(button, (*(date.begin() + 1)).second);

			//選択されるようにする
			button->SetSelect(true, numController);

			return;
		}
				
	}


	//ボタンを追加
	void AddButton(ButtonBase* button) 
	{	
		//ボタンがまだ１つも登録されていないのなら
		if (nowUseButton.empty()) button->SetSelect(true,ZERO);

		//ボタンを追加
		nowUseButton.push_back(button);
	}

	//任意に選択状態のボタンを変更
	void SetSelect(ButtonBase* button, int numController)
	{
		for (auto i = nowUseButton.begin(); i != nowUseButton.end(); i++)
		{
			//同じコントローラー番号なら
			if((*i)->GetControllerNum() == numController)
				(*i)->SetSelect(false, numController);
		}

		button->SetSelect(true, numController);
	}

	//リセットする
	void Reset()
	{
		//空にする
		nowUseButton.clear();
	}
};