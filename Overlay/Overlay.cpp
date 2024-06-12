#include "Overlay.hpp"

inline MARGINS gMargin = { 0, 0, 600, 600 };
inline MARGINS zero = { -1, -1, -1, -1 };
inline DWORD dwLastFrameTime = 0;
inline int iLastTick = 0;

static void LimitFPS(int targetfps)
{
    DWORD currentTime = timeGetTime();
    if ((int)(currentTime - dwLastFrameTime) < (1000 / targetfps))
    {
		std::this_thread::sleep_for(std::chrono::milliseconds(currentTime - dwLastFrameTime));
    }
	dwLastFrameTime = currentTime;
}

static void ClickThough(bool click)
{
    if (click)
    {
        SetWindowLong(UI::hWnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
    }
    else
    {
        SetWindowLong(UI::hWnd, GWL_EXSTYLE, WS_EX_LAYERED);
    }
}

static void CalcScreenPos()
{
    UI::iGuiX = UI::iScreenWidth - 600;
    UI::iGuiY = UI::iScreenHeight - 500;
}

static ID3D11Device* g_pd3dDevice = NULL;
static ID3D11DeviceContext* g_pd3dDeviceContext = NULL;
static IDXGISwapChain* g_pSwapChain = NULL;
static ID3D11RenderTargetView* g_mainRenderTargetView = NULL;
static ID3D11ShaderResourceView* renderLogo = nullptr;

static void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

static void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = NULL; }
}

static HRESULT CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    if (D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext) != S_OK)
        return E_FAIL;

    CreateRenderTarget();

    return S_OK;
}

static void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = NULL; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = NULL; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = NULL; }
}

