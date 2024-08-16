#pragma once

#include "GameState.h"

class ActorSelectionState : public GameState
{

public:
	char currentCamRaySymbol = ' ';
	int currentCamRayActorIntersect = 0;

public:
	void OnEnterKey() override;
};