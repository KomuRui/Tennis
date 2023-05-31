#pragma once

class GameObject;

//�R���|�[�l���g���N���X
class Component
{
private:
    
    //�R���X�g���N�^
    Component() {}

    //�f�X�g���N�^
    virtual ~Component() {}

public:
   
    //�e
    GameObject* parent;

    //�ŏ��̈�񂾂��Ă΂��
    virtual void Start() {}

    //�X�V
    virtual void Update() {}

    //�`��
    virtual void Draw() {}
};