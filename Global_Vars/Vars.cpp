#include "Vars.hpp"

namespace UI
{
	bool bShowMenu = true;
	bool bShowWatermark = true;
	HWND hWnd = NULL;
	int iLogoWidth = 128;
	int iLogoHeight = 92;
	int iScreenWidth = 0;
	int iScreenHeight = 0;
	int iGuiX = 0;
	int iGuiY = 0;
	int iTab = 0;
	int iExploitPage = 1;
	int iPlayer1ExploitPage = 1;
}

namespace Game
{
	uintptr_t moduleBase = NULL;
	HWND hWnd = NULL;
	DWORD procID = NULL;
	HANDLE hProc = NULL;
	int bSetAddress = 0;
}

namespace FeatureSettings
{
	bool bTrueState = true;
	bool bFalseState = false;
	bool bDisableAllFeatures = false;
	bool bIsInGame = false;
	int iP1PointsValue = 0;
	int iP2PointsValue = 0;
	int iP3PointsValue = 0;
	int iP4PointsValue = 0;
	int iP1RunValue = 1;
	int iP2RunValue = 1;
	int iP3RunValue = 1;
	int iP4RunValue = 1;
	int iP1WCValue = 0;
	int iP2WCValue = 0;
	int iP3WCValue = 0;
	int iP4WCValue = 0;
	int iJumpHeightValue = 39;
#pragma region Player 1 Bools
	bool bP1InfiniteHealth = false;
	bool bP1InfiniteClipAmmo = false;
	bool bP1InfiniteStockAmmo = false;
	bool bP1RapidFire = false;
	bool bP1InfinitePoints = false;
	bool bP1DynamicPoints = false;
	bool bP1AlwaysInstaKill = false;
	bool bP1JumpHeight = false;
	bool bP1RunSpeed = false;
	bool bP1Speed = false;
	bool bZombieTP = false;
	bool bExtraZombiesTP = false;
	bool bTPAllZombies = false;
	bool bNewZombieLocation = false;
	bool bP1WCycle = false;
	bool bP1WCycleKey = false;
	bool bP1Name = false;
#pragma endregion	
#pragma region Player 2 Bools
	bool bP2InfiniteHealth = false;
	bool bP2InfiniteAmmo = false;
	bool bP2InfiniteClipAmmo = false;
	bool bP2InfiniteStockAmmo = false;
	bool bP2InfinitePoints = false;
	bool bP2DynamicPoints = false;
	bool bP2RapidFire = false;
	bool bP2JumpHeight = false;
	bool bP2RunSpeed = false;
	float p2RunSpeedvalue = 1.f;
	bool bP2WCycle = false;
#pragma endregion
#pragma region Player 3 Bools
	bool bP3InfiniteHealth = false;
	bool bP3InfiniteAmmo = false;
	bool bP3InfiniteClipAmmo = false;
	bool bP3InfiniteStockAmmo = false;
	bool bP3InfinitePoints = false;
	bool bP3DynamicPoints = false;
	bool bP3RapidFire = false;
	bool bP3JumpHeight = false;
	bool bP3RunSpeed = false;
	float p3RunSpeedvalue = 1.f;
	bool bP3WCycle = false;
#pragma endregion
#pragma region Player 4 Bools
	bool bP4InfiniteHealth = false;
	bool bP4InfiniteAmmo = false;
	bool bP4InfiniteClipAmmo = false;
	bool bP4InfiniteStockAmmo = false;
	bool bP4InfinitePoints = false;
	bool bP4DynamicPoints = false;
	bool bP4RapidFire = false;
	bool bP4JumpHeight = false;
	bool bP4RunSpeed = false;
	float p4RunSpeedvalue = 1.f;
	bool bP4WCycle = false;
#pragma endregion
#pragma region Extra Goodies Bools
	bool bJetPack = false;
	bool bAimbot = true;
	bool bZombieCount = false;
	bool bNoRecoilOn = false;
	bool bNoRecoilOff = false;
	bool bNoSpreadOn = false;
	bool bNoGunJitter = false;
#pragma endregion
}

