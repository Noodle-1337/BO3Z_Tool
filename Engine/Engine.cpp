#include "../Overlay/Overlay.hpp"

namespace Engine
{
	SDK::Entity_t entity;

	// Check if Player is in Game.
	void IsInGame()
	{
		if (SDK::IsInGame() < 1)
		{
			if (Game::bSetAddress == 0)
			{
				entity.GetPlayerAddr();
				entity.GetPlayerValues();
				Aimbot::entityAim.GetPlayerAddr();
				Game::bSetAddress = 2;
			}
			else if (Game::bSetAddress == 1)
			{
				entity.GetPlayerAddr();
				entity.GetPlayerValues();
				Aimbot::entityAim.GetPlayerAddr();
				Game::bSetAddress = 2;
			}
			if (FeatureSettings::bIsInGame)
			{
				FeatureSettings::bIsInGame = false;
			}
		}
		else if (SDK::IsInGame() > 0)
		{
			if (Game::bSetAddress == 0)
			{
				entity.GetPlayerAddr();
				entity.GetPlayerValues();
				Aimbot::entityAim.GetPlayerAddr();
				Game::bSetAddress = 1;
			}
			else if (Game::bSetAddress == 2)
			{
				entity.GetPlayerAddr();
				entity.GetPlayerValues();
				Aimbot::entityAim.GetPlayerAddr();
				Game::bSetAddress = 1;
			}
			if (!FeatureSettings::bIsInGame)
			{
				FeatureSettings::bIsInGame = true;
			}
		}
	}
	// Features for Player 1 - 4 ( also includes zombies features ).
	void PlayerFeatures()
	{
		while (true)
		{
			if (FeatureSettings::bIsInGame)
			{
#pragma region Player 1 Features.
				if (FeatureSettings::bP1InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer1Index, &FeatureSettings::bTrueState);
				}
				if (!FeatureSettings::bP1InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer1Index, &FeatureSettings::bFalseState);
				}
				if (FeatureSettings::bP1InfiniteClipAmmo)
				{
					entity.SetPlayerClipAmmo(GameValues::iPlayer1Index);
				}
				if (FeatureSettings::bP1InfiniteStockAmmo)
				{
					entity.SetPlayerStockAmmo(GameValues::iPlayer1Index);
				}
				if (FeatureSettings::bP1DynamicPoints)
				{
					entity.SetCustomPlayerPoints(GameValues::iPlayer1Index);
					FeatureSettings::bP1DynamicPoints = false;
				}
				if (FeatureSettings::bP1InfinitePoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer1Index);
				}
				if (FeatureSettings::bP1AlwaysInstaKill)
				{
					entity.EnableInstaKill();
				}
				if (FeatureSettings::bP1RunSpeed)
				{
					entity.SetPlayerRunSpeed(GameValues::iPlayer1Index);
					FeatureSettings::bP1RunSpeed = false;
				}
				if (FeatureSettings::bP1JumpHeight)
				{
					entity.SetPlayerJumpHeight(&FeatureSettings::bTrueState);
				}
				if (FeatureSettings::bNoRecoilOn)
				{
					entity.SetNoRecoil(&FeatureSettings::bTrueState);
				}
				if (!FeatureSettings::bNoRecoilOn)
				{
					entity.SetNoRecoil(&FeatureSettings::bFalseState);
				}
				/*if (FeatureSettings::bNoSpreadOn)
				{
					entity.EnableNoSpread();
				}*/
				if (FeatureSettings::bP1RapidFire)
				{
					entity.EnableRapidFire(GameValues::iPlayer1Index);
				}
				/*if (FeatureSettings::bJetPack)
				{
					entity.EnablePlayerJetPck();
				}*/
				if (FeatureSettings::bP1WCycle)
				{
					entity.SetPlayerWeapon(GameValues::iPlayer1Index);
					FeatureSettings::bP1WCycle = false;
				}
				if (FeatureSettings::bP1WCycleKey)
				{
					if (GetAsyncKeyState(AimSettings::iAimKey) & 1)
					{
						FeatureSettings::iP1WCValue = FeatureSettings::iP1WCValue + 1;
						entity.SetPlayerWeapon(GameValues::iPlayer1Index);
					}
				}
#pragma endregion

#pragma region Player 2 Features.
				if (FeatureSettings::bP2InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer2Index, &FeatureSettings::bTrueState);
				}
				if (!FeatureSettings::bP2InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer2Index, &FeatureSettings::bFalseState);
				}
				if (FeatureSettings::bP2InfiniteClipAmmo)
				{
					entity.SetPlayerClipAmmo(GameValues::iPlayer2Index);
				}
				if (FeatureSettings::bP2InfiniteStockAmmo)
				{
					entity.SetPlayerStockAmmo(GameValues::iPlayer2Index);
				}
				if (FeatureSettings::bP2DynamicPoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer2Index);
					FeatureSettings::bP2DynamicPoints = false;
				}
				if (FeatureSettings::bP2InfinitePoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer2Index);
				}
				if (FeatureSettings::bP2RunSpeed)
				{
					entity.SetPlayerRunSpeed(GameValues::iPlayer2Index);
					FeatureSettings::bP2RunSpeed = false;
				}
				if (FeatureSettings::bP2RapidFire)
				{
					entity.EnableRapidFire(GameValues::iPlayer2Index);
				}
				if (FeatureSettings::bP2WCycle)
				{
					entity.SetPlayerWeapon(GameValues::iPlayer2Index);
				}
