#pragma once
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"
#include "Triangle.h"
#include "Cubemap.h"

class ACubemapActor : public AActor
{
private:
    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

    Triangle* linePart1, *linePart2;
    AActor* observedObj;

private:
    void AttachCubemapWithOtherObj();

    void Attaching();

public:
    ACubemapActor(Cubemap* staticMesh);

    ACubemapActor(Cubemap* staticMesh, AActor* observedObj);

    void BeginPlay() override;

    void Tick() override;
};