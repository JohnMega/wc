#pragma once
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"
#include "Circle.h"

class ASmokeActor : public AActor
{
private:
    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

    std::string particleTextureFolder;
    int currentColorIndex;
    Circle* endCircle;

public:
    ASmokeActor(StaticMesh* staticMesh, Circle* endCircle, int colorIndex = 0);

    void ChangeParticleColor();

    int GetCurrentColorIndex() const noexcept;

    void BeginPlay() override;

    void Tick() override;
};