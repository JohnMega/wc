
#include <string>
#include <iomanip>
#include <Windows.h>
#include "ATriggerLine.h"
#include "ACameraActor.h"
#include "Circle.h"
#include "ABaseActor.h"

extern ACamerasActor camActor;
extern int currentObservedActorIndex;

ATriggerLine::ATriggerLine(StaticMesh* trigger, int typeOfTrigger, AdditionalTriggerInfo* additTriggerInfo)
	: trigger(trigger)
	, typeOfTrigger(typeOfTrigger)
	, observedObj(this)
	, additTriggerInfo(additTriggerInfo)
{
	Model* model = new Model;
	linePart1 = new Triangle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, model, { 0,0,0 });
	linePart1->SetTextureParams("Textures/PartYColor.bmp", { 0,1,0 }, { 1,1,0 }, { 1,0,0 });
	AddActorToStorage<ABaseActor>(actors, linePart1);
	typesOfActors.push_back(static_cast<int>(objectType::TRIANGLE));

	linePart2 = new Triangle({ 0,0,0 }, { 0,0,0 }, { 0,0,0 }, model, { 0,0,0 });
	linePart2->SetTextureParams("Textures/PartYColor.bmp", { 0,1,0 }, { 1,1,0 }, { 1,0,0 });
	AddActorToStorage<ABaseActor>(actors, linePart2);
	typesOfActors.push_back(static_cast<int>(objectType::TRIANGLE));
}

ATriggerLine::ATriggerLine(StaticMesh* trigger, int typeOfTrigger, AdditionalTriggerInfo* additTriggerInfo, AActor* observedObj) 
	: ATriggerLine(trigger, typeOfTrigger, additTriggerInfo)
{
	this->observedObj = observedObj;
	this->observedObj->AttachTrigger(trigger, typeOfTrigger);
}

bool ATriggerLine::IsDotInRange(COORDS dot, Range objRange) const noexcept
{
	if (dot.x >= objRange.xStart && dot.x <= objRange.xEnd && dot.y >= objRange.yStart && dot.y <= objRange.yEnd
		&& dot.z >= objRange.zStart && dot.z <= objRange.zEnd)
		return true;

	return false;
}

void ATriggerLine::DeleteThisActor()
{
	int thisActorIndex;
	for (size_t i = 1; i < actors.size(); ++i)
	{
		if (actors[i] == this)
		{
			thisActorIndex = i;
			break;
		}
	}

	actors.erase(actors.begin() + thisActorIndex);
	typesOfActors.erase(typesOfActors.begin() + (thisActorIndex - 1));

	actors.erase(actors.begin() + thisActorIndex - 1);
	typesOfActors.erase(typesOfActors.begin() + (thisActorIndex - 2));

	actors.erase(actors.begin() + thisActorIndex - 2);
	typesOfActors.erase(typesOfActors.begin() + (thisActorIndex - 3));
}

void ATriggerLine::BeginPlay()
{ }

void ATriggerLine::Tick()
{
	if (observedObj == this)
	{
		currentObservedActorIndex = 1;

		COORDS endDot = camActor.GetCurrentCamera()->GetVerCamDir() * 1 + camActor.GetCurrentCamera()->GetCameraCoord();
		linePart1->SetNewSurfaceDots(endDot, endDot + 0.1f, trigger->GetCentreCoord());
		linePart2->SetNewSurfaceDots(trigger->GetCentreCoord(), trigger->GetCentreCoord() + 0.1f, endDot);

		if (currentGameState == defaultGameState)
		{
			for (size_t i = 1; i < actors.size(); ++i)
			{
				if (actors[i] == this) continue;

				if (actors[i]->isActorHasStaticMesh() && actors[i]->isActorHasTrigger())
				{
					Range currObjRange;
					if (typesOfActors[i - 1] == (int)objectType::MODEL)
						currObjRange = ((Model*)actors[i]->GetStaticMesh())->GetModelRange();
					else if (actors[i]->GetStaticMesh()->GetObjType() == objectType::CIRCLE)
						currObjRange = ((Circle*)actors[i]->GetStaticMesh())->GetCircleRange();
					else
						currObjRange = actors[i]->GetStaticMesh()->GetRange();

					if (IsDotInRange(linePart1->GetSurfaceDot1(), currObjRange))
					{
						observedObj = actors[i];
						break;
					}
				}
			}

			// delete this object if goal obj was not found
			if (observedObj == this)
			{
				DeleteThisActor();
			}
			else
				observedObj->AttachTrigger(trigger, typeOfTrigger);
		}
	}
	else
	{
		linePart1->SetNewSurfaceDots(observedObj->GetStaticMesh()->GetCentreCoord(), observedObj->GetStaticMesh()->GetCentreCoord() + 0.1f, trigger->GetCentreCoord());
		linePart2->SetNewSurfaceDots(trigger->GetCentreCoord(), trigger->GetCentreCoord() + 0.1f, observedObj->GetStaticMesh()->GetCentreCoord());
	
		bool isObservedObjAvailable = false, isTriggerAvailable = false;
		for (size_t i = 0; i < actors.size(); ++i)
		{
			if (actors[i]->isActorHasStaticMesh())
				if (actors[i]->GetStaticMesh() == trigger) isTriggerAvailable = true;

			if (actors[i] == observedObj) isObservedObjAvailable = true;
		}

		if (!isObservedObjAvailable || !isTriggerAvailable)
		{
			if(!isTriggerAvailable)
			for (size_t i = 0; i < actors.size(); ++i)
			{
				if (actors[i]->isActorHasTrigger())
					actors[i]->DetachTrigger(trigger);
			}

			DeleteThisActor();
		}
	}
}