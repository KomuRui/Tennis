#include "ImageBase.h"
#include "../Engine/ResourceManager/ImageManager.h"

//�R���X�g���N�^
ImageBase::ImageBase(GameObject* parent, std::string modelPath, std::string name)
	: GameObject(parent, name), hPict_(-1), ModelNamePath_(modelPath)
{
}

//������
void ImageBase::Initialize()
{

	///////////////�摜�f�[�^�̃��[�h///////////////////
	
	hPict_ = ImageManager::Load(ModelNamePath_);
	ARGUMENT_INITIALIZE(pathName_, ModelNamePath_);
	assert(hPict_ >= ZERO);

	//�p���p�̏�����
	ChildInitialize();
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void ImageBase::StartUpdate()
{
	//�p���p��Start�X�V
	ChildStartUpdate();
}

//�X�V
void ImageBase::Update()
{
	//�p���p�̍X�V
	ChildUpdate();
}

//�`��
void ImageBase::Draw()
{
	//�摜�\��
	ImageManager::SetTransform(hPict_, transform_);
	ImageManager::SetUi(hPict_);

	//�p���p�̕`��
	ChildDraw();
}

//���
void ImageBase::Release()
{
}
