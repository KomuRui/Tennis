#pragma once
#include "Image.h"
#include "Global.h"

/// <summary>
/// ������`�悷��N���X
/// </summary>
class Text
{

	//////////////////////////�摜���/////////////////////////////

	int hPict_;                     //�摜�ԍ�
	unsigned int width_, height_;	//1�������̕��ƍ���
	char fileName_[MAX_PATH];       //�����̉摜
	unsigned int rowLength_;        //�摜�̒��ɉ���������ł��邩

	//////////////////////////�\��/////////////////////////////

	float textInterval_; //�����̊Ԋu
	float speed_;        //�����̕\������Ԋu�̑��x
	int fpsCount_;       //�t���[���̃J�E���g
	int totalDrawNum_;   //�`�悵�Ă�������

public:
	Text();
	~Text();

	/// <summary>
	/// �������i�f�t�H���g�̐ݒ�j
	/// </summary>
	/// <returns>�����^���s</returns>
	HRESULT Initialize(float speed = 1.0f,float textInterval = 0.005f);

	/// <summary>
	/// �������i�I���W�i���̉摜���g���������j
	/// </summary>
	/// <param name="fileName">�摜�t�@�C����</param>
	/// <param name="charWidth">�摜�̂P�����̕��i�s�N�Z���j</param>
	/// <param name="charHeight">�摜�̂P�����̍����i�s�N�Z���j</param>
	/// <param name="rowLength">�摜�̒��ɉ��ɉ���������ł��邩</param>
	/// <returns>�����^���s</returns>
	HRESULT Initialize(const char* fileName, const unsigned int charWidth, const unsigned int charHeight, const unsigned int rowLength, float speed = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// �`��i������:�����j
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="str">�\��������������</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	void NumberDraw(int x, int y, const char* str, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
    /// �`��i�����l�j
    /// </summary>
    /// <param name="x">�\���ʒu�i����j</param>
    /// <param name="y">�\���ʒu�i����j</param>
    /// <param name="value">�\���������l</param>
    /// <param name="ratio">�\�����镶���̔{��</param>
	void NumberDraw(int x, int y, int value, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// �`��i������j�ꕶ�����Ƃɏ��X�ɕ\������
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="str">�\��������������</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	/// <returns>true�Ȃ�Ō�܂ŕ`�悳��Ă���,false�Ȃ�Ō�܂ŕ`�悳��Ă��Ȃ�</returns>
	bool SlowlyDraw(int x, int y, const wchar_t* str,float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// �`��i������j��\������
	/// </summary>
	/// <param name="x">�\���ʒu�i����j</param>
	/// <param name="y">�\���ʒu�i����j</param>
	/// <param name="str">�\��������������</param>
	/// <param name="ratio">�\�����镶���̔{��</param>
	/// <returns>true�Ȃ�Ō�܂ŕ`�悳��Ă���,false�Ȃ�Ō�܂ŕ`�悳��Ă��Ȃ�</returns>
	void Draw(int x, int y, const wchar_t* str, float ratio = 1.0f, float textInterval = 0.005f);

	/// <summary>
	/// �`�悵�Ă����������Z�b�g
	/// </summary>
	/// <param name="num">�Z�b�g����������</param>
	void SetTotalDrawNum(int num) { totalDrawNum_ = num; }

	/// <summary>
	/// �`��X�s�[�h���Z�b�g
	/// </summary>
	/// <param name="spd">�Z�b�g�������X�s�[�h</param>
	void SetDrawSpeed(float spd) { speed_ = spd * 60; }

	/// <summary>
	/// �`�悵�Ă������������Z�b�g
	/// </summary>
	void ResetTotalDrawNum() { totalDrawNum_ = (int)ZERO; }

	//���
	void Release();
};