#pragma endregion

#pragma region Player 3 Features.
				if (FeatureSettings::bP3InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer3Index, &FeatureSettings::bTrueState);
				}
				if (!FeatureSettings::bP3InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer3Index, &FeatureSettings::bFalseState);
				}
				if (FeatureSettings::bP3InfiniteClipAmmo)
				{
					entity.SetPlayerClipAmmo(GameValues::iPlayer3Index);
				}
				if (FeatureSettings::bP3InfiniteStockAmmo)
				{
					entity.SetPlayerStockAmmo(GameValues::iPlayer3Index);
				}
				if (FeatureSettings::bP3DynamicPoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer3Index);
					FeatureSettings::bP3DynamicPoints = false;
				}
				if (FeatureSettings::bP3InfinitePoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer3Index);
				}
				if (FeatureSettings::bP3RunSpeed)
				{
					entity.SetPlayerRunSpeed(GameValues::iPlayer3Index);
					FeatureSettings::bP3RunSpeed = false;
				}
				if (FeatureSettings::bP3RapidFire)
				{
					entity.EnableRapidFire(GameValues::iPlayer3Index);
				}
				if (FeatureSettings::bP3WCycle)
				{
					entity.SetPlayerWeapon(GameValues::iPlayer3Index);
				}
#pragma endregion

#pragma region Player 4 Features.
				if (FeatureSettings::bP4InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer4Index, &FeatureSettings::bTrueState);
				}
				if (!FeatureSettings::bP4InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer4Index, &FeatureSettings::bFalseState);
				}
				if (FeatureSettings::bP4InfiniteClipAmmo)
				{
					entity.SetPlayerClipAmmo(GameValues::iPlayer4Index);
				}
				if (FeatureSettings::bP4InfiniteStockAmmo)
				{
					entity.SetPlayerStockAmmo(GameValues::iPlayer4Index);
				}
				if (FeatureSettings::bP4DynamicPoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer4Index);
					FeatureSettings::bP4DynamicPoints = false;
				}
				if (FeatureSettings::bP4InfinitePoints)
				{
					entity.FreezePlayerPoints(GameValues::iPlayer4Index);
				}
				if (FeatureSettings::bP4RunSpeed)
				{
					entity.SetPlayerRunSpeed(GameValues::iPlayer4Index);
					FeatureSettings::bP4RunSpeed = false;
				}
				if (FeatureSettings::bP4RapidFire)
				{
					entity.EnableRapidFire(GameValues::iPlayer4Index);
				}
				if (FeatureSettings::bP4WCycle)
				{
					entity.SetPlayerWeapon(GameValues::iPlayer4Index);
				}
#pragma endregion

#pragma region Zombie Features.
				if (FeatureSettings::bZombieTP)
				{
					entity.EnableZombieTP();
				}
				if (FeatureSettings::bZombieCount)
				{
					entity.GetZombieCount();
				}
