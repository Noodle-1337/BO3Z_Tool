#include "Entity.hpp"

namespace SDK
{
	int IsInGame()
	{
		Utils::Read((BYTE*)Offsets::inGameAddr, (BYTE*)&GameValues::iInGameValue, sizeof(GameValues::iInGameValue), Game::hProc);
		return GameValues::iInGameValue;
	}

	bool WorldToScreen(vec3_t originPos, vec2_t& screenOut, float windowWidth, float windowHeight)
	{
		float Matrix[16] = 
		{ 0.f, 0.f , 0.f , 0.f, 
			0.f, 0.f, 0.f, 0.f, 
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f };

		Utils::Read((BYTE*)Game::moduleBase + Offsets::viewMatrix, (BYTE*)&Matrix, sizeof(Matrix), Game::hProc);

		vec4_t clipCoords;
		clipCoords.x = originPos.x * Matrix[0] + originPos.y * Matrix[1] + originPos.z * Matrix[2] + Matrix[3];
		clipCoords.y = originPos.x * Matrix[4] + originPos.y * Matrix[5] + originPos.z * Matrix[6] + Matrix[7];
		clipCoords.z = originPos.x * Matrix[8] + originPos.y * Matrix[9] + originPos.z * Matrix[10] + Matrix[11];
		clipCoords.w = originPos.x * Matrix[12] + originPos.y * Matrix[13] + originPos.z * Matrix[14] + Matrix[15];

		if (clipCoords.w < 0.1f)
			return false;

		vec3_t NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		screenOut.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
		screenOut.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
		return true;
	}

	float UnitsToMeter(float units)
	{
		return units * 0.0254f;
	}

#pragma region Player Functions
	void Entity_t::SetPlayerAddr()
	{
		Offsets::playerBase = Game::moduleBase + Offsets::playerBasePtr;
		Offsets::playerPedBase = Game::moduleBase + Offsets::playerPedPtr;
		Offsets::inGameAddr = Game::moduleBase + Offsets::inGamePtr;
		Offsets::jumpHeightBase = Game::moduleBase + Offsets::jumpHeightPtr;
		Offsets::playerNoRecoilBase = Game::moduleBase + Offsets::playerNoRecoilPtr;
		Offsets::inGameAddr = Game::moduleBase + Offsets::inGamePtr;
	}

