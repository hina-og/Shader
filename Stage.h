#pragma once
#include "Engine/GameObject.h"

struct CONSTBUFER_MODEL
{
    XMFLOAT4 lightPosition_;//�����ʒu
    XMFLOAT4 eyePosition_;//���_�ʒu
};

struct CONSTBUFER_STAGE
{
    XMFLOAT4 lightPosition_;//�����ʒu
    XMFLOAT4 eyePosition_;//���_�ʒu
};

//���������Ǘ�����N���X
class Stage : public GameObject
{
    int hModel_;    //���f���ԍ�
    int hRoom_;
    int hGround;
    int hBunny_;

    int hDonutTexPh_;
    int hDonutTexLa_;
    int hDonutCoPh_;
    int hDonutCoLa_;

    ID3D11Buffer* pConstantBuffer_;
    void InitConstantBuffer();
public:
    //�R���X�g���N�^
    Stage(GameObject* parent);

    //�f�X�g���N�^
    ~Stage();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;
};