LRESULT WINAPI WndProc(HWND HookhWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Overlay::Loop()
{
    UI::iScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    UI::iScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    CalcScreenPos();

    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "BO3 Zombie Tool", NULL};
    ::RegisterClassEx(&wc);
	UI::hWnd = ::CreateWindow(wc.lpszClassName, "BO3 Zombie Tool", WS_EX_TOPMOST | WS_POPUP, 0, 0, UI::iScreenWidth, UI::iScreenHeight, NULL, NULL, wc.hInstance, NULL);
    ClickThough(true);
    SetLayeredWindowAttributes(UI::hWnd, 0, 255, LWA_ALPHA);
    gMargin = { 0, 0, UI::iScreenWidth, UI::iScreenHeight };
    DwmExtendFrameIntoClientArea(UI::hWnd, &gMargin);
    if (CreateDeviceD3D(UI::hWnd) < 0)
    {
        CleanupDeviceD3D();
        return;
    }
    ::ShowWindow(UI::hWnd, SW_SHOWDEFAULT);
    ::UpdateWindow(UI::hWnd);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;

    ImGui::StyleColorsDark();
    ImGui_ImplWin32_Init(UI::hWnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 18.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Header = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 26.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Header2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 22.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Body = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 20.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::Body2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Roboto_compressed_data, Roboto_compressed_size, 16.f, nullptr, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
    ImGui::FA = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(awesome_light_compressed_data, awesome_light_compressed_size, 20.0f, &icons_config, icons_ranges);
    ImGui::FA2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(Awesome, Awesome_size, 16.f, &icons_config, icons_ranges);
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.00f);

    D3DX11_IMAGE_LOAD_INFO info;
    ID3DX11ThreadPump* pump{ nullptr };
    D3DX11CreateShaderResourceViewFromMemory(g_pd3dDevice, _BO3Logo, sizeof(_BO3Logo), &info,
        pump, &renderLogo, 0);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }
        ::SetWindowPos(UI::hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        LimitFPS(144);
        if (GetKeyState(VK_INSERT) & 0x8000)
        {
            if (((int)GetTickCount64() - iLastTick) > 1000)
            {
                UI::bShowMenu = !UI::bShowMenu;
				iLastTick = (int)GetTickCount64();
            }
        }
        if (UI::bShowMenu)
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            Render::Start();
            Menu::RenderMenu();
            Menu::RenderWatermark();
			Engine::ESP::DoESP();
			Engine::ESP::MiscFeatures();
            Render::End();
            ClickThough(false);
        }
        else
        {
            ImVec4* colors = ImGui::GetStyle().Colors;
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
            Render::Start();
            Menu::RenderWatermark();
			Engine::ESP::DoESP();
			Engine::ESP::MiscFeatures();
            Render::End();
            ClickThough(true);
        }
        ImGui::EndFrame();
        ImGui::Render();
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, NULL);
        float clearColor[4] = { 0.0f,0.0f,0.0f,0.0f };
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, (float*)&clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        g_pSwapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(UI::hWnd);
    ::UnregisterClass(wc.lpszClassName, wc.hInstance);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    switch (msg)
    {
    case WM_SIZE:
        if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            CreateRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

namespace ImGui
{
#pragma region GUI Setup Functions
	ImFont* Header = NULL;
	ImFont* Header2 = NULL;
	ImFont* Body = NULL;
	ImFont* Body2 = NULL;
	ImFont* FA = NULL;
	ImFont* FA2 = NULL;
	ImColor BO3Orange = ImColor(255, 100, 15, 255);
	ImColor DarkGrey22 = ImColor(22, 22, 22, 255);
	ImColor LightGrey26 = ImColor(26, 26, 26, 255);
	ImColor White = ImColor(255, 255, 255, 255);
	ImColor Red = ImColor(254, 94, 87, 255);
	ImColor Green = ImColor(116, 170, 92, 255);
	ImColor Yellow = ImColor(250, 188, 56, 255);
	ImVec4 active = ImVec4(ImColor(255, 100, 15, 255));
	ImVec4 inactive = ImVec4(ImColor(255, 100, 15, 75));

	void ImGui::RenderLogo()
	{
		ImGui::Image((void*)renderLogo, ImVec2((float)UI::iLogoWidth, (float)UI::iLogoHeight));
	}

	void SCP(float xPos, float yPos)
	{
		ImGui::SetCursorPos(ImVec2(xPos, yPos));
	}

	void SCPX(float xPos)
	{
		ImGui::SetCursorPosX(xPos);
	}

	void SCPY(float yPos)
	{
		ImGui::SetCursorPosY(yPos);
	}

	void Line(int newId)
	{
		std::string id = ("ImGui_Sauce_line_" + std::to_string(newId));
		ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
		{
			ImGui::BeginChild(id.c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 1), false);
			ImGui::Separator();
			ImGui::EndChild();
		}
		ImGui::PopStyleColor();
	}

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine)
	{
		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(text).x / 2));
		ImGui::Text(text);
		ImGui::Spacing();
		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void CenterColorTextCustom(const char* nonColorText, const char* colorText, int lineId, ImColor color, BOOL separator, BOOL newLine)
	{
		ImGui::Spacing();
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(nonColorText).x / 2 + ImGui::CalcTextSize(colorText).x / 2));
		ImGui::Text(nonColorText);
		ImGui::SameLine((ImGui::GetContentRegionAvail().x / 2) - (ImGui::CalcTextSize(colorText).x / 2 - ImGui::CalcTextSize(nonColorText).x / 2));
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color));
		ImGui::Text(colorText);
		ImGui::PopStyleColor();
		ImGui::Spacing();
		if (separator)
		{
			ImGui::NewLine();
			Line(lineId);
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextNL(const char* text, BOOL newLine)
	{
		ImGui::Text(text);
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSL(const char* text, BOOL sameLine, BOOL newLine)
	{
		ImGui::Text(text);
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void TextSCP(const char* text, float xPos, float yPos)
	{
		ImGui::SCP(xPos, yPos);
		ImGui::Text(text);
	}

	void TextColor(const char* text, ImVec4 color, int lineId, BOOL seperator, BOOL newLine)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(color));
		ImGui::Text(text);
		ImGui::PopStyleColor();
		if (seperator)
		{
			ImGui::NewLine();
			Line(lineId);
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonNL(const char* featureName, bool* featureBool, ImVec2 size, BOOL newLine)
	{
		if (ImGui::Button(featureName, size))
		{
			*featureBool = !*featureBool;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonSCP(const char* featureName, bool* featureBool, float xPos, float yPos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(xPos, yPos);
		if (ImGui::Button(featureName, size))
		{
			*featureBool = !*featureBool;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonIntSCP(const char* featureName, int* featureInt, int value, float xPos, float yPos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(xPos, yPos);
		if (ImGui::Button(featureName, size))
		{
			*featureInt = value;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonPageSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushStyleColor(ImGuiCol_Button, UI::iTab == pageNumber ? active : inactive);
		if (ImGui::Button(label, size))
		{
			*page = pageNumber;
		}
		ImGui::PopStyleColor();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ButtonWindowSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine)
	{
		ImGui::SCP(pos.x, pos.y);
		if (ImGui::Button(label, size))
		{
			*page = pageNumber;
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void InputIntNL(const char* featureName, int* featureInt, bool* featureBool, float size, BOOL sameLine, BOOL newLine)
	{
		ImGui::PushItemWidth(size);
		if (ImGui::InputInt(featureName, featureInt))
		{
			*featureBool = true;
		}
		ImGui::PopItemWidth();
		if (sameLine)
		{
			ImGui::SameLine();
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ColorEditFeature(const char* featureName, float* colorEditFloat, BOOL newLine)
	{
		ImGui::PushItemWidth(105);
		ImGui::ColorEdit3(featureName, colorEditFloat, ImGuiColorEditFlags_NoInputs);
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void WeaponCycleComboBox(const char* featureName, float size, BOOL newLine)
	{
		const char* cWeaponCycleKeySelection[] = { (" LMB"), (" RMB"), (" MMB"), (" X1MB"), (" X2MB"), (" TAB"), (" LSHIFT"), (" LCTRL"), (" LALT"), (" CAPS"), (" SPACE"),
			(" '0'"), (" '1'"), (" '2'"), (" '3'"), (" 'C'"), (" 'E'"), (" 'F'"), (" 'Q'"), (" 'V'"), (" 'X'"), (" 'Z'"), (" LWIN") };
		static const char* currentItem = (" Select Key");
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, currentItem, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cWeaponCycleKeySelection); n++)
			{
				bool bSelected = (currentItem == cWeaponCycleKeySelection[n]);
				if (ImGui::Selectable(cWeaponCycleKeySelection[n], bSelected))
					currentItem = cWeaponCycleKeySelection[n];
				if (ImGui::IsItemClicked(bSelected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						AimSettings::iAimKey = 0x01;
					}
					if (n == 1)
					{
						AimSettings::iAimKey = 0x02;
					}
					if (n == 2)
					{
						AimSettings::iAimKey = 0x04;
					}
					if (n == 3)
					{
						AimSettings::iAimKey = 0x05;
					}
					if (n == 4)
					{
						AimSettings::iAimKey = 0x06;
					}
					if (n == 5)
					{
						AimSettings::iAimKey = 0x09;
					}
					if (n == 6)
					{
						AimSettings::iAimKey = 0x10;
					}
					if (n == 7)
					{
						AimSettings::iAimKey = 0x11;
					}
					if (n == 8)
					{
						AimSettings::iAimKey = 0x12;
					}
					if (n == 9)
					{
						AimSettings::iAimKey = 0x14;
					}
					if (n == 10)
					{
						AimSettings::iAimKey = 0x20;
					}
					if (n == 11)
					{
						AimSettings::iAimKey = 0x30;
					}
					if (n == 12)
					{
						AimSettings::iAimKey = 0x31;
					}
					if (n == 13)
					{
						AimSettings::iAimKey = 0x32;
					}
					if (n == 14)
					{
						AimSettings::iAimKey = 0x33;
					}
					if (n == 15)
					{
						AimSettings::iAimKey = 0x43;
					}
					if (n == 16)
					{
						AimSettings::iAimKey = 0x45;
					}
					if (n == 17)
					{
						AimSettings::iAimKey = 0x46;
					}
					if (n == 18)
					{
						AimSettings::iAimKey = 0x51;
					}
					if (n == 19)
					{
						AimSettings::iAimKey = 0x56;
					}
					if (n == 20)
					{
						AimSettings::iAimKey = 0x58;
					}
					if (n == 21)
					{
						AimSettings::iAimKey = 0x5A;
					}
					if (n == 22)
					{
						AimSettings::iAimKey = 0x5B;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ZombieTPComboBox(const char* featureName, float size, BOOL newLine)
	{
		const char* cZombieTPKeySelection[] = { (" LMB"), (" RMB"), (" MMB"), (" X1MB"), (" X2MB"), (" TAB"), (" LSHIFT"), (" LCTRL"), (" LALT"), (" CAPS"), (" SPACE"),
			(" '0'"), (" '1'"), (" '2'"), (" '3'"), (" 'C'"), (" 'E'"), (" 'F'"), (" 'Q'"), (" 'V'"), (" 'X'"), (" 'Z'"), (" LWIN") };
		static const char* currentItem = (" Select Key");
		ImGui::PushItemWidth(size);
		if (ImGui::BeginCombo(featureName, currentItem, ImGuiComboFlags_NoArrowButton))
		{
			for (int n = 0; n < IM_ARRAYSIZE(cZombieTPKeySelection); n++)
			{
				bool bSelected = (currentItem == cZombieTPKeySelection[n]);
				if (ImGui::Selectable(cZombieTPKeySelection[n], bSelected))
					currentItem = cZombieTPKeySelection[n];
				if (ImGui::IsItemClicked(bSelected))
				{
					ImGui::SetItemDefaultFocus();
					if (n == 0)
					{
						MiscSettings::iZombieTPKey = 0x01;
					}
					if (n == 1)
					{
						MiscSettings::iZombieTPKey = 0x02;
					}
					if (n == 2)
					{
						MiscSettings::iZombieTPKey = 0x04;
					}
					if (n == 3)
					{
						MiscSettings::iZombieTPKey = 0x05;
					}
					if (n == 4)
					{
						MiscSettings::iZombieTPKey = 0x06;
					}
					if (n == 5)
					{
						MiscSettings::iZombieTPKey = 0x09;
					}
					if (n == 6)
					{
						MiscSettings::iZombieTPKey = 0x10;
					}
					if (n == 7)
					{
						MiscSettings::iZombieTPKey = 0x11;
					}
					if (n == 8)
					{
						MiscSettings::iZombieTPKey = 0x12;
					}
					if (n == 9)
					{
						MiscSettings::iZombieTPKey = 0x14;
					}
					if (n == 10)
					{
						MiscSettings::iZombieTPKey = 0x20;
					}
					if (n == 11)
					{
						MiscSettings::iZombieTPKey = 0x30;
					}
					if (n == 12)
					{
						MiscSettings::iZombieTPKey = 0x31;
					}
					if (n == 13)
					{
						MiscSettings::iZombieTPKey = 0x32;
					}
					if (n == 14)
					{
						MiscSettings::iZombieTPKey = 0x33;
					}
					if (n == 15)
					{
						MiscSettings::iZombieTPKey = 0x43;
					}
					if (n == 16)
					{
						MiscSettings::iZombieTPKey = 0x45;
					}
					if (n == 17)
					{
						MiscSettings::iZombieTPKey = 0x46;
					}
					if (n == 18)
					{
						MiscSettings::iZombieTPKey = 0x51;
					}
					if (n == 19)
					{
						MiscSettings::iZombieTPKey = 0x56;
					}
					if (n == 20)
					{
						MiscSettings::iZombieTPKey = 0x58;
					}
					if (n == 21)
					{
						MiscSettings::iZombieTPKey = 0x5A;
					}
					if (n == 22)
					{
						MiscSettings::iZombieTPKey = 0x5B;
					}
				}
			}
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine)
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImDrawList* draw_list = ImGui::GetWindowDrawList();

		float height = ImGui::GetFrameHeight();
		float width = height * 1.55f;
		float radius = height * 0.50f;

		ImGui::InvisibleButton(toggleName, ImVec2(width, height));
		if (ImGui::IsItemClicked())
			*featureBool = !*featureBool;

		float t = *featureBool ? 1.0f : 0.0f;

		ImGuiContext& g = *GImGui;
		float ANIM_SPEED = 0.08f;
		if (g.LastActiveId == g.CurrentWindow->GetID(toggleName))// && g.LastActiveIdTimer < ANIM_SPEED)
		{
			float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
			t = *featureBool ? (t_anim) : (1.0f - t_anim);
		}

		ImU32 col_bg;
		if (ImGui::IsItemHovered())
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.78f, 0.78f, 0.78f, 0.40f), ImVec4(ImColor(255, 100, 15, 200)), t));
		else
			col_bg = ImGui::GetColorU32(ImLerp(ImVec4(0.85f, 0.85f, 0.85f, 0.60f), ImVec4(ImColor(255, 100, 15, 255)), t));

		draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
		draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

		ImGui::SameLine();
		ImGui::Text(toggleName);

		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	float GetX()
	{
		return ImGui::GetContentRegionAvail().x;
	}

	float GetY()
	{
		return ImGui::GetContentRegionAvail().y;
	}

	void SetCreationTime()
	{
		ConfigSettings::iCreationTime = GetTickCount64();
		//printf("Creation Time: %i\n\n", creationTime);
	}

	bool IsExpired()
	{
		if (ConfigSettings::sNotifyMssg.size() > 0)
		{
			ConfigSettings::iElapsedTime = GetTickCount64() - ConfigSettings::iCreationTime;
			//printf("Elapsed Time: %i\n\n", elapsedTime);
		}
		if (ConfigSettings::iElapsedTime > ConfigSettings::iDissmisTime)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void SetNotifyMessage(const char* text)
	{
		ConfigSettings::bNotifyMssg = true;
		ImGui::SetCreationTime();
		ConfigSettings::sNotifyMssg = text;
	}

	void ResetNotifyMessage()
	{
		if (ImGui::IsExpired())
		{
			ConfigSettings::sNotifyMssg.clear();
			ConfigSettings::iElapsedTime = 0;
			ConfigSettings::iCreationTime = 0;
			ConfigSettings::bNotifyMssg = false;
		}
	}

	void FadeNotifyMessage()
	{
		if (ConfigSettings::sNotifyMssg.size() > 0)
		{
			if (ConfigSettings::iElapsedTime < 1000)
			{
				ConfigSettings::fFadePercentage = (float)ConfigSettings::iElapsedTime / 1000.0f;
				//printf("Fade In Percent: %f  ", fadePercentage);
			}
			else if (ConfigSettings::iElapsedTime > 2000)
			{
				ConfigSettings::fFadePercentage = 1.0f - ((float)(ConfigSettings::iElapsedTime - 2000) / 1000.0f);
				//printf("Fade Out Percent: %f  ", fadePercentage);
			}
		}
	}

	void RenderNotifyMessage(const char* text)
	{
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.f, 1.f, 1.f, ConfigSettings::fFadePercentage));
		ImGui::PushFont(Body2);
		ImGui::CenterText(text, 0, FALSE, FALSE);
		ImGui::PopFont();
		ImGui::PopStyleColor();
		ImGui::FadeNotifyMessage();
		ImGui::ResetNotifyMessage();
	}

	void RenderNotifyWindow(ImVec2 pos, ImVec2 size)
	{
		ImGui::SCP(pos.x, pos.y);
		ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(1.f, 0.412f, 0.f, ConfigSettings::fFadePercentage));
		if (ImGui::BeginChild("NotifyWindow", ImVec2(size.x, size.y), false, windowFlags))
		{
			ImGui::SCPY(7);
			ImGui::RenderNotifyMessage(ConfigSettings::sNotifyMssg.c_str());
		} ImGui::PopStyleColor(); ImGui::EndChild();
	}

	void SetupConfigIcon()
	{
		if (ConfigSettings::iTrackConfigLoaded == 1)
		{
			ImGui::SCP(345, 145);
			ImGui::PushFont(FA);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(Green));
			ImGui::Text(ICON_FA_CHECK_CIRCLE);
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
		if (ConfigSettings::iTrackConfigLoaded == 2)
		{
			ImGui::SCP(345, 225);
			ImGui::PushFont(FA);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(Green));
			ImGui::Text(ICON_FA_CHECK_CIRCLE);
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
		if (ConfigSettings::iTrackConfigLoaded == 3)
		{
			ImGui::SCP(345, 306);
			ImGui::PushFont(FA);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(Green));
			ImGui::Text(ICON_FA_CHECK_CIRCLE);
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
		if (ConfigSettings::iTrackConfigLoaded == 4)
		{
			ImGui::SCP(345, 387);
			ImGui::PushFont(FA);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(Green));
			ImGui::Text(ICON_FA_CHECK_CIRCLE);
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
		if (ConfigSettings::iTrackConfigLoaded == 5)
		{
			ImGui::SCP(345, 468);
			ImGui::PushFont(FA);
			ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(Green));
			ImGui::Text(ICON_FA_CHECK_CIRCLE);
			ImGui::PopStyleColor();
			ImGui::PopFont();
		}
	}

	void SetupDoubleButtonFeatures(const char* featureName1, const char* featureName2, bool* featureBool1, bool* featureBoolLoaded, bool* featureBool2, BOOL newLine)
	{
		ImGui::SCPX(100);
		ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(ImColor(0, 68, 170, 125)));
		if (ImGui::Button(featureName1, ImVec2(115, 27)))
		{
			*featureBool1 = true;
			*featureBoolLoaded = true;
			if (ConfigSettings::iTrackConfigLoaded == 1)
			{
				if (ConfigSettings::bLoadedConfig2)
				{
					ConfigSettings::bLoadedConfig1 = false;
				}
				if (ConfigSettings::bLoadedConfig3)
				{
					ConfigSettings::bLoadedConfig1 = false;
				}
				if (ConfigSettings::bLoadedConfig4)
				{
					ConfigSettings::bLoadedConfig1 = false;
				}
				if (ConfigSettings::bLoadedConfig5)
				{
					ConfigSettings::bLoadedConfig1 = false;
				}
			}
			if (ConfigSettings::iTrackConfigLoaded == 2)
			{
				if (ConfigSettings::bLoadedConfig1)
				{
					ConfigSettings::bLoadedConfig2 = false;
				}
				if (ConfigSettings::bLoadedConfig3)
				{
					ConfigSettings::bLoadedConfig2 = false;
				}
				if (ConfigSettings::bLoadedConfig4)
				{
					ConfigSettings::bLoadedConfig2 = false;
				}
				if (ConfigSettings::bLoadedConfig5)
				{
					ConfigSettings::bLoadedConfig2 = false;
				}
			}
			if (ConfigSettings::iTrackConfigLoaded == 3)
			{
				if (ConfigSettings::bLoadedConfig1)
				{
					ConfigSettings::bLoadedConfig3 = false;
				}
				if (ConfigSettings::bLoadedConfig2)
				{
					ConfigSettings::bLoadedConfig3 = false;
				}
				if (ConfigSettings::bLoadedConfig4)
				{
					ConfigSettings::bLoadedConfig3 = false;
				}
				if (ConfigSettings::bLoadedConfig5)
				{
					ConfigSettings::bLoadedConfig3 = false;
				}
			}
			if (ConfigSettings::iTrackConfigLoaded == 4)
			{
				if (ConfigSettings::bLoadedConfig1)
				{
					ConfigSettings::bLoadedConfig4 = false;
				}
				if (ConfigSettings::bLoadedConfig2)
				{
					ConfigSettings::bLoadedConfig4 = false;
				}
				if (ConfigSettings::bLoadedConfig3)
				{
					ConfigSettings::bLoadedConfig4 = false;
				}
				if (ConfigSettings::bLoadedConfig5)
				{
					ConfigSettings::bLoadedConfig4 = false;
				}
			}
			if (ConfigSettings::iTrackConfigLoaded == 5)
			{
				if (ConfigSettings::bLoadedConfig1)
				{
					ConfigSettings::bLoadedConfig5 = false;
				}
				if (ConfigSettings::bLoadedConfig2)
				{
					ConfigSettings::bLoadedConfig5 = false;
				}
				if (ConfigSettings::bLoadedConfig3)
				{
					ConfigSettings::bLoadedConfig5 = false;
				}
				if (ConfigSettings::bLoadedConfig4)
				{
					ConfigSettings::bLoadedConfig5 = false;
				}
			}
		}
		ImGui::SameLine();
		ImGui::SCPX(220);
		if (ImGui::Button(featureName2, ImVec2(115, 27)))
		{
			*featureBool2 = true;
		}
		ImGui::PopStyleColor();
		if (*featureBoolLoaded)
		{
			if (ConfigSettings::bLoadedConfig1)
			{
				ConfigSettings::iTrackConfigLoaded = 1;
			}
			if (ConfigSettings::bLoadedConfig2)
			{
				ConfigSettings::iTrackConfigLoaded = 2;
			}
			if (ConfigSettings::bLoadedConfig3)
			{
				ConfigSettings::iTrackConfigLoaded = 3;
			}
			if (ConfigSettings::bLoadedConfig4)
			{
				ConfigSettings::iTrackConfigLoaded = 4;
			}
			if (ConfigSettings::bLoadedConfig5)
			{
				ConfigSettings::iTrackConfigLoaded = 5;
			}
		}
		if (newLine)
		{
			ImGui::NewLine();
		}
	}

	void SetupLoadedConfigText()
	{
		if (!ConfigSettings::bLoadedConfig1 && !ConfigSettings::bLoadedConfig2 && !ConfigSettings::bLoadedConfig3 && !ConfigSettings::bLoadedConfig4 && !ConfigSettings::bLoadedConfig5)
		{
			ConfigSettings::iTrackConfigLoaded = 0;
			ImGui::CenterColorTextCustom("Loaded Config : ", "No Config Loaded", 0, Red, FALSE, TRUE);
		}
		if (ConfigSettings::iTrackConfigLoaded == 1)
		{
			ImGui::CenterColorTextCustom("Loaded Config : ", "Config 1 Loaded", 0, Green, FALSE, TRUE);
		}
		if (ConfigSettings::iTrackConfigLoaded == 2)
		{
			ImGui::CenterColorTextCustom("Loaded Config : ", "Config 2 Loaded", 0, Green, FALSE, TRUE);
		}
		if (ConfigSettings::iTrackConfigLoaded == 3)
		{
			ImGui::CenterColorTextCustom("Loaded Config : ", "Config 3 Loaded", 0, Green, FALSE, TRUE);
		}
		if (ConfigSettings::iTrackConfigLoaded == 4)
		{
			ImGui::CenterColorTextCustom("Loaded Config : ", "Config 4 Loaded", 0, Green, FALSE, TRUE);
		}
		if (ConfigSettings::iTrackConfigLoaded == 5)
		{
			ImGui::CenterColorTextCustom("Loaded Config : ", "Config 5 Loaded", 0, Green, FALSE, TRUE);
		}
		if (ConfigSettings::bSavedConfig1)
		{
			ImGui::SetNotifyMessage("- Config 1 Saved -");
			ConfigSettings::bSavedConfig1 = false;
		}
		if (ConfigSettings::bSavedConfig2)
		{
			ImGui::SetNotifyMessage("- Config 2 Saved -");
			ConfigSettings::bSavedConfig2 = false;
		}
		if (ConfigSettings::bSavedConfig3)
		{
			ImGui::SetNotifyMessage("- Config 3 Saved -");
			ConfigSettings::bSavedConfig3 = false;
		}
		if (ConfigSettings::bSavedConfig4)
		{
			ImGui::SetNotifyMessage("- Config 4 Saved -");
			ConfigSettings::bSavedConfig4 = false;
		}
		if (ConfigSettings::bSavedConfig5)
		{
			ImGui::SetNotifyMessage("- Config 5 Saved -");
			ConfigSettings::bSavedConfig5 = false;
		}
	}

	void SetupConfigSaveSettings()
	{
		ImGui::SetupLoadedConfigText();
		ImGui::CenterText("Configuration 1", 0, FALSE, TRUE);
		ImGui::SetupDoubleButtonFeatures("Load Config 1", "Save Config 1", &ConfigSettings::bLoadConfig1, &ConfigSettings::bLoadedConfig1, &ConfigSettings::bSaveConfig1, TRUE);
		ImGui::CenterText("Configuration 2", 0, FALSE, TRUE);
		ImGui::SetupDoubleButtonFeatures("Load Config 2", "Save Config 2", &ConfigSettings::bLoadConfig2, &ConfigSettings::bLoadedConfig2, &ConfigSettings::bSaveConfig2, TRUE);
		ImGui::CenterText("Configuration 3", 0, FALSE, TRUE);
		ImGui::SetupDoubleButtonFeatures("Load Config 3", "Save Config 3", &ConfigSettings::bLoadConfig3, &ConfigSettings::bLoadedConfig3, &ConfigSettings::bSaveConfig3, TRUE);
		ImGui::CenterText("Configuration 4", 0, FALSE, TRUE);
		ImGui::SetupDoubleButtonFeatures("Load Config 4", "Save Config 4", &ConfigSettings::bLoadConfig4, &ConfigSettings::bLoadedConfig4, &ConfigSettings::bSaveConfig4, TRUE);
		//ImGui::CenterText("Configuration 5", 0, FALSE, TRUE);
		//ImGui::SetupDoubleButtonFeatures("Load Config 5", "Save Config 5", &ConfigSettings::bLoadConfig5, &ConfigSettings::bLoadedConfig5, &ConfigSettings::bSaveConfig5, TRUE);
		ImGui::SetupConfigIcon();
	}

	void SetGUITheme()
	{
		ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_HDR | ImGuiColorEditFlags_PickerHueWheel);
		ImGuiStyle* Style = &ImGui::GetStyle();
		Style->WindowBorderSize = 0;
		Style->FrameBorderSize = 0;
		Style->WindowRounding = 4;
		Style->ChildRounding = 4;
		Style->ChildBorderSize = 2;
		Style->FrameRounding = 4;
		Style->ScrollbarSize = 0;
		Style->WindowPadding = ImVec2(0, 0);
		Style->FramePadding = ImVec2(0, 0);
		Style->ItemSpacing = ImVec2(0, 0);
		Style->ItemInnerSpacing = ImVec2(0, 0);
		Style->IndentSpacing = 0;
		Style->DisplayWindowPadding = ImVec2(0, 0);
		Style->Colors[ImGuiCol_WindowBg] = BO3Orange;
		Style->Colors[ImGuiCol_ChildBg] = BO3Orange;
		Style->Colors[ImGuiCol_Border] = BO3Orange;
		Style->Colors[ImGuiCol_Text] = ImColor(255, 255, 255);
		Style->Colors[ImGuiCol_FrameBg] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgHovered] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_FrameBgActive] = ImColor(40, 40, 40, 255);
		Style->Colors[ImGuiCol_SliderGrab] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 0, 255, 255);
		Style->Colors[ImGuiCol_Button] = ImColor(255, 100, 15, 255);
		Style->Colors[ImGuiCol_ButtonHovered] = ImColor(255, 100, 15, 200);
		Style->Colors[ImGuiCol_ButtonActive] = ImColor(255, 100, 15, 155);
		Style->Colors[ImGuiCol_Separator] = BO3Orange;
		Style->Colors[ImGuiCol_SeparatorActive] = BO3Orange;
		Style->Colors[ImGuiCol_CheckMark] = BO3Orange;
		Style->Colors[ImGuiCol_HeaderHovered] = BO3Orange;
		Style->Colors[ImGuiCol_HeaderActive] = BO3Orange;
		Style->Colors[ImGuiCol_Header] = BO3Orange;
		Style->Colors[ImGuiCol_TextSelectedBg] = BO3Orange;
	}
#pragma endregion

#pragma region Main GUI Render Function
	void RenderGUI()
	{
		// Main Child Window.
		if (ImGui::BeginChild("MainChildWindow", ImVec2(600, 500), true, windowFlags))
		{
			// Top Logo Window.
			ImGui::SCP(0, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("TopLogoWindow", ImVec2(144, 120), true, windowFlags))
			{
				ImGui::SCP(ImGui::GetX() / 2 - 64, ImGui::GetY() / 2 - 46);
				ImGui::RenderLogo();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Top Header Window.
			ImGui::SCP(145, 0);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("TopHeaderWindow", ImVec2(454, 50), true, windowFlags))
			{
				ImGui::SCPY(12);
				ImGui::PushFont(Header2);
				if (UI::iTab == 0)
				{
					ImGui::CenterText("BO3 Zombie Visuals", 0, FALSE, FALSE);
				}
				if (UI::iTab == 1)
				{
					ImGui::CenterText("BO3 Zombie Aimbot", 0, FALSE, FALSE);
				}
				if (UI::iTab == 2)
				{
					ImGui::CenterText("BO3 Zombie Exploits", 0, FALSE, FALSE);
				}
				if (UI::iTab == 3)
				{
					ImGui::CenterText(("SAVE | LOAD | CONFIG SYSTEM"), 0, FALSE, FALSE);
				}
				ImGui::PopFont();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Left Side Task Bar.
			ImGui::SCP(1, 120);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("LeftSideTaskBarWindow", ImVec2(145, 379), true, windowFlags))
			{
				// Window Buttons.
				ImGui::PushFont(Body2);
				ImGui::ButtonPageSCP("ESP", &UI::iTab, 0, ImVec2(10, 43), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Beta", &UI::iTab, 1, ImVec2(10, 138), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Player", &UI::iTab, 2, ImVec2(10, 233), ImVec2(125, 40), FALSE);
				ImGui::ButtonPageSCP("Settings", &UI::iTab, 3, ImVec2(10, 328), ImVec2(125, 40), FALSE);
				ImGui::PopFont();
				ImGui::PushFont(Body);
				ImGui::TextSCP("Visuals", 10, 13);
				ImGui::TextSCP("Aimbot", 10, 108);
				ImGui::TextSCP("Exploits", 10, 203);
				ImGui::TextSCP("Config", 10, 298);
				ImGui::PopFont();
				ImGui::PushFont(Body2);
				ImGui::TextSCP(ICON_FA_VECTOR_SQUARE, 15, 57);
				ImGui::TextSCP(ICON_FA_BULLSEYE, 15, 152);
				ImGui::TextSCP(ICON_FA_CODE, 15, 247);
				ImGui::TextSCP(ICON_FA_COGS, 15, 342);
				ImGui::PopFont();
			} ImGui::PopStyleColor(); ImGui::EndChild();

			// Main Content.
			ImGui::SCP(145, 60);
			ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(DarkGrey22));
			if (ImGui::BeginChild("MainContentWindow", ImVec2(454, 439), true, windowFlags))
			{
				// Visuals Window.
				if (UI::iTab == 0)
				{
					// Visuals Features Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("VisualsFeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Visuals", 10, TRUE, TRUE);
						ImGui::Indent(12);
						ImGui::ToggleNL("  2D Box", &VisualSettings::bZombie2DBox, TRUE);
						ImGui::ToggleNL("  2D Bracket", &VisualSettings::bZombie2DBrackets, TRUE);
						ImGui::ToggleNL("  Box Filled", &VisualSettings::bZombieBoxFilled, TRUE);
						ImGui::ToggleNL("  Snapline", &VisualSettings::bZombieSnaplines, TRUE);
						ImGui::ToggleNL("  Health Bar", &VisualSettings::bZombieHealthBar, TRUE);
						ImGui::ToggleNL("  Distance", &VisualSettings::bZombieDistance, TRUE);
						ImGui::ToggleNL("  Crosshair +", &MiscSettings::bCrosshair, TRUE);
						ImGui::ToggleNL("  FOV Circle", &MiscSettings::bPlayerFov, TRUE);
						ImGui::ButtonIntSCP("Snapline Top", &VisualSettings::iZombieSnaplinePos, 1, 12, 343, ImVec2(188, 20), FALSE);
						ImGui::ButtonIntSCP("Snapline Mid", &VisualSettings::iZombieSnaplinePos, 2, 12, 368, ImVec2(188, 20), FALSE);
						ImGui::ButtonIntSCP("Snapline Bottom", &VisualSettings::iZombieSnaplinePos, 3, 12, 393, ImVec2(188, 20), FALSE);
						ImGui::Unindent(12);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

					// Visuals Color Settings Window.
					ImGui::SCP(232, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("ColorSettingsWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Color Settings", 10, TRUE, TRUE);
						ImGui::Indent(12);
						ImGui::ColorEditFeature("  2D Box", (float*)&VisualSettings::boxImColor, TRUE);
						ImGui::ColorEditFeature("  2D Bracket", (float*)&VisualSettings::bracketBoxImColor, TRUE);
						ImGui::ColorEditFeature("  Box Filled", (float*)&VisualSettings::boxFilledImColor, TRUE);
						ImGui::ColorEditFeature("  Snapline", (float*)&VisualSettings::snaplineImColor, TRUE);
						ImGui::ColorEditFeature("  Health Text", (float*)&VisualSettings::healthTextImColor, TRUE);
						ImGui::ColorEditFeature("  Distance", (float*)&VisualSettings::distanceImColor, TRUE);
						ImGui::ColorEditFeature("  Crosshair +", (float*)&VisualSettings::crosshairImColor, TRUE);
						ImGui::ColorEditFeature("  FOV", (float*)&VisualSettings::fovImColor, TRUE);
						ImGui::ToggleNL("  Draw Watermark", &UI::bShowWatermark, FALSE);
						ImGui::Unindent(12);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
				// Aimbot Window.
				if (UI::iTab == 1)
				{
					// Aimbot Features Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("AimbotFeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Aimbot", 10, TRUE, TRUE);
						ImGui::SCPY(ImGui::GetY() / 2 - 50);
						ImGui::CenterText("COMING SOON!", 0, FALSE, FALSE);
						ImGui::SCPY(ImGui::GetY() / 2 + 50);
						ImGui::CenterText("PLEASE BE PATIENT", 0, FALSE, FALSE);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

					// Aimbot Bone Select Window.
					ImGui::SCP(232, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("AimbotBoneSettingsWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
					{
						ImGui::SCPY(10);
						ImGui::CenterText("Bone Select", 10, TRUE, TRUE);
						ImGui::SCPY(ImGui::GetY() / 2 - 50);
						ImGui::CenterText("COMING SOON!", 0, FALSE, FALSE);
						ImGui::SCPY(ImGui::GetY() / 2 + 50);
						ImGui::CenterText("PLEASE BE PATIENT", 0, FALSE, FALSE);
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
				// Exploits Window.
				if (UI::iTab == 2)
				{
					if (UI::iExploitPage == 1)
					{
						if (UI::iPlayer1ExploitPage == 1)
						{
							// Player 1 Feature Window.
							ImGui::SCP(10, 10);
							ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
							if (ImGui::BeginChild("Player1FeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
							{
								ImGui::SCPY(10);
								ImGui::CenterText("Player 1 ( HOST )", 10, TRUE, TRUE);
								ImGui::Indent(12);
								ImGui::ToggleNL("  Godmode", &FeatureSettings::bP1InfiniteHealth, TRUE);
								ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP1InfiniteClipAmmo, TRUE);
								ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP1InfiniteStockAmmo, TRUE);
								ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP1RapidFire, TRUE);
								ImGui::ToggleNL("  No Recoil", &FeatureSettings::bNoRecoilOn, TRUE);
								ImGui::InputIntNL("  Points  ", &FeatureSettings::iP1PointsValue, &FeatureSettings::bP1DynamicPoints, 100, TRUE, FALSE);
								ImGui::ToggleNL("", &FeatureSettings::bP1InfinitePoints, TRUE);
								ImGui::InputIntNL("  Weapon Cycle", &FeatureSettings::iP1WCValue, &FeatureSettings::bP1WCycle, 80, FALSE, TRUE);
								ImGui::ToggleNL("  Weapon Cycle HotKey", &FeatureSettings::bP1WCycleKey, TRUE);
								ImGui::WeaponCycleComboBox("  WC HotKey", 80, FALSE);
								ImGui::Unindent(12);
								ImGui::ButtonWindowSCP(">", &UI::iPlayer1ExploitPage, 2, ImVec2(152, 390), ImVec2(50, 20), FALSE);
							} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
						}

						if (UI::iPlayer1ExploitPage == 2)
						{
							// Player 1 Feature Window Extended.
							ImGui::SCP(10, 10);
							ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
							ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
							if (ImGui::BeginChild("Player1FeatureWindowExtended", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
							{
								ImGui::SCPY(10);
								ImGui::CenterText("Player 1 ( HOST )", 10, TRUE, TRUE);
								ImGui::Indent(12);
								ImGui::ToggleNL("  Zombie Counter", &FeatureSettings::bZombieCount, TRUE);
								ImGui::ToggleNL("  Teleport Zombie", &FeatureSettings::bZombieTP, TRUE);
								ImGui::ZombieTPComboBox("  TP HotKey", 80, TRUE);
								ImGui::ToggleNL("  Zombie InstaKill", &FeatureSettings::bP1AlwaysInstaKill, TRUE);
								ImGui::InputIntNL("  Run Speed  ", &FeatureSettings::iP1RunValue, &FeatureSettings::bP1RunSpeed, 100, FALSE, TRUE);
								ImGui::InputIntNL("  Jumpheight", &FeatureSettings::iJumpHeightValue, &FeatureSettings::bP1JumpHeight, 100, FALSE, FALSE);
								ImGui::Unindent(12);
								ImGui::ButtonWindowSCP("<", &UI::iPlayer1ExploitPage, 1, ImVec2(152, 390), ImVec2(50, 20), FALSE);
							} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
						}

						// Player 2 Feature Window.
						ImGui::SCP(232, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player2FeatureWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 2", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP2InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP2InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP2InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP2RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP2PointsValue, &FeatureSettings::bP2DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP2InfinitePoints, TRUE);
							ImGui::InputIntNL("  Run Speed  ", &FeatureSettings::iP2RunValue, &FeatureSettings::bP2RunSpeed, 100, FALSE, FALSE);
							ImGui::Unindent(12);
							ImGui::ButtonWindowSCP(">", &UI::iExploitPage, 2, ImVec2(152, 390), ImVec2(50, 20), FALSE);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
					}

					if (UI::iExploitPage == 2)
					{
						// Player 3 Feature Window.
						ImGui::SCP(10, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player3FeatureWindow", ImVec2(ImGui::GetX() / 2 - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 3", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP3InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP3InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP3InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP3RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP3PointsValue, &FeatureSettings::bP3DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP3InfinitePoints, TRUE);
							ImGui::InputIntNL("  Run Speed  ", &FeatureSettings::iP3RunValue, &FeatureSettings::bP3RunSpeed, 100, FALSE, FALSE);
							ImGui::Unindent(12);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();

						// Player 4 Feature Window.
						ImGui::SCP(232, 10);
						ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
						ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
						if (ImGui::BeginChild("Player4FeatureWindow", ImVec2(ImGui::GetX() - 10, ImGui::GetY() - 10), false, windowFlags))
						{
							ImGui::SCPY(10);
							ImGui::CenterText("Player 4", 10, TRUE, TRUE);
							ImGui::Indent(12);
							ImGui::ToggleNL("  Godmode", &FeatureSettings::bP4InfiniteHealth, TRUE);
							ImGui::ToggleNL("  Unlimited Clip", &FeatureSettings::bP4InfiniteClipAmmo, TRUE);
							ImGui::ToggleNL("  Unlimited Stock", &FeatureSettings::bP4InfiniteStockAmmo, TRUE);
							ImGui::ToggleNL("  Rapid Fire", &FeatureSettings::bP4RapidFire, TRUE);
							ImGui::InputIntNL("  Points  ", &FeatureSettings::iP4PointsValue, &FeatureSettings::bP4DynamicPoints, 100, TRUE, FALSE);
							ImGui::ToggleNL("", &FeatureSettings::bP4InfinitePoints, TRUE);
							ImGui::InputIntNL("  Run Speed  ", &FeatureSettings::iP4RunValue, &FeatureSettings::bP4RunSpeed, 100, FALSE, FALSE);
							ImGui::Unindent(12);
							ImGui::ButtonWindowSCP("<", &UI::iExploitPage, 1, ImVec2(152, 390), ImVec2(50, 20), FALSE);
						} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
					}
				}
				// Config System Window.
				if (UI::iTab == 3)
				{
					// Config Feature Window.
					ImGui::SCP(10, 10);
					ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(LightGrey26));
					ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 10);
					if (ImGui::BeginChild("ConfigSystemWindow", ImVec2(434, ImGui::GetY() - 10), false, windowFlags))
					{
						// Render Notify Window.
						if (ConfigSettings::bNotifyMssg)
						{
							ImGui::RenderNotifyWindow(ImVec2(276, 8), ImVec2(150, 30));
						}
						ImGui::SCPY(10);
						ImGui::CenterText("Config System", 10, TRUE, TRUE);
						ImGui::SetupConfigSaveSettings();
					} ImGui::PopStyleColor(); ImGui::PopStyleVar(); ImGui::EndChild();
				}
			} ImGui::PopStyleColor(); ImGui::EndChild();
		} ImGui::EndChild();
	}
#pragma endregion
}

void Menu::RenderWatermark()
{
	if (UI::bShowWatermark)
	{
		Render::EasyText(ImVec2(10, 10), ImGui::BO3Orange, "Open Source BO3 ZM Tool", 15.f);
	}
}

void Menu::RenderMenu()
{
    ImGui::SetNextWindowPos(ImVec2((float)UI::iGuiX / 2.f, (float)UI::iGuiY / 2.f), ImGuiCond_Once);

    ImGui::SetGUITheme();

    if (ImGui::Begin("BO3 Zombie Tool", 0, windowFlags))
    {
        ImGui::RenderGUI();
    } ImGui::End();
}

namespace Render
{
	void Start()
	{
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2((float)UI::iScreenWidth, (float)UI::iScreenHeight), ImGuiCond_Always);
		ImGui::Begin("TransparentBackgroundWindow", (bool*)true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
	}

	void End()
	{
		ImGui::End();
	}

	extern __inline void Text(ImVec2 pos, float fontsize, ImColor color, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect)
	{
		ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), fontsize, pos, color, text_begin, text_end,
			wrap_width, cpu_fine_clip_rect);
	}

	extern __inline void RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags)
	{
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x0, y0), ImVec2(x1, y1), color, rounding, rounding_corners_flags);
	}

	extern __inline void RectFilled2(float x, float y, float w, float h, ImColor color)
	{
		ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0, 0);
	}

	extern __inline void Line(ImVec2 a, ImVec2 b, ImColor color, float thickness)
	{
		ImGui::GetWindowDrawList()->AddLine(a, b, color, thickness);
	}

	extern __inline void DrawBoxBrackets(ImDrawList* list, float x, float y, float width, float height, ImColor color, float thickness)
	{
		ImVec2 dLine[2];
		dLine[0] = { x, y };
		dLine[1] = { x + 1 * (width / 4), y };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x + 3 * (width / 4), y };
		dLine[1] = { x + width, y };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x + width, y };
		dLine[1] = { x + width, y + 1 * (height / 4) };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x + width, y + 3 * (height / 4) };
		dLine[1] = { x + width, y + height };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x, y + height };
		dLine[1] = { x + 1 * (width / 4), y + height };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x + 3 * (width / 4), y + height };
		dLine[1] = { x + width, y + height };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x, y };
		dLine[1] = { x, y + 1 * (height / 4) };
		list->AddLine(dLine[0], dLine[1], color, thickness);

		dLine[0] = { x, y + 3 * (height / 4) };
		dLine[1] = { x, y + height };
		list->AddLine(dLine[0], dLine[1], color, thickness);
	}

	extern __inline void EasyText(ImVec2 pos, ImColor color, const char* text, float fontSize)
	{
		Text(ImVec2(pos.x + 1.f, pos.y + 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
		Text(ImVec2(pos.x - 1.f, pos.y - 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
		Text(ImVec2(pos.x, pos.y - 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
		Text(ImVec2(pos.x, pos.y + 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text, text + strlen(text), 800, 0);
		Text(ImVec2(pos.x, pos.y), fontSize, color, text, text + strlen(text), 800, 0);
	}

	extern __inline void EasyNumber(ImVec2 pos, ImColor color, int number, float fontSize)
	{
		auto text = std::to_string(number);
		Text(ImVec2(pos.x + 1.f, pos.y + 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
		Text(ImVec2(pos.x - 1.f, pos.y - 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
		Text(ImVec2(pos.x, pos.y - 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
		Text(ImVec2(pos.x, pos.y + 1.f), fontSize, ImColor(0.f, 0.f, 0.f, 1.f), text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
		Text(ImVec2(pos.x, pos.y), fontSize, color, text.c_str(), text.c_str() + strlen(text.c_str()), 800, 0);
	}

	extern __inline void DrawBox(ImColor color, float x, float y, float w, float h)
	{
		float thicc = 1.0f;
		Line(ImVec2(x, y), ImVec2(x + w, y), color, thicc);
		Line(ImVec2(x, y), ImVec2(x, y + h), color, thicc);
		Line(ImVec2(x + w, y), ImVec2(x + w, y + h), color, thicc);
		Line(ImVec2(x, y + h), ImVec2(x + w, y + h), color, thicc);
	}

	extern __inline void Circle(ImColor color, float fov)
	{
		ImVec2 center = ImVec2((float)UI::iScreenWidth / 2, (float)UI::iScreenHeight / 2);
		ImGui::GetWindowDrawList()->AddCircle(center, fov, color, 100, 1.f);
	}

#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
	extern __inline void HealthBar(float x, float y, float w, float h, int ehealth)
	{
		int healthValue = max(0, min(ehealth, 100));

		ImColor barColor = ImColor
		(
			min(510 * (100 - healthValue) / 100, 255),
			min(510 * healthValue / 100, 255),
			25,
			255
		);

		RectFilled(x, y, x + w, y + (int)((h / 100.0f) * (float)ehealth), barColor, 0.0f, 0);
	}

	extern __inline void CustomHealthColor(float currentHealth, float maxHealth, ImColor* healthColor)
	{
		int healthValue = (int)(max(0, min(currentHealth, maxHealth)));

		ImColor lerpColor = ImColor
		(
			min(510 * ((int)maxHealth - healthValue) / (int)maxHealth, 255),
			min(510 * healthValue / (int)maxHealth, 255),
			25,
			255
		);

		*healthColor = lerpColor;
	}

	extern __inline float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...)
	{
		va_list(args);
		va_start(args, text);

		CHAR wbuffer[256] = { };
		vsprintf_s(wbuffer, text, args);

		va_end(args);

		auto DrawList = ImGui::GetForegroundDrawList();

		std::stringstream stream(text);
		std::string line;

		float y = 0.0f;
		int i = 0;

		while (std::getline(stream, line))
		{
			ImVec2 textSize = pFont->CalcTextSizeA(size, FLT_MAX, 0.0f, wbuffer);

			if (center)
			{
				DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x - textSize.x / 2.0f) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

				DrawList->AddText(pFont, size, ImVec2(pos.x - textSize.x / 2.0f, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
			}
			else
			{
				DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x) + 1, (pos.y + textSize.y * i) - 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);
				DrawList->AddText(pFont, size, ImVec2((pos.x) - 1, (pos.y + textSize.y * i) + 1), ImGui::GetColorU32(ImVec4(0, 0, 0, 255)), wbuffer);

				DrawList->AddText(pFont, size, ImVec2(pos.x, pos.y + textSize.y * i), ImGui::GetColorU32(color), wbuffer);
			}

			y = pos.y + textSize.y * (i + 1);
			i++;
		}
		return y;
	}
}