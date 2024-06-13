#pragma once
#include "../../Utils/Utils.hpp"

namespace SDK
{
	int IsInGame();

	bool WorldToScreen(vec3_t originPos, vec2_t& screenOut, float windowWidth, float windowHeight);

	float UnitsToMeter(float units);

	class Entity_t
	{
	public:
		// Current addresses.
		uintptr_t playerClipAmmoAddr = 0;
		uintptr_t playerStockAmmoAddr = 0;
		uintptr_t playerPointsAddr = 0;
		uintptr_t playerRunSpeedAddr = 0;
		uintptr_t playerRapidFireAddr = 0;
		uintptr_t playerNoSpreadAddr = 0;
		uintptr_t playerSetWeaponAddr = 0;
		uintptr_t playerGetPosAddr = 0;
		//
		uintptr_t zombieHealthAddr = 0;
		uintptr_t zombieHealthMaxAddr = 0;
		uintptr_t zombieGetPosAddr = 0;
		uintptr_t zombieGetHeadPosAddr = 0;
		uintptr_t zombieGetValidAddr = 0;

#pragma region Player Functions
		void SetPlayerAddr();

		void GetPlayerAddr();
		
		void GetPlayerValues();

		uintptr_t GetJumpHeightBase();

		void SetGodMode(int index, bool* state);

		void SetPlayerClipAmmo(int index);

		void SetPlayerStockAmmo(int index);

		void SetCustomPlayerPoints(int index);

		void FreezePlayerPoints(int index);

		void EnableInstaKill();

		void SetPlayerJumpHeight(bool* state);

		void SetPlayerRunSpeed(int index);

		void EnableRapidFire(int index);

		void SetNoRecoil(bool* state);

		// Needs Fixed.
		void EnableNoSpread();

		// Needs Fixed.
		void EnablePlayerJetPck();

		void SetPlayerWeapon(int index);

		vec3_t GetPlayerPos();

		vec3_t GetZombiePos(int index);

		vec3_t GetZombieHeadPos(int index);

		vec3_t GetHeadPosition(vec3_t origin);

		void GetBox(vec2_t screenOrigin, vec2_t screenHead, vec2_t& topLeft, vec2_t& bottomRight);
#pragma endregion

#pragma region Zombie Functions
		void SetZombieAddr();

		int GetZombieHealth(int index);

		int GetZombieHealthMax(int index);

		int IsZombieValid(int index);

		void EnableZombieTP();

		int GetZombieCount();
#pragma endregion
	};
}
