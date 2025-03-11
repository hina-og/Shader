#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"



//�R���X�g���N�^
Stage::Stage(GameObject* parent)
    :GameObject(parent, "Stage"), pConstantBuffer_(nullptr)
{
    hModel_ = -1;
    hRoom_ = -1;
    hGround = -1;
    hBunny_ = -1;

    hDonutTexPh_ = -1;
    hDonutTexLa_ = -1;
    hDonutCoPh_ = -1;
    hDonutCoLa_ = -1;

}

//�f�X�g���N�^
Stage::~Stage()
{
}

//������
void Stage::Initialize()
{
    hModel_ = Model::Load("Assets\\Ball.fbx");
    hRoom_ = Model::Load("Assets\\room.fbx");
    hGround = Model::Load("Assets\\plane3.fbx");
    hBunny_ = Model::Load("Assets\\stanford-bunny.fbx");
    hDonutTexPh_ = Model::Load("Assets\\donutTePh.fbx");
    hDonutTexLa_ = Model::Load("Assets\\donutTeLa.fbx");
    hDonutCoPh_ = Model::Load("Assets\\donutCoPh.fbx");
    hDonutCoLa_ = Model::Load("Assets\\donutCoLa.fbx");
    Camera::SetPosition(XMFLOAT3{ 0, 0.8, -2.8 });
    Camera::SetTarget(XMFLOAT3{ 0,0.8,0 });

    InitConstantBuffer();
}

//�X�V
void Stage::Update()
{
    transform_.rotate_.y += 0.5f;
    if (Input::IsKey(DIK_A))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x - 0.01f,p.y, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_D))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x + 0.01f,p.y, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_W))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x,p.y, p.z + 0.01f,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_S))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x ,p.y, p.z - 0.01f,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_SPACE))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x,p.y + 0.01f, p.z,p.w };
        Direct3D::SetLightPos(p);
    }
    if (Input::IsKey(DIK_LSHIFT))
    {
        XMFLOAT4 p = Direct3D::GetLightPos();
        p = { p.x ,p.y - 0.01f, p.z,p.w };
        Direct3D::SetLightPos(p);
    }

    CONSTBUFER_STAGE cb;
    cb.lightPosition_ = Direct3D::GetLightPos();
    XMStoreFloat4(&cb.eyePosition_, Camera::GetPosition());


    D3D11_MAPPED_SUBRESOURCE pdata;
    Direct3D::pContext_->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
    memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�

    Direct3D::pContext_->Unmap(pConstantBuffer_, 0);	//�ĊJ

    //�R���X�^���g�o�b�t�@
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
}

//�`��
void Stage::Draw()
{

    Transform ltr;
    ltr.position_ = { Direct3D::GetLightPos().x,Direct3D::GetLightPos().y,Direct3D::GetLightPos().z };
    ltr.scale_ = { 0.1,0.1,0.1 };
    Model::SetTransform(hModel_, ltr);
    Model::Draw(hModel_);


    Transform tr;
    tr.position_ = { 0, 0, 0 };
    //tr.scale_ = { 5.0f, 5.0f, 5.0f };
    tr.rotate_ = { 0,0,0 };
    //Model::SetTransform(hGround, tr);
    //Model::Draw(hGround);

    Model::SetTransform(hRoom_, tr);
    Model::Draw(hRoom_);

    static Transform tbunny;
    tbunny.scale_ = { 1,1,1 };
    tbunny.position_ = { -0.5,1.2,0 };
    tbunny.rotate_.y += 0.5;
    Model::SetTransform(hDonutTexPh_, tbunny);
    Model::Draw(hDonutTexPh_);

    tbunny.scale_ = { 1,1,1 };
    tbunny.position_ = { 0.5,1.2,0 };
    tbunny.rotate_.y += 0.5;
    Model::SetTransform(hDonutTexLa_, tbunny);
    Model::Draw(hDonutTexLa_);

    tbunny.scale_ = { 1,1,1 };
    tbunny.position_ = { -0.5,0.3,0 };
    tbunny.rotate_.y += 0.5;
    Model::SetTransform(hDonutCoPh_, tbunny);
    Model::Draw(hDonutCoPh_);

    tbunny.scale_ = { 1,1,1 };
    tbunny.position_ = { 0.5,0.3,0 };
    tbunny.rotate_.y += 0.5;
    Model::SetTransform(hDonutCoLa_, tbunny);
    Model::Draw(hDonutCoLa_);

    ImGui::Text("Rotate:%.3f", tbunny.rotate_.y);

    //�R���X�^���g�o�b�t�@�̐ݒ�ƃV�F�[�_�[�ւ̃R���X�^���g�o�b�t�@�̃Z�b�g������
    //�R���X�^���g�o�b�t�@�̐ݒ�ƃV�F�[�_�[�ւ̃R���X�^���g�o�b�t�@�̃Z�b�g������
}

//�J��
void Stage::Release()
{
}

void Stage::InitConstantBuffer()
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(CONSTBUFER_MODEL);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    HRESULT hr;
    hr = Direct3D::pDevice_->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
    if (FAILED(hr))
    {
        MessageBox(NULL, "�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s���܂���", "�G���[", MB_OK);
    }
}