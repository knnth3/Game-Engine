#pragma once
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")
#include <d3d11.h>
#include <comdef.h>
#include "DX11Camera.h"
#include "Primitives.h"
#include "D3Dcompiler.h"

#define Check(x, lpctstr) \
	if(!(x)) { MessageBox(0, lpctstr, L"Error", MB_OK);}

#define CheckSuccess(hresult) \
	{_com_error err(hresult); Check(SUCCEEDED(hresult), err.ErrorMessage());}


namespace Lime
{
	class DX11Renderer
	{
	public:
		DLL_EXPORT DX11Renderer(HWND window, int width, int height);
		DLL_EXPORT ~DX11Renderer();

		DLL_EXPORT HRESULT Initialize();
		DLL_EXPORT void Close();

		DLL_EXPORT void Render();
		DLL_EXPORT void AttatchCamera(std::shared_ptr<DX11Camera>& ptr);
	private:
		std::vector<glm::vec3> m_verticies;
		HRESULT CreateBuffers();
		HRESULT CreateShaders();
		HRESULT CreateConstBuffers();
		HRESULT CreateRenderStates();
		HRESULT CompileShader(LPCWSTR srcFile, LPCSTR entryPoint, 
			LPCSTR profile, ID3DBlob** blob);
		unsigned int m_width, m_height;
		HWND m_window;
		HINSTANCE m_hInstance;
		IDXGISwapChain* SwapChain;
		ID3D11Device* m_dx11device;
		ID3D11DeviceContext* m_dx11Context;
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Buffer* m_ObjConstBuffer;
		ID3D11Buffer* m_indexBuffer;
		ID3D11Buffer* m_vertexBuffer;
		LPCWSTR m_psPath;
		LPCWSTR m_vsPath;
		ID3DBlob *vsBlob = nullptr;
		ID3DBlob *psBlob = nullptr;
		ID3D11VertexShader* VS;
		ID3D11PixelShader* PS;
		ID3D11InputLayout* vertLayout;
		std::vector<ID3D11VertexShader*> m_vertexShaders;
		std::vector<ID3D11PixelShader*> m_pixelShaders;
		ID3D11DepthStencilView* depthStencilView;
		ID3D11Texture2D* depthStencilBuffer;
		std::shared_ptr<DX11Camera> m_camera;
		ID3D11RasterizerState* WireFrame;
		struct ConstBuffer
		{
			XMMATRIX WVP;
		};
		ConstBuffer m_ObjBuffer;

		//Temp
		Vertex2 v[8] =
		{
			Vertex2(-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
			Vertex2(-1.0f, +1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f),
			Vertex2(+1.0f, +1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
			Vertex2(+1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f),
			Vertex2(-1.0f, -1.0f, +1.0f, 0.0f, 1.0f, 1.0f, 1.0f),
			Vertex2(-1.0f, +1.0f, +1.0f, 1.0f, 1.0f, 1.0f, 1.0f),
			Vertex2(+1.0f, +1.0f, +1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
			Vertex2(+1.0f, -1.0f, +1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
		};

		DWORD indices[36] = {
			// front face
			0, 1, 2,
			0, 2, 3,

			// back face
			4, 6, 5,
			4, 7, 6,

			// left face
			4, 5, 1,
			4, 1, 0,

			// right face
			3, 2, 6,
			3, 6, 7,

			// top face
			1, 5, 6,
			1, 6, 2,

			// bottom face
			4, 0, 3,
			4, 3, 7
		};

		XMMATRIX cube1World;
		XMMATRIX cube2World;

		XMMATRIX Rotation;
		XMMATRIX Scale;
		XMMATRIX Translation;
		float rot = 0.01f;
	};


}