#pragma once
#include <vector>
#include <utility>
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"

class ASimple : public AActor
{
private:
    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

public:
    ASimple(StaticMesh* staticMesh);

    void BeginPlay() override;

    void Tick() override;
};