
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <format>
#include <conio.h>
#include <Windows.h>

#include "Menu.h"
#include "MenuTypesDeclares.h"
#include "GameState.h"
#include "ActorSelectionState.h"
#include "BuildModeState.h"
#include "BuildModeObjFreezeState.h"
#include "Maths.h"
#include "Preprocessor.h"
#include "ACamera.h"
#include "ASpectatorCamera.h"
#include "Pixel.h"
#include "StaticMesh.h"
#include "Parallelepiped.h"
#include "SkyboxPart.h"
#include "Circle.h"
#include "EnvShake.h"
#include "Pyramid.h"
#include "Triangle.h"
#include "Light.h"
#include "AActor.h"
#include "Delegate.h"
#include "ATriggerActor.h"
#include "AMovementArrows.h"
#include "AMovementCircles.h"
#include "AMovementScales.h"
#include "ATriggerLine.h"
#include "ATriggerActor.h"
#include "ACubemapActor.h"
#include "ABaseActor.h"
#include "ASkyboxPart.h"
#include "ASmokeActor.h"
#include "ALightActor.h"
#include "Render.h"
#include "ObjFileParse.h"
#include "Model.h"
#include "FileLoader.h"
#include "MapLoader.h"
#include "MenuTypesImpl.h"
#include "SpawnCubeMenuTypesImpl.h"
#include "SpawnSpriteMenuTypesImpl.h"
#include "SpawnTriggerMenuTypesImpl.h"

double tick;
char key = 0;

void OnGameKeyCheck()
{
	if (key == ESC_KEY)
	{
		currentGameState->OnKeyEsc();
	}
	else if (key == ENTER_KEY)
	{
		currentGameState->OnEnterKey();
	}
	else if (key == ARROW_UP_KEY || key == ARROW_DOWN_KEY)
	{
		currentGameState->OnArrowUpDownKey();
	}
	else if (key == ADDITIONAL_LENGTH_INC_KEY || key == ADDITIONAL_LENGTH_DEC_KEY)
	{
		currentGameState->OnAdditionalLengthKey();
	}
	else if (key == ADDITIONAL_WIDTH_INC_KEY || key == ADDITIONAL_WIDTH_DEC_KEY)
	{
		currentGameState->OnAdditionalWidthKey();
	}
	else if (key == INC_LIGHT_POWER_KEY || key == DEC_LIGHT_POWER_KEY)
	{
		currentGameState->OnLightPowerAndParabRadKey();
	}
	else if (key == DELETE_KEY)
	{
		currentGameState->OnDeleteKey();
	}
	else if (key == FREEZE_KEY)
	{
		currentGameState->OnFreezeKey();
	}
	else if (key == PARAB_SPAWN_KEY)
	{
		currentGameState->OnSpawnParabKey();
	}
	else if (key == COLOR_CHANGE_KEY)
	{
		currentGameState->OnColorChangeKey();
	}
	else if (key == RAY_FROM_CAMERA_KEY)
	{
		currentGameState->OnRayFromCameraKey();
	}
	else if (key == ENABLE_MOVEMENT_ARROWS)
	{
		rotatedCirclesActor->DisablePartsOnObject();
		movementScalesActor->DisablePartsOnObject();
		movementArrowsActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}
	else if (key == ENABLE_ROTATED_CIRCLES)
	{
		movementArrowsActor->DisablePartsOnObject();
		movementScalesActor->DisablePartsOnObject();
		rotatedCirclesActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}
	else if (key == ENABLE_MOVEMENT_SCALES)
	{
		movementArrowsActor->DisablePartsOnObject();
		rotatedCirclesActor->DisablePartsOnObject();
		movementScalesActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}
}

void DrawMenu()
{
	generalMenuClass->DrawMenuTypes();
}

void DrawEditorStars()
{
	generalMenuClass->DrawMenuStars();
}

