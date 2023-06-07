#pragma once
#include "../Base/NormalObject.h"
#include "../Engine/GameObject/GameObject.h"
#include "../State/PlayerState/PlayerStateManager.h"
#include "../Engine/ResourceManager/ModelManager.h"
#include "../Engine/Component/Transform/Transform.h"

class Racket;

/// <summary>
/// Player�̊��N���X
/// </summary>
class PlayerBase : public NormalObject
{
protected:

	///////////////�L�����̕K�v�ȏ��///////////////////

	Racket* pRacket_;                   //���P�b�g
	PlayerStateManager* pState_;        // Player�̏�Ԃ�\���ϐ�

	/////////////////////�J����//////////////////////

	XMVECTOR camVec_;                   //Player����J�����܂ł̃x�N�g��
	XMVECTOR camVec2_;                   //Player����J�����܂ł̃x�N�g��

public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	PlayerBase(GameObject* parent, std::string modelFilePath_, std::string name);


	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void ChildInitialize() override;

	//�X�V
	void ChildUpdate() override;

	///////////////////////////�֐�////////////////////////////

	/// <summary>
	/// �J�����̏���
	/// </summary>
	void CameraBehavior();

	/////////////////////�Z�b�g�Q�b�g�֐�//////////////////////

	/// <summary>
	/// ���f���ԍ��擾
	/// </summary>
	/// <returns>���f���ԍ�</returns>
	int GetModelNum() { return hModel_; } 

	/// <summary>
	/// ���P�b�g�擾
	/// </summary>
	/// <returns>���P�b�g</returns>
	Racket* GetRacket() { return pRacket_; }

	/// <summary>
	/// ��Ԃ��擾
	/// </summary>
	/// <returns>���</returns>
	PlayerStateManager* GetState() { return pState_; }
};

