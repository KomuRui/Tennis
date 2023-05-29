#include "CreateStage.h"
#include "../GameObject/Light.h"
#include "../GameObject/CameraTransitionObject.h"
#include "../../UI/ImageBase.h"
#include "../../UI/ScalingImage.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../GameObject/GameObject.h"
#include "../../Base/Mob.h"
#include "../../Base/NormalObject.h"
#include "../../OtherObject/TitleScene/TennisCourt.h"
#include "../../OtherObject/TitleScene/TennisCourtAround.h"
#include "../../OtherObject/TitleScene/Net.h"
#include "../../OtherObject/TitleScene/NetAround.h"
#include "../../OtherObject/TitleScene/Water.h"
#include "../../OtherObject/TitleScene/Ball.h"
#include "../../Player/PlayerBase.h"
#include "../../Engine/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

//�R���X�g���N�^
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//�I�u�W�F�N�g�쐬
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform t)
{
	
	/////////////////////Player///////////////////////

	if (inName == "Player")
	{
		GameManager::SetpPlayer(InstantiateNormal<PlayerBase>(parent, ModelPathName, inName, t));
	}

	/////////////////////Base///////////////////////

	if (inName == "Mob")
	{
		InstantiateMob3D<Mob>(parent, ModelPathName, inName, t);
	}
	if (inName == "NormalObject")
	{
		InstantiateNormal<NormalObject>(parent, ModelPathName, inName, t);
	}

	/////////////////////UI///////////////////////

	if (inName == "ImageBase")
	{
		InstantiateNormal<ImageBase>(parent, ModelPathName, inName, t);
	}
	if (inName == "ScalingImage")
	{
		InstantiateNormal<ScalingImage>(parent, ModelPathName, inName, t);
	}

	/////////////////////OtherObject///////////////////////

	if (inName == "TennisCourt")
	{
		InstantiateNormal<TennisCourt>(parent, ModelPathName, inName, t);
	}
	if (inName == "TennisCourtAround")
	{
		InstantiateNormal<TennisCourtAround>(parent, ModelPathName, inName, t);
	}
	if (inName == "Net")
	{
		InstantiateNormal<Net>(parent, ModelPathName, inName, t);
	}
	if (inName == "NetAround")
	{
		InstantiateNormal<NetAround>(parent, ModelPathName, inName, t);
	}
	if (inName == "Water")
	{
		InstantiateNormal<Water>(parent, ModelPathName, inName, t);
	}
	if (inName == "Ball")
	{
		InstantiateNormal<Ball>(parent, ModelPathName, inName, t);
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//�J������������ϐ��p��
		StageCameraTransition information;

		//�e��񏉊���
		information.CameraPosition = XMFLOAT3(0,0,0);
		information.CameraTarget = t.rotate_;
		information.CollisionSize = t.scale_;

		//�R���X�g���N�^�Ă�
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//��]�Ɗg���0�ɏ���������
		ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

		pNewObject->SetTransform(t);
		pNewObject->Initialize();
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z, 0), t.scale_.x);
	}

	/////////////////////Gimmick///////////////////////

}

//�e�X�e�[�W�̃t�@�C�����[�h���X�e�[�W���쐬���Ă����
void CreateStage::LoadFileCreateStage(GameObject* parent, std::string filename)
{
	//�e�p�����[�^�i�[�p
	std::string ModelPathName;
	std::string Name;
	Transform t;

	//�e��񂪂���Βǉ�����
	if (parent != nullptr)
		t.pParent_ = parent->GetTransform();
	else
		t.pParent_ = nullptr;

	//�t�@�C���ǂݍ���
	ifstream ifsj("Data/StageData/Title/Title.json");
	json json_object;
	ifsj >> json_object;

	//�e�l�擾
	for (auto it = json_object.begin(); it != json_object.end(); it++) {
		
		ARGUMENT_INITIALIZE(ModelPathName,json_object[it.key()]["FileName"]);
		ARGUMENT_INITIALIZE(Name,json_object[it.key()]["TypeName"]);
		ARGUMENT_INITIALIZE(t.position_,XMFLOAT3(json_object[it.key()]["Position"][0], json_object[it.key()]["Position"][1], json_object[it.key()]["Position"][2]));
		ARGUMENT_INITIALIZE(t.rotate_,XMFLOAT3(json_object[it.key()]["Rotate"][0], json_object[it.key()]["Rotate"][1], json_object[it.key()]["Rotate"][2]));
		ARGUMENT_INITIALIZE(t.scale_,XMFLOAT3(json_object[it.key()]["Scale"][0], json_object[it.key()]["Scale"][1], json_object[it.key()]["Scale"][2]));

		//�p�����[�^����ɃI�u�W�F�N�g�쐬
		CreateObject(parent, ModelPathName, Name, t);
	}	

}

