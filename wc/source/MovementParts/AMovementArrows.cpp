
#include <string>
#include "AMovementArrows.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "FileLoader.h"
#include "Triangle.h"
#include "ABaseActor.h"

extern std::vector<AActor*> actors;
extern EDITOR_STATE currMenuState;

std::string AMovementArrows::GetPartName()
{
	return partName;
}

extern RECT desktop_rect_;
void AMovementArrows::SelectedMode()
{
	if (currMenuState == EDITOR_STATE::GAME || (GetKeyState(VK_RBUTTON) & 0x8000))
	{
		SetStandartColorOnPart(partXActorIndex, partXObjParseInfo);
		SetStandartColorOnPart(partYActorIndex, partYObjParseInfo);
		SetStandartColorOnPart(partZActorIndex, partZObjParseInfo);

		currentPartsState = PARTS_STATES::SELECT_MODE;
	}

	if (abs(partNewMouseCoords.x - partOldMouseCoords.x) > abs(desktop_rect_.right - desktop_rect_.left) / 3.0f
		|| abs(partNewMouseCoords.y - partOldMouseCoords.y) > abs(desktop_rect_.bottom - desktop_rect_.top) / 4.0f) return;

	if (currentPartIndex == partXActorIndex)
		currentObservedObj->SetCentreCoord() = { currentObservedObj->GetCentreCoord().x - (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, currentObservedObj->GetCentreCoord().y, currentObservedObj->GetCentreCoord().z };

	if (currentPartIndex == partYActorIndex)
		currentObservedObj->SetCentreCoord() = { currentObservedObj->GetCentreCoord().x, currentObservedObj->GetCentreCoord().y - (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, currentObservedObj->GetCentreCoord().z };

	if (currentPartIndex == partZActorIndex)
		currentObservedObj->SetCentreCoord() = { currentObservedObj->GetCentreCoord().x, currentObservedObj->GetCentreCoord().y, currentObservedObj->GetCentreCoord().z - (partNewMouseCoords.y - partOldMouseCoords.y) / 30.0f };

	currentObservedObj->UpdateRange(currentObservedObj->GetObjType() == objectType::PARALLELEPIPED && currentObservedObj->IsParaboloid() ? 2 : 0);
	if(currentObservedObj->GetObjType() == objectType::PARALLELEPIPED && currentObservedObj->IsRotate())
		currentObservedObj->Rotation(0.0001f);
}

AMovementArrows::AMovementArrows() : partName("arrow"), AMovementParts()
{
	SpawnPartModel("arrowX");
	partXActorIndex = actors.size() - 1;

	SpawnPartModel("arrowY");
	partYActorIndex = actors.size() - 1;

	SpawnPartModel("arrowZ");
	partZActorIndex = actors.size() - 1;

	((Model*)actors[partXActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partYActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partZActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
}