	void Entity_t::GetPlayerAddr()
	{
		Offsets::playerPedBaseAddr = Utils::PointerChain(Game::hProc, Offsets::playerPedBase, Offsets::playerGodModeOffset);
		playerClipAmmoAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerClipAmmoOffset);
		playerStockAmmoAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerStockAmmoOffset);
		playerRunSpeedAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerRunSpeedOffset);
		playerPointsAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerPointsOffset);
		playerRapidFireAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerRapidFireOffset);
		playerNoSpreadAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerNoSpreadOffset);
		playerSetWeaponAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerSetWeaponOffset);
		playerGetPosAddr = Utils::PointerChain(Game::hProc, Offsets::playerBase, Offsets::playerCoordOffset);
		zombieHealthAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHealthOffset);
		zombieHealthMaxAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHealthMaxOffset);
		zombieGetPosAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieCoord);
		zombieGetHeadPosAddr = Utils::PointerChain(Game::hProc, Offsets::zombieBase, Offsets::zombieHeadCoord);
	}

	void Entity_t::GetPlayerValues()
	{
		Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 0), (BYTE*)&GameValues::iPlayer1CurrentPointsValue, sizeof(GameValues::iPlayer1CurrentPointsValue), Game::hProc);
		Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 1), (BYTE*)&GameValues::iPlayer2CurrentPointsValue, sizeof(GameValues::iPlayer2CurrentPointsValue), Game::hProc);
		Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 2), (BYTE*)&GameValues::iPlayer3CurrentPointsValue, sizeof(GameValues::iPlayer3CurrentPointsValue), Game::hProc);
		Utils::Read((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * 3), (BYTE*)&GameValues::iPlayer4CurrentPointsValue, sizeof(GameValues::iPlayer4CurrentPointsValue), Game::hProc);
		FeatureSettings::iP1PointsValue = GameValues::iPlayer1CurrentPointsValue;
		FeatureSettings::iP2PointsValue = GameValues::iPlayer2CurrentPointsValue;
		FeatureSettings::iP3PointsValue = GameValues::iPlayer3CurrentPointsValue;
		FeatureSettings::iP4PointsValue = GameValues::iPlayer4CurrentPointsValue;
	}

	uintptr_t Entity_t::GetJumpHeightBase()
	{
		return Offsets::jumpHeightBase;
	}

	void Entity_t::SetGodMode(int index, bool* state)
	{
		switch (index)
		{
		case 0:
			// Check whether we are back in lobby that way we don't crash the game. I'm sure this can be cleaner but it's a temp fix for now.
			Utils::Read((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayer1GodModeDefaultValue, sizeof(GameValues::iPlayer1GodModeDefaultValue), Game::hProc);

			if (*state)
			{
				if (GameValues::iPlayer1GodModeDefaultValue == 0)
					return;

				if (GameValues::iPlayer1GodModeCurrentValue != GameValues::iPlayerGodModeOn)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOn, sizeof(GameValues::iPlayerGodModeOn), Game::hProc);
					GameValues::iPlayer1GodModeCurrentValue = GameValues::iPlayerGodModeOn;
				}
			}
			else if (!*state)
			{
				if (GameValues::iPlayer1GodModeCurrentValue != GameValues::iPlayerGodModeOff)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOff, sizeof(GameValues::iPlayerGodModeOff), Game::hProc);
					GameValues::iPlayer1GodModeCurrentValue = GameValues::iPlayerGodModeOff;
				}
			}
			break;
		case 1:
			// Check whether we are back in lobby that way we don't crash the game. I'm sure this can be cleaner but it's a temp fix for now.
			Utils::Read((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayer2GodModeDefaultValue, sizeof(GameValues::iPlayer2GodModeDefaultValue), Game::hProc);

			if (*state)
			{
				if (GameValues::iPlayer2GodModeDefaultValue == 0)
					return;

				if (GameValues::iPlayer2GodModeCurrentValue != GameValues::iPlayerGodModeOn)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOn, sizeof(GameValues::iPlayerGodModeOn), Game::hProc);
					GameValues::iPlayer2GodModeCurrentValue = GameValues::iPlayerGodModeOn;
				}
			}
			else if (!*state)
			{
				if (GameValues::iPlayer2GodModeCurrentValue != GameValues::iPlayerGodModeOff)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOff, sizeof(GameValues::iPlayerGodModeOff), Game::hProc);
					GameValues::iPlayer2GodModeCurrentValue = GameValues::iPlayerGodModeOff;
				}
			}
			break;
		case 2:
			// Check whether we are back in lobby that way we don't crash the game. I'm sure this can be cleaner but it's a temp fix for now.
			Utils::Read((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayer3GodModeDefaultValue, sizeof(GameValues::iPlayer3GodModeDefaultValue), Game::hProc);

			if (*state)
			{
				if (GameValues::iPlayer3GodModeDefaultValue == 0)
					return;

				if (GameValues::iPlayer3GodModeCurrentValue != GameValues::iPlayerGodModeOn)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOn, sizeof(GameValues::iPlayerGodModeOn), Game::hProc);
					GameValues::iPlayer3GodModeCurrentValue = GameValues::iPlayerGodModeOn;
				}
			}
			else if (!*state)
			{
				if (GameValues::iPlayer3GodModeCurrentValue != GameValues::iPlayerGodModeOff)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOff, sizeof(GameValues::iPlayerGodModeOff), Game::hProc);
					GameValues::iPlayer3GodModeCurrentValue = GameValues::iPlayerGodModeOff;
				}
			}
			break;
		case 3:
			// Check whether we are back in lobby that way we don't crash the game. I'm sure this can be cleaner but it's a temp fix for now.
			Utils::Read((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayer4GodModeDefaultValue, sizeof(GameValues::iPlayer4GodModeDefaultValue), Game::hProc);

			if (*state)
			{
				if (GameValues::iPlayer4GodModeDefaultValue == 0)
					return;

				if (GameValues::iPlayer4GodModeCurrentValue != GameValues::iPlayerGodModeOn)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOn, sizeof(GameValues::iPlayerGodModeOn), Game::hProc);
					GameValues::iPlayer4GodModeCurrentValue = GameValues::iPlayerGodModeOn;
				}
			}
			else if (!*state)
			{
				if (GameValues::iPlayer4GodModeCurrentValue != GameValues::iPlayerGodModeOff)
				{
					Utils::Write((BYTE*)Offsets::playerPedBaseAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iPlayerGodModeOff, sizeof(GameValues::iPlayerGodModeOff), Game::hProc);
					GameValues::iPlayer4GodModeCurrentValue = GameValues::iPlayerGodModeOff;
				}
			}
			break;
		}
	}

	void Entity_t::SetPlayerClipAmmo(int index)
	{
		for (int i = 0; i < 9; i++)
		{
			Utils::Write((BYTE*)playerClipAmmoAddr + (Offsets::playerArray * i) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewAmmoValue, sizeof(GameValues::iPlayerNewAmmoValue), Game::hProc);
		}
	}

	void Entity_t::SetPlayerStockAmmo(int index)
	{
		for (int i = 0; i < 9; i++)
		{
			Utils::Write((BYTE*)playerStockAmmoAddr + (Offsets::playerArray * i) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewAmmoValue, sizeof(GameValues::iPlayerNewAmmoValue), Game::hProc);
		}
	}

	void Entity_t::SetCustomPlayerPoints(int index)
	{
		switch (index)
		{
		case 0:
			GameValues::iPlayer1NewCustomPointsValue = FeatureSettings::iP1PointsValue;
			Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer1NewCustomPointsValue, sizeof(GameValues::iPlayer1NewCustomPointsValue), Game::hProc);
			break;
		case 1:
			GameValues::iPlayer2NewCustomPointsValue = FeatureSettings::iP2PointsValue;
			Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer2NewCustomPointsValue, sizeof(GameValues::iPlayer2NewCustomPointsValue), Game::hProc);
			break;
		case 2:
			GameValues::iPlayer3NewCustomPointsValue = FeatureSettings::iP3PointsValue;
			Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer3NewCustomPointsValue, sizeof(GameValues::iPlayer3NewCustomPointsValue), Game::hProc);
			break;
		case 3:
			GameValues::iPlayer4NewCustomPointsValue = FeatureSettings::iP4PointsValue;
			Utils::Write((BYTE*)playerPointsAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer4NewCustomPointsValue, sizeof(GameValues::iPlayer4NewCustomPointsValue), Game::hProc);
			break;
		}
	}

	void Entity_t::FreezePlayerPoints(int index)
	{
		SetCustomPlayerPoints(index);
	}

	void Entity_t::EnableInstaKill()
	{
		for (int i = 0; i < 80; i++)
		{
			Utils::Read((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::iZombieInstaKillCurrentHealthValue, sizeof(GameValues::iZombieInstaKillCurrentHealthValue), Game::hProc);
			if (GameValues::iZombieInstaKillCurrentHealthValue < 1)
				continue;
			Utils::Write((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::iZombieNewHealthValue, sizeof(GameValues::iZombieNewHealthValue), Game::hProc);
		}
	}

	void Entity_t::SetPlayerJumpHeight(bool* state)
	{
		if (*state)
		{
			if (FeatureSettings::iJumpHeightValue == 39)
				return;

			GameValues::fGlobalNewJumpHeightValue = (float)FeatureSettings::iJumpHeightValue;
			Utils::Write((BYTE*)GetJumpHeightBase(), (BYTE*)&GameValues::fGlobalNewJumpHeightValue, sizeof(GameValues::fGlobalNewJumpHeightValue), Game::hProc);
		}
		else if (!*state)
		{
			GameValues::fGlobalNewJumpHeightValue = 39;
			Utils::Write((BYTE*)GetJumpHeightBase(), (BYTE*)&GameValues::fGlobalNewJumpHeightValue, sizeof(GameValues::fGlobalNewJumpHeightValue), Game::hProc);
		}
	}

	void Entity_t::SetPlayerRunSpeed(int index)
	{
		switch (index)
		{
		case 0:
			GameValues::fPlayer1NewRunSpeedValue = (float)FeatureSettings::iP1RunValue;
			Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer1NewRunSpeedValue, sizeof(GameValues::fPlayer1NewRunSpeedValue), Game::hProc);
			break;
		case 1:
			GameValues::fPlayer2NewRunSpeedValue = (float)FeatureSettings::iP2RunValue;
			Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer2NewRunSpeedValue, sizeof(GameValues::fPlayer2NewRunSpeedValue), Game::hProc);
			break;
		case 2:
			GameValues::fPlayer3NewRunSpeedValue = (float)FeatureSettings::iP3RunValue;
			Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer3NewRunSpeedValue, sizeof(GameValues::fPlayer3NewRunSpeedValue), Game::hProc);
			break;
		case 3:
			GameValues::fPlayer4NewRunSpeedValue = (float)FeatureSettings::iP4RunValue;
			Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::fPlayer4NewRunSpeedValue, sizeof(GameValues::fPlayer4NewRunSpeedValue), Game::hProc);
			break;
		default:
			if (GameValues::fPlayer1NewRunSpeedValue > 1.f)
			{
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * 0), (BYTE*)&GameValues::fPlayerDefaultRunSpeedValue, sizeof(GameValues::fPlayerDefaultRunSpeedValue), Game::hProc);
			}
			if (GameValues::fPlayer2NewRunSpeedValue > 1.f)
			{
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * 1), (BYTE*)&GameValues::fPlayerDefaultRunSpeedValue, sizeof(GameValues::fPlayerDefaultRunSpeedValue), Game::hProc);
			}
			if (GameValues::fPlayer3NewRunSpeedValue > 1.f)
			{
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * 2), (BYTE*)&GameValues::fPlayerDefaultRunSpeedValue, sizeof(GameValues::fPlayerDefaultRunSpeedValue), Game::hProc);
			}
			if (GameValues::fPlayer4NewRunSpeedValue > 1.f)
			{
				Utils::Write((BYTE*)playerRunSpeedAddr + (Offsets::playerArraySizeOffset * 3), (BYTE*)&GameValues::fPlayerDefaultRunSpeedValue, sizeof(GameValues::fPlayerDefaultRunSpeedValue), Game::hProc);
			}
		}
	}

	void Entity_t::EnableRapidFire(int index)
	{
		Utils::Write((BYTE*)playerRapidFireAddr + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayerNewRapidFireValue, sizeof(GameValues::iPlayerNewRapidFireValue), Game::hProc);
	}

	void Entity_t::SetNoRecoil(bool* state)
	{
		if (*state)
		{
			if (GameValues::iPlayer1GodModeDefaultValue == 0)
				return;

			if (GameValues::noRecoilValue != std::byte(0x75))
			{
				Utils::Write((BYTE*)Offsets::playerNoRecoilBase, (BYTE*)&GameValues::iPlayerNoRecoilOn, sizeof(GameValues::iPlayerNoRecoilOn), Game::hProc);
				GameValues::noRecoilValue = std::byte(0x75);
			}
		}
		else if (!*state)
		{
			if (GameValues::noRecoilValue != std::byte(0x74))
			{
				Utils::Write((BYTE*)Offsets::playerNoRecoilBase, (BYTE*)&GameValues::iPlayerNoRecoilOff, sizeof(GameValues::iPlayerNoRecoilOff), Game::hProc);
				GameValues::noRecoilValue = std::byte(0x74);
			}
		}
	}

	// Needs Fixed.
	void Entity_t::EnableNoSpread()
	{
		Utils::Write((BYTE*)playerNoSpreadAddr, (BYTE*)&GameValues::iPlayerNoSpreadValue, sizeof(GameValues::iPlayerNoSpreadValue), Game::hProc);
	}

	// Needs Fixed.
	void Entity_t::EnablePlayerJetPck()
	{
		if (GetAsyncKeyState(VK_SPACE) && 1)
		{
			Utils::Read((BYTE*)Offsets::playerZCoordAddr, (BYTE*)&GameValues::fCurrentPlayerCoordsZ, sizeof(GameValues::fCurrentPlayerCoordsZ), Game::hProc);
			GameValues::fGlobalJetPackValue = GameValues::fCurrentPlayerCoordsZ + GameValues::fGlobalJetPackAddValue;
			Utils::Write((BYTE*)Offsets::playerZCoordAddr, (BYTE*)&GameValues::fGlobalJetPackValue, sizeof(GameValues::fGlobalJetPackValue), Game::hProc);
		}
	}

	void Entity_t::SetPlayerWeapon(int index)
	{
		switch (index)
		{
		case 0:
			GameValues::iPlayer1NewWeaponValue = FeatureSettings::iP1WCValue;
			Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer1NewWeaponValue, sizeof(GameValues::iPlayer1NewWeaponValue), Game::hProc);
			break;
		case 1:
			GameValues::iPlayer2NewWeaponValue = FeatureSettings::iP2WCValue;
			Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer2NewWeaponValue, sizeof(GameValues::iPlayer2NewWeaponValue), Game::hProc);
			break;
		case 2:
			GameValues::iPlayer3NewWeaponValue = FeatureSettings::iP3WCValue;
			Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer3NewWeaponValue, sizeof(GameValues::iPlayer3NewWeaponValue), Game::hProc);
			break;
		case 3:
			GameValues::iPlayer4NewWeaponValue = FeatureSettings::iP4WCValue;
			Utils::Write((BYTE*)playerSetWeaponAddr + (Offsets::playerWeaponArray * 6) + (Offsets::playerArraySizeOffset * index), (BYTE*)&GameValues::iPlayer4NewWeaponValue, sizeof(GameValues::iPlayer4NewWeaponValue), Game::hProc);
			break;
		}
	}

	vec3_t Entity_t::GetPlayerPos()
	{
		Utils::Read((BYTE*)playerGetPosAddr, (BYTE*)&GameValues::currentPlayerCoords, sizeof(GameValues::currentPlayerCoords), Game::hProc);
		return GameValues::currentPlayerCoords;
	}

	vec3_t Entity_t::GetZombiePos(int index)
	{
		Utils::Read((BYTE*)zombieGetPosAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::currentZombieCoords, sizeof(GameValues::currentZombieCoords), Game::hProc);
		return GameValues::currentZombieCoords;
	}

	vec3_t Entity_t::GetZombieHeadPos(int index)
	{
		Utils::Read((BYTE*)zombieGetHeadPosAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::currentZombieHeadCoords, sizeof(GameValues::currentZombieHeadCoords), Game::hProc);
		return GameValues::currentZombieHeadCoords;
	}

	vec3_t Entity_t::GetHeadPosition(vec3_t origin)
	{
		return origin -= vec3_t{ 10, 20, 10 };
	}

	void Entity_t::GetBox(vec2_t screenOrigin, vec2_t screenHead, vec2_t& topLeft, vec2_t& bottomRight)
	{
		auto height = screenOrigin.y - screenHead.y;
		float width = 0;
		width = height / 4.0f;

		auto size = 1;
		auto left_x = screenOrigin.x - width - size;
		auto right_x = screenOrigin.x + width + size;
		auto top_y = screenHead.y - size;
		auto bottom_y = screenOrigin.y + size;

		topLeft = { left_x, top_y };
		bottomRight = { right_x, bottom_y };
	}
