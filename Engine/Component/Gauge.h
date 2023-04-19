#pragma once
#include "../GameObject/GameObject.h"

//�̗̓Q�[�W���Ǘ�����N���X
class Gauge : public GameObject
{
    int nowHp_; //���݂̂g�o
    int maxHp_; //�ő�g�o

    float stopRatio_;       //�ő�HP�ɑ΂���Œ肳�ꂽ�Q�[�W�̊���
    float moveRatio_;       //�ő�HP�ɑ΂���ω����Ă�Q�[�W�̊���
    float speed_;           //�ω����鎞�̃Q�[�W�X�s�[�h

    //�g�p����摜�̎��
    enum
    {
        PICT_FRAME,
        PICT_GREEN,
        PICT_LGREEN,
        PICT_RED,
        PICT_MAX
    };

    //�摜�ԍ�
    int hPict_[PICT_MAX];

public:
    //�R���X�g���N�^
    Gauge(GameObject* parent);

    //�f�X�g���N�^
    ~Gauge();

    //������
    void Initialize() override;

   //�X�V�̑O�Ɉ��Ă΂��֐�
    void StartUpdate() override {};

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    /// <summary>
    /// �_���[�W���󂯂�
    /// </summary>
    /// <param name="value">�_���[�W��</param>
    void Damage(int value);

    /// <summary>
    /// ��
    /// </summary>
    /// <param name="value">�񕜗�</param>
    void Recovery(int value);

    /// <summary>
    /// MaxHP���Z�b�g
    /// </summary>
    /// <param name="value">MaxHp</param>
    void SetMaxHp(int value) { maxHp_ = value; }

    /// <summary>
    /// ���݂�Hp���Z�b�g
    /// </summary>
    /// <param name="value">���݂�Hp</param>
    void SetNowHp(int value) { nowHp_ = value; }
};