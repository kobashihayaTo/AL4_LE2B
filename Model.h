#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
class Model
{
private: // エイリアス
// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public://サブクラス

		// 頂点データ構造体
	struct VertexPosNormalUv
	{
		XMFLOAT3 pos; // xyz座標
		XMFLOAT3 normal; // 法線ベクトル
		XMFLOAT2 uv;  // uv座標
	};

	//マテリアル
	struct Material
	{
		std::string name;//マテリアル
		XMFLOAT3 ambient;//アンビエント影響度
		XMFLOAT3 diffuse;//ディフューズ影響度
		XMFLOAT3 specular;//スペキュラー影響度
		float alpha;
		std::string textureFilename;//テクスチャファイル名
		//コンストラクタ
		Material() {
			ambient = { 0.3f,0.3f,0.3f };
			diffuse = { 0.0f,0.0f,0.0f };
			specular = { 0.0f,0.0f,0.0f };
			alpha = 1.0f;
		}
	};
public:
	//OBJファイルから3Dモデルを読み込む
	static Model* LoadFromOBJ();
	/// <summary>
	/// テクスチャ読み込み
	/// </summary>
	bool LoadTexture(const std::string& directoryPath, const std::string& filename);
	/// <summary>
	/// マテリアル読み込み
	/// </summary>
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	//setter
	static void SetDevice(ID3D12Device* device) { Model::device = device; }

private://非公開のメンバ関数
	//OBJファイルから3Dモデルを読み込む
	void LoadFromInternal();

private:
	// デスクリプタサイズ
	UINT descriptorHandleIncrementSize;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView;
	// デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// 頂点データ配列
	std::vector<VertexPosNormalUv>vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	//マテリアル
	Material material;

	// デバイス
	static ID3D12Device* device;
};

