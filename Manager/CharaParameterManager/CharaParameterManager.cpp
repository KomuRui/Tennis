#include "CharaParameterManager.h"

namespace
{
	//パラメータ
	struct Parameter
	{
		float speed;      //スピード
		float power;      //パワー
		float technique;  //テクニック
	};

	//各キャラのモデルパス名
	static const string CHARA_MODEL_PATH[] = {
		"MainCharacter/Player.fbx",
		"MainCharacter/Player_Princess.fbx",
		"MainCharacter/Player_Pig.fbx",
		"MainCharacter/Player_Drop.fbx",
		"MainCharacter/Player_Boss.fbx",
		"MainCharacter/Player_BossChild.fbx",
	};

	//キャラパラメータを保存しているjsonファイルのパス
	static const string CHARA_PARAMETER_PATH = "Data/CharaData/CharaParameter.json";
}

//各キャラクターのパラメータを管理
namespace CharaParameterManager
{

	//パラメータ管理するmap
	map<string, Parameter> parameterTable;

	//初期化
	void Initialize()
	{
		//ラリー
		ifstream ifs(CHARA_PARAMETER_PATH);
		json json_Object;
		ifs >> json_Object;

		//基準点分回す
		for (string name : CHARA_MODEL_PATH)
		{
			parameterTable[name].speed = json_Object[name]["speed"];
			parameterTable[name].power = json_Object[name]["power"];
			parameterTable[name].technique = json_Object[name]["technique"];
		}
	}

	//キャラのスピードを取得
	float GetCharaSpeed(string charaModelPath) { return parameterTable[charaModelPath].speed; }

	//キャラのパワーを取得
	float GetCharaPower(string charaModelPath) { return parameterTable[charaModelPath].power; }

	//キャラのテクニックを取得
	float GetCharaTechnique(string charaModelPath) { return parameterTable[charaModelPath].technique; }
}