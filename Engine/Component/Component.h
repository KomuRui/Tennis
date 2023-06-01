#pragma once

class GameObject;

//�R���|�[�l���g���N���X
class Component
{
public:
   
    //�e
    GameObject* parent;

    //�R���X�g���N�^
    Component() :parent(nullptr) {}

    //�f�X�g���N�^
    virtual ~Component() {}

    //�ŏ��̈�񂾂��Ă΂��
    virtual void Start() {}

    //�X�V
    virtual void Update() {}

    //�`��
    virtual void Draw() {}
};