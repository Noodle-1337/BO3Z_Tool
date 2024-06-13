#pragma once
#include "../Overlay/Overlay.hpp"
#include "../Extra_Headers/Display_Messages.hpp"
#include "../json/json.hpp"
#include "../fmt/format.hpp"

namespace Startup
{
	// Simple Random String Generator Function.
	std::string chars{ "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()`~-_=+[{]{|;:'\",<.>/?" };
	std::random_device rd;
	std::mt19937 generator(rd());
	std::string RandStr(DWORD length)
	{
		const DWORD char_size = (DWORD)chars.size();
		std::uniform_int_distribution<> random_int(0, char_size - 1);
		std::string output;
		for (DWORD i = 0; i < length; ++i)
			output.push_back(chars[random_int(generator)]);
		return output;
	}

	// Set Console App Title and Window Foreground Setting.
	void SetConsoleAppInfo()
	{
		//AllocConsole();
		//freopen("CONOUT$", "w", stdout);
		//freopen("CONIN$", "r", stdin);
		SetConsoleTitle(RandStr(12).c_str());
	}

	// Get Pid and Module Base.
	void GetGameInfo()
	{
		Game::procID = Utils::GetProcId("BlackOps3.exe");
		if (Game::procID < 1)
		{
			Notify::Popup("Load Black Ops 3 first!", "[ ERROR ]", MB_ICONWARNING | MB_DEFBUTTON2);
			exit(0);
		}
		else if (Game::procID > 1)
		{
			Game::hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Game::procID);
			Game::moduleBase = Utils::GetModuleBaseAddress(Game::procID, "BlackOps3.exe");
			Engine::entity.SetPlayerAddr();
			Engine::entity.SetZombieAddr();
		}
	}

	// Create our Separate Threads.
	void CreateThreads()
	{
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Overlay::Loop, 0 , 0, nullptr);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Engine::PlayerFeatures, 0, 0, nullptr);
	}
}

namespace ConfigSystem
{
	// Convert Color to String for Json.
	std::string ColorToString(ImColor color)
	{
		float colors[4];
		colors[0] = color.Value.x;
		colors[1] = color.Value.y;
		colors[2] = color.Value.z;
		colors[3] = color.Value.w;

		std::string format = fmt::format("X({}) Y({}) Z({}) W({})", colors[0], colors[1], colors[2], colors[3]);
		return format;
	}

	// Convert String to Color for Json.
	ImVec4 StringToColor(std::string color)
	{
		float x, y, z, w;
		sscanf_s(color.c_str(), "X(%f) Y(%f) Z(%f) W(%f)", &x, &y, &z, &w);

		return ImVec4(x, y, z, w);
	}

