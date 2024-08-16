
#include <string>
#include "AMovementScales.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "FileLoader.h"
#include "Triangle.h"
#include "ABaseActor.h"

extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;
extern EDITOR_STATE currMenuState;

std::string AMovementScales::GetPartName()
{
	return partName;
}

extern RECT desktop_rect_;
void AMovementScales::SelectedMode()
{
	static const int ANGLE_ROTATION_SUM = -2;

	if (currMenuState == EDITOR_STATE::GAME || (GetKeyState(VK_RBUTTON) & 0x8000))
	{
		SetStandartColorOnPart(partXActorIndex, partXObjParseInfo);
		SetStandartColorOnPart(partYActorIndex, partYObjParseInfo);
		SetStandartColorOnPart(partZActorIndex, partZObjParseInfo);

		currentPartsState = PARTS_STATES::SELECT_MODE;
	}

	if (abs(partNewMouseCoords.x - partOldMouseCoords.x) > abs(desktop_rect_.right - desktop_rect_.left) / 3.0f
		|| abs(partNewMouseCoords.y - partOldMouseCoords.y) > abs(desktop_rect_.bottom - desktop_rect_.top) / 4.0f) return;

	if (currentObservedObj->GetObjType() == objectType::PARALLELEPIPED || currentObservedObj->GetObjType() == objectType::PYRAMID)
	{
		if (currentPartIndex == partXActorIndex) currentObservedObj->GetLenght() += (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f;
		else if (currentPartIndex == partYActorIndex) currentObservedObj->GetWidth() += (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f;
		else if (currentPartIndex == partZActorIndex) currentObservedObj->GetHeight() -= (partNewMouseCoords.y - partOldMouseCoords.y) / 30.0f;

		currentObservedObj->GetLenght() = (currentObservedObj->GetLenght() < 0.1f ? 0.1f : currentObservedObj->GetLenght());
		currentObservedObj->GetWidth() = (currentObservedObj->GetWidth() < 0.1f ? 0.1f : currentObservedObj->GetWidth());
		currentObservedObj->GetHeight() = (currentObservedObj->GetHeight() < 0.1f ? 0.1f : currentObservedObj->GetHeight());

		actors[currentObservedActorIndex]->GetStaticMesh()->UpdateRange(1);
		actors[currentObservedActorIndex]->GetStaticMesh()->Rotation(0, ANGLE_ROTATION_SUM);
	}
	else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::MODEL))
	{
		if (currentPartIndex == partZActorIndex)
		{
			if (partNewMouseCoords.y - partOldMouseCoords.y != 0)
				((Model*)currentObservedObj)->SetScale(-(partNewMouseCoords.y - partOldMouseCoords.y) / 30.0f);
		}
		else
		{
			if (partNewMouseCoords.x - partOldMouseCoords.x != 0)
				((Model*)currentObservedObj)->SetScale((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f);
		}
	}
}

AMovementScales::AMovementScales() : partName("scale"), AMovementParts()
{
	SpawnPartModel("scaleX");
	partXActorIndex = actors.size() - 1;

	SpawnPartModel("scaleY");
	partYActorIndex = actors.size() - 1;

	SpawnPartModel("scaleZ");
	partZActorIndex = actors.size() - 1;

	((Model*)actors[partXActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partYActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partZActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
}