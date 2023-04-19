#pragma once
#include <string>
#include <dsound.h>

// ���C�u���������N
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")


//-----------------------------------------------------------
//DirectSound���g�����T�E���h�Đ��N���X
//-----------------------------------------------------------
class Sound
{
    LPDIRECTSOUND8			    pDSound_;	//DirectSound�I�u�W�F�N�g
    LPDIRECTSOUNDBUFFER	pPrimary_;	//�v���C�}���o�b�t�@

    //�v���C�}���o�b�t�@�̍쐬
    void CreatePrimaryBuffer();

public:
    Sound();
    ~Sound();

    //������
    //�����FhWnd	�E�B���h�E�n���h��
    void Initialize(HWND hWnd);

    //�t�@�C���̃��[�h
    //�����Fdsb			�T�E���h�o�b�t�@
    //�����FfileName	�t�@�C����
    HRESULT Load(LPDIRECTSOUNDBUFFER* dsb, const std::string& fileName) const;

    //�Đ�
    //�����Fdsb	�T�E���h�o�b�t�@
    static void Play(LPDIRECTSOUNDBUFFER* dsb);

    //�Đ�
    //�����Fdsb	�T�E���h�o�b�t�@
    static void PlayLoop(LPDIRECTSOUNDBUFFER* dsb);

    //��~
    //�����Fdsb	�T�E���h�o�b�t�@
    static void Stop(LPDIRECTSOUNDBUFFER* dsb);


    //�J��
    void Release() const;
};