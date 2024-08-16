
#include "BuildModeState.h"
#include "GlobalVars.h"
#include "Preprocessor.h"
#include "ACameraActor.h"
#include "Parallelepiped.h"
#include "ABaseActor.h"
#include "ASmokeActor.h"
#include "Circle.h"
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

void BuildModeState::OnArrowUpDownKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
	{
		if (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[currentObservedActorIndex]->GetStaticMesh())) return;
	}

	moveCurrentFigureConstant = (key == ARROW_UP_KEY ? moveCurrentFigureConstant + 1
		: ((moveCurrentFigureConstant > 1) ? moveCurrentFigureConstant - 1 : moveCurrentFigureConstant));
}

void BuildModeState::OnObjControlKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
	{
		if (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[currentObservedActorIndex]->GetStaticMesh())) return;
	}
}

void BuildModeState::OnBaseLenghtKey()
{
	SizeKeyImpl(BASE_LENGTH_INC_KEY, 0);
}

void BuildModeState::OnBaseWidthKey()
{
	SizeKeyImpl(BASE_WIDTH_INC_KEY, 4);
}

void BuildModeState::OnHeightKey()
{
	SizeKeyImpl(HEIGHT_INC_KEY, 8);
}

void BuildModeState::OnAdditionalLengthKey()
{
	SizeKeyImpl(ADDITIONAL_LENGTH_INC_KEY, 12);
}

void BuildModeState::OnAdditionalWidthKey()
{
	SizeKeyImpl(ADDITIONAL_WIDTH_INC_KEY, 16);
}

void BuildModeState::OnZAxisRotationKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED) //&& *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) == *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + 4))
		RotationKeyImpl(0);
	else if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::MODEL)
		actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(1, Z_AXIS_ROTATION_KEY);
}

void BuildModeState::OnXAxisRotationKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
		RotationKeyImpl(1);
	else if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::MODEL)
		actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(1, X_AXIS_ROTATION_KEY);
}

void BuildModeState::OnYAxisRotationKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
		RotationKeyImpl(2);
	else if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::MODEL)
		actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(1, Y_AXIS_ROTATION_KEY);
}

void BuildModeState::OnLightPowerAndParabRadKey()
{
	GameState::OnLightPowerAndParabRadKey();

	LightPowerImpl(INC_LIGHT_POWER_KEY);
}

void BuildModeState::OnFreezeKey()
{
	currentGameState = (currentGameState == (GameState*)buildModeObjFreezeState ? buildModeState : (GameState*)buildModeObjFreezeState);
}

void BuildModeState::OnSpawnParabKey()
{
	if (currentObservedParalIndex == -1) return;

	if (actors[currentObservedParalIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
	{
		if (!*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh())) return;

		float rad = *reinterpret_cast<float*>(sizeof(StaticMesh) + 28 + (char*)actors[currentObservedParalIndex]->GetStaticMesh());

		COORDS parabCoords = *reinterpret_cast<COORDS*>(sizeof(StaticMesh) + 32 + (char*)actors[currentObservedParalIndex]->GetStaticMesh());
		AddActorToStorage<ABaseActor>(actors, new Parallelepiped(rad * 2, rad * 2, 1, { parabCoords.x, parabCoords.y, parabCoords.z }, false, false, false, actors[currentObservedParalIndex]->GetStaticMesh()->GetColor()));
		typesOfActors.push_back(static_cast<int>(objectType::PARALLELEPIPED));
		currentObservedActorIndex = actors.size() - 1;

		*reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) = true;
		*reinterpret_cast<Range*>(sizeof(StaticMesh) + (32 + sizeof(COORDS)) + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) = actors[currentObservedParalIndex]->GetStaticMesh()->GetRange();
	}
}

void BuildModeState::LightPowerImpl(char keyIndex)
{
	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::LIGHT))
	{
		int& IValue = *reinterpret_cast<int*>(actors[currentObservedActorIndex]->GetLight());

		IValue = (key == keyIndex ? IValue + 10
			: ((IValue > 10) ? IValue - 10 : IValue));
	}
	else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
	{
		float oldRad = ((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->GetRad();
		float newRad = (key == keyIndex ? oldRad + 0.1f
			: ((oldRad > 0.2f) ? oldRad - 0.1f : oldRad));

		((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetRad(newRad);
	}
}

void BuildModeState::SizeKeyImpl(char keyIndex, int actorPtrConstant)
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PYRAMID)
	{
		float& sizeField = *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + actorPtrConstant);

		sizeField = (key == keyIndex ? sizeField + 0.1f
			: ((sizeField > 1) ? sizeField - 0.1f : sizeField));

		actors[currentObservedActorIndex]->GetStaticMesh()->UpdateRange();
	}
}

void BuildModeState::RotationKeyImpl(int actorPtrConstant)
{
	if (!isInBuildModeOnSpawnPlayer && !isInBuildModeOnSpawnPyramid)
	{
		if (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[currentObservedActorIndex]->GetStaticMesh())) return;

		bool& ZRotationField = *reinterpret_cast<bool*> (sizeof(StaticMesh) + 12 + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + 0);
		bool& XRotationField = *reinterpret_cast<bool*> (sizeof(StaticMesh) + 12 + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + 1);
		bool& YRotationField = *reinterpret_cast<bool*> (sizeof(StaticMesh) + 12 + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + 2);

		if ((int)*reinterpret_cast<float*> (sizeof(StaticMesh) + 16 + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) % 181 == 0 &&
			*reinterpret_cast<float*> (sizeof(StaticMesh) + 16 + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) > 0)
		{
			ZRotationField = XRotationField = YRotationField = false;
			*reinterpret_cast<float*> (sizeof(StaticMesh) + 16 + (char*)actors[currentObservedActorIndex]->GetStaticMesh()) = 0;
			actors[currentObservedActorIndex]->GetStaticMesh()->UpdateRange(1);
		}

		bool& CurrentRotationField = *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[currentObservedActorIndex]->GetStaticMesh() + actorPtrConstant);
		if (!actors[currentObservedActorIndex]->GetStaticMesh()->IsRotate() || CurrentRotationField)
		{
			if (!CurrentRotationField)
			{
				CurrentRotationField = true;
				actors[currentObservedActorIndex]->GetStaticMesh()->UpdateRange(1);
			}
			actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(1);
		}
	}
}

void BuildModeState::OnColorChangeKey()
{
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::CIRCLE && actors[currentObservedActorIndex]->isActorHasLight())
		((ALightActor*)actors[currentObservedActorIndex])->ChangeLightTexture();
	else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::ENV_PARTICLES))
		((ASmokeActor*)actors[currentObservedActorIndex])->ChangeParticleColor();
	else
		actors[currentObservedActorIndex]->GetStaticMesh()->SetColor() = (actors[currentObservedActorIndex]->GetStaticMesh()->GetColor() == 8 ? 1 : actors[currentObservedActorIndex]->GetStaticMesh()->GetColor() + 1);
}