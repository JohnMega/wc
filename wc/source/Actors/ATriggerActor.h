#pragma once
#include <vector>
#include <utility>
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"

extern std::vector<AActor*> actors;
extern int currentObservedActorIndex;

class ATriggerActor : public AActor
{
private:
    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

public:
    COORDS observedObjCentreCoord = {0,0,0};

public:
    ATriggerActor(StaticMesh* staticMesh);

    void BeginPlay() override;

    void Tick() override;
};