#pragma endregion
			}
			if (!FeatureSettings::bIsInGame)
			{
				// Player 1 Features.
				if (FeatureSettings::bP1InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer1Index, &FeatureSettings::bFalseState);
				}
				if (FeatureSettings::bNoRecoilOn)
				{
					entity.SetNoRecoil(&FeatureSettings::bFalseState);
				}
				/*if (FeatureSettings::bJetPack)
				{
					FeatureSettings::bJetPack = false;
					entity.fGlobalJetPackValue = 0.f;
					entity.fGlobalJetPackAddValue = 8.f;
				}*/
				// Player 2 Features.
				if (FeatureSettings::bP2InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer2Index, &FeatureSettings::bFalseState);
				}
				// Player 3 Features.
				if (FeatureSettings::bP3InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer3Index, &FeatureSettings::bFalseState);
				}
				// Player 4 Features.
				if (FeatureSettings::bP4InfiniteHealth)
				{
					entity.SetGodMode(GameValues::iPlayer4Index, &FeatureSettings::bFalseState);
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(3));
		}
	}
	// Disbale All Features.
	void DisableAllFeatures()
	{
		if (Utils::GetProcId("BlackOps3.exe") < 1)
		{
			exit(0);
		}
		if (GetAsyncKeyState(VK_DELETE) & 1 || FeatureSettings::bDisableAllFeatures)
		{
			/*
			*	Player 1 booleans
			*/
			FeatureSettings::bP1InfiniteHealth = false;
			entity.SetGodMode(GameValues::iPlayer1Index, &FeatureSettings::bFalseState);
			FeatureSettings::bP1InfiniteClipAmmo = false;
			FeatureSettings::bP1InfiniteStockAmmo = false;
			FeatureSettings::bP1InfinitePoints = false;
			FeatureSettings::bP1AlwaysInstaKill = false;
			FeatureSettings::bNoRecoilOn = false;
			entity.SetNoRecoil(&FeatureSettings::bFalseState);
			FeatureSettings::bP1RapidFire = false;
			FeatureSettings::bP1JumpHeight = false;
			FeatureSettings::bZombieTP = false;
			FeatureSettings::bExtraZombiesTP = false;
			FeatureSettings::bTPAllZombies = false;
			FeatureSettings::bP1WCycle = false;
			/*
			*	Player 2 booleans
			*/
			FeatureSettings::bP2InfiniteHealth = false;
			entity.SetGodMode(GameValues::iPlayer2Index, &FeatureSettings::bFalseState);
			FeatureSettings::bP2InfiniteClipAmmo = false;
			FeatureSettings::bP2InfiniteStockAmmo = false;
			FeatureSettings::bP2InfinitePoints = false;
			FeatureSettings::bP2RapidFire = false;
			FeatureSettings::bP2WCycle = false;
			/*
			*	Player 3 booleans
			*/
			FeatureSettings::bP3InfiniteHealth = false;
			entity.SetGodMode(GameValues::iPlayer3Index, &FeatureSettings::bFalseState);
			FeatureSettings::bP3InfiniteClipAmmo = false;
			FeatureSettings::bP3InfiniteStockAmmo = false;
			FeatureSettings::bP3InfinitePoints = false;
			FeatureSettings::bP3RapidFire = false;
			FeatureSettings::bP3WCycle = false;
			/*
			*	Player 4 booleans
			*/
			FeatureSettings::bP4InfiniteHealth = false;
			entity.SetGodMode(GameValues::iPlayer4Index, &FeatureSettings::bFalseState);
			FeatureSettings::bP4InfiniteClipAmmo = false;
			FeatureSettings::bP4InfiniteStockAmmo = false;
			FeatureSettings::bP4InfinitePoints = false;
			FeatureSettings::bP4RapidFire = false;
			FeatureSettings::bP4WCycle = false;
			/*
			*	Extra Goodies booleans
			*/
			VisualSettings::bZombie2DBox = false;
			VisualSettings::bZombie2DBrackets = false;
			VisualSettings::bZombieSnaplines = false;
			MiscSettings::bCrosshair = false;
			MiscSettings::bPlayerFov = false;
			FeatureSettings::bZombieCount = false;
		}
		if (GetAsyncKeyState(VK_HOME))
		{
			/*
			*	Player 1 booleans
			*/
			entity.SetGodMode(GameValues::iPlayer1Index, &FeatureSettings::bFalseState);
			entity.SetNoRecoil(&FeatureSettings::bFalseState);
			entity.SetPlayerRunSpeed(1337);
			entity.SetPlayerJumpHeight(&FeatureSettings::bFalseState);
			/*
			*	Player 2 booleans
			*/
			entity.SetGodMode(GameValues::iPlayer2Index, &FeatureSettings::bFalseState);
			/*
			*	Player 3 booleans
			*/
			entity.SetGodMode(GameValues::iPlayer3Index, &FeatureSettings::bFalseState);
			/*
			*	Player 4 booleans
			*/
			entity.SetGodMode(GameValues::iPlayer4Index, &FeatureSettings::bFalseState);
			exit(0);
		}
	}

	namespace ESP
	{
		// Check if outScreen positions are past the edge of the monitor.
		__inline static bool OnScreenStrict(vec2_t V)
		{
			if (V.x > 0.01f && V.y > 0.01f && V.x < (float)UI::iScreenWidth && V.y < (float)UI::iScreenHeight)
				return true;
			return false;
		}

		// What does this function do?
		extern __inline void DoESP()
		{
			if (FeatureSettings::bIsInGame)
			{
				for (int i = 0; i < 80; i++)
				{
					int iCurrentZHealth = entity.GetZombieHealth(i);
					int iCurrentZMaxHealth = entity.GetZombieHealthMax(i);

					if (iCurrentZHealth < 1 || iCurrentZHealth == 0)
						continue;

					int iCurrentValid = entity.IsZombieValid(i);

					if (iCurrentValid != 1 && iCurrentValid != 3)
						continue;

					vec2_t vScreen = { 0, 0 };
					vec2_t vHead = { 0, 0 };
					vec3_t vZombiePos = entity.GetZombiePos(i);
					vec3_t vZombieHeadPos = entity.GetZombieHeadPos(i);
					vec3_t vPlayerPos = entity.GetPlayerPos();
					vec3_t vHeadPos = { 0, 0, 0 };

					if (SDK::WorldToScreen(vZombiePos, vScreen, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
					{
						if (OnScreenStrict(vScreen))
						{
							vHeadPos = entity.GetHeadPosition(vZombieHeadPos);

							if (SDK::WorldToScreen(vHeadPos, vHead, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
							{
								if (OnScreenStrict(vHead))
								{
									vec2_t topLeft = { 0, 0 }, bottomRight = { 0, 0 };
									entity.GetBox(vScreen, vHead, topLeft, bottomRight);

									float headHeight = vHead.y - vScreen.y;
									float width = headHeight / 2;
									float center = width;

									if (VisualSettings::bZombieSnaplines)
									{
										if (VisualSettings::iZombieSnaplinePos == 1)
										{
											Render::Line(ImVec2((float)UI::iScreenWidth / 2, (float)UI::iScreenHeight - (float)UI::iScreenHeight), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
										}
										else if (VisualSettings::iZombieSnaplinePos == 2)
										{
											Render::Line(ImVec2((float)UI::iScreenWidth / 2, (float)UI::iScreenHeight / 2), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
										}
										else if (VisualSettings::iZombieSnaplinePos == 3)
										{
											Render::Line(ImVec2((float)UI::iScreenWidth / 2, (float)UI::iScreenHeight), ImVec2(vScreen.x, vHead.y), VisualSettings::snaplineImColor, 1.f);
										}
									}
									if (VisualSettings::bZombie2DBrackets)
									{
										if (VisualSettings::bZombieHealthBar)
										{
											char buf[64];
											sprintf_s(buf, "[%i]Health", iCurrentZHealth);
											Render::CustomHealthColor((float)iCurrentZHealth, (float)iCurrentZMaxHealth, &VisualSettings::healthBarImColor);
											Render::DrawBoxBrackets(ImGui::GetWindowDrawList(), topLeft.x - center, bottomRight.y, center, headHeight, VisualSettings::healthBarImColor, 1.f);
											Render::DrawOutlinedText(ImGui::Body, ImVec2(vScreen.x, vHead.y - 20), 13.0f, VisualSettings::healthTextImColor, true, buf);
										}
										else
										{
											Render::DrawBoxBrackets(ImGui::GetWindowDrawList(), topLeft.x - center, bottomRight.y, center, headHeight, VisualSettings::bracketBoxImColor, 1.f);
										}
									}
									if (VisualSettings::bZombieBoxFilled)
									{
										Render::RectFilled2(topLeft.x - center, bottomRight.y, center, headHeight, VisualSettings::boxFilledImColor);
									}
									if (VisualSettings::bZombie2DBox)
									{
										Render::DrawBox(VisualSettings::boxImColor, topLeft.x - center, bottomRight.y, center, headHeight);
									}
									if (VisualSettings::bZombieDistance)
									{
										float dist = SDK::UnitsToMeter(vPlayerPos.distance_to(vZombiePos));
										char buf[64];
										sprintf_s(buf, "[%.1f]m", dist);
										Render::DrawOutlinedText(ImGui::Body, ImVec2(vScreen.x, vScreen.y + 10), 13.0f, VisualSettings::distanceImColor, true, buf);
									}
								}
							}
						}
					}
				}
			}
		}

		// Small Crosshair in the Center of the Screen.
		constexpr long fCrosshairSize = (const long)10.0f;
		ImVec2 vCenterScreenPos = ImVec2((float)WND_SIZEX / 2, (float)WND_SIZEY / 2); // ImVec2((float)UI::iScreenWidth / 2.f, (float)UI::iScreenHeight / 2.f);

		// Misc Features go here.
		extern __inline void MiscFeatures()
		{
			if (MiscSettings::bCrosshair)
			{				
				Render::Line(ImVec2((vCenterScreenPos.x), (vCenterScreenPos.y) - fCrosshairSize), ImVec2((vCenterScreenPos.x), (vCenterScreenPos.y) + fCrosshairSize), VisualSettings::crosshairImColor, 1.5f);
				Render::Line(ImVec2((vCenterScreenPos.x) - fCrosshairSize, (vCenterScreenPos.y)), ImVec2((vCenterScreenPos.x) + fCrosshairSize, (vCenterScreenPos.y)), VisualSettings::crosshairImColor, 1.5f);
			}
			if (MiscSettings::bPlayerFov)
			{
				Render::Circle(VisualSettings::fovImColor, MiscSettings::fPlayerFovSize);
			}
			if (FeatureSettings::bZombieCount)
			{
				// Draw Zombie Counter in Bottom Left Screen.
				Render::EasyText(ImVec2(10, (float)UI::iScreenHeight - 30), VisualSettings::zombieCounterImColor, "Zombie Count: ", 15.f);
				Render::EasyNumber(ImVec2(100, (float)UI::iScreenHeight - 30), VisualSettings::zombieCounterValueImColor, GameValues::iZombieCountValue, 15.f);
			}
		}
	}

	namespace Aimbot
	{
		SDK::Entity_t entityAim;

		__inline static float DistanceCursor(vec2_t vec)
		{
			POINT p;
			if (GetCursorPos(&p))
			{
				float ydist = (vec.y - p.y);
				float xdist = (vec.x - p.x);
				float ret = (float)sqrt(pow(ydist, 2) + pow(xdist, 2));
				return ret;
			}
			else
			{
				return 0;
			}
		}

		__inline static vec2_t Smooth(vec2_t pos)
		{
			vec2_t center{ (float)(UI::iScreenWidth / 2), (float)(UI::iScreenHeight / 2) };
			vec2_t target{ 0, 0 };
			if (pos.x != 0) {
				if (pos.x > center.x) {
					target.x = -(center.x - pos.x);
					target.x /= 1;
					if (target.x + center.x > center.x * 2)
						target.x = 0;
				}

				if (pos.x < center.x) {
					target.x = pos.x - center.x;
					target.x /= 1;
					if (target.x + center.x < 0)
						target.x = 0;
				}
			}

			if (pos.y != 0) {
				if (pos.y > center.y) {
					target.y = -(center.y - pos.y);
					target.y /= 1;
					if (target.y + center.y > center.y * 2)
						target.y = 0;
				}

				if (pos.y < center.y) {
					target.y = pos.y - center.y;
					target.y /= 1;
					if (target.y + center.y < 0)
						target.y = 0;
				}
			}

			target.x /= AimSettings::fAimSmooth;
			target.y /= AimSettings::fAimSmooth;

			if (abs(target.x) < 1) {
				if (target.x > 0) {
					target.x = 1;
				}
				if (target.x < 0) {
					target.x = -1;
				}
			}
			if (abs(target.y) < 1) {
				if (target.y > 0) {
					target.y = 1;
				}
				if (target.y < 0) {
					target.y = -1;
				}
			}

			return target;
		}

		__inline static void MouseAim(vec2_t target)
		{
			INPUT input;
			input.type = INPUT_MOUSE;
			input.mi.mouseData = 0;
			input.mi.time = 0;
			input.mi.dx = (LONG)target.x;
			input.mi.dy = (LONG)target.y;
			input.mi.dwFlags = MOUSEEVENTF_MOVE;
			SendInput(1, &input, sizeof(input));
		}

		__inline static int GetClosestTarget()
		{
			for (int i = 0; i < 1000; i++)
			{
				int iCurrentZHealth = entityAim.GetZombieHealth(i);

				if (iCurrentZHealth < 1 || iCurrentZHealth == 0)
					continue;

				int iCurrentValid = entityAim.IsZombieValid(i);

				if (iCurrentValid != 1 && iCurrentValid != 3)
					continue;

				vec3_t vZombiePos = entityAim.GetZombiePos(i);
				vec3_t vZombieHeadPos = entityAim.GetZombieHeadPos(i);
				vec3_t vPlayerPos = entityAim.GetPlayerPos();
				vec3_t vHeadPos = { 0, 0, 0 };
				vec2_t vScreen = { 0, 0 };
				vec2_t vScreenHead = { 0, 0 };

				if (SDK::WorldToScreen(vZombiePos, vScreen, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
				{
					vHeadPos = entity.GetHeadPosition(vZombieHeadPos);

					if (SDK::WorldToScreen(vHeadPos, vScreenHead, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
					{
						float fFov = DistanceCursor(vScreenHead);

						if (fFov < MiscSettings::fPlayerFovSize)
						{
							float fCurrentDist = SDK::UnitsToMeter(vPlayerPos.distance_to(vZombiePos));

							if (fCurrentDist < AimSettings::fClosestDist)
							{
								AimSettings::fClosestDist = fCurrentDist;
								AimSettings::iBestTarget = i;
							}
							if (fCurrentDist > AimSettings::fClosestDist)
							{
								continue;
							}
						}
					}
				}
			}
			AimSettings::fClosestDist = FLT_MAX;
			return AimSettings::iBestTarget;
		}

		void DoAimbot()
		{
			if (FeatureSettings::bAimbot)
			{
				if (FeatureSettings::bIsInGame)
				{
					if (GetAsyncKeyState(AimSettings::iAimKey))
					{
						int iCurrentTarget = GetClosestTarget();
						vec3_t vZombiePos = entityAim.GetZombiePos(iCurrentTarget);
						vec3_t vZombieHeadPos = entityAim.GetZombieHeadPos(iCurrentTarget);
						vec3_t vPlayerPos = entityAim.GetPlayerPos();
						vec3_t vHeadPos = { 0, 0, 0 };
						vec2_t vScreen = { 0, 0 };
						vec2_t vScreenHead = { 0, 0 };

						if (SDK::WorldToScreen(vZombiePos, vScreen, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
						{
							vHeadPos = entityAim.GetHeadPosition(vZombieHeadPos);

							vHeadPos -= vec3_t{ +5, 0, +10 };

							if (SDK::WorldToScreen(vHeadPos, vScreenHead, (float)UI::iScreenWidth, (float)UI::iScreenHeight))
							{
								float fCurrentDist = SDK::UnitsToMeter(vPlayerPos.distance_to(vZombiePos));

								if (fCurrentDist < 200.f)
								{
									float fFov = DistanceCursor(vScreenHead);

									if (fFov < MiscSettings::fPlayerFovSize)
									{
										MouseAim(Smooth(vScreenHead));
									}
								}
							}
						}
					}
				}
			}
		}
	}
}