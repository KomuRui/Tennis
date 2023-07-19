#include "CreateStage.h"
#include "../GameObject/Light.h"
#include "../GameObject/CameraTransitionObject.h"
#include "../../UI/ImageBase.h"
#include "../../UI/ScalingImage.h"
#include "../../UI/Title/StartImage.h"
#include "../../UI/ModeSelect/ScreenFadeImage.h"
#include "../../UI/ModeSelect/RogoImage.h"
#include "../../UI/ModeSelect/PlayerImage.h"
#include "../../UI/ModeSelect/Button/ExplanationButton.h"
#include "../../UI/ModeSelect/Button/MiniGameButton.h"
#include "../../UI/ModeSelect/Button/OneVSOneButton.h"
#include "../../UI/CharaSelect/Button/BossButton.h"
#include "../../UI/CharaSelect/Button/BossChildButton.h"
#include "../../UI/CharaSelect/Button/DropButton.h"
#include "../../UI/CharaSelect/Button/MainCharButton.h"
#include "../../UI/CharaSelect/Button/PigButton.h"
#include "../../UI/CharaSelect/Button/PrincessButton.h"
#include "../../UI/CharaSelect/QuestionImage.h"
#include "../../UI/CharaSelect/Button/YesButton.h"
#include "../../UI/CharaSelect/Button/NoButton.h"
#include "../../UI/CharaSelect/CharaSelectScreenFadeImage.h"
#include "../../UI/CourtSelect/CourtSelectScreenFadeImage.h"
#include "../../UI/CourtSelect/Button/ClayCourtButton.h"
#include "../../UI/CourtSelect/Button/GrassCourtButton.h"
#include "../../UI/CourtSelect/Button/HardCourtButton.h"
#include "../../UI/InfoSelect/InfoSelectScreenFadeImage.h"
#include "../../UI/InfoSelect/Button/GameButton.h"
#include "../../UI/InfoSelect/Button/SetButton.h"
#include "../../Manager/ButtonManager/ButtonManager.h"
#include "../../Manager/GameManager/GameManager.h"
#include "../GameObject/GameObject.h"
#include "../../Base/NormalObject.h"
#include "../../OtherObject/PlayScene/TennisCourt.h"
#include "../../OtherObject/PlayScene/TennisCourtAround.h"
#include "../../OtherObject/PlayScene/Net.h"
#include "../../OtherObject/PlayScene/NetAround.h"
#include "../../OtherObject/PlayScene/Water.h"
#include "../../OtherObject/PlayScene/Ball.h"
#include "../../OtherObject/PlayScene/Referee.h"
#include "../../OtherObject/PlayScene/Sky.h"
#include "../../Player/PlayerBase.h"
#include "../Component/Transform/Transform.h"
#include "../../Engine/nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

//�R���X�g���N�^
CreateStage::CreateStage()
	:createShineController_(false)
{
}

