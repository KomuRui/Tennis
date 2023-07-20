#include "Global.h"
#include "ImageManager.h"

//3D�摜���Ǘ�����
namespace ImageManager
{
	//���[�h�ς݂̉摜�f�[�^�ꗗ
	std::vector<ImageData*>	_datas;

	//ui�̕`��p
	std::vector<int> _uiDrawDatas;

	//text�̕`��p
	std::vector<TextData> _textDrawDatas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//�摜�����[�h
	int Load(std::string fileName)
	{
		ImageData* pData = new ImageData;

		//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
			{
				pData->pSprite = _datas[i]->pSprite;
				isExist = true;
				break;
			}
		}

		//�V���Ƀt�@�C�����J��
		if (isExist == false)
		{
			pData->pSprite = new Sprite;
			if (FAILED(pData->pSprite->Load(fileName)))
			{
				//�J���Ȃ�����
				SAFE_DELETE(pData->pSprite);
				SAFE_DELETE(pData);
				return -1;
			}

			//�����J����
			pData->fileName = fileName;
		}


		//�g���ĂȂ��ԍ����������T��
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] == nullptr)
			{
				_datas[i] = pData;
				return i;
			}
		}

		//�V���ɒǉ�
		_datas.push_back(pData);

		//�摜�ԍ�����U��
		int handle = (int)_datas.size() - 1;

		//�؂蔲���͈͂����Z�b�g
		ResetRect(handle);

		return handle;
	}



	//�`��
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}
		_datas[handle]->transform->Calclation();
		_datas[handle]->pSprite->Draw(_datas[handle]->transform, _datas[handle]->rect, _datas[handle]->alpha, _datas[handle]->isScreenCapture);
	}

	//Ui�`��
	void UiDraw()
	{
		for (auto i = _uiDrawDatas.begin(); i != _uiDrawDatas.end(); i++)
		{
			_datas[(*i)]->transform->Calclation();
			_datas[(*i)]->pSprite->Draw(_datas[(*i)]->transform, _datas[(*i)]->rect, _datas[(*i)]->alpha, _datas[(*i)]->isScreenCapture);
		}

		//��ɂ���	
		_uiDrawDatas.clear();
	}

	//Text�`��
	void TextDraw()
	{
		for (auto i = _textDrawDatas.begin(); i != _textDrawDatas.end(); i++)
		{
			(*i).transform->Calclation();
			_datas[(*i).handle]->pSprite->Draw((*i).transform, (*i).rect, _datas[(*i).handle]->alpha, _datas[(*i).handle]->isScreenCapture);
		}

		//��ɂ���	
		_textDrawDatas.clear();
	}


	//�C�ӂ̉摜���J��
	void Release(int handle)
	{
		if (handle < 0 || _datas[handle]->isScreenCapture || handle >= _datas.size())
		{
			return;
		}

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false)
		{
			SAFE_DELETE(_datas[handle]->pSprite);
		}

		SAFE_DELETE(_datas[handle]);
	}

	//�S�Ẳ摜�����
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			Release(i);
		}
		_datas.clear();
		_uiDrawDatas.clear();
	}

	//UI���Z�b�g(�Ō�ɕ`�悵�����Ƃ��Ɏg��)
	void SetUi(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_uiDrawDatas.push_back(handle);
	}

	//�e�L�X�g���Z�b�g(�Ō�ɕ`�悵�����Ƃ��Ɏg��
	void SetText(int handle, RECT rect, Transform* transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		TextData data;
		data.handle = handle;
		data.rect = rect;
		data.transform = transform;
		_textDrawDatas.push_back(data);
	}


	//�؂蔲���͈͂̐ݒ�
	void SetRect(int handle, int x, int y, int width, int height)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->rect.left = x;
		_datas[handle]->rect.top = y;
		_datas[handle]->rect.right = width;
		_datas[handle]->rect.bottom = height;
	}


	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	void ResetRect(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

		_datas[handle]->rect.left = 0;
		_datas[handle]->rect.top = 0;
		_datas[handle]->rect.right = (long)size.x;
		_datas[handle]->rect.bottom = (long)size.y;

	}

	//�A���t�@�l�ݒ�
	void SetAlpha(int handle, float alpha)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->alpha = (float)alpha;
	}

	//�A���t�@�l�Q�b�g
	float GetAlpha(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return 0;
		}
		return _datas[handle]->alpha * 255;
	}

	//�L���v�`����ʂ��ǂ����Z�b�g
	void SetScreenCapture(int handle, bool flag)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}
		_datas[handle]->isScreenCapture = flag;
	}

	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform* transform)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		_datas[handle]->transform = transform;
	}


	//���[���h�s��̎擾
	XMMATRIX GetMatrix(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return XMMatrixIdentity();
		}
		return _datas[handle]->transform->GetWorldMatrix();
	}

	//�X�v���C�g���擾
	Sprite* GetSprite(int handle)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return nullptr;
		}
		return _datas[handle]->pSprite;
	}

	//�X�v���C�g���Z�b�g
	void SetSprite(int handle,Sprite* s)
	{
		_datas[handle]->pSprite = s;
	}
}

