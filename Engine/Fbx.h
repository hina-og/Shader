#pragma once

#include <d3d11.h>
#include <fbxsdk.h>
#include <string>
#include "Transform.h"
#include <vector>


#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

using std::vector;

class Texture;

class Fbx
{
	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
		XMFLOAT4 specular;//鏡面反射係数
		XMFLOAT4 shininess;//鏡面反射のパラメーター
		XMFLOAT4 ambient;//環境光の反射係数（環境光の色？）
		XMFLOAT4 factor;
	};

	struct CONSTBUFER_MODEL
	{
		XMMATRIX	matWVP;//スクリーン変換マトリクス
		XMMATRIX	matW; //ワールド変換マトリクス
		XMMATRIX	matNormal;//法線ワールド変換用マトリクス
		XMFLOAT4	diffuseColor;//RGBの拡散反射係数（色）
		//XMFLOAT4    lightPosition;//光源位置
		XMFLOAT4	diffuseFactor;//拡散光の反射係数
		XMFLOAT4 ambientColor;
		XMFLOAT4 specularColor;
		XMFLOAT4 shininess;
		int			isTextured;
	};

	struct VERTEX
	{
		XMVECTOR position;//位置
		XMVECTOR uv; //テクスチャ座標
		XMVECTOR normal; //法線ベクトル
	};

	bool light;//true:点光源、false:平行光源

	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	ID3D11Buffer* pVertexBuffer_;
	ID3D11Buffer** pIndexBuffer_;
	ID3D11Buffer* pConstantBuffer_;
	std::vector<MATERIAL> pMaterialList_;
	vector <int> indexCount_;
	
	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void IntConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);
public:

	Fbx();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};