#pragma once
#include "../../Engine/ResourceManager/Global.h"
#include "../../Engine/DirectX/Sprite.h"
#include "../../Engine/ResourceManager/Text.h"
#include "../../Engine/Component/EasingMove.h"
#include "TennisCourt.h"
#include <map>

//�X�R�A���
struct ScoreInfo
{
	int point;      //�|�C���g��
	int gamePoint;  //�Q�[���|�C���g��
	int setPoint;   //�Z�b�g�|�C���g��
};

//�e�L�X�g���
struct TextInfo
{
	XMFLOAT3 pos;
	XMFLOAT2 scale;
};

//�e�j�X�̃X�R�A
class Score
{
	map<TennisCourtName, ScoreInfo> scoreTable_;			//�X�R�A�\
	map<TennisCourtName, pair<Text*, TextInfo>> scoreText_; //�X�R�A�̃e�L�X�g�\���p

	TennisCourtName pointGetTennisCourtName_;               //�|�C���g�擾���e�j�X�R�[�g�̖��O

	Text* pHyphenText_;					 //�n�C�t���\������p
	TextInfo hyphenTextInfo_;			 //�e�L�X�g�̃|�W�V����

	XMFLOAT3 allScale_;                  //���ׂĂ̊g�嗦
	XMFLOAT3 pointGetScale_;             //�|�C���g�擾�������̊g�嗦

	std::unique_ptr<EasingMove> zPlusCourtEasingPos_ = std::make_unique<EasingMove>();     //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> zMinusCourtEasingPos_ = std::make_unique<EasingMove>();    //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> hyphenEasingPos_ = std::make_unique<EasingMove>();         //�ʒu�C�[�W���O�p
	std::unique_ptr<EasingMove> allScaleEasing_ = std::make_unique<EasingMove>();          //���ׂĂ̊g�嗦�C�[�W���O�p
	std::unique_ptr<EasingMove> pointGetScaleEasing_ = std::make_unique<EasingMove>();     //���ׂĂ̊g�嗦�C�[�W���O�p

	std::map<int, int> table;      //�X�R�A�\(�L�[:�J�E���g��0,1,2,3 �o�����[:�\������X�R�A��)

	std::unique_ptr<Sprite> offGameUi_ = std::make_unique<Sprite>();           //�Q�[�����擾����UI
	std::unique_ptr<Sprite> onZPlusCourtGameUi_ = std::make_unique<Sprite>();  //Z�v���X�R�[�g���Q�[���擾����UI
	std::unique_ptr<Sprite> onZMinusCourtGameUi_ = std::make_unique<Sprite>(); //Z�}�C�i�X�R�[�g���Q�[���擾����UI
	
public:

	//�R���X�g���N�^
	Score();

	/// <summary>
	/// �`��(�R�C���̎擾����Player���C�t�̕\��)
	/// </summary>
	void Draw();

	/// <summary>
	/// �|�C���g���`��
	/// </summary>
	void PointDraw();

	/// <summary>
	/// �Q�[���|�C���g�`��
	/// </summary>
	void GamePointDraw();

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

