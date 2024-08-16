
#include "GameState.h"
#include "GlobalVars.h"
#include "Preprocessor.h"
#include "ACameraActor.h"

extern std::vector<class AActor*> actors;
extern std::vector<int> typesOfActors;

extern GameState* currentGameState;
extern GameState* defaultGameState;
extern class ActorSelectionState* actorSelectionState;
extern class BuildModeObjFreezeState* buildModeObjFreezeState;
extern EDITOR_STATE currMenuState;
extern int moveCurrentFigureConstant;
extern int currentObservedParalIndex;
extern int currentObservedActorIndex;
extern int currentActorIntersectRayCam;
extern bool isInActorSelectionMode;
extern bool isInBuildModeOnSpawnCube;
extern bool isInBuildModeOnSpawnPyramid;
extern bool isInBuildModeOnSpawnLight;
extern bool isInBuildModeOnSpawnPlayer;
extern char key;

void GameState::OnKeyEsc()
{
	currMenuState = EDITOR_STATE::EDITOR;
}

void GameState::OnEnterKey()
{
	if (currentObservedParalIndex != -1)
		if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
			*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

	currentGameState = defaultGameState;
	currentObservedParalIndex = -1;
	moveCurrentFigureConstant = 5;
	isInBuildModeOnSpawnCube = false;
	isInBuildModeOnSpawnPyramid = false;
	isInBuildModeOnSpawnLight = false;
	isInBuildModeOnSpawnPlayer = false;
}

void GameState::OnLightPowerAndParabRadKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED
		&& *reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedActorIndex]->GetStaticMesh()))
	{
		float& rad = *reinterpret_cast<float*>(sizeof(StaticMesh) + 28 + (char*)actors[currentObservedActorIndex]->GetStaticMesh());

		rad = (key == INC_LIGHT_POWER_KEY ? rad + 0.2
			: ((rad > 1) ? rad - 0.2 : rad));
	}
}

void GameState::OnDeleteKey()
{
	if (currentObservedActorIndex == 1) return;

	if (currentObservedActorIndex == currentObservedParalIndex)
		currentObservedParalIndex = -1;

	currentGameState = (actors.size() - 1 == 1 || typesOfActors[actors.size() - 2 - 1] == (int)objectType::MOVEMENT_PART ? defaultGameState : (GameState*)buildModeObjFreezeState);
	moveCurrentFigureConstant = 5;
	isInBuildModeOnSpawnCube = false;
	isInBuildModeOnSpawnPyramid = false;
	isInBuildModeOnSpawnLight = false;
	isInBuildModeOnSpawnPlayer = false;
	
	//delete actors[currentObservedActorIndex];

	if (actors.size() > 1)
	{
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::ENV_PARTICLES))
		{
			actors.erase(actors.begin() + currentObservedActorIndex);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 1));

			actors.erase(actors.begin() + currentObservedActorIndex);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 1));
		}
		else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
		{
			actors.erase(actors.begin() + currentObservedActorIndex);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 1));

			if (typesOfActors[currentObservedActorIndex - 2] == static_cast<int>(objectType::ENV_PARTICLES))
			{
				actors.erase(actors.begin() + currentObservedActorIndex - 1);
				typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 2));
			}
		}
		else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::ENV_CUBEMAP))
		{
			actors.erase(actors.begin() + currentObservedActorIndex);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 1));

			actors.erase(actors.begin() + currentObservedActorIndex - 1);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 2));

			actors.erase(actors.begin() + currentObservedActorIndex - 2);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 3));
		}
		else
		{
			actors.erase(actors.begin() + currentObservedActorIndex);
			typesOfActors.erase(typesOfActors.begin() + (currentObservedActorIndex - 1));
		}
	}

	currentObservedActorIndex = 1;
}

void GameState::OnRayFromCameraKey()
{
	currentGameState = (GameState*)actorSelectionState;
}