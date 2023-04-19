#include <vector>
#include "Audio.h"

//3D�摜���Ǘ�����
namespace Audio
{
    //�T�E���h�N���X�̃I�u�W�F�N�g
    Sound* pSound_;

    //���[�h�ς݂̉摜�f�[�^�ꗗ
    std::vector<AudioData*>	data_;
    int isPlaySe_ = 1;
    int isPlayBgm_ = 1;


    //������
    void Initialize(const HWND hWnd)
    {
        pSound_ = new Sound;
        pSound_->Initialize(hWnd);

        AllRelease();
    }


    //�T�E���h�t�@�C�������[�h
    int Load(const std::string& fileName)
    {
        auto* pData = new AudioData;

        //�J�����t�@�C���ꗗ���瓯���t�@�C�����̂��̂��������T��
        bool isExist = false;

        for (auto& index : data_)
        {
            //���łɊJ���Ă���ꍇ
            if (index != nullptr && index->fileName == fileName)
            {
                pData->pSoundBuffer = index->pSoundBuffer;
                isExist = true;
                break;
            }
        }

        //�V���Ƀt�@�C�����J��
        if (isExist == false)
        {
            pData->pSoundBuffer = new LPDIRECTSOUNDBUFFER;

            if (FAILED(pSound_->Load(pData->pSoundBuffer, fileName)))
            {
                //�J���Ȃ�����
                SAFE_DELETE(pData)
                    return -1;
            }

            //�����J����
            pData->fileName = fileName;
        }


        //�g���ĂȂ��ԍ����������T��
        for (int index = 0; index < data_.size(); ++index)
        {
            if (data_[index] == nullptr)
            {
                data_[index] = pData;
                return index;
            }
        }

        //�V���ɒǉ�
        data_.push_back(pData);
        return static_cast<int>(data_.size()) - 1;
    }



    //�Đ�
    void Play(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr)
        {
            return;
        }

        if (isPlaySe_)
            Sound::Play(data_[handle]->pSoundBuffer);
    }

    void PlayLoop(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr) {
            return;
        }

        if (isPlayBgm_)
            Sound::PlayLoop(data_[handle]->pSoundBuffer);
    }


    //��~
    void Stop(const int handle)
    {
        if (handle < 0 || handle >= data_.size() || data_[handle] == nullptr)
        {
            return;
        }

        Sound::Stop(data_[handle]->pSoundBuffer);
    }



    //�C�ӂ̃T�E���h���J��
    void Release(const int handle)
    {
        if (handle < 0 || handle >= data_.size())
        {
            return;
        }

        //�����T�E���h�𑼂ł��g���Ă��Ȃ���
        bool isExist = false;

        for (int index = 0; index < data_.size(); ++index)
        {
            //���łɊJ���Ă���ꍇ
            if (data_[index] != nullptr && index != handle && data_[index]->pSoundBuffer == data_[handle]->pSoundBuffer)
            {
                isExist = true;
                break;
            }
        }

        //�g���ĂȂ���΃��f�����
        if (isExist == false)
        {
            SAFE_DELETE(data_[handle]->pSoundBuffer)
        }


        SAFE_DELETE(data_[handle])
    }



    //�S�ẴT�E���h�����
    void AllRelease()
    {
        for (int index = 0; index < data_.size(); ++index)
        {
            Release(index);
        }
        data_.clear();
    }


    //�Q�[���I�����ɍs������
    void ReleaseDirectSound()
    {
        SAFE_DELETE(pSound_)
    }
}
