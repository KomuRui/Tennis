#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "TennisCourt.h"
#include <map>

//�e�L�X�g���
struct Textinfo
{
	XMFLOAT3 pos;
	XMFLOAT2 scale;
};

//�e�j�X�̃X�R�A
class Score
{
	map<TennisCourtName, int> scoreTable_;					//�X�R�A�\
	map<TennisCourtName, pair<Text*, Textinfo>> scoreText_; //�X�R�A�̃e�L�X�g�\���p

	TennisCourtName pointGetTennisCourtName_;               //�|�C���g�擾���e�j�X�R�[�g�̖��O

	Text* pHyphenText_;					 //�n�C�t���\������p
	Textinfo hyphenTextInfo_;			 //�e�L�X�g�̃|�W�V����

	XMFLOAT3 allScale_;                  //���ׂĂ̊g�嗦
	XMFLOAT3 pointGetScale_;             //�|�C���g�擾�������̊g�嗦

	std::unique_ptr<EasingMove> zPlusCourtEasingPos_ = std::make_unique<EasingMove>();     //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> zMinusCourtEasingPos_ = std::make_unique<EasingMove>();    //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> hyphenEasingPos_ = std::make_unique<EasingMove>();         //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> allScaleEasing_ = std::make_unique<EasingMove>();          //���ׂĂ̊g�嗦�C�[�W���O�p
	std::unique_ptr<EasingMove> pointGetScaleEasing_ = std::make_unique<EasingMove>();     //���ׂĂ̊g�嗦�C�[�W���O�p

	std::map<int, int> table;      //�X�R�A�\(�L�[:�J�E���g��0,1,2,3 �o�����[:�\������X�R�A��)
	
public:

	//�R���X�g���N�^
	Score();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

	/// <summary>
	/// �X�R�A���Z
	/// </summary>
	void AddScore(TennisCourtName n);

	/// <summary>
	/// �ʒu��߂�����
	/// </summary>
	void ReturnMovePos();

	/// <summary>
	/// �C�[�W���O�ŃX�R�A�ύX
	/// </summary>
	void ChangeScoreEasing();

};

