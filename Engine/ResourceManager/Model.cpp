#include "Global.h"
#include "Model.h"

//3D���f���iFBX�t�@�C���j���Ǘ�����
namespace Model
{
	//���[�h�ς݂̃��f���f�[�^�ꗗ
	std::vector<ModelData*>	_datas;

	//������
	void Initialize()
	{
		AllRelease();
	}

	//���f�������[�h
	int Load(std::string fileName)
	{
			ModelData* pData = new ModelData;


			//�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
			bool isExist = false;
			for (int i = 0; i < _datas.size(); i++)
			{
				//���łɊJ���Ă���ꍇ
				if (_datas[i] != nullptr && _datas[i]->fileName == fileName)
				{
					pData->pFbx = _datas[i]->pFbx;
					isExist = true;
					break;
				}
			}

			//�V���Ƀt�@�C�����J��
			if (isExist == false)
			{
				pData->pFbx = new Fbx;
				if (FAILED(pData->pFbx->Load(fileName)))
				{
					//�J���Ȃ�����
					SAFE_DELETE(pData->pFbx);
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
			return (int)_datas.size() - 1;
	}



	//�`��
	void Draw(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//�A�j���[�V�������g���̂Ȃ�
		if (_datas[handle]->isAnim)
		{
			//���Ԃ��~�܂��Ă��Ȃ�������A�j���[�V������i�߂�
			if(!Direct3D::GetTimeScale())
			_datas[handle]->nowFrame += _datas[handle]->animSpeed;
		}
		else
		{
			_datas[handle]->nowFrame = 0;
		}

		//�Ō�܂ŃA�j���[�V����������߂�
		if (_datas[handle]->nowFrame > (float)_datas[handle]->endFrame)
			_datas[handle]->nowFrame = (float)_datas[handle]->startFrame;



		if (_datas[handle]->pFbx)
		{
			_datas[handle]->pFbx->Draw(_datas[handle]->transform, (int)_datas[handle]->nowFrame, _datas[handle]->alpha, _datas[handle]->ambient,_datas[handle]->speculer, _datas[handle]->brightness,_datas[handle]->uvScroll, _datas[handle]->outLineColor, _datas[handle]->isOutLineDraw, _datas[handle]->shaderType);
		}
	}

	void SetAlpha(int handle, float Alpha)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->alpha = Alpha;
		
	}

	void SetAmbient(int handle, XMFLOAT4 ambt)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->ambient = ambt;
	}

