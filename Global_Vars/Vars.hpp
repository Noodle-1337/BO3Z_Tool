#pragma once
#include "../Includes/Includes.hpp"

namespace UI
{
	extern bool bShowMenu;
	extern bool bShowWatermark;
	extern HWND hWnd;
	extern int iLogoWidth;
	extern int iLogoHeight;
	extern int iScreenWidth;
	extern int iScreenHeight;
	extern int iGuiX;
	extern int iGuiY;
	extern int iTab;
	extern int iExploitPage;
	extern int iPlayer1ExploitPage;
}

namespace Game
{
	extern uintptr_t moduleBase;
	extern HWND hWnd;
	extern DWORD procID;
	extern HANDLE hProc;
	extern int bSetAddress;
}

namespace FeatureSettings
{
	extern bool bTrueState;
	extern bool bFalseState;
	extern bool bDisableAllFeatures;
	extern bool bIsInGame;
	extern int iP1PointsValue;
	extern int iP2PointsValue;
	extern int iP3PointsValue;
	extern int iP4PointsValue;
	extern int iP1RunValue;
	extern int iP2RunValue;
	extern int iP3RunValue;
	extern int iP4RunValue;
	extern int iP1WCValue;
	extern int iP2WCValue;
	extern int iP3WCValue;
	extern int iP4WCValue;
	extern int iJumpHeightValue;
#pragma region Player 1 Bools
	extern bool bP1InfiniteHealth;
	extern bool bP1InfiniteClipAmmo;
	extern bool bP1InfiniteStockAmmo;
	extern bool bP1RapidFire;
	extern bool bP1InfinitePoints;
	extern bool bP1DynamicPoints;
	extern bool bP1AlwaysInstaKill;
	extern bool bP1JumpHeight;
	extern bool bP1RunSpeed;
	extern bool bP1Speed;
	extern bool bZombieTP;
	extern bool bExtraZombiesTP;
	extern bool bTPAllZombies;
	extern bool bNewZombieLocation;
	extern bool bP1WCycle;
	extern bool bP1WCycleKey;
	extern bool bP1Name;
#pragma endregion	
#pragma region Player 2 Bools
	extern bool bP2InfiniteHealth;
	extern bool bP2InfiniteAmmo;
	extern bool bP2InfiniteClipAmmo;
	extern bool bP2InfiniteStockAmmo;
	extern bool bP2InfinitePoints;
	extern bool bP2DynamicPoints;
	extern bool bP2RapidFire;
	extern bool bP2JumpHeight;
	extern bool bP2RunSpeed;
	extern float p2RunSpeedvalue;
	extern bool bP2WCycle;
#pragma endregion
#pragma region Player 3 Bools
	extern bool bP3InfiniteHealth;
	extern bool bP3InfiniteAmmo;
	extern bool bP3InfiniteClipAmmo;
	extern bool bP3InfiniteStockAmmo;
	extern bool bP3InfinitePoints;
	extern bool bP3DynamicPoints;
	extern bool bP3RapidFire;
	extern bool bP3JumpHeight;
	extern bool bP3RunSpeed;
	extern float p3RunSpeedvalue;
	extern bool bP3WCycle;
#pragma endregion
#pragma region Player 4 Bools
	extern bool bP4InfiniteHealth;
	extern bool bP4InfiniteAmmo;
	extern bool bP4InfiniteClipAmmo;
	extern bool bP4InfiniteStockAmmo;
	extern bool bP4InfinitePoints;
	extern bool bP4DynamicPoints;
	extern bool bP4RapidFire;
	extern bool bP4JumpHeight;
	extern bool bP4RunSpeed;
	extern float p4RunSpeedvalue;
	extern bool bP4WCycle;
#pragma endregion
#pragma region Extra Goodies Bools
	extern bool bJetPack;
	extern bool bAimbot;
	extern bool bZombieCount;
	extern bool bNoRecoilOn;
	extern bool bNoRecoilOff;
	extern bool bNoSpreadOn;
	extern bool bNoGunJitter;
#pragma endregion
}