//�I�u�W�F�N�g�쐬
void CreateStage::CreateObject(GameObject* parent, std::string ModelPathName, std::string inName, Transform* t)
{
	
	/////////////////////Player///////////////////////

	if (inName == "Player")
	{
		GameManager::SetpPlayer(InstantiateNormal<PlayerBase>(parent, ModelPathName, inName, t));
	}

	/////////////////////Base///////////////////////

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
	if (inName == "StartImage")
	{
		InstantiateNormal<StartImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "ScreenFadeImage")
	{
		InstantiateNormal<ScreenFadeImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "RogoImage")
	{
		InstantiateNormal<RogoImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "PlayerImage")
	{
		InstantiateNormal<PlayerImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "QuestionImage")
	{
		InstantiateNormal<QuestionImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "CharaSelectScreenFadeImage")
	{
		InstantiateNormal<CharaSelectScreenFadeImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "CourtSelectScreenFadeImage")
	{
		InstantiateNormal<CourtSelectScreenFadeImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "InfoSelectScreenFadeImage")
	{
		InstantiateNormal<InfoSelectScreenFadeImage>(parent, ModelPathName, inName, t);
	}
	if (inName == "ExplanationButton")
	{
		InstantiateButton<ExplanationButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "MiniGameButton")
	{
		InstantiateButton<MiniGameButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "OneVSOneButton")
	{
		InstantiateButton<OneVSOneButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "BossButton")
	{
		InstantiateButton<BossButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "BossChildButton")
	{
		InstantiateButton<BossChildButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "DropButton")
	{
		InstantiateButton<DropButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "MainCharButton")
	{
		InstantiateButton<MainCharButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "PigButton")
	{
		InstantiateButton<PigButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "PrincessButton")
	{
		InstantiateButton<PrincessButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "YesButton")
	{
		InstantiateButton<YesButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "NoButton")
	{
		InstantiateButton<NoButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "HardCourtButton")
	{
		InstantiateButton<HardCourtButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "ClayCourtButton")
	{
		InstantiateButton<ClayCourtButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "GrassCourtButton")
	{
		InstantiateButton<GrassCourtButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "SetButton")
	{
		InstantiateButton<SetButton>(parent, ModelPathName, inName, t);
	}
	if (inName == "GameButton")
	{
		InstantiateButton<GameButton>(parent, ModelPathName, inName, t);
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
		GameManager::SetpBall(InstantiateNormal<Ball>(parent, ModelPathName, inName, t));
	}
	if (inName == "Sky")
	{
		InstantiateNormal<Sky>(parent, ModelPathName, inName, t);
	}

	/////////////////////Camera////////////////////////

	if (inName == "Camera")
	{
		//�J������������ϐ��p��
		StageCameraTransition information;

		//�e��񏉊���
		information.CameraPosition = XMFLOAT3(0,0,0);
		information.CameraTarget = t->rotate_;
		information.CollisionSize = t->scale_;

		//�R���X�g���N�^�Ă�
		CameraTransitionObject* pNewObject = new CameraTransitionObject(parent, information);
		if (parent != nullptr)
		{
			parent->PushBackChild(pNewObject);
		}

		//��]�Ɗg���0�ɏ���������
		ARGUMENT_INITIALIZE(t->rotate_, XMFLOAT3(0, 0, 0));
		ARGUMENT_INITIALIZE(t->scale_, XMFLOAT3(0, 0, 0));

		pNewObject->GetComponent<Transform>()->SetTransform(t);
		pNewObject->Initialize();
		createStageAllObject_.push_back(pNewObject);
	}

	/////////////////////Light/////////////////////////

	if (inName == "Light")
	{
		Light::CreateLight(XMFLOAT4(t->position_.x, t->position_.y, t->position_.z, 0), t->scale_.x);
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
		t.parent = parent;
	else
		t.parent = nullptr;

	//�t�@�C���ǂݍ���
	ifstream ifs(filename);
	json json_object;
	ifs >> json_object;


	//�e�l�擾
	for (auto it = json_object.begin(); it != json_object.end(); it++) {
		
		ARGUMENT_INITIALIZE(ModelPathName,json_object[it.key()]["FileName"]);
		ARGUMENT_INITIALIZE(Name,json_object[it.key()]["TypeName"]);
		ARGUMENT_INITIALIZE(t.position_,XMFLOAT3(json_object[it.key()]["Position"][0], json_object[it.key()]["Position"][1], json_object[it.key()]["Position"][2]));
		ARGUMENT_INITIALIZE(t.rotate_,XMFLOAT3(json_object[it.key()]["Rotate"][0], json_object[it.key()]["Rotate"][1], json_object[it.key()]["Rotate"][2]));
		ARGUMENT_INITIALIZE(t.scale_,XMFLOAT3(json_object[it.key()]["Scale"][0], json_object[it.key()]["Scale"][1], json_object[it.key()]["Scale"][2]));
		ARGUMENT_INITIALIZE(t.parent, parent);

		//�p�����[�^����ɃI�u�W�F�N�g�쐬
		CreateObject(parent, ModelPathName, Name, &t);
	}	

}

//�e�X�e�[�W�̃t�@�C�����[�h�������Ă����
void CreateStage::LoadFile(GameObject* parent, std::string filename)
{
	//�e�p�����[�^�i�[�p
	std::string ModelPathName;
	std::string Name;
	Transform t;

	//�e��񂪂���Βǉ�����
	if (parent != nullptr)
		t.parent = parent;
	else
		t.parent = nullptr;

	//�t�@�C���ǂݍ���
	ifstream ifs(filename);
	json json_object;
	ifs >> json_object;

	//�e�l�擾
	for (auto it = json_object.begin(); it != json_object.end(); it++) {

		//�����i�[���Ă����ϐ�
		CreateStageInfo info;

		ARGUMENT_INITIALIZE(info.ModelPathName, json_object[it.key()]["FileName"]);
		ARGUMENT_INITIALIZE(info.inName, json_object[it.key()]["TypeName"]);
		ARGUMENT_INITIALIZE(info.t->position_, XMFLOAT3(json_object[it.key()]["Position"][0], json_object[it.key()]["Position"][1], json_object[it.key()]["Position"][2]));
		ARGUMENT_INITIALIZE(info.t->rotate_, XMFLOAT3(json_object[it.key()]["Rotate"][0], json_object[it.key()]["Rotate"][1], json_object[it.key()]["Rotate"][2]));
		ARGUMENT_INITIALIZE(info.t->scale_, XMFLOAT3(json_object[it.key()]["Scale"][0], json_object[it.key()]["Scale"][1], json_object[it.key()]["Scale"][2]));
		ARGUMENT_INITIALIZE(info.t->parent, t.parent);

		//�ۑ����Ă���
		info_.push_back(info);
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
T* CreateStage::InstantiateNormal(GameObject* pParent,std::string modelPath, std::string name, Transform* t)
{
	T* pNewObject = new T(pParent, modelPath,name);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}

	if (pNewObject->GetComponent<Transform>())
		pNewObject->GetComponent<Transform>()->SetTransform(t);

	pNewObject->Initialize();

	createStageAllObject_.push_back(pNewObject);

	return pNewObject;
}

//���ʌ^�̐���(���O�ƃ��f���p�X�w�肵�Ȃ�)
template <class T>
T* CreateStage::InstantiateNormal(GameObject* pParent, Transform* t)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}

	if(pNewObject->GetComponent<Transform>())
		pNewObject->GetComponent<Transform>()->SetTransform(t);

	pNewObject->Initialize();

	return pNewObject;
}

//�{�^���̐���
template <class T>
T* CreateStage::InstantiateButton(GameObject* pParent, std::string modelPath, std::string name, Transform* t)
{
	T* p = InstantiateNormal<T>(pParent, modelPath, name, t);
	ButtonManager::AddButton(p);

	return p;
}