
#include <vector>
#include <iostream>
#include "ActorSelectionState.h"
#include "GlobalVars.h"

extern std::vector<class AActor*> actors;

extern GameState* currentGameState;
extern class BuildModeObjFreezeState* buildModeObjFreezeState;
extern int currentObservedActorIndex;
extern std::vector<int> typesOfActors;

void ActorSelectionState::OnEnterKey()
{
	GameState::OnEnterKey();

	if (currentCamRaySymbol != ' ' && typesOfActors[currentCamRayActorIntersect - 1] != static_cast<int>(objectType::MOVEMENT_PART)
		&& typesOfActors[currentCamRayActorIntersect - 1] != static_cast<int>(objectType::TRIANGLE))
	{
		currentObservedActorIndex = currentCamRayActorIntersect;
		currentGameState = (GameState*)buildModeObjFreezeState;
	}
	else
		currentObservedActorIndex = actors.size() - 1;
}