namespace AimSettings
{
	extern float fCurrentDist;
	extern float fClosestDist;
	extern float fCacheDist[24];
	extern float fFov;
	extern int iBestTarget;
	extern int iCheckTarget;
	extern vec2_t vScreen;
	extern vec2_t vHead;
	//
	extern float fFovLimit;
	extern float fAimSmooth;
	extern int iAimKey;
}

namespace MiscSettings
{
	extern bool bCrosshair;
	extern bool bPlayerFov;
	extern float fPlayerFovSize;
	extern int iZombieTPKey;
}

namespace VisualSettings
{
	extern bool bRecoilText;
	extern bool bZombieSnaplines;
	extern bool bZombieSnaplinesTop;
	extern bool bZombieSnaplinesMid;
	extern bool bZombieSnaplinesBottom;
	extern int iZombieSnaplinePos;
	extern bool bZombie2DBox;
	extern bool bZombie2DBrackets;
	extern bool bZombieBoxFilled;
	extern bool bZombieHealthBar;
	extern bool bZombieDistance;
	extern bool bZombie2DBracketsRainbow;
	extern bool bZombie2DBoxesRainbow;
	extern bool bZombieSnaplinesRainbow;
	extern bool bZombieDistanceRainbow;
	extern bool bZombieCrosshairRainbow;
	extern bool bZombieFovRainbow;
	extern float fBoxColor[4];
	extern float fBracketBoxColor[4];
	extern float fBoxFilledColor[4];
	extern float fSnaplineColor[4];
	extern float fDistanceColor[4];
	extern float fHealthTextColor[4];
	extern float fCrosshairColor[4];
	extern float fFovColor[4];
	extern float fZombieCounterColor[4];
	extern float fZombieCounterValueColor[4];
	//
	extern ImVec4 whiteText;
	extern ImVec4 blackText;
	extern ImColor boxImColor;
	extern ImColor bracketBoxImColor;
	extern ImColor boxFilledImColor;
	extern ImColor snaplineImColor;
	extern ImColor distanceImColor;
	extern ImColor healthTextImColor;
	extern ImColor healthBarImColor;
	extern ImColor crosshairImColor;
	extern ImColor fovImColor;
	extern ImColor zombieCounterImColor;
	extern ImColor zombieCounterValueImColor;
}

namespace ConfigSettings
{
	// Config Names.
	extern const char* items[5];
	// Load & Save Bools.
	extern bool bLoadConfig1;
	extern bool bLoadConfig2;
	extern bool bLoadConfig3;
	extern bool bLoadConfig4;
	extern bool bLoadConfig5;
	extern bool bLoadedConfig;
	extern bool bLoadedConfig1;
	extern bool bLoadedConfig2;
	extern bool bLoadedConfig3;
	extern bool bLoadedConfig4;
	extern bool bLoadedConfig5;
	extern bool bLoadedConfigNotify1;
	extern bool bLoadedConfigNotify2;
	extern bool bLoadedConfigNotify3;
	extern bool bLoadedConfigNotify4;
	extern bool bLoadedConfigNotify5;
	extern bool bSaveConfig1;
	extern bool bSaveConfig2;
	extern bool bSaveConfig3;
	extern bool bSaveConfig4;
	extern bool bSaveConfig5;
	extern bool bSavedConfig1;
	extern bool bSavedConfig2;
	extern bool bSavedConfig3;
	extern bool bSavedConfig4;
	extern bool bSavedConfig5;
	extern bool bSavedConfigNotify1;
	extern bool bSavedConfigNotify2;
	extern bool bSavedConfigNotify3;
	extern bool bSavedConfigNotify4;
	extern bool bSavedConfigNotify5;
	extern int iTrackConfigLoaded;
	//
	extern ULONGLONG iElapsedTime;
	extern ULONGLONG iCreationTime;
	extern ULONGLONG iDissmisTime;
	extern float fFadePercentage;
	extern int iNotifyX;
	extern int iNotifyY;
	extern bool bNotifyMssg;
	extern std::string sNotifyMssg;
}

