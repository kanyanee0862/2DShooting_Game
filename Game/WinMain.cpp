#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW 
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW
#endif
#endif
#include "src/Utility/Vec.hpp"
#include "src/Utility/Utility.hpp"
#include "src/GameController/GameMain.hpp"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(98);
	ShowConsole();
	GameMain main;
	main.run();
}
