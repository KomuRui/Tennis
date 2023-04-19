#include "Gauge.h"
#include "../ResourceManager/Image.h"

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"),
    hPict_{ -1,-1,-1,-1 },
    stopRatio_((float)nowHp_ / (float)maxHp_), moveRatio_(stopRatio_),

    nowHp_(1),      //����HP 
    maxHp_(1),      //MaxHP
    speed_(0.002f)  //�o�[�̈ړ����x
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    //�摜�t�@�C�����[�h
    //�g�p����摜�t�@�C����
    string fileName[] = { "Gauge_Frame", "Gauge_Green", "Gauge_LightGreen", "Gauge_Red" };

    //���[�h
    for (int i = (int)ZERO; i < PICT_MAX; i++)
    {
        hPict_[i] = Image::Load("Image/Gauge/" + fileName[i] + ".png");
        assert(hPict_[i] >= ZERO);
    }
}

//�X�V
void Gauge::Update()
{
    //�ő�HP�ɑ΂���A����HP�̊���
    ARGUMENT_INITIALIZE(stopRatio_,(float)nowHp_ / (float)maxHp_);

    //�o�[�𓮂���
    if (moveRatio_ < stopRatio_) moveRatio_ += speed_;
    if (moveRatio_ > stopRatio_) moveRatio_ -= speed_;

}

//�`��
void Gauge::Draw()
{
    //�摜�\���p
    Transform gaugeTrans;

    //HP�ω��Ȃ�
    if (abs(moveRatio_ - stopRatio_) < speed_)
    {
        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //�񕜒�
    else if (moveRatio_ < stopRatio_)
    {
        //���΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_LGREEN]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }

    //�_���[�W��
    else
    {
        //�ԃQ�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
        Image::Draw(hPict_[PICT_RED]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //�g
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[PICT_FRAME]);
}


//�J��
void Gauge::Release()
{
}

//�_���[�W
void Gauge::Damage(int value)
{
    nowHp_ -= value;
    if (nowHp_ < ZERO) nowHp_ = (int)ZERO;
}

//��
void Gauge::Recovery(int value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}