	void SetSpeculer(int handle, XMFLOAT4 Speculer)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->speculer = Speculer;
	}

	void SetOutLineColor(int handle, XMFLOAT4 OutLine)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->outLineColor = OutLine;
	}

	void SetBrightness(int handle, float Brightness)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->brightness = Brightness;
	}

	void SetRayFlag(int handle, bool flag)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->isRay = flag;
	}

	void SetOutLineDrawFlag(int handle, bool flag)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->isOutLineDraw = flag;
	}

	void SetBlockObj(int handle, Block* block)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->pBlock = block;
	}

	void SetObstacleObj(int handle, GameObject* Obstacle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->pObstacle = Obstacle;
	}

	//�g���V�F�[�_���Z�b�g
	void SetShederType(int handle, Direct3D::SHADER_TYPE type)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->shaderType = type;
	}

	//UV�X�N���[���̒l���Z�b�g
	void SetUvScroll(int handle, float scroll)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		_datas[handle]->uvScroll = scroll;
	}

	//�C�ӂ̃��f�����J��
	void Release(int handle)
	{
		if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
		{
			return;
		}

		//�������f���𑼂ł��g���Ă��Ȃ���
		bool isExist = false;
		for (int i = 0; i < _datas.size(); i++)
		{
			//���łɊJ���Ă���ꍇ
			if (_datas[i] != nullptr && i != handle && _datas[i]->pFbx == _datas[handle]->pFbx)
			{
				isExist = true;
				break;
			}
		}

		//�g���ĂȂ���΃��f�����
		if (isExist == false )
		{
			SAFE_DELETE(_datas[handle]->pFbx);
		}


		SAFE_DELETE(_datas[handle]);
	}


	//�S�Ẵ��f�������
	void AllRelease()
	{
		for (int i = 0; i < _datas.size(); i++)
		{
			if (_datas[i] != nullptr)
			{
				Release(i);
			}
		}
		_datas.clear();
	}


	//�A�j���[�V�����̃t���[�������Z�b�g
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed)
	{
		_datas[handle]->SetAnimFrame(startFrame, endFrame, animSpeed);
	}

	void SetAnimFlag(int handle,bool flag)
	{
		_datas[handle]->isAnim = flag;
	}

	void SetAnimSpeed(int handle, float speed)
	{
		_datas[handle]->animSpeed = speed;
	}

	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle)
	{
		return (int)_datas[handle]->nowFrame;
	}


	//�C�ӂ̃{�[���̈ʒu���擾
	XMFLOAT3 GetBonePosition(int handle, std::string boneName)
	{

		XMFLOAT3 pos = _datas[handle]->pFbx->GetBonePosition(boneName);
		XMVECTOR vec = XMVector3TransformCoord(XMLoadFloat3(&pos), _datas[handle]->transform.GetWorldMatrix());
		XMStoreFloat3(&pos, vec);
		return pos;
	}


	//���[���h�s���ݒ�
	void SetTransform(int handle, Transform & transform)
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
		return _datas[handle]->transform.GetWorldMatrix();
	}


	//���C�L���X�g�i���C���΂��ē����蔻��j
	void RayCast(int handle, RayCastData *data)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 target = Float3Add(data->start, data->dir);
		XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = vecTarget - vecStart;

		XMStoreFloat3(&data->start, vecStart);
		XMStoreFloat3(&data->dir, vecDir);

		_datas[handle]->pFbx->RayCast(data); 
		matInv = _datas[handle]->transform.GetWorldMatrix();
		XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
	}

	//���C�L���X�g(�����������f���̃A�E�g���C����\��������)
	void RayCastOutLineSet(RayCastData* data, XMFLOAT4 outLineColor)
	{
		auto ehandle = _datas.begin();
		XMFLOAT3 start = data->start;
		XMFLOAT3 dir = data->dir;
		data->hit = false;
		bool hit = false;
		float dist = 99999.0f;
		ModelData* hModelNum = nullptr;
		XMFLOAT3 normal = { ZERO,ZERO, ZERO };

		do
		{
			XMFLOAT3 target = Float3Add(start, dir);
			XMMATRIX matInv = XMMatrixInverse(nullptr, (*ehandle)->transform.GetWorldMatrix());
			XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&start), matInv);
			XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
			XMVECTOR vecDir = XMVector3Normalize(vecTarget - vecStart);

			XMStoreFloat3(&data->start, vecStart);
			XMStoreFloat3(&data->dir, vecDir);

			(*ehandle)->pFbx->RayCast(data);

			if (data->hit)
			{
				hit = true;

				if (dist > data->dist)
				{
					dist = data->dist;
					normal = data->normal;
					hModelNum = (*ehandle);

					data->start = start;
					matInv = (*ehandle)->transform.GetWorldMatrix();
					XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
					XMStoreFloat3(&normal, XMVector3TransformCoord(XMLoadFloat3(&data->normal), (*ehandle)->transform.mmRotate_));

					data->block = (*ehandle)->pBlock;
					data->obstacle = (*ehandle)->pObstacle;
				}
			}

			ehandle++;
		} while (ehandle != _datas.end());

		//�X�V
		data->hit = hit;
		data->normal = normal;

		//�A�E�g���C���X�V
		if (hModelNum->isOutLineDraw && hModelNum != nullptr)
			hModelNum->isOutLineDraw = false;
		else if(hModelNum != nullptr)
			hModelNum->isOutLineDraw = true;

		//�A�E�g���C���̐F
		hModelNum->outLineColor = outLineColor;
	}

	//��ԋ߂��|���S���̖@���ƃ|�W�V������RayCastData�Ɋi�[
	void NearPolyNormal(int handle, NearPolyData* data)
	{
		if (handle < 0 || handle >= _datas.size())
		{
			return;
		}

		XMFLOAT3 target = data->start;
		XMMATRIX matInv = XMMatrixInverse(nullptr, _datas[handle]->transform.GetWorldMatrix());
		XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&data->start), matInv);
		XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
		XMVECTOR vecDir = vecTarget - vecStart;

		XMStoreFloat3(&data->start, vecStart);

		_datas[handle]->pFbx->NearPolyNormal(data);

		matInv = _datas[handle]->transform.GetWorldMatrix();
		XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
	}

	//���C�L���X�g(Block�������)
	void AllRayCast(int handle, RayCastData* data)
	{
		auto ehandle = _datas.begin();
		XMFLOAT3 start = data->start;
		XMFLOAT3 dir = data->dir;
		data->hit = false;
		bool hit = false;
		float dist = 99999.0f;
		XMFLOAT3 normal = { ZERO,ZERO, ZERO};

		do
		{
			//���C���Ƃ΂����f�������C�̓����蔻�������Ɛݒ肵�Ă���Ƃ�
			if ((*ehandle)->isRay)
			{

					XMFLOAT3 target = Float3Add(start, dir);
					XMMATRIX matInv = XMMatrixInverse(nullptr, (*ehandle)->transform.GetWorldMatrix());
					XMVECTOR vecStart = XMVector3TransformCoord(XMLoadFloat3(&start), matInv);
					XMVECTOR vecTarget = XMVector3TransformCoord(XMLoadFloat3(&target), matInv);
					XMVECTOR vecDir = XMVector3Normalize(vecTarget - vecStart);

					XMStoreFloat3(&data->start, vecStart);
					XMStoreFloat3(&data->dir, vecDir);

					(*ehandle)->pFbx->RayCast(data);

					if (data->hit)
					{
						hit = true;

						if (dist > data->dist)
						{
							dist = data->dist;
							normal = data->normal;

							data->start = start;
							matInv = (*ehandle)->transform.GetWorldMatrix();
							XMStoreFloat3(&data->pos, XMVector3TransformCoord(XMLoadFloat3(&data->pos), matInv));
							XMStoreFloat3(&normal, XMVector3TransformCoord(XMLoadFloat3(&data->normal), (*ehandle)->transform.mmRotate_));

							data->block = (*ehandle)->pBlock;
							data->obstacle = (*ehandle)->pObstacle;
						}
					}
			}

			ehandle++;
		} while (ehandle != _datas.end());

		//�X�V
		data->hit = hit;
		data->normal = normal;
	}
}