
#include <string>
#include <iomanip>
#include <Windows.h>
#include "ASimple.h"
#include "ACameraActor.h"
#include "Circle.h"

extern ACamerasActor camActor;

ASimple::ASimple(StaticMesh* staticMesh)
    : staticMesh(staticMesh)
{ }

void ASimple::BeginPlay()
{ }

void ASimple::Tick()
{
    if (staticMesh->GetObjType() == objectType::MODEL)
    {
        reinterpret_cast<Model*>(staticMesh)->AnimationHandle();
    }
    else if (staticMesh->GetObjType() == objectType::CIRCLE)
    {
        reinterpret_cast<Circle*>(staticMesh)->SetNormVec(camActor.GetCurrentCamera()->GetCameraCoord());
    }
}