	// Validate Dir.
	void ValidatePath(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path))
		{
			std::filesystem::create_directory(path);
		}
		else if (!std::filesystem::is_directory(path))
		{
			std::filesystem::remove(path);
			std::filesystem::create_directory(path);
		}
	}

	// Get Current File Path Dir.
	std::filesystem::path GetCurrentFilePathDir()
	{
		std::filesystem::path filePath = std::filesystem::current_path();
		filePath /= "BO3Z_Tool_Config";
		ValidatePath(filePath);
		return filePath;
	}

	// Import Settongs from Config.
	void ImportFromJson(const nlohmann::json& j)
	{
		FeatureSettings::bP1InfiniteHealth = j["P1 Godmode"];
		FeatureSettings::bP1InfiniteClipAmmo = j["P1 Unlimited Clip"];
		FeatureSettings::bP1InfiniteStockAmmo = j["P1 Unlimited Stock"];
		FeatureSettings::bP1RapidFire = j["P1 Rapid Fire"];
		FeatureSettings::bNoRecoilOn = j["P1 No Recoil"];
		FeatureSettings::bP1RunSpeed = j["P1 Run Speed"];
		FeatureSettings::iP1RunValue = j["P1 Run Speed Value"];
		FeatureSettings::bP1JumpHeight = j["JumpHeight"];
		FeatureSettings::iJumpHeightValue = j["JumpHeight Value"];
		FeatureSettings::bZombieCount = j["Zombie Counter"];
		FeatureSettings::bP1AlwaysInstaKill = j["Zombie InstaKill"];
		FeatureSettings::bP2InfiniteHealth = j["P2 Godmode"];
		FeatureSettings::bP2InfiniteClipAmmo = j["P2 Unlimited Clip"];
		FeatureSettings::bP2InfiniteStockAmmo = j["P2 Unlimited Stock"];
		FeatureSettings::bP2RapidFire = j["P2 Rapid Fire"];
		FeatureSettings::bP2RunSpeed = j["P2 Run Speed"];
		FeatureSettings::iP2RunValue = j["P2 Run Speed Value"];
		FeatureSettings::bP3InfiniteHealth = j["P3 Godmode"];
		FeatureSettings::bP3InfiniteClipAmmo = j["P3 Unlimited Clip"];
		FeatureSettings::bP3InfiniteStockAmmo = j["P3 Unlimited Stock"];
		FeatureSettings::bP3RapidFire = j["P3 Rapid Fire"];
		FeatureSettings::bP3RunSpeed = j["P3 Run Speed"];
		FeatureSettings::iP3RunValue = j["P3 Run Speed Value"];
		FeatureSettings::bP4InfiniteHealth = j["P4 Godmode"];
		FeatureSettings::bP4InfiniteClipAmmo = j["P4 Unlimited Clip"];
		FeatureSettings::bP4InfiniteStockAmmo = j["P4 Unlimited Stock"];
		FeatureSettings::bP4RapidFire = j["P4 Rapid Fire"];
		FeatureSettings::bP4RunSpeed = j["P4 Run Speed"];
		FeatureSettings::iP4RunValue = j["P4 Run Speed Value"];
		UI::bShowWatermark = j["Draw Watermark"];
		FeatureSettings::bAimbot = j["Aimbot"];
		AimSettings::fAimSmooth = j["Aimbot Smooth"];
		MiscSettings::fPlayerFovSize = j["FOV Size"];
		VisualSettings::bZombie2DBox = j["2D Box"];
		VisualSettings::bZombie2DBrackets = j["2D Bracket"];
		VisualSettings::bZombieBoxFilled = j["Box Filled"];
		VisualSettings::bZombieSnaplines = j["Snapline"];
		VisualSettings::bZombieHealthBar = j["Health Bar"];
		VisualSettings::bZombieDistance = j["Distance"];
		MiscSettings::bCrosshair = j["Crosshair +"];
		MiscSettings::bPlayerFov = j["FOV Circle"];
		VisualSettings::boxImColor = StringToColor(j["2D Box Color"]);
		VisualSettings::bracketBoxImColor = StringToColor(j["2D Bracket Color"]);
		VisualSettings::boxFilledImColor = StringToColor(j["Box Filled Color"]);
		VisualSettings::snaplineImColor = StringToColor(j["Snapline Color"]);
		VisualSettings::healthTextImColor = StringToColor(j["Health Text Color"]);
		VisualSettings::distanceImColor = StringToColor(j["Distance Color"]);
		VisualSettings::crosshairImColor = StringToColor(j["Crosshair + Color"]);
		VisualSettings::fovImColor = StringToColor(j["FOV Circle Color"]);
	}

	// Write to json format.
	nlohmann::json ToJson()
	{
		return nlohmann::json{
			{ "P1 Godmode", FeatureSettings::bP1InfiniteHealth },
			{ "P1 Unlimited Clip", FeatureSettings::bP1InfiniteClipAmmo },
			{ "P1 Unlimited Stock", FeatureSettings::bP1InfiniteStockAmmo },
			{ "P1 Rapid Fire", FeatureSettings::bP1RapidFire },
			{ "P1 No Recoil", FeatureSettings::bNoRecoilOn },
			{ "P1 Run Speed", FeatureSettings::bP1RunSpeed },
			{ "P1 Run Speed Value", FeatureSettings::iP1RunValue },
			{ "JumpHeight", FeatureSettings::bP1JumpHeight },
			{ "JumpHeight Value", FeatureSettings::iJumpHeightValue },
			{ "Zombie Counter", FeatureSettings::bZombieCount },
			{ "Zombie InstaKill", FeatureSettings::bP1AlwaysInstaKill },
			{ "P2 Godmode", FeatureSettings::bP2InfiniteHealth },
			{ "P2 Unlimited Clip", FeatureSettings::bP2InfiniteClipAmmo },
			{ "P2 Unlimited Stock", FeatureSettings::bP2InfiniteStockAmmo },
			{ "P2 Rapid Fire", FeatureSettings::bP2RapidFire },
			{ "P2 Run Speed", FeatureSettings::bP2RunSpeed },
			{ "P2 Run Speed Value", FeatureSettings::iP2RunValue },
			{ "P3 Godmode", FeatureSettings::bP3InfiniteHealth },
			{ "P3 Unlimited Clip", FeatureSettings::bP3InfiniteClipAmmo },
			{ "P3 Unlimited Stock", FeatureSettings::bP3InfiniteStockAmmo },
			{ "P3 Rapid Fire", FeatureSettings::bP3RapidFire },
			{ "P3 Run Speed", FeatureSettings::bP3RunSpeed },
			{ "P3 Run Speed Value", FeatureSettings::iP3RunValue },
			{ "P4 Godmode", FeatureSettings::bP4InfiniteHealth },
			{ "P4 Unlimited Clip", FeatureSettings::bP4InfiniteClipAmmo },
			{ "P4 Unlimited Stock", FeatureSettings::bP4InfiniteStockAmmo },
			{ "P4 Rapid Fire", FeatureSettings::bP4RapidFire },
			{ "P4 Run Speed", FeatureSettings::bP4RunSpeed },
			{ "P4 Run Speed Value", FeatureSettings::iP4RunValue },
			{ "Draw Watermark", UI::bShowWatermark },
			{ "Aimbot", FeatureSettings::bAimbot },
			{ "Aimbot Smooth", AimSettings::fAimSmooth },
			{ "FOV Size", MiscSettings::fPlayerFovSize },
			{ "2D Box", VisualSettings::bZombie2DBox },
			{ "2D Bracket", VisualSettings::bZombie2DBrackets },
			{ "Box Filled", VisualSettings::bZombieBoxFilled },
			{ "Snapline", VisualSettings::bZombieSnaplines },
			{ "Health Bar", VisualSettings::bZombieHealthBar },
			{ "Distance", VisualSettings::bZombieDistance },
			{ "Crosshair +", MiscSettings::bCrosshair },
			{ "FOV Circle", MiscSettings::bPlayerFov },
			{ "2D Box Color", ColorToString(VisualSettings::boxImColor) },
			{ "2D Bracket Color", ColorToString(VisualSettings::bracketBoxImColor) },
			{ "Box Filled Color", ColorToString(VisualSettings::boxFilledImColor) },
			{ "Snapline Color", ColorToString(VisualSettings::snaplineImColor) },
			{ "Health Text Color", ColorToString(VisualSettings::healthTextImColor) },
			{ "Distance Color", ColorToString(VisualSettings::distanceImColor) },
			{ "Crosshair + Color", ColorToString(VisualSettings::crosshairImColor) },
			{ "FOV Circle Color", ColorToString(VisualSettings::fovImColor) }
		};
	}

	// Setup Load and Save Config Files.
	void SetupLoadAndSaveConfig(const char* configFile, bool* configLoad, bool* configLoaded, bool* saveConfig, bool* savedConfig)
	{
		if (*configLoad)
		{
			if (std::filesystem::exists(GetCurrentFilePathDir()))
			{
				std::filesystem::path BO3ZMConfig = GetCurrentFilePathDir();

				BO3ZMConfig /= configFile;

				if (!std::filesystem::exists(BO3ZMConfig))
				{
					*configLoad = false;
					*configLoaded = false;
				}
				else
				{
					// Load Config from File.
					nlohmann::json jImportSettings;
					std::ifstream iReadFile;
					iReadFile.open(BO3ZMConfig);
					iReadFile >> jImportSettings;
					iReadFile.close();
					ImportFromJson(jImportSettings);
				}
				*configLoad = false;
			}
		}
		if (*saveConfig)
		{
			if (std::filesystem::exists(GetCurrentFilePathDir()))
			{
				std::filesystem::path BO3ZMConfig = GetCurrentFilePathDir();

				BO3ZMConfig /= configFile;

				if (!std::filesystem::exists(BO3ZMConfig))
				{
					// Create Save Config File.
					std::ofstream bSaveFile;
					bSaveFile.open(BO3ZMConfig);
					bSaveFile << ToJson().dump(4);
					bSaveFile.close();
					*saveConfig = false;
					*savedConfig = true;
				}
				else
				{
					std::ofstream bSaveFile;
					bSaveFile.open(BO3ZMConfig);
					bSaveFile << ToJson().dump(4);
					bSaveFile.close();
					*savedConfig = true;
				}
				*saveConfig = false;
			}
		}
	}

	// Load and Save Config Files.
	void LoadAndSaveConfig()
	{
		SetupLoadAndSaveConfig("Config1.json", &ConfigSettings::bLoadConfig1, &ConfigSettings::bLoadedConfig1, &ConfigSettings::bSaveConfig1, &ConfigSettings::bSavedConfig1);
		SetupLoadAndSaveConfig("Config2.json", &ConfigSettings::bLoadConfig2, &ConfigSettings::bLoadedConfig2, &ConfigSettings::bSaveConfig2, &ConfigSettings::bSavedConfig2);
		SetupLoadAndSaveConfig("Config3.json", &ConfigSettings::bLoadConfig3, &ConfigSettings::bLoadedConfig3, &ConfigSettings::bSaveConfig3, &ConfigSettings::bSavedConfig3);
		SetupLoadAndSaveConfig("Config4.json", &ConfigSettings::bLoadConfig4, &ConfigSettings::bLoadedConfig4, &ConfigSettings::bSaveConfig4, &ConfigSettings::bSavedConfig4);
		SetupLoadAndSaveConfig("Config5.json", &ConfigSettings::bLoadConfig5, &ConfigSettings::bLoadedConfig5, &ConfigSettings::bSaveConfig5, &ConfigSettings::bSavedConfig5);
	}
}