namespace AimSettings
{
	float fCurrentDist = NULL;
	float fClosestDist = FLT_MAX;
	float fCacheDist[24] = { };
	float fFov = NULL;
	int iBestTarget = -1;
	int iCheckTarget = NULL;
	vec2_t vScreen = { 0, 0 };
	vec2_t vHead = { 0, 0 };
	//
	float fFovLimit = 0;
	float fAimSmooth = 1.5f;
	int iAimKey = 0x0;
}

namespace MiscSettings
{
	bool bCrosshair = true;
	bool bPlayerFov = false;
	float fPlayerFovSize = 300.f;
	int iZombieTPKey = 0x0;
}

namespace VisualSettings
{
	bool bRecoilText = false;
	bool bZombieSnaplines = false;
	bool bZombieSnaplinesTop = false;
	bool bZombieSnaplinesMid = false;
	bool bZombieSnaplinesBottom = false;
	int iZombieSnaplinePos = 1;
	bool bZombie2DBox = false;
	bool bZombie2DBrackets = true;
	bool bZombieBoxFilled = true;
	bool bZombieHealthBar = true;
	bool bZombieDistance = true;
	bool bZombie2DBracketsRainbow = false;
	bool bZombie2DBoxesRainbow = false;
	bool bZombieSnaplinesRainbow = false;
	bool bZombieDistanceRainbow = false;
	bool bZombieCrosshairRainbow = false;
	bool bZombieFovRainbow = false;
	float fBoxColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fBracketBoxColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fBoxFilledColor[4] = { 0.f, 0.f, 0.f, 0.18f };
	float fSnaplineColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fDistanceColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fHealthTextColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fCrosshairColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fFovColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fZombieCounterColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	float fZombieCounterValueColor[4] = { 1.f, 0.5f, 0.15f, 1.f };
	//
	ImVec4 whiteText = ImVec4(255.f / 255.f, 255.f / 255.f, 255.f / 255.f, 1.0f);
	ImVec4 blackText = ImVec4(0.f / 255.f, 0.f / 255.f, 0.f / 255.f, 1.0f);
	ImColor boxImColor = ImColor(fBoxColor[0], fBoxColor[1], fBoxColor[2]);
	ImColor bracketBoxImColor = ImColor(fBracketBoxColor[0], fBracketBoxColor[1], fBracketBoxColor[2]);
	ImColor boxFilledImColor = ImColor(fBoxFilledColor[0], fBoxFilledColor[1], fBoxFilledColor[2], fBoxFilledColor[3]);
	ImColor snaplineImColor = ImColor(fSnaplineColor[0], fSnaplineColor[1], fSnaplineColor[2]);
	ImColor distanceImColor = ImColor(fDistanceColor[0], fDistanceColor[1], fDistanceColor[2]);
	ImColor healthTextImColor = ImColor(fHealthTextColor[0], fHealthTextColor[1], fHealthTextColor[2]);
	ImColor healthBarImColor;
	ImColor crosshairImColor = ImColor(fCrosshairColor[0], fCrosshairColor[1], fCrosshairColor[2]);
	ImColor fovImColor = ImColor(fFovColor[0], fFovColor[1], fFovColor[2]);
	ImColor zombieCounterImColor = ImColor(fZombieCounterColor[0], fZombieCounterColor[1], fZombieCounterColor[2]);
	ImColor zombieCounterValueImColor = ImColor(fZombieCounterValueColor[0], fZombieCounterValueColor[1], fZombieCounterValueColor[2]);
}

