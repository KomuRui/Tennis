#include <stdlib.h>
#include "../DirectX/Direct3D.h"
#include "Text.h"
#include "Global.h"
#include "../GameObject/Camera.h"
#include "../../Manager/TextManager/TextManager.h"
#include "../../Manager/GameManager/GameManager.h"


Text::Text() : hPict_(-1), width_(128), height_(256), fileName_("Text/MainFont.png"), rowLength_(16), speed_(1.0f), fpsCount_(0), totalDrawNum_(1)
{
}

Text::~Text()
{
}

//�������i�f�t�H���g�j
HRESULT Text::Initialize(float speed, float textInterval)
{
	//�摜�̃��[�h
	hPict_ = ImageManager::Load(fileName_);
	assert(hPict_ >= 0);

	//60FPS�Ɖ��肷��
	speed_ = speed * 60; 
	textInterval_ = textInterval;

	return S_OK;
}

//�������i�I���W�i���̉摜�j
HRESULT Text::Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength, float speed, float textInterval)
{
	strcpy_s(fileName_, fileName);
	width_ = charWidth;
	height_ = charHeight;
	rowLength_ = rowLength;
	speed_ = speed * 60; //60FPS�Ɖ��肷��
	return Initialize();
}


//�`��i������:�����j
void Text::NumberDraw(float x, float y, const char* str, XMFLOAT2 ratio, float textInterval)
{
	//�\���ʒu�i����j���v�Z
	float px = x, py = y;

	//�P�������\������
	for (int i = 0; str[i] != '\0'; i++)	//������̖����܂ŗ�����I���
	{
		//�\���������������A�摜�̉��Ԗڂɏ����Ă��邩�����߂�
		int id = str[i] - '0';

		//�\���������������A�摜�̂ǂ��ɂ��邩�����߂�
		int x = id % rowLength_;	//�����牽�Ԗ�
		int y = id / rowLength_;	//�ォ�牽�Ԗ�

		//�\������ʒu
		transform.position_.x = px;
		transform.position_.y = py;

		//�傫��
		transform.scale_.x = ratio.x;
		transform.scale_.y = ratio.y;

		transform.parent = nullptr;

		//�\������͈�
		RECT r;
		r.left = width_ * x;
		r.top = height_ * y;
		r.right = width_;
		r.bottom = height_;

		//�\��
		ImageManager::SetText(hPict_, r, &transform);

		//���̈ʒu�ɂ��炷
		px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f) * transform.scale_.x) - textInterval;
	}
}

