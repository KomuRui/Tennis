#pragma once


/// <summary>
/// �Q�[���I�u�W�F�N�g�̏���\������GUI
/// </summary>
namespace GameObjectInfoGui
{
	/// </summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �Q�[���I�u�W�F�N�g�̏���`��
	/// </summary>
	void GameObjectInfoDraw();

	/// <summary>
	/// ���O�ƃg�����X�t�H�[���`��
	/// </summary>
	void NameAndTransformDraw();

	/// </summary>
	/// �F���`��
	/// </summary>
	void ColorInfoDraw();

	/// </summary>
	/// ���f�����`��
	/// </summary>
	void ModelInfoDraw();

	/// <summary>
	/// ���f���ݒ�
	/// </summary>
	/// <param name="ModelNum">���f���ԍ�</param>
	void SetModel(int ModelNum);
}