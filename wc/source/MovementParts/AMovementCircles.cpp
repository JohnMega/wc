
#include <string>
#include "AMovementCircles.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "FileLoader.h"
#include "Triangle.h"
#include "ABaseActor.h"
#include "Parallelepiped.h"
#include "Preprocessor.h"

extern ACamerasActor camActor;
extern int moveCurrentFigureConstant;
extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;
extern EDITOR_STATE currMenuState;

std::string AMovementCircles::GetPartName()
{
	return partName;
}

void AMovementCircles::UpdatePartsCentreCoords()
{
	float dis;
	COORDS currentPartsCentre = camActor.GetCurrentCamera()->GetVerCamDir() * 15 + camActor.GetCurrentCamera()->GetCameraCoord();

	dis = abs(((Model*)actors[partXActorIndex]->GetStaticMesh())->GetModelRange().xEnd - ((Model*)actors[partXActorIndex]->GetStaticMesh())->GetModelRange().xStart);
	actors[partXActorIndex]->GetStaticMesh()->SetCentreCoord() = { currentPartsCentre.x - (dis) / 2.0f
	, currentPartsCentre.y
	, currentPartsCentre.z };
	actors[partXActorIndex]->GetStaticMesh()->UpdateRange();

	dis = abs(((Model*)actors[partYActorIndex]->GetStaticMesh())->GetModelRange().yEnd - ((Model*)actors[partYActorIndex]->GetStaticMesh())->GetModelRange().yStart);
	actors[partYActorIndex]->GetStaticMesh()->SetCentreCoord() = { currentPartsCentre.x
	, currentPartsCentre.y + (dis) / 2.0f
	, currentPartsCentre.z };
	actors[partYActorIndex]->GetStaticMesh()->UpdateRange();

	actors[partZActorIndex]->GetStaticMesh()->SetCentreCoord() = { currentPartsCentre.x - 5
	, currentPartsCentre.y + 5
	, currentPartsCentre.z - 5 };
	actors[partZActorIndex]->GetStaticMesh()->UpdateRange();
}

extern RECT desktop_rect_;
void AMovementCircles::SelectedMode()
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

	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::PARALLELEPIPED) && !currentObservedObj->IsParaboloid())
	{
		if (currentPartIndex == partXActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, 1);

		if (currentPartIndex == partYActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, 0);

		if (currentPartIndex == partZActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, 2);
	}
	else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::MODEL))
	{
		if (currentPartIndex == partXActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, Y_AXIS_ROTATION_KEY);

		if (currentPartIndex == partYActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, X_AXIS_ROTATION_KEY);

		if (currentPartIndex == partZActorIndex)
			currentObservedObj->Rotation((partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f, Z_AXIS_ROTATION_KEY);
	}
	else if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
	{
		if (((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->GetCircleRotateMode() == false)
		{
			COORDS spriteNormVec = ((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->GetNormVec();
			
			if (currentPartIndex == partXActorIndex)
				spriteNormVec = VecYAxisRotation(spriteNormVec, (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f);

			if (currentPartIndex == partYActorIndex)
				spriteNormVec = VecXAxisRotation(spriteNormVec, (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f);

			if (currentPartIndex == partZActorIndex)
				spriteNormVec = VecZAxisRotation(spriteNormVec, (partNewMouseCoords.x - partOldMouseCoords.x) / 30.0f);

			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetCircleRotateMode(true);
			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetNormVec(spriteNormVec + actors[currentObservedActorIndex]->GetStaticMesh()->GetCentreCoord());
			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetCircleRotateMode(false);
		}
	}
}

AMovementCircles::AMovementCircles() : partName("circle"), AMovementParts()
{
	SpawnPartModel("circleX");
	partXActorIndex = actors.size() - 1;

	SpawnPartModel("circleY");
	partYActorIndex = actors.size() - 1;

	SpawnPartModel("circleZ");
	partZActorIndex = actors.size() - 1;

	((Model*)actors[partXActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partYActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partZActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
}