namespace GameValues
{
	// Player Feature Values
	extern int iPlayer1GodModeDefaultValue;
	extern int iPlayer1GodModeCurrentValue;
	extern int iPlayer2GodModeDefaultValue;
	extern int iPlayer2GodModeCurrentValue;
	extern int iPlayer3GodModeDefaultValue;
	extern int iPlayer3GodModeCurrentValue;
	extern int iPlayer4GodModeDefaultValue;
	extern int iPlayer4GodModeCurrentValue;
	extern int iPlayerGodModeOn;
	extern int iPlayerGodModeOff;
	extern std::byte iPlayerNoRecoilOn;
	extern std::byte iPlayerNoRecoilOff;
	extern std::byte noRecoilValue;
	extern int iPlayerHealthValue;
	extern int iPlayerNewAmmoValue;
	extern int iPlayerNewPointsValue;
	extern int iPlayer1NewCustomPointsValue;
	extern int iPlayer2NewCustomPointsValue;
	extern int iPlayer3NewCustomPointsValue;
	extern int iPlayer4NewCustomPointsValue;
	extern int iPlayer1CurrentPointsValue;
	extern int iPlayer2CurrentPointsValue;
	extern int iPlayer3CurrentPointsValue;
	extern int iPlayer4CurrentPointsValue;
	extern int iPlayerNewRecoilValue;
	extern int iPlayerNewRapidFireValue;
	extern int iPlayer1NewWeaponValue;
	extern int iPlayer2NewWeaponValue;
	extern int iPlayer3NewWeaponValue;
	extern int iPlayer4NewWeaponValue;
	extern int iPlayerNoSpreadValue;
	extern float fPlayer1NewRunSpeedValue;
	extern float fPlayer2NewRunSpeedValue;
	extern float fPlayer3NewRunSpeedValue;
	extern float fPlayer4NewRunSpeedValue;
	extern float fPlayerDefaultRunSpeedValue;
	extern int iPlayerStanceValue;
	extern float fCurrentPlayerCoordsX;
	extern float fCurrentPlayerCoordsY;
	extern float fCurrentPlayerCoordsZ;
	extern vec3_t currentPlayerCoords;
	extern vec3_t currentPlayerCoordsTeleport;
	extern float fCurrentPlayerCoordsTeleportX;
	extern float fCurrentPlayerCoordsTeleportY;
	extern float fCurrentPlayerCoordsTeleportZ;
	extern float fCurrentPlayerViewAngleX;
	extern float fCurrentPlayerViewAngleY;
	extern float fCurrentPlayerViewAngleZ;
	extern float fPlayerDistance;
	extern int iPlayer1Index;
	extern int iPlayer2Index;
	extern int iPlayer3Index;
	extern int iPlayer4Index;
	//Vec3 currentPlayerViewAngleXYZ;
	// Zombie Feature Values
	extern int iZombieCurrentHealthValue;
	extern int iZombieInstaKillCurrentHealthValue;
	extern int iZombieMaxHealthValue;
	extern int iZombieNewHealthValue;
	extern int iZombieValidValue;
	extern int iZombieNewCriticalValue;
	extern int iZombieCountValue;
	extern float fCurrentZombiesCoordsX;
	extern float fCurrentZombiesCoordsY;
	extern float fCurrentZombiesCoordsZ;
	extern float fCurrentZombiesCoordsHeadX;
	extern float fCurrentZombiesCoordsHeadY;
	extern float fCurrentZombiesCoordsHeadZ;
	extern vec3_t currentZombieCoords;
	extern vec3_t currentZombieHeadCoords;
	extern float fZombieDistance;
	extern float fClosestZombie;
	extern uintptr_t zombieTarget;
	// Global Game Feature Values
	extern int iInGameValue;
	extern float fGlobalNewJumpHeightValue;
	extern float fGlobalDefaultJumpHeightValue;
	extern float fGlobalJetPackValue;
	extern float fGlobalJetPackAddValue;
}