//�`��i������j�ꕶ�����Ƃɏ��X�ɕ\������
bool Text::SlowlyDraw(int x, int y, const wchar_t* str, float ratio, float textInterval)
{
	//�\���ʒu�i����j���v�Z
	//Sprite�N���X�͒��S��(0,0)�A�E�オ(1,1)�Ƃ������W�����A�����̈����͍����(0,0)�A�h�b�g�P�ʂŎw�肵�Ă���
	float px, py;

	//�����͍��㌴�_�����A�X�v���C�g�͉�ʒ��������_�Ȃ̂ŁA��ʃT�C�Y�̔������炷
	px = (float)(x - Direct3D::screenWidth_ / 2);
	py = (float)(-y + Direct3D::screenHeight_ / 2);	//Y����+-���]

	//�X�v���C�g��Position��1���炷�Ɖ�ʃT�C�Y�̔��������̂ŁA�s�N�Z���P�ʂɕϊ�
	px /= (float)(Direct3D::screenWidth_ / 2.0f);
	py /= (float)(Direct3D::screenHeight_ / 2.0f);

	//�P�������\������
	for (int i = 0; str[i] != '\0'; i++)	//������̖����܂ŗ�����I���
	{
		//�����\�����Ă�������菬�����Ȃ�
		if (i < totalDrawNum_)
		{
			//�����ɂ���ď����ς���
			switch (str[i])
			{
				//���s
				case  '|':
				{
					//�\������X��������
					px = (float)(x - Direct3D::screenWidth_ / 2.0f);
					px /= (float)(Direct3D::screenWidth_ / 2.0f);

					//Y���������炷
					py -= 0.1f;

					break;
				}

				//�󔒂Ȃ炸�炷
				case ' ':
				{
					//���̈ʒu�ɂ��炷
					px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f)) + textInterval;

					break;
				}

				//�J�����ړ�
				case '{':
				{
					//�J�����ݒ�
					Camera::SetUpDirection(UP_VECTOR);
					Camera::InterpolationMove({15,35,0}, { 0,25,0 }, 0.03f);
					break;
				}

				//�J�������ɖ߂�
				case '}':
				{
					break;
				}

				//�ʏ�
				default:
				{
					//�\���������������A�摜�̉��Ԗڂɏ����Ă��邩�����߂�
					int id = TextManager::GetNumber(str[i]);

					//�\���������������A�摜�̂ǂ��ɂ��邩�����߂�
					int x = id % rowLength_;	//�����牽�Ԗ�
					int y = id / rowLength_;	//�ォ�牽�Ԗ�

					//�\������ʒu
					Transform transform;
					transform.position_.x = px;
					transform.position_.y = py;

					//�傫��
					transform.scale_.x *= ratio;
					transform.scale_.y *= ratio;

					ImageManager::SetTransform(hPict_,&transform);

					//�\������͈�
					ImageManager::SetRect(hPict_, width_ * x, height_ * y, width_, height_);

					//�\��
					ImageManager::Draw(hPict_);

					//���̈ʒu�ɂ��炷
					px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f) * transform.scale_.x) + textInterval;

					break;
				}
			}

		}
		else
			break;
	}

	//1�����₷
	fpsCount_++;

	//����fpsCount_���X�s�[�h���傫���Ȃ�����
	if (fpsCount_ > speed_)
	{
		ARGUMENT_INITIALIZE(fpsCount_, (int)ZERO);
		totalDrawNum_++;
	}

	//�����Ō�܂ŕ`��ł��Ă���̂Ȃ�
	if (totalDrawNum_ > wcslen(str))
		return true;

	return false;
}

//�`��i������j��\������
void Text::Draw(float x, float y, const wchar_t* str, XMFLOAT2 ratio, float textInterval)
{
	//�\���ʒu�i����j���v�Z
	//Sprite�N���X�͒��S��(0,0)�A�E�オ(1,1)�Ƃ������W�����A�����̈����͍����(0,0)�A�h�b�g�P�ʂŎw�肵�Ă���
	float px = x, py = y;

	//�P�������\������
	for (int i = 0; str[i] != '\0'; i++)	//������̖����܂ŗ�����I���
	{
		//����@�Ȃ���s
		if (str[i] == '|')
		{
			//�\������X��������
			px = (float)(x - Direct3D::screenWidth_ / 2.0f);
			px /= (float)(Direct3D::screenWidth_ / 2.0f);

			//Y���������炷
			py -= 0.1f;
		}
		//�󔒂Ȃ炸�炷
		else if (str[i] == ' ')
		{
			//���̈ʒu�ɂ��炷
			px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f)) + textInterval;
		}
		else
		{
			//�\���������������A�摜�̉��Ԗڂɏ����Ă��邩�����߂�
			int id = TextManager::GetNumber(str[i]);

			//�\���������������A�摜�̂ǂ��ɂ��邩�����߂�
			int x = id % rowLength_;	//�����牽�Ԗ�
			int y = id / rowLength_;	//�ォ�牽�Ԗ�

			//�\������ʒu
			Transform transform;
			transform.position_.x = px;
			transform.position_.y = py;

			//�傫��
			transform.scale_.x = ratio.x;
			transform.scale_.y = ratio.y;

			ImageManager::SetTransform(hPict_, &transform);

			//�\������͈�
			ImageManager::SetRect(hPict_, width_ * x, height_ * y, width_, height_);

			//�\��
			ImageManager::Draw(hPict_);

			//���̈ʒu�ɂ��炷
			px += (width_ / (float)(Direct3D::screenWidth_ / 2.0f) * transform.scale_.x) + textInterval;
		}
	}

}

//�`��i�����l�j
void Text::NumberDraw(float x, float y, int value, XMFLOAT2 ratio, float textInterval)
{
	//������ɕϊ�
	char str[256];
	sprintf_s(str, "%d", value);

	NumberDraw(x, y, str, ratio, textInterval);
}

//���
void Text::Release()
{
	ImageManager::Release(hPict_);
}
