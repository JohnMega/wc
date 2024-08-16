
#include <string>
#include <iomanip>
#include <Windows.h>
#include "ATriggerActor.h"
#include "ACameraActor.h"
#include "Circle.h"

extern ACamerasActor camActor;
extern std::vector<int> typesOfActors;

ATriggerActor::ATriggerActor(StaticMesh* staticMesh)
    : staticMesh(staticMesh)
{ }

void ATriggerActor::BeginPlay()
{ }

void ATriggerActor::Tick()
{ }