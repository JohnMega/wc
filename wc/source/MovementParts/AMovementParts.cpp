
#include <string>
#include "AMovementParts.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "FileLoader.h"
#include "Triangle.h"
#include "ABaseActor.h"

extern ACamerasActor camActor;
extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;
extern EDITOR_STATE currMenuState;

std::string AMovementParts::GetPartName()
{
	return partName;
}

void AMovementParts::SpawnPartModel(std::string partName)
{
	std::string fileName = partName;
	std::string objFileNameWithExtensions = "Models/" + GetPartName() + "s/";
	objFileNameWithExtensions += fileName;

	Model* model = new Model;
	ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)).c_str(), objFileNameWithExtensions.c_str());
	if (partName == GetPartName() + "X") partXObjParseInfo = objParseInfo;
	else if (partName == GetPartName() + "Y") partYObjParseInfo = objParseInfo;
	else if (partName == GetPartName() + "Z") partZObjParseInfo = objParseInfo;

	for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
	{
		model->GetModelPolygons().push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
		((Triangle*)model->GetModelPolygons().back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
	}

	model->UpdateRange();
	model->SetFileName() = fileName;
	AddActorToStorage<ABaseActor>(actors, model);
	typesOfActors.push_back(static_cast<int>(objectType::MOVEMENT_PART));

	size_t verticesSize = objParseInfo.vertices.size();
	size_t facesSize = objParseInfo.faceIndex.size();
	size_t texturesSize = objParseInfo.textures.size();
	size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
	for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
	for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
	for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
	for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
}

void AMovementParts::SetSelectedColorOnPart(int partIndex, ObjParseInfo partObjParseInfo)
{
	Model* model = (Model*)actors[partIndex]->GetStaticMesh();
	for (size_t i = 0; i < partObjParseInfo.faceIndex.size(); ++i)
		((Triangle*)model->GetModelPolygons()[i])->SetTextureParams("Textures/PartSelectedColor.bmp", partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].x], partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].y], partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].z]);
}

void AMovementParts::SetStandartColorOnPart(int partIndex, ObjParseInfo partObjParseInfo)
{
	Model* partXModel = (Model*)actors[partIndex]->GetStaticMesh();
	for (size_t i = 0; i < partObjParseInfo.faceIndex.size(); ++i)
		((Triangle*)partXModel->GetModelPolygons()[i])->SetTextureParams(partObjParseInfo.facesTextureNames[i], partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].x], partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].y], partObjParseInfo.textures[partObjParseInfo.faceIndex[i][1].z]);
}

void AMovementParts::UpdatePartsCentreCoords()
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

	dis = abs(((Model*)actors[partZActorIndex]->GetStaticMesh())->GetModelRange().zEnd - ((Model*)actors[partZActorIndex]->GetStaticMesh())->GetModelRange().zStart);
	actors[partZActorIndex]->GetStaticMesh()->SetCentreCoord() = { currentPartsCentre.x
	, currentPartsCentre.y
	, currentPartsCentre.z + (dis) / 2.0f };
	actors[partZActorIndex]->GetStaticMesh()->UpdateRange();
}

void AMovementParts::ClearAllPartInfo()
{
	((Model*)actors[partXActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partYActorIndex]->GetStaticMesh())->SetModelRenderMode(false);
	((Model*)actors[partZActorIndex]->GetStaticMesh())->SetModelRenderMode(false);

	currentPartIndex = -1;
	currentPartsState = PARTS_STATES::SELECT_MODE;
	currentObservedObj = nullptr;
	currentObservedObjIndex = -1;
}

AMovementParts::AMovementParts()
	: currentPartIndex(-1)
	, currentPartsState(PARTS_STATES::SELECT_MODE)
	, currentObservedObj(nullptr)
	, currentObservedObjIndex(-1)
{ }

extern int imageActorsIndexes[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
extern RECT desktop_rect_;
void AMovementParts::SelectMode()
{
	int mouseX = (partNewMouseCoords.x - desktop_rect_.left) / 8 - 2;
	int mouseY = (partNewMouseCoords.y - desktop_rect_.top) / 16 - 3;

	if (mouseX >= 0 && mouseX < SCREEN_WIDTH - 2 && mouseY >= 0 && mouseY < SCREEN_HEIGHT - 2)
	{
		int actorIndex = imageActorsIndexes[mouseY][mouseX];
		if ((actorIndex >= 0 && actorIndex < actors.size()) && typesOfActors[actorIndex - 1] == static_cast<int>(objectType::MOVEMENT_PART))
		{
			currentPartIndex = actorIndex;
			if (actorIndex == partXActorIndex) SetSelectedColorOnPart(partXActorIndex, partXObjParseInfo);
			else if (actorIndex == partYActorIndex) SetSelectedColorOnPart(partYActorIndex, partYObjParseInfo);
			else if (actorIndex == partZActorIndex) SetSelectedColorOnPart(partZActorIndex, partZObjParseInfo);
		}
		else
		{
			currentPartIndex = -1;
			SetStandartColorOnPart(partXActorIndex, partXObjParseInfo);
			SetStandartColorOnPart(partYActorIndex, partYObjParseInfo);
			SetStandartColorOnPart(partZActorIndex, partZObjParseInfo);
		}
	}

	if (GetKeyState(VK_LBUTTON) & 0x8000)
	{
		if (currentPartIndex != -1) currentPartsState = PARTS_STATES::SELECTED;
	}
}

void AMovementParts::EnablePartsOnObject(StaticMesh* object)
{
	if (currentObservedObjIndex != -1)
	{
		ClearAllPartInfo();
		return;
	}

	currentObservedObjIndex = currentObservedActorIndex;
	currentObservedObj = actors[currentObservedObjIndex]->GetStaticMesh();
	
	UpdatePartsCentreCoords();

	((Model*)actors[partXActorIndex]->GetStaticMesh())->SetModelRenderMode(true);
	((Model*)actors[partYActorIndex]->GetStaticMesh())->SetModelRenderMode(true);
	((Model*)actors[partZActorIndex]->GetStaticMesh())->SetModelRenderMode(true);
}

void AMovementParts::DisablePartsOnObject()
{
	ClearAllPartInfo();
}

void AMovementParts::BeginPlay()
{ }

void AMovementParts::Tick()
{
	partOldMouseCoords = partNewMouseCoords;
	GetCursorPos(&partNewMouseCoords);

	if (currentObservedObj != nullptr)
	{
		if (currMenuState == EDITOR_STATE::GAME || currentPartsState == PARTS_STATES::SELECTED)
			UpdatePartsCentreCoords();

		if (currentPartsState == PARTS_STATES::SELECT_MODE) SelectMode();
		else if (currentPartsState == PARTS_STATES::SELECTED) SelectedMode();

		if (currentObservedObjIndex != currentObservedActorIndex)
		{
			ClearAllPartInfo();
		}
	}
}