namespace ConfigSettings
{
	// Config Names.
	const char* items[5] = { " Config 1", " Config 2", " Config 3", " Config 4", " Config 5" };
	// Load & Save Bools.
	bool bLoadConfig1 = false;
	bool bLoadConfig2 = false;
	bool bLoadConfig3 = false;
	bool bLoadConfig4 = false;
	bool bLoadConfig5 = false;
	bool bLoadedConfig = false;
	bool bLoadedConfig1 = false;
	bool bLoadedConfig2 = false;
	bool bLoadedConfig3 = false;
	bool bLoadedConfig4 = false;
	bool bLoadedConfig5 = false;
	bool bLoadedConfigNotify1 = false;
	bool bLoadedConfigNotify2 = false;
	bool bLoadedConfigNotify3 = false;
	bool bLoadedConfigNotify4 = false;
	bool bLoadedConfigNotify5 = false;
	bool bSaveConfig1 = false;
	bool bSaveConfig2 = false;
	bool bSaveConfig3 = false;
	bool bSaveConfig4 = false;
	bool bSaveConfig5 = false;
	bool bSavedConfig1 = false;
	bool bSavedConfig2 = false;
	bool bSavedConfig3 = false;
	bool bSavedConfig4 = false;
	bool bSavedConfig5 = false;
	bool bSavedConfigNotify1 = false;
	bool bSavedConfigNotify2 = false;
	bool bSavedConfigNotify3 = false;
	bool bSavedConfigNotify4 = false;
	bool bSavedConfigNotify5 = false;
	int iTrackConfigLoaded = 1337;
	//
	ULONGLONG iElapsedTime = 0;
	ULONGLONG iCreationTime = 0;
	ULONGLONG iDissmisTime = 3000;
	float fFadePercentage = 0.f;
	int iNotifyX = 0;
	int iNotifyY = 0;
	bool bNotifyMssg = false;
	std::string sNotifyMssg = "";
}

namespace GameValues
{
	// Player Feature Values
	int iPlayer1GodModeDefaultValue = 0;
	int iPlayer1GodModeCurrentValue = 0;
	int iPlayer2GodModeDefaultValue = 0;
	int iPlayer2GodModeCurrentValue = 0;
	int iPlayer3GodModeDefaultValue = 0;
	int iPlayer3GodModeCurrentValue = 0;
	int iPlayer4GodModeDefaultValue = 0;
	int iPlayer4GodModeCurrentValue = 0;
	int iPlayerGodModeOn = 12297;
	int iPlayerGodModeOff = 12296;
	std::byte iPlayerNoRecoilOn = std::byte(0x75);
	std::byte iPlayerNoRecoilOff = std::byte(0x74);
	std::byte noRecoilValue = std::byte(0);
	int iPlayerHealthValue = 0;
	int iPlayerNewAmmoValue = 255;
	int iPlayerNewPointsValue = 100000;
	int iPlayer1NewCustomPointsValue = 0;
	int iPlayer2NewCustomPointsValue = 0;
	int iPlayer3NewCustomPointsValue = 0;
	int iPlayer4NewCustomPointsValue = 0;
	int iPlayer1CurrentPointsValue = 0;
	int iPlayer2CurrentPointsValue = 0;
	int iPlayer3CurrentPointsValue = 0;
	int iPlayer4CurrentPointsValue = 0;
	int iPlayerNewRecoilValue = 0;
	int iPlayerNewRapidFireValue = 0;
	int iPlayer1NewWeaponValue = 0;
	int iPlayer2NewWeaponValue = 0;
	int iPlayer3NewWeaponValue = 0;
	int iPlayer4NewWeaponValue = 0;
	int iPlayerNoSpreadValue = 0;
	float fPlayer1NewRunSpeedValue = 1.f;
	float fPlayer2NewRunSpeedValue = 1.f;
	float fPlayer3NewRunSpeedValue = 1.f;
	float fPlayer4NewRunSpeedValue = 1.f;
	float fPlayerDefaultRunSpeedValue = 1.f;
	int iPlayerStanceValue = 0;
	float fCurrentPlayerCoordsX = 0;
	float fCurrentPlayerCoordsY = 0;
	float fCurrentPlayerCoordsZ = 0;
	vec3_t currentPlayerCoords = { 0, 0, 0 };
	vec3_t currentPlayerCoordsTeleport = { 0, 0, 0 };
	float fCurrentPlayerCoordsTeleportX = 0;
	float fCurrentPlayerCoordsTeleportY = 0;
	float fCurrentPlayerCoordsTeleportZ = 0;
	float fCurrentPlayerViewAngleX = 0;
	float fCurrentPlayerViewAngleY = 0;
	float fCurrentPlayerViewAngleZ = 0;
	float fPlayerDistance = 0;
	int iPlayer1Index = 0;
	int iPlayer2Index = 1;
	int iPlayer3Index = 2;
	int iPlayer4Index = 3;
	//Vec3 currentPlayerViewAngleXYZ;
	// Zombie Feature Values
	int iZombieCurrentHealthValue = 0;
	int iZombieInstaKillCurrentHealthValue = 0;
	int iZombieMaxHealthValue = 0;
	int iZombieNewHealthValue = 1;
	int iZombieNewCriticalValue = -1;
	int iZombieCountValue = 0;
	float fCurrentZombiesCoordsX = 0;
	float fCurrentZombiesCoordsY = 0;
	float fCurrentZombiesCoordsZ = 0;
	float fCurrentZombiesCoordsHeadX = 0;
	float fCurrentZombiesCoordsHeadY = 0;
	float fCurrentZombiesCoordsHeadZ = 0;
	vec3_t currentZombieCoords = { 0, 0, 0 };
	vec3_t currentZombieHeadCoords = { 0, 0, 0 };
	float fZombieDistance = 0;
	float fClosestZombie = 0;
	uintptr_t zombieTarget = 0;
	// Global Game Feature Values
	int iInGameValue = 0;
	float fGlobalNewJumpHeightValue = 39.f;
	float fGlobalDefaultJumpHeightValue = 39.f;
	float fGlobalJetPackValue = 0;
	float fGlobalJetPackAddValue = 8.f;
}