//�e�X�e�[�W�̃t�@�C�����[�h�������Ă����
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//�t�@�C���I�[�v��
	const char* fileName = filename.c_str();
	std::ifstream ifs(fileName);

	//�f�[�^��1������ϐ�
	std::string buf;

	//�K�v�Ȋe�p�����[�^��ۑ�����p�̕�����z��(pos.x,pos,y,pos.z�Ƃ�)
	std::string data[14] = { "" };

	//,�̐�
	int sum = 0;

	//�����܂œǂ�
	while (!ifs.eof())
	{
		//1��buf�Ɋi�[
		std::getline(ifs, buf);

		//buf�̃T�C�Y�����[�v
		for (int i = 0; i < buf.size(); i++)
		{
			//�e�p�����[�^�������data�Ɋi�[���Ă���
			if (buf[i] != ',')
			{
				data[sum] += buf[i];
			}
			else
				sum++;
		}

		//�����i�[���Ă����ϐ�
		CreateStageInfo info;


		//�e�p�����[�^��ϐ��Ɋi�[���Ă���
		info.parent = parent;
		info.ModelPathName = data[0];
		info .inName = data[1];

		Transform t;

		info.t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
		info.t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
		info.t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };


		//�J�����̃|�W�V������K�v�Ƃ���I�u�W�F�N�g�Ȃ�
		if (info.inName.find("Camera") != std::string::npos || info.inName == "ShineLight")
			info.camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
		//����ȊO�͎g��Ȃ��̂�0�ɂ��Ă���
		else
			info.camPos = { 0,0,0 };

		info_.push_back(info);

		//���ׂď�����
		for (int i = 0; i < 14; i++)
		{
			data[i] = "";
		}
		sum = 0;
	}

}

//LoadFile���g���ă��[�h�����t�@�C�������ɃX�e�[�W���쐬
void CreateStage::LoadFileBasedCreateStage()
{
	for (auto i = info_.begin(); i != info_.end(); i++)
	{
		CreateObject((*i).parent, (*i).ModelPathName, (*i).inName, (*i).t);
	}
}

//�쐬�����X�e�[�W�����ׂč폜
void CreateStage::AllCreateStageDelete(bool isKillPlayer)
{
	//������X�e�[�W����
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end();)
	{
		(*i)->KillMe();
		i = createStageAllObject_.erase(i);
	}

	//����Player������̂Ȃ�
	if (GameManager::GetpPlayer() != nullptr && isKillPlayer)GameManager::GetpPlayer()->KillMe();

	//���ׂăN���A
	createStageAllObject_.clear();
}

/// <summary>
/// �쐬�����X�e�[�W���ׂĕ`��ƍX�V���Ȃ��悤��
/// </summary>
void CreateStage::AllCreateStageInvisibleAndLeave()
{
	//������X�e�[�W����
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Invisible();
		(*i)->Leave();
	}
}

/// <summary>
/// �쐬�����S�ẴX�e�[�W���X�V����
/// </summary>
void CreateStage::AllCreateStageUpdate()
{
	//������X�e�[�W����
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		if((*i) != nullptr)
			(*i)->Update();

		//��Ȃ�I��
		if (createStageAllObject_.empty()) return;
	}
}

/// <summary>
/// �쐬�����S�ẴX�e�[�W��`�悷��
/// </summary>
void CreateStage::AllCreateStageDraw()
{
	//������X�e�[�W����
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Draw();
	}
}

/// <summary>
/// �쐬�����X�e�[�W���ׂĕ`��ƍX�V����悤��
/// </summary>
void CreateStage::AllCreateStageVisibleAndEnter()
{
	//������X�e�[�W����
	for (auto i = createStageAllObject_.begin(); i != createStageAllObject_.end(); i++)
	{
		(*i)->Visible();
		(*i)->Enter();
	}
}

//���ʂ̐���
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent,std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath,name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//���ʌ^�̐���(���O�ƃ��f���p�X�w�肵�Ȃ�)
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent, Transform t)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}

//Mob���p������3D�I�u�W�F����
template <class T>
T* CreateStage::InstantiateMob3D(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->SetAngle(t.rotate_.y);
	pNewObject->Initialize();
	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//�{�^���̐���
template <class T>
T* CreateStage::InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	ButtonManager::AddButton(p);

	return p;
}

//���̐���
template <class T>
T* CreateStage::InstantiatePlanet(GameObject* pParent, std::string modelPath, std::string name, Transform t)
{
	T* pNewObject = new T(pParent, modelPath, name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetTransform(t);
	pNewObject->Initialize();

	return pNewObject;
}