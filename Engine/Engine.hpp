#pragma once
#include "Entity/Entity.hpp"

namespace Engine
{
	extern SDK::Entity_t entity;
	void IsInGame();
	void PlayerFeatures();
	void DisableAllFeatures();

	namespace ESP
	{
		void DoESP();
		void MiscFeatures();
	}

	namespace Aimbot
	{
		extern SDK::Entity_t entityAim;
		void DoAimbot();
	}
}