#pragma endregion

#pragma region Zombie Functions
	void Entity_t::SetZombieAddr()
	{
		Offsets::zombieBase = Game::moduleBase + Offsets::zombieBasePtr;
		Offsets::zombieCountBase = Game::moduleBase + Offsets::zombieCountPtr;
	}

	int Entity_t::GetZombieHealth(int index)
	{
		Utils::Read((BYTE*)zombieHealthAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iZombieCurrentHealthValue, sizeof(GameValues::iZombieCurrentHealthValue), Game::hProc);
		return GameValues::iZombieCurrentHealthValue;
	}

	int Entity_t::GetZombieHealthMax(int index)
	{
		Utils::Read((BYTE*)zombieHealthMaxAddr + (Offsets::zombieArraySize * index), (BYTE*)&GameValues::iZombieMaxHealthValue, sizeof(GameValues::iZombieMaxHealthValue), Game::hProc);
		return GameValues::iZombieMaxHealthValue;
	}

	void Entity_t::EnableZombieTP()
	{
		if (GetAsyncKeyState(MiscSettings::iZombieTPKey) & 1)
		{
			// Player Coords.
			Utils::Read((BYTE*)playerGetPosAddr, (BYTE*)&GameValues::currentPlayerCoordsTeleport, sizeof(GameValues::currentPlayerCoordsTeleport), Game::hProc);
		}
		for (int i = 0; i < 80; i++)
		{
			// Zombie Coords.
			Utils::Write((BYTE*)zombieGetPosAddr + (Offsets::zombieArraySize * i), (BYTE*)&GameValues::currentPlayerCoordsTeleport, sizeof(GameValues::currentPlayerCoordsTeleport), Game::hProc);
		}
	}

	int Entity_t::GetZombieCount()
	{
		Utils::Read((BYTE*)Offsets::zombieCountBase, (BYTE*)&GameValues::iZombieCountValue, sizeof(GameValues::iZombieCountValue), Game::hProc);
		return GameValues::iZombieCountValue;
	}
#pragma endregion
}