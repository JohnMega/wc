
#include <string>
#include <iomanip>
#include <Windows.h>
#include "ACubemapActor.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "ABaseActor.h"
#include "GameState.h"

extern ACamerasActor camActor;
extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;
extern int currentObservedActorIndex;

ACubemapActor::ACubemapActor(Cubemap* staticMesh)
    : staticMesh((Circle*)staticMesh)
	, observedObj(this)
{
	Model* model = new Model;
	linePart1 = new Triangle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, model, { 0,0,0 });
	linePart1->SetTextureParams("Textures/PartXColor.bmp", { 0,1,0 }, { 1,1,0 }, { 1,0,0 });
	AddActorToStorage<ABaseActor>(actors, linePart1);
	typesOfActors.push_back(static_cast<int>(objectType::TRIANGLE));

	linePart2 = new Triangle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, model, { 0,0,0 });
	linePart2->SetTextureParams("Textures/PartXColor.bmp", { 0,1,0 }, { 1,1,0 }, { 1,0,0 });
	AddActorToStorage<ABaseActor>(actors, linePart2);
	typesOfActors.push_back(static_cast<int>(objectType::TRIANGLE));
}

ACubemapActor::ACubemapActor(Cubemap* staticMesh, AActor* observedObj) : ACubemapActor(staticMesh)
{
	this->observedObj = observedObj;
	this->observedObj->AttachCubemap(staticMesh);
}

void ACubemapActor::AttachCubemapWithOtherObj()
{
	float minDist = 10000;
	for (size_t i = 1; i < actors.size(); ++i)
	{
		if (!(typesOfActors[i - 1] != (int)objectType::ENV_CUBEMAP && typesOfActors[i - 1] != (int)objectType::ENV_PARTICLES && typesOfActors[i - 1] != (int)objectType::LIGHT
			&& typesOfActors[i - 1] != (int)objectType::MOVEMENT_PART && typesOfActors[i - 1] != (int)objectType::SKYBOX && typesOfActors[i - 1] != (int)objectType::TRIANGLE)) continue;
		if (!actors[i]->isActorHasStaticMesh() || actors[i]->isActorHasCubemap() || actors[i] == this) continue;

		float dist = dotDistance(staticMesh->GetCentreCoord(), actors[i]->GetStaticMesh()->GetCentreCoord());
		if (dist < minDist)
		{
			minDist = dist;
			observedObj = actors[i];
		}
	}

	if (minDist != 10000)
		observedObj->AttachCubemap(staticMesh);
	else
		observedObj = this;
}

void ACubemapActor::Attaching()
{
	bool isCubemapNeedToAttach = true;
	for (size_t i = 1; i < actors.size(); ++i)
	{
		if (actors[i] == this) continue;

		if (actors[i] == observedObj)
		{
			isCubemapNeedToAttach = false;
			break;
		}
	}

	if (isCubemapNeedToAttach) AttachCubemapWithOtherObj();
}

void ACubemapActor::BeginPlay()
{ }

void ACubemapActor::Tick()
{
	reinterpret_cast<Circle*>(staticMesh)->SetNormVec(camActor.GetCurrentCamera()->GetCameraCoord());

	if(!(staticMesh->GetCentreCoord().x == 0 && staticMesh->GetCentreCoord().y == 0 && staticMesh->GetCentreCoord().z == 0))
		Attaching();

	linePart1->SetNewSurfaceDots(observedObj->GetStaticMesh()->GetCentreCoord(), observedObj->GetStaticMesh()->GetCentreCoord() + 0.1f, staticMesh->GetCentreCoord());
	linePart2->SetNewSurfaceDots(staticMesh->GetCentreCoord(), staticMesh->GetCentreCoord() + 0.1f, observedObj->GetStaticMesh()->GetCentreCoord());
}