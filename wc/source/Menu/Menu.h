#pragma once

#include "GlobalVars.h"
#include "ACameraActor.h"
#include "AMovementParts.h"

extern std::vector<class AActor*> actors;
extern std::vector<int> typesOfActors;

extern void GetNewMousePos();

class GameState* currentGameState;
GameState* defaultGameState;
class ActorSelectionState* actorSelectionState;
class BuildModeState* buildModeState;
class BuildModeObjFreezeState* buildModeObjFreezeState;

ACamerasActor camActor;
AMovementParts* movementArrowsActor;
AMovementParts* rotatedCirclesActor;
AMovementParts* movementScalesActor;

EDITOR_STATE currMenuState = EDITOR_STATE::GAME;
int moveCurrentFigureConstant = 5;
int currentObservedParalIndex = -1;
int currentObservedActorIndex = 0;

void OnGameKeyCheck();

void DrawMenu();

void DrawEditorStars();

void OnEditorKeyCheck();

void OnSubEditorKeyCheck();

void GetKey();

void SpawnDefaultFigures();

void MoveCurrentFigure(int currIndex);

void OnGame();

void IsInBuildMode();

void MenuImpl();