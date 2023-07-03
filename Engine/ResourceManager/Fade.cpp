#include "Fade.h"
#include "../System.h"

//�萔
namespace
{
	//�t�@�C���l�[���ɕK�v�ȏ��
	struct FNAME_LIST {
		int ID;
		std::string NAME;
	};

	//�V�[����ID�ƃt�@�C���p�X�l�[���̐ݒ�
	static const FNAME_LIST FNAME[] = {
		{ SCENE_ID_PLAY, "Tutorial1Fade" },
	};

	//�t�@�C���p�X�ɋ��ʂ��ĕK�v�Ȃ���
	static const std::string PATH = "Image/Fade/";

	//�t�F�[�h����Ƃ��̉��Z���鋗��
	static const float FADE_ADD_DISTANCE = 10.0f;

	//�t�F�[�h����Ƃ��̉��Z���铧���x
	static const float FADE_ADD_ALPHA = 0.01f;
}

//�t�F�[�h���s���Ƃ��Ɏg��(��̂P�x�ɂP�񂵂��g���Ȃ��̂�namespace)
namespace Fade
{

	///////////////////////////////�ϐ�//////////////////////////////////

	int fadeStatus_;    //�t�F�[�h�̏��
	float maxDistance_; //�~�t�F�[�h�Ŏg�p����ő勗��
	float nowDistance_; //�~�t�F�[�h�Ŏg�p���鍡�̋���

	//�~�t�F�[�h�p�̉摜(�V�[���̐���)
	Sprite* pSprite_[SCENE_ID_MAX];

	//�Q�[���I�[�o�[�t�F�C�h�p�̉摜
	Sprite* pGameOver_;
	EasingMove* pEasingScale_; //�C�[�W���O���邽�߂̃N���X(�g��k��)
	EasingMove* pEasingRotate_;//�C�[�W���O���邽�߂̃N���X(��])
	Transform gameOver_;       //�Q�[���I�[�o�[�摜�p�̃g�����X�t�H�[��

	//�ʏ�t�F�C�h�p�̉摜(��)
	Sprite* pNormal_;
	Transform normal_;         //�ʏ�t�F�C�h�p�̉摜�̃g�����X�t�H�[��
	float normalAlpha_;        //�ʏ�t�F�C�h�̓����x

	//�~�t�F�[�h�p�̉摜�̕�����(�V�[���̐���)
	std::string fadeImage_[SCENE_ID_MAX];

	///////////////////////////////�֐�//////////////////////////////////

	//������
	void Fade::Initialize()
	{
		//�t�F�[�h�p�̉摜���[�h
		for (auto& f : FNAME) {
			ARGUMENT_INITIALIZE(pSprite_[f.ID], new Sprite);
			pSprite_[f.ID]->Load(PATH + f.NAME + ".png");
		}

		//�Q�[���I�[�o�[�p�̉摜���[�h
		ARGUMENT_INITIALIZE(pGameOver_, new Sprite);
		pGameOver_->Load("Image/Player/GameOver.png");

		//�ʏ�p�̉摜���[�h
		ARGUMENT_INITIALIZE(pNormal_, new Sprite);
		pNormal_->Load("Image/Fade/NormalFade.png");

		//�e�ϐ�������
		ARGUMENT_INITIALIZE(normalAlpha_, ZERO);
		ARGUMENT_INITIALIZE(fadeStatus_, NOOP);
		ARGUMENT_INITIALIZE(maxDistance_, (float)(std::sqrt(pow((Direct3D::screenHeight_ / 2), 2) + pow((Direct3D::screenWidth_ / 2), 2))));
		ARGUMENT_INITIALIZE(nowDistance_, ZERO);
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&gameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&gameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
	}

	//�V�[���J�ڂ̎��̏�����
	void Fade::SceneTransitionInitialize()
	{
		//���낢�돉������Ԃɂ��Ă���
		ARGUMENT_INITIALIZE(pEasingScale_, new EasingMove(&gameOver_.scale_, XMFLOAT3(5, 5, 5), XMFLOAT3(1, 1, 1), 4.0f, Easing::OutQuart));
		ARGUMENT_INITIALIZE(pEasingRotate_, new EasingMove(&gameOver_.rotate_, XMFLOAT3(0, 0, 720), XMFLOAT3(0, 0, 0), 4.0f, Easing::OutQuart));
	}

