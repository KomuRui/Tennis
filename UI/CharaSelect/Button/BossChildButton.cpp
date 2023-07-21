#include "BossChildButton.h"
#include "../../../Engine/ResourceManager/ImageManager.h"
#include "../../../Manager/ButtonManager/ButtonManager.h"
#include "../../../Manager/GameManager/GameManager.h"

//�萔
namespace
{
	static const XMFLOAT3 CHARA_IMAGE_POS_ADD_VALUE = { ZERO,2.0f,ZERO };  //�L�����摜�̑΂��Ẳ��Z�l
	static const XMFLOAT3 POS_ADD_VALUE = {  0.75f, 0.75f, ZERO };         //�|�W�V�����ɑ΂��Ẳ��Z�l
	static const float EASING_TIME = 0.6f;                                 //�C�[�W���O����
	static const float SELECT_PICT_EASING_TIME = 0.75f;                    //�I���摜�̃C�[�W���O����
}

//�R���X�g���N�^
BossChildButton::BossChildButton(GameObject* parent, std::string modelPath, std::string name)
	:EasingButton(parent, modelPath, name), hCharaPict_(-1)
{
	ARGUMENT_INITIALIZE(tCharaPict_, std::make_unique<Transform>());
	ARGUMENT_INITIALIZE(easingCharaPict_, std::make_unique<EasingMove>());
}

//������
void BossChildButton::ChildInitialize()
{
	//�R���g���[���[�̑I���摜�̃g�����X�t�H�[����ύX
	ARGUMENT_INITIALIZE(charaSelectSceneUI, ((CharaSelectSceneUI*)FindObject("CharaSelectSceneUI")));

	//�C�[�W���O�ݒ�
	easing_->Reset(&transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE), transform_->position_, EASING_TIME, Easing::OutBack);
	ARGUMENT_INITIALIZE(transform_->position_, VectorToFloat3(transform_->position_ + POS_ADD_VALUE));

	//�摜���[�h
	ARGUMENT_INITIALIZE(hCharaPict_, ImageManager::Load("Image/CharaSelect/BossChild.png"));
	tCharaPict_.get()->SetPosition(charaSelectSceneUI->GetCharaPictPos(numController_));
}

//�X�V
void BossChildButton::EasingButtonChileUpdate()
{
	//���������Ă��邩�C�[�W���O�������Ō�܂ŏI�����Ă���̂Ȃ�
	if (isMove_ && charaSelectSceneUI->GetEasing(numController_).IsFinish() && easingCharaPict_->IsFinish())
		ARGUMENT_INITIALIZE(isMove_, false);

	easingCharaPict_->Move();

	//�I��������Ԃ�B�{�^�����������Ȃ�
	if (!charaSelectSceneUI->IsDrawConfirmationUI() && isSelectNoChange_ && Input::IsPadButtonDown(XINPUT_GAMEPAD_B, numController_))
	{
		charaSelectSceneUI->SetIsOK(false, numController_);
		SetSelectNoChange(false);
	}
}

//�`��
void BossChildButton::ChildDraw()
{
	//�I������Ă���̂Ȃ�
	if (isSelect_ || !easingCharaPict_->IsFinish())
	{
		ImageManager::SetTransform(hCharaPict_, tCharaPict_.get());
		ImageManager::SetUi(hCharaPict_);
	}
}

//�{�^���������ꂽ�牽���邩
void BossChildButton::IsButtonPush()
{
	charaSelectSceneUI->SetIsOK(true, numController_);

	//�������ݗp
	json json_object;

	//�����̃f�[�^��ǂݍ���
	std::ifstream input_file("Data/StageData/Play/PlayObject.json");
	input_file >> json_object;
	input_file.close();

	//�t�@�C���l�[���X�V
	char fileName[50] = "MainCharacter/Player_BossChild.fbx";
	if (numController_)
		json_object["Player1"]["FileName"] = fileName;
	else
		json_object["Player"]["FileName"] = fileName;

	//��������
	std::ofstream output_file("Data/StageData/Play/PlayObject.json");
	output_file << json_object;
	output_file.close();

	SetSelectNoChange(true);
}

//�{�^�����I�����ꂽ�u�Ԃɉ������邩
void BossChildButton::IsButtonSelect()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	easingCharaPict_->Reset(&tCharaPict_.get()->position_, VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE), charaSelectSceneUI->GetCharaPictPos(numController_), EASING_TIME, Easing::InCubic);
	tCharaPict_.get()->SetPosition(VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) + CHARA_IMAGE_POS_ADD_VALUE));
	charaSelectSceneUI->ResetEasing(transform_->position_, numController_);
}

//�{�^�����I���������ꂽ�u�Ԃɉ������邩
void BossChildButton::IsButtonSelectRelease()
{
	ARGUMENT_INITIALIZE(isMove_, true);
	easingCharaPict_->Reset(&tCharaPict_.get()->position_, charaSelectSceneUI->GetCharaPictPos(numController_), VectorToFloat3(charaSelectSceneUI->GetCharaPictPos(numController_) - CHARA_IMAGE_POS_ADD_VALUE), EASING_TIME, Easing::InCubic);
}
