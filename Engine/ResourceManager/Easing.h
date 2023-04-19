#pragma once
#include "Global.h"

//�e�C�[�W���O�֐��̐���
//������̃T�C�g���Q�Ƃ��Ă��܂�
//https://easings.net/ja

/// <summary>
/// �C�[�W���O(�ɋ}�݂����Ȃ���)
/// </summary>
namespace Easing
{

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InSine(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutSine(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutSine(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InQuad(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutQuad(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutQuad(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InCubic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutCubic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutCubic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InQuart(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutQuart(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutQuart(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InQuint(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutQuint(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutQuint(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InExpo(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutExpo(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutExpo(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InCirc(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutCirc(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutCirc(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InBack(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutBack(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutBack(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InElastic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutElastic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutElastic(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InBounce(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float OutBounce(float x);

	/// <param name="x">0�`1�̊Ԃ̒l�@0 : �A�j���[�V�����̊J�n  1 : �A�j���[�V�����̏I��</param>
	/// <returns>0�`1�̊Ԃ̒l : �{��</returns>
	float InOutBounce(float x);
};