	//�`��
	void Fade::Draw()
	{
		//�t�F�[�h�p�̕`��
		FadeDraw();
	}

	///////////////////////////////�Z�b�g�Q�b�g�֐�//////////////////////////////////

	//��ԃZ�b�g
	void Fade::SetFadeStatus(int status, std::string filename)
	{
		//�����t�@�C���l�[���̋L�q������΃m�[�}���t�F�C�h�̉摜�ύX
		if(filename != "") pNormal_->Load(filename);

		//�X�e�[�^�X�X�V
		ARGUMENT_INITIALIZE(fadeStatus_, status);

		//��Ԃɂ���ĕ�����
		switch (fadeStatus_)
		{

			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�~�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			ARGUMENT_INITIALIZE(nowDistance_, ZERO);
			break;

			//�~�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			ARGUMENT_INITIALIZE(nowDistance_, maxDistance_);
			break;

			//�ʏ�t�F�[�h�C��
		case FADE_NORMAL_IN:

			ARGUMENT_INITIALIZE(normalAlpha_, ZERO);
			break;

			//�ʏ�t�F�[�h�A�E�g
		case FADE_NORMAL_OUT:

			ARGUMENT_INITIALIZE(normalAlpha_, 1.0f);
			break;

			//����ȊO
		default:

			break;
		}
	}

	//��ԃQ�b�g
	int Fade::GetFadeStatus() { return fadeStatus_; }

	//�ʏ�̃t�F�[�h����������Ȃ����ǂ���
	bool isNormalFadeNotTransparency() { return (normalAlpha_ >= 1.0f); }

	///////////////////////////////�t�F�[�h�p�֐�////////////////////////////////////

	//�t�F�[�h�`��
	void Fade::FadeDraw()
	{
		//��Ԃɂ���ĕς���
		switch (fadeStatus_)
		{
			//�摜�����`��
		case DRAW:

			NormalDraw();
			break;

			//�~�t�F�[�h�C��
		case FADE_CIRCLE_IN:

			FadeInCircleDraw();
			break;

			//�~�t�F�[�h�A�E�g
		case FADE_CIRCLE_OUT:

			FadeOutCircleDraw();
			break;

			//�ʏ�t�F�[�h�C��
		case FADE_NORMAL_IN:

			FadeInNormalDraw();
			break;

			//�ʏ�t�F�[�h�A�E�g
		case FADE_NORMAL_OUT:

			FadeOutNormalDraw();
			break;

			//����ȊO
		default:

			break;
		}

	}

	//�`��
	void Fade::NormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(&t, rect,1.0f);
	}

	//�~�t�F�[�h�C���`��
	void Fade::FadeInCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ += FADE_ADD_DISTANCE;

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(&t, nowDistance_, rect);
	};

	//�~�t�F�[�h�A�E�g�`��
	void Fade::FadeOutCircleDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		nowDistance_ -= FADE_ADD_DISTANCE;

		if (nowDistance_ < ZERO)
			ARGUMENT_INITIALIZE(nowDistance_, ZERO);

		//�`��
		pSprite_[GameManager::GetpSceneManager()->GetSceneId()]->Draw(&t, nowDistance_, rect);
	};

    //�t�F�[�h�C���`��
	void Fade::FadeInNormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//���X�ɓ�������Ȃ�
		normalAlpha_ += FADE_ADD_ALPHA;

		//�`��
		pNormal_->Draw(&t,rect, normalAlpha_);
	}

	//�t�F�[�h�A�E�g�`��
	void Fade::FadeOutNormalDraw()
	{
		//�摜�p��transform
		Transform t;

		//�e�N�X�`���̃T�C�Y�擾
		XMFLOAT3 size = pNormal_->GetTextureSize();

		//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
		RECT rect;
		rect.left = (LONG)ZERO;
		rect.top = (LONG)ZERO;
		rect.right = (long)size.x;
		rect.bottom = (long)size.y;

		//���X�ɓ�����
		normalAlpha_ -= FADE_ADD_ALPHA;

		//�`��
		pNormal_->Draw(&t,rect, normalAlpha_);
	}
}
