//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

#pragma once
#include "DXSample.h"
#include "DynamicConstantBuffer.h"
#include "MemoryMappedPSOCache.h"
#include "SimpleVertexShader.hlsl.h"
#include "SimplePixelShader.hlsl.h"
#include "QuadVertexShader.hlsl.h"
#include "InvertPixelShader.hlsl.h"
#include "BlitPixelShader.hlsl.h"
#include "GrayScalePixelShader.hlsl.h"
#include "EdgeDetectPixelShader.hlsl.h"
#include "BlurPixelShader.hlsl.h"
#include "WarpPixelShader.hlsl.h"
#include "PixelatePixelShader.hlsl.h"
#include "DistortPixelShader.hlsl.h"
#include "WavePixelShader.hlsl.h"
#include "UberPixelShader.hlsl.h"

using namespace Microsoft::WRL;
using namespace DirectX;
using namespace std;

enum EffectPipelineType
{
	// These always get compiled at startup.
	BaseNormal3DRender,
	BaseUberShader,

	// These are compiled a la carte.
	PostBlit,
	PostInvert,
	PostGrayScale,
	PostEdgeDetect,
	PostBlur,
	PostWarp,
	PostPixelate,
	PostDistort,
	PostWave,
	EffectPipelineTypeCount
};

struct GraphicsShaderSet
{
	D3D12_INPUT_LAYOUT_DESC inputLayout;
	D3D12_SHADER_BYTECODE VS;
	D3D12_SHADER_BYTECODE PS;
	D3D12_SHADER_BYTECODE DS;
	D3D12_SHADER_BYTECODE HS;
	D3D12_SHADER_BYTECODE GS;
};

static const D3D12_INPUT_ELEMENT_DESC g_cSimpleInputElementDescs[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

static const D3D12_INPUT_ELEMENT_DESC g_cQuadInputElementDescs[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
};

static const D3D12_INPUT_LAYOUT_DESC g_cForwardRenderInputLayout = { g_cSimpleInputElementDescs, _countof(g_cSimpleInputElementDescs) };
static const D3D12_INPUT_LAYOUT_DESC g_cQuadInputLayout = { g_cQuadInputElementDescs, _countof(g_cQuadInputElementDescs) };

static const GraphicsShaderSet g_cEffectShaderData[EffectPipelineTypeCount] =
{
	{
		g_cForwardRenderInputLayout,
		{ g_SimpleVertexShader, sizeof(g_SimpleVertexShader) },
		{ g_SimplePixelShader, sizeof(g_SimplePixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_UberPixelShader, sizeof(g_UberPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_BlitPixelShader, sizeof(g_BlitPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{g_QuadVertexShader, sizeof(g_QuadVertexShader)},
		{g_InvertPixelShader, sizeof(g_InvertPixelShader)},
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_GrayScalePixelShader, sizeof(g_GrayScalePixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_EdgeDetectPixelShader, sizeof(g_EdgeDetectPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_BlurPixelShader, sizeof(g_BlurPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_WarpPixelShader, sizeof(g_WarpPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_PixelatePixelShader, sizeof(g_PixelatePixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_DistortPixelShader, sizeof(g_DistortPixelShader) },
		{},
		{},
		{},
	},
	{
		g_cQuadInputLayout,
		{ g_QuadVertexShader, sizeof(g_QuadVertexShader) },
		{ g_WavePixelShader, sizeof(g_WavePixelShader) },
		{},
		{},
		{},
	},
};

static const LPWCH g_cCacheFileNames[EffectPipelineTypeCount] =
{
	L"normal3dPSO.cache",
	L"ubershaderPSO.cache",
	L"blitEffectPSO.cache",
	L"invertEffectPSO.cache",
	L"grayscaleEffectPSO.cache",
	L"edgeDetectEffectPSO.cache",
	L"blurEffectPSO.cache",
	L"warpEffectPSO.cache",
	L"pixelateEffectPSO.cache",
	L"distortEffectPSO.cache",
	L"waveEffectPSO.cache",
};

class PSOLibrary
{
public:
	PSOLibrary(UINT frameCount, UINT cbvRootSignatureIndex);
	~PSOLibrary();

	void Build(ID3D12Device* pDevice, ID3D12RootSignature* pRootSignature);

	void SetPipelineState(
		ID3D12Device* pDevice,
		ID3D12RootSignature* pRootSignature,
		ID3D12GraphicsCommandList* pCommandList,
		_In_range_(0, EffectPipelineTypeCount-1) EffectPipelineType type,
		UINT frameIndex);

	void EndFrame();
	void ClearPSOCache();
	void ToggleUberShader();
	void ToggleDiskLibrary();
	void DestroyShader(EffectPipelineType type);

	bool UberShadersEnabled() { return m_useUberShaders; }
	bool DiskCacheEnabled() { return m_useDiskLibraries; }

private:
	static const UINT BaseEffectCount = 2;

	struct CompilePSOThreadData
	{
		PSOLibrary* pLibrary;
		ID3D12Device* pDevice;
		ID3D12RootSignature* pRootSignature;
		EffectPipelineType type;

		HANDLE threadHandle;
	};

	// This will be used to tell the uber shader which effect to use.
	struct UberShaderConstantBuffer
	{
		UINT32 effectIndex;
	};

	static void CompilePSO(CompilePSOThreadData* pDataPackage);
	void WaitForThreads();

	ComPtr<ID3D12PipelineState> m_pipelineStates[EffectPipelineTypeCount];
	bool m_compiledPSOFlags[EffectPipelineTypeCount];
	bool m_inflightPSOFlags[EffectPipelineTypeCount];
	MemoryMappedPSOCache m_diskCaches[EffectPipelineTypeCount];
	HANDLE m_flagsMutex;
	CompilePSOThreadData m_workerThreads[EffectPipelineTypeCount];

	bool m_useUberShaders;
	bool m_useDiskLibraries;
	std::wstring m_assetsPath;

	UINT m_cbvRootSignatureIndex;
	UINT m_maxDrawsPerFrame;
	UINT m_drawIndex;

	DynamicConstantBuffer m_dynamicCB;
};