namespace Offsets
{
#pragma region Player Vars
	DWORD viewMatrix = 0x36752A0;
	uintptr_t playerBasePtr = 0xA549DE0;
	uintptr_t playerPedPtr = 0xA549DE8;
	uintptr_t playerNoRecoilPtr = 0x11BD903; // \x84\xc0\x74\x00\x32\xc0\xe9\x00\x00\x00\x00\x48\x83\xc4 xxx?xxx????xxx // 84 c0 74 ? 32 c0 e9 ? ? ? ? 48 83 c4
	uintptr_t playerNoRecoilBase = 0;
	uintptr_t playerNoSpreadBase = 0;
	uintptr_t playerBase = 0;
	uintptr_t playerBaseAddr = 0;
	uintptr_t playerPedBase = 0;
	uintptr_t playerPedBaseAddr = 0;
	uintptr_t playerPedBaseAddrCache = 0;
	uintptr_t playerPedHealthAddr = 0;
	uintptr_t playerPedHealthMaxAddr = 0;
	uintptr_t playerCoordAddr = 0;
	uintptr_t playerXCoordAddr = 0;
	uintptr_t playerYCoordAddr = 0;
	uintptr_t playerZCoordAddr = 0;
	uintptr_t playerArraySizeOffset = { 0x171F0 }; // New
	uintptr_t playerWeaponArraySizeOffset = { 0x40 };
	uintptr_t playerArray = { 0x4 };
	uintptr_t playerWeaponArray = { 0x8 };
	std::vector <unsigned int> playerNameOffset = { 0x6060 };
	std::vector <unsigned int> playerGodModeOffset = { 0x2A8 }; // New
	std::vector <unsigned int> playerNormalHealthOffset = { 0x16F28 }; // New
	std::vector <unsigned int> playerClipAmmoOffset = { 0x684 }; // New
	std::vector <unsigned int> playerStockAmmoOffset = { 0x648 }; // New
	std::vector <unsigned int> playerRapidFireOffset = { 0x54 }; // New
	std::vector <unsigned int> playerRapidFireOffset2 = { 0xE80 };
	std::vector <unsigned int> playerNoSpreadOffset = { 0xB78 }; // New
	std::vector <unsigned int> playerNoRecoilOffset = { 0x12F8 }; // 66 41 89 80 ? ? ? ? f3 c3 90 84 0f
	std::vector <unsigned int> playerPointsOffset = { 0x16E84 }; // New
	std::vector <unsigned int> playerRunSpeedOffset = { 0x16BEC }; // New
	std::vector <unsigned int> playerStanceOffset = { 0x334 }; // New
	std::vector <unsigned int> playerLocationOffset = { 0xDE8 };
	std::vector <unsigned int> playerSetWeaponOffset = { 0x378 };
	std::vector <unsigned int> gameSkipRounds = { 0x333D8 };
	std::vector <unsigned int> playerKillsOffset = { 0x5D28 };
	std::vector <unsigned int> playerCoordOffset = { 0x30 };
	std::vector <unsigned int> playerXCoord = { 0x30 };
	std::vector <unsigned int> playerYCoord = { 0x34 };
	std::vector <unsigned int> playerZCoord = { 0x38 };
	std::vector <unsigned int> playerXView = { 0xD0 };
	std::vector <unsigned int> playerYView = { 0xD4 };
	std::vector <unsigned int> playerZView = { 0xD8 };
#pragma endregion

#pragma region Zombie Vars
	uintptr_t zombieBasePtr = 0xA549E48; // New
	uintptr_t zombieBase = 0;
	uintptr_t zombieBaseAddr = 0;
	uintptr_t zombieCountPtr = 0x0A3D3A2C; // New
	uintptr_t zombieCountBase = 0;
	uintptr_t zombieCountBaseAddr = 0;
	uintptr_t zombiesCoordAddr = 0;
	uintptr_t zombiesXCoordAddr = 0;
	uintptr_t zombiesYCoordAddr = 0;
	uintptr_t zombiesZCoordAddr = 0;
	uintptr_t zombiesHeadCoordAddr = 0;
	uintptr_t zombiesHeadXCoordAddr = 0;
	uintptr_t zombiesHeadYCoordAddr = 0;
	uintptr_t zombiesHeadZCoordAddr = 0;
	uintptr_t zombieArraySize = 0x4F8; // New
	uintptr_t zombieNextEntitiyOffset = 0x8;
	std::vector <unsigned int> zombieHealthOffset = { 0x8, 0x2C8 }; // New
	std::vector <unsigned int> zombieHealthMaxOffset = { 0x8, 0x2CC }; // New 
	std::vector <unsigned int> zombieCoord = { 0x8, 0x230 }; // New
	std::vector <unsigned int> zombieXCoord = { 0x8, 0x230 }; // New
	std::vector <unsigned int> zombieYCoord = { 0x8, 0x234 }; // New 
	std::vector <unsigned int> zombieZCoord = { 0x8, 0x238 }; // New
	std::vector <unsigned int> zombieHeadCoord = { 0x8, 0x224 }; // New
	std::vector <unsigned int> zombieHeadXCoord = { 0x8, 0x224 }; // New
	std::vector <unsigned int> zombieHeadYCoord = { 0x8, 0x228 }; // New
	std::vector <unsigned int> zombieHeadZCoord = { 0x8, 0x22C }; // New
	std::vector <unsigned int> zombieHeadXYZCoord = { 0x8, 0x224, 0x228, 0x22C }; // New
#pragma endregion

#pragma region Global Lobby Vars
	uintptr_t inGamePtr = 0x19C780BC;
	uintptr_t inGameAddr = 0;
	uintptr_t jumpHeightPtr = 0x30789C4;
	uintptr_t jumpHeightBase = 0;
#pragma endregion
}