namespace Offsets
{
#pragma region Player Vars
	extern DWORD viewMatrix;
	extern uintptr_t playerBasePtr;
	extern uintptr_t playerPedPtr;
	extern uintptr_t playerNoRecoilPtr;
	extern uintptr_t playerNoRecoilBase;
	extern uintptr_t playerNoSpreadBase;
	extern uintptr_t playerBase;
	extern uintptr_t playerBaseAddr;
	extern uintptr_t playerPedBase;
	extern uintptr_t playerPedBaseAddr;
	extern uintptr_t playerPedBaseAddrCache;
	extern uintptr_t playerPedHealthAddr;
	extern uintptr_t playerPedHealthMaxAddr;
	extern uintptr_t playerCoordAddr;
	extern uintptr_t playerXCoordAddr;
	extern uintptr_t playerYCoordAddr;
	extern uintptr_t playerZCoordAddr;
	extern uintptr_t playerArraySizeOffset;
	extern uintptr_t playerWeaponArraySizeOffset;
	extern uintptr_t playerArray;
	extern uintptr_t playerWeaponArray;
	extern std::vector <unsigned int> playerNameOffset;
	extern std::vector <unsigned int> playerGodModeOffset;
	extern std::vector <unsigned int> playerNormalHealthOffset;
	extern std::vector <unsigned int> playerClipAmmoOffset;
	extern std::vector <unsigned int> playerStockAmmoOffset;
	extern std::vector <unsigned int> playerRapidFireOffset;
	extern std::vector <unsigned int> playerRapidFireOffset2;
	extern std::vector <unsigned int> playerNoSpreadOffset;
	extern std::vector <unsigned int> playerNoRecoilOffset;
	extern std::vector <unsigned int> playerPointsOffset;
	extern std::vector <unsigned int> playerRunSpeedOffset;
	extern std::vector <unsigned int> playerStanceOffset;
	extern std::vector <unsigned int> playerLocationOffset;
	extern std::vector <unsigned int> playerSetWeaponOffset;
	extern std::vector <unsigned int> gameSkipRounds;
	extern std::vector <unsigned int> playerKillsOffset;
	extern std::vector <unsigned int> playerCoordOffset;
	extern std::vector <unsigned int> playerXCoord;
	extern std::vector <unsigned int> playerYCoord;
	extern std::vector <unsigned int> playerZCoord;
	extern std::vector <unsigned int> playerXView;
	extern std::vector <unsigned int> playerYView;
	extern std::vector <unsigned int> playerZView;
#pragma endregion

#pragma region Zombie Vars
	extern uintptr_t zombieBasePtr;
	extern uintptr_t zombieBase;
	extern uintptr_t zombieBaseAddr;
	extern uintptr_t zombieCountPtr;
	extern uintptr_t zombieCountBase;
	extern uintptr_t zombieCountBaseAddr;
	extern uintptr_t zombiesCoordAddr;
	extern uintptr_t zombiesXCoordAddr;
	extern uintptr_t zombiesYCoordAddr;
	extern uintptr_t zombiesZCoordAddr;
	extern uintptr_t zombiesHeadCoordAddr;
	extern uintptr_t zombiesHeadXCoordAddr;
	extern uintptr_t zombiesHeadYCoordAddr;
	extern uintptr_t zombiesHeadZCoordAddr;
	extern uintptr_t zombiesValidAddr;
	extern uintptr_t zombieArraySize;
	extern uintptr_t zombieNextEntitiyOffset;
	extern std::vector <unsigned int> zombieHealthOffset;
	extern std::vector <unsigned int> zombieHealthMaxOffset;
	extern std::vector <unsigned int> zombieValidOffset;
	extern std::vector <unsigned int> zombieCoord;
	extern std::vector <unsigned int> zombieXCoord;
	extern std::vector <unsigned int> zombieYCoord;
	extern std::vector <unsigned int> zombieZCoord;
	extern std::vector <unsigned int> zombieHeadCoord;
	extern std::vector <unsigned int> zombieHeadXCoord;
	extern std::vector <unsigned int> zombieHeadYCoord;
	extern std::vector <unsigned int> zombieHeadZCoord;
	extern std::vector <unsigned int> zombieHeadXYZCoord;
#pragma endregion

#pragma region Global Lobby Vars
	extern uintptr_t inGamePtr;
	extern uintptr_t inGameAddr;
	extern uintptr_t jumpHeightPtr;
	extern uintptr_t jumpHeightBase;
#pragma endregion
}