void OnEditorKeyCheck()
{
	if (key == ESC_KEY)
	{
		currMenuState = EDITOR_STATE::GAME;
	}
	else if (key == MENU_SCROLL_KEY)
	{
		DrawEditorStars();
	}
	else if (key == ENTER_KEY)
	{
		generalMenuClass->CheckAddMenuTypesToStorage();
	}
	else if (key == ARROW_RIGHT_KEY)
	{
		if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_CUBE)
		{
			currMenuState = EDITOR_STATE::SUB_EDITOR;
			currentMenuType = MENU_TYPES::SPAWN_CUBE_MENU;

			SpawnCubeMenuClass->DrawMenuTypes();
			SpawnCubeMenuClass->DrawMenuStars();
		}
		else if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_SPRITE)
		{
			currMenuState = EDITOR_STATE::SUB_EDITOR;
			currentMenuType = MENU_TYPES::SPAWN_SPRITE_MENU;

			SpawnSpriteMenuClass->DrawMenuTypes();
			SpawnSpriteMenuClass->DrawMenuStars();
		}
		else if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_TRIGGER)
		{
			currMenuState = EDITOR_STATE::SUB_EDITOR;
			currentMenuType = MENU_TYPES::SPAWN_TRIGGER_MENU;

			SpawnTriggerMenuClass->DrawMenuTypes();
			SpawnTriggerMenuClass->DrawMenuStars();
		}
	}
	else if (key == ENABLE_MOVEMENT_ARROWS)
	{
		rotatedCirclesActor->DisablePartsOnObject();
		movementScalesActor->DisablePartsOnObject();
		movementArrowsActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}
	else if (key == ENABLE_ROTATED_CIRCLES)
	{
		movementArrowsActor->DisablePartsOnObject();
		movementScalesActor->DisablePartsOnObject();
		rotatedCirclesActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}
	else if (key == ENABLE_MOVEMENT_SCALES)
	{
		movementArrowsActor->DisablePartsOnObject();
		rotatedCirclesActor->DisablePartsOnObject();
		movementScalesActor->EnablePartsOnObject(actors[currentObservedActorIndex]->GetStaticMesh());
	}

	key = NOTHING_KEY;
}

void OnSubEditorKeyCheck()
{
	if (key == ARROW_LEFT_KEY)
	{
		SpawnCubeMenuClass->ClearMenuTypes();
		SpawnSpriteMenuClass->ClearMenuTypes();
		SpawnTriggerMenuClass->ClearMenuTypes();

		currMenuState = EDITOR_STATE::EDITOR;
		currentMenuType = MENU_TYPES::EDITOR_MENU;
	}
	else if (key == 's' || key == 'S')
	{
		SpawnCubeMenuClass->DrawMenuStars();
		SpawnSpriteMenuClass->DrawMenuStars();
		SpawnTriggerMenuClass->DrawMenuStars();
	}
	else if (key == ENTER_KEY)
	{
		SpawnCubeMenuClass->CheckAddMenuTypesToStorage();
		SpawnSpriteMenuClass->CheckAddMenuTypesToStorage();
		SpawnTriggerMenuClass->CheckAddMenuTypesToStorage();

		currMenuState = EDITOR_STATE::GAME;
		currentMenuType = MENU_TYPES::EDITOR_MENU;
	}

	key = NOTHING_KEY;
}

void GetKey()
{
	if (_kbhit())
	{
		key = _getch();
	}
}

void SpawnDefaultFigures()
{
	camActor.AddCamera(new ASpectatorCamera({ 10, 10, 20 }));

	AddActorToStorage(actors, &camActor);

	AddActorToStorage<AMovementArrows>(actors, (AMovementArrows*)(movementArrowsActor = new AMovementArrows));
	typesOfActors.push_back(static_cast<int>(objectType::MOVEMENT_PART));
	AddActorToStorage<AMovementCircles>(actors, (AMovementCircles*)(rotatedCirclesActor = new AMovementCircles));
	typesOfActors.push_back(static_cast<int>(objectType::MOVEMENT_PART));
	AddActorToStorage<AMovementScales>(actors, (AMovementScales*)(movementScalesActor = new AMovementScales));
	typesOfActors.push_back(static_cast<int>(objectType::MOVEMENT_PART));

	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(5, 1000, 1000, { 0, 0, 0 }, 3), ASkyboxPart::FORWARD_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));
	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(1000, 5, 1000, { 0, 0, 0 }, 4), ASkyboxPart::RIGHT_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));
	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(5, 1000, 1000, { 0, 0, 0 }, 3), ASkyboxPart::BACK_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));
	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(1000, 5, 1000, { 0, 0, 0 }, 4), ASkyboxPart::LEFT_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));
	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(1000, 1000, 5, { 0, 0, 0 }, 2), ASkyboxPart::UP_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));
	AddActorToStorage<ASkyboxPart>(actors, new SkyboxPart(1000, 1000, 5, { 0, 0, 0 }, 2), ASkyboxPart::DOWN_PART);
	typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));

	AddActorToStorage<ALightActor>(actors, new Light({ 10000000, {20, -30,45} }), new Circle({ 20, -30,45 }, { 1,0,0 }, "Textures/env_light/env_light0.bmp", 1, 5));
	typesOfActors.push_back(static_cast<int>(objectType::LIGHT));

	AddActorToStorage<ABaseActor>(actors, new Parallelepiped(100, 150, 5, { 80, -80, 0 }, false, false, false, 2));
	typesOfActors.push_back(static_cast<int>(objectType::PARALLELEPIPED));

	currentObservedActorIndex = actors.size() - 1;
}

void MoveCurrentFigure(int currIndex)
{
	actors[currIndex]->GetStaticMesh()->SetCentreCoord() = { moveCurrentFigureConstant * camActor.GetCurrentCamera()->GetVerCamDir().x + camActor.GetCurrentCamera()->GetCameraCoord().x,
			moveCurrentFigureConstant * camActor.GetCurrentCamera()->GetVerCamDir().y + camActor.GetCurrentCamera()->GetCameraCoord().y,
			moveCurrentFigureConstant * camActor.GetCurrentCamera()->GetVerCamDir().z + camActor.GetCurrentCamera()->GetCameraCoord().z };

	actors[currIndex]->GetStaticMesh()->UpdateRange();
	if (actors[currIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED && actors[currIndex]->GetStaticMesh()->IsRotate())
		actors[currIndex]->GetStaticMesh()->Rotation(0.0001f);
}

extern char image[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
extern int imageActorsIndexes[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
void OnGame()
{
	std::clock_t start;
	start = std::clock();

	GetNewMousePos();

	for (size_t i = 0; i < actors.size(); ++i)
		actors[i]->Tick();

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

	Rendering(actors, *camActor.GetCurrentCamera());
	ShowImage();
	actorSelectionState->currentCamRaySymbol = image[(SCREEN_HEIGHT - 2) / 2][(SCREEN_WIDTH - 2) / 2];
	actorSelectionState->currentCamRayActorIntersect = imageActorsIndexes[(SCREEN_HEIGHT - 2) / 2][(SCREEN_WIDTH - 2) / 2];
	ClearImage();

	tick = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	/*SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 20, 0 });
	std::cout << "            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 20, 0 });
	std::cout << tick;*/
}

void IsInBuildMode()
{
	if ((currentGameState == buildModeState || currentGameState == buildModeObjFreezeState) && actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
	{
		if (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[currentObservedActorIndex]->GetStaticMesh())) return;
	}

	if (currentGameState == buildModeState)
		MoveCurrentFigure(currentObservedActorIndex);
}

extern POINT NewMouseCoords;
extern RECT desktop_rect_;
void MenuImpl()
{
	defaultGameState = new GameState();
	actorSelectionState = new ActorSelectionState();
	buildModeState = new BuildModeState();
	buildModeObjFreezeState = new BuildModeObjFreezeState();
	currentGameState = defaultGameState;

	currEditorMenuState = EDITOR_MENU_TYPE::SPAWN_CUBE;
	DrawEditorStars();

	while (true)
	{
		GetKey();

		if (currMenuState == EDITOR_STATE::GAME)
		{
			OnGameKeyCheck();
			IsInBuildMode();
			OnGame();
		}
		else if (currMenuState == EDITOR_STATE::EDITOR)
		{
			OnEditorKeyCheck();

			std::clock_t start;
			start = std::clock();

			GetNewMousePos();

			for (size_t i = 1; i < actors.size(); ++i)
				actors[i]->Tick();

			ClearImage();

			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));

			Rendering(actors, *camActor.GetCurrentCamera());
			ShowImage();

			tick = (std::clock() - start) / (double)CLOCKS_PER_SEC;
		}
		else if (currMenuState == EDITOR_STATE::SUB_EDITOR)
		{
			OnSubEditorKeyCheck();
		}
	}
}