
#include "BuildModeObjFreezeState.h"
#include "GlobalVars.h"
#include "Preprocessor.h"
#include "ACameraActor.h"
#include "Parallelepiped.h"
#include "ABaseActor.h"
#include "MenuTypesDeclares.h"

extern std::vector<class AActor*> actors;
extern std::vector<int> typesOfActors;

extern GameState* currentGameState;
extern GameState* defaultGameState;
extern BuildModeState* buildModeState;
extern class BuildModeObjFreezeState* buildModeObjFreezeState;
extern EDITOR_STATE currMenuState;
extern int moveCurrentFigureConstant;
extern int currentObservedParalIndex;
extern int currentObservedActorIndex;
extern bool isInBuildModeOnSpawnCube;
extern bool isInBuildModeOnSpawnPyramid;
extern bool isInBuildModeOnSpawnLight;
extern bool isInBuildModeOnSpawnPlayer;
extern char key;

void BuildModeObjFreezeState::OnArrowUpDownKey()
{ }

void BuildModeObjFreezeState::OnObjControlKey()
{
	BuildModeState::OnObjControlKey();

	COORDS newCoord = actors[currentObservedActorIndex]->GetStaticMesh()->GetCentreCoord();

	if (key == ARROW_LEFT_KEY) newCoord = { newCoord.x + 0.1f, newCoord.y, newCoord.z };
	else if (key == ARROW_RIGHT_KEY) newCoord = { newCoord.x - 0.1f, newCoord.y, newCoord.z };
	else if (key == 'u') newCoord = { newCoord.x, newCoord.y, newCoord.z + 0.1f };
	else if (key == 'j') newCoord = { newCoord.x, newCoord.y, newCoord.z - 0.1f };

	actors[currentObservedActorIndex]->GetStaticMesh()->SetCentreCoord() = newCoord;
	actors[currentObservedActorIndex]->GetStaticMesh()->UpdateRange();

	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED && actors[currentObservedActorIndex]->GetStaticMesh()->IsRotate())
		actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(0.0001f);
}

void BuildModeObjFreezeState::OnBaseLenghtKey()
{
	BuildModeState::OnBaseLenghtKey();
}

void BuildModeObjFreezeState::OnBaseWidthKey()
{
	BuildModeState::OnBaseWidthKey();
}

void BuildModeObjFreezeState::OnHeightKey()
{
	BuildModeState::OnHeightKey();
}

void BuildModeObjFreezeState::OnAdditionalLengthKey()
{
	BuildModeState::OnAdditionalLengthKey();
}

void BuildModeObjFreezeState::OnAdditionalWidthKey()
{
	BuildModeState::OnAdditionalWidthKey();
}

void BuildModeObjFreezeState::OnZAxisRotationKey()
{
	BuildModeState::OnZAxisRotationKey();
}

void BuildModeObjFreezeState::OnXAxisRotationKey()
{
	BuildModeState::OnXAxisRotationKey();
}

void BuildModeObjFreezeState::OnYAxisRotationKey()
{
	BuildModeState::OnYAxisRotationKey();
}

void BuildModeObjFreezeState::OnLightPowerAndParabRadKey()
{
	BuildModeState::OnLightPowerAndParabRadKey();
}

void BuildModeObjFreezeState::OnFreezeKey()
{
	BuildModeState::OnFreezeKey();
}

void BuildModeObjFreezeState::OnSpawnParabKey()
{
	BuildModeState::OnSpawnParabKey();
}

void BuildModeObjFreezeState::OnColorChangeKey()
{
	BuildModeState::OnColorChangeKey();
}