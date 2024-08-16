#pragma once
#include "Preprocessor.h"
#include "Light.h"
#include "AActor.h"

class ALightActor : public AActor
{
private:
    UPROPERTY(Light, lightSource)
    Light* lightSource;

    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

    std::string lightTexturesFolder = "Textures/env_light/env_light";
    std::vector<COORDS> lightColors;
    int currentLightTextureIndex = 0;

public:
    ALightActor(Light* lightSource, StaticMesh* staticMesh, int currentLightTextureIndex = 0);

    int GetCurrentLightTextureIndex() const noexcept;

    COORDS GetLightColor() const noexcept;

    void ChangeLightTexture();

    void BeginPlay() override;

    void Tick() override;
};