/*
*	UPDATE Change Log:
*	
*	Update : 01/23/23 | Updated Codebase. Fixed several bugs. Fixed crashing issues due to No Recoil and God Mode.
*	
*	Update : 02/18/23 | Updated Codebase. Cleaned up file names.
* 
*	Update : 03/23/23 | Overhauled Codebase. Overhauled UI.
* 
*	Update : 05/09/23 | Updated offsets.
* 
*	Update : 07/11/23 | Updated Codebase. Cleaned up Player and Zombie Coordinate Reads/Writes.
* 
*	Update : 07/13/23 | Added button toggle for weapon cycle. Also added combo box (aka dropdown menu) for selecting weapon cycle hotkey. Also added Zombie Counter toggle to Player 1 Exploits.
* 
*	Update : 11/03/23 | A lot has been updated. Mostly codebase updates with a sprinkle of ESP features added in.
* 
*   Update : 11/26/23 | Some small adjustments.
* 
*	Update : 02/08/24 | Added base Config System. Still need to add the rest of the features to be exported and imported from the config system.
* 
*	Update : 06/12/24 | Added all ESP/Player exploit features to the Config system. Also added a Watermark toggle.
* 
*	Update : 06/13/24 | Fixed Aimbot system and added valid checks to both ESP/Aimbot. Fixed Zombie Counter. Added Aimbot features to the config system and UI.
* 
* 
*	TODO:
* 
*	Aimbot: Add Skeleton/Bone Selection.
*	ESP: Add Skeleton ESP.
*	Exploits: Fix JetPack feature. Fix No Spread.
*	Config System: Add Aimbot features to the config system.
*/

#include "BO3_Main.hpp"

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	Startup::SetConsoleAppInfo();
	Startup::GetGameInfo();
	Startup::CreateThreads();
	while (true)
	{
		Engine::IsInGame();
		Engine::Aimbot::DoAimbot();
		Engine::DisableAllFeatures();
		ConfigSystem::LoadAndSaveConfig();
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
}