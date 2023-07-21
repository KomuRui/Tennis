#include "CharaParameterManager.h"

namespace
{
	//�p�����[�^
	struct Parameter
	{
		float speed;      //�X�s�[�h
		float power;      //�p���[
		float technique;  //�e�N�j�b�N
	};

	//�e�L�����̃��f���p�X��
	static const string CHARA_MODEL_PATH[] = {
		"MainCharacter/Player.fbx",
		"MainCharacter/Player_Princess.fbx",
		"MainCharacter/Player_Pig.fbx",
		"MainCharacter/Player_Drop.fbx",
		"MainCharacter/Player_Boss.fbx",
		"MainCharacter/Player_BossChild.fbx",
	};

	//�L�����p�����[�^��ۑ����Ă���json�t�@�C���̃p�X
	static const string CHARA_PARAMETER_PATH = "Data/CharaData/CharaParameter.json";
}

//�e�L�����N�^�[�̃p�����[�^���Ǘ�
namespace CharaParameterManager
{

	//�p�����[�^�Ǘ�����map
	map<string, Parameter> parameterTable;

	//������
	void Initialize()
	{
		//�����[
		ifstream ifs(CHARA_PARAMETER_PATH);
		json json_Object;
		ifs >> json_Object;

		//��_����
		for (string name : CHARA_MODEL_PATH)
		{
			parameterTable[name].speed = json_Object[name]["speed"];
			parameterTable[name].power = json_Object[name]["power"];
			parameterTable[name].technique = json_Object[name]["technique"];
		}
	}

	//�L�����̃X�s�[�h���擾
	float GetCharaSpeed(string charaModelPath) { return parameterTable[charaModelPath].speed; }

	//�L�����̃p���[���擾
	float GetCharaPower(string charaModelPath) { return parameterTable[charaModelPath].power; }

	//�L�����̃e�N�j�b�N���擾
	float GetCharaTechnique(string charaModelPath) { return parameterTable[charaModelPath].technique; }
}