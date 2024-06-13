#pragma once
#include "../Engine/Engine.hpp"

#define WND_SIZEX GetSystemMetrics(SM_CXSCREEN)
#define WND_SIZEY GetSystemMetrics(SM_CYSCREEN)

#define MAX_RGB 255.0
#define HELPMARKERDESC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ ? ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#define HELPMARKERDISC(str) ImGui::SameLine(); ImGui::TextColored(ImColor(0, 130, 15, 255), "[ * ]"); if (ImGui::IsItemHovered()) ImGui::SetTooltip(str)
#pragma warning(disable: 26812 26815)

inline DWORD windowFlags = ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoSavedSettings;

namespace Overlay
{
	void Loop();
}

namespace Render
{
	void Start();

	void End();

	void Text(ImVec2 pos, float fontsize, ImColor color, const char* text_begin, const char* text_end, float wrap_width, const ImVec4* cpu_fine_clip_rect);

	void RectFilled(float x0, float y0, float x1, float y1, ImColor color, float rounding, int rounding_corners_flags);

	void RectFilled2(float x, float y, float w, float h, ImColor color);

	void Line(ImVec2 a, ImVec2 b, ImColor color, float thickness);

	void DrawBoxBrackets(ImDrawList* list, float x, float y, float width, float height, ImColor color, float thickness);

	void EasyText(ImVec2 pos, ImColor color, const char* text, float fontSize);

	void EasyNumber(ImVec2 pos, ImColor color, int number, float fontSize);

	void DrawBox(ImColor color, float x, float y, float w, float h);

	void Circle(ImColor color, float fov);

	void HealthBar(float x, float y, float w, float h, int ehealth);

	void CustomHealthColor(float currentHealth, float maxHealth, ImColor* healthColor);

	float DrawOutlinedText(ImFont* pFont, const ImVec2& pos, float size, ImU32 color, bool center, const char* text, ...);
}

namespace Menu
{
	void RenderWatermark();

	void RenderMenu();
}

namespace ImGui
{
#pragma region GUI Setup Functions
	extern ImFont* Header;
	extern ImFont* Header2;
	extern ImFont* Body;
	extern ImFont* Body2;
	extern ImFont* FA;
	extern ImFont* FA2;
	extern ImColor BO3Orange;
	extern ImColor DarkGrey22;
	extern ImColor LightGrey26;
	extern ImColor White;
	extern ImVec4 active;
	extern ImVec4 inactive;

	void RenderLogo();

	void SCP(float xPos, float yPos);

	void SCPX(float xPos);

	void SCPY(float yPos);

	void Line(int newId);

	void CenterText(const char* text, int lineId, BOOL separator, BOOL newLine);

	void TextNL(const char* text, BOOL newLine);

	void TextSL(const char* text, BOOL sameLine, BOOL newLine);

	void TextSCP(const char* text, float xPos, float yPos);

	void TextColor(const char* text, ImVec4 color, int lineId, BOOL seperator, BOOL newLine);

	void ButtonNL(const char* featureName, bool* featureBool, ImVec2 size, BOOL newLine);

	void ButtonSCP(const char* featureName, bool* featureBool, float xPos, float yPos, ImVec2 size, BOOL newLine);

	void ButtonIntSCP(const char* featureName, int* featureInt, int value, float xPos, float yPos, ImVec2 size, BOOL newLine);

	void ButtonPageSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine);

	void ButtonWindowSCP(const char* label, int* page, int pageNumber, ImVec2 pos, ImVec2 size, BOOL newLine);

	void InputIntNL(const char* featureName, int* featureInt, bool* featureBool, float size, BOOL sameLine, BOOL newLine);

	void InputFloatNL(const char* featureName, float* featureFloat, float minValue, float maxValue, float size, BOOL sameLine, BOOL newLine);

	void ColorEditFeature(const char* featureName, float* colorEditFloat, BOOL newLine);

	void WeaponCycleComboBox(const char* featureName, float size, BOOL newLine);

	void ZombieTPComboBox(const char* featureName, float size, BOOL newLine);

	void AimbotKeyComboBox(const char* featureName, float size, BOOL newLine);

	void ToggleNL(const char* toggleName, bool* featureBool, BOOL newLine);

	float GetX();

	float GetY();

	void SetCreationTime();

	bool IsExpired();

	void SetNotifyMessage(const char* text);

	void ResetNotifyMessage();

	void FadeNotifyMessage();

	void RenderNotifyMessage(const char* text);

	void RenderNotifyWindow(ImVec2 pos, ImVec2 size);

	void SetupConfigIcon();

	void SetupDoubleButtonFeatures(const char* featureName1, const char* featureName2, bool* featureBool1, bool* featureBoolLoaded, bool* featureBool2, BOOL newLine);

	void SetupLoadedConfigText();

	void SetupConfigSaveSettings();

	void SetGUITheme();
#pragma endregion

#pragma region Main GUI Render Function
	void RenderGUI();
#pragma endregion
}