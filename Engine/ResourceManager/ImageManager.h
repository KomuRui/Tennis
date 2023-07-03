#pragma once

#include <vector>
#include <string>
#include "../DirectX/Sprite.h"
#include "../Component/Transform/Transform.h"

//-----------------------------------------------------------
//2D�摜���Ǘ�����
//-----------------------------------------------------------
namespace ImageManager
{
	//�摜���
	struct ImageData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�����摜�f�[�^�̃A�h���X
		Sprite*		pSprite;

		//�؂蔲���͈�
		RECT		rect;

		//�A���t�@
		float		alpha;

		//�s��
		Transform* transform;

		//��ʃL���v�`�����ǂ���
		bool isScreenCapture;

		//�R���X�g���N�^
		ImageData() : pSprite(nullptr)
		{
			fileName = "";
			alpha = 1.0f;
			pSprite = nullptr;
			isScreenCapture = false;
		}
	};


	//������
	void Initialize();

	//�摜�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̉摜�f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int handle);

	/// <summary>
	/// Ui�`��
	/// </summary>
	void UiDraw();

	//�C�ӂ̉摜���J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẳ摜�����
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	/// <summary>
	/// UI���Z�b�g(�Ō�ɕ`�悵�����Ƃ��Ɏg��)
	/// </summary>
	/// <param name="handle">�ԍ�</param>
	void SetUi(int handle);

	//�؂蔲���͈͂̐ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fx		�؂蔲�������͈͂̍��[�w���W
	//�����Fy		�؂蔲�������͈͂̏�[�x���W
	//�����Fwidth	�؂蔲�������͈͂̕�
	//�����Fheight	�؂蔲�������͈͂̍���
	void SetRect(int handle, int x, int y, int width, int height);

	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	void ResetRect(int handle);

	//�A���t�@�l���w��
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Falpha �A���t�@�l�i�s�����x�j�@0�`1�Ŏw��
	void SetAlpha(int handle, float alpha);

	//�A���t�@�l���Q�b�g����
	float GetAlpha(int handle);
	
	//�L���v�`����ʂ��ǂ����Z�b�g
	void SetScreenCapture(int handle, bool flag);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform* transform);

	//���[���h�s��̎擾
	//�����Fhandle	�m�肽���摜�̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);

	/// <summary>
	/// �X�v���C�g���擾
	/// </summary>
	/// <param name="handle">�摜�ԍ�</param>
	/// <returns>�X�v���C�g</returns>
	Sprite* GetSprite(int handle);

	/// <summary>
	/// �X�v���C�g��ݒ�
	/// </summary>
	/// <param name="handle">�摜�ԍ�</param>
	void SetSprite(int handle, Sprite* s);
}