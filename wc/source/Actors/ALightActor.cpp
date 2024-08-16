
#include <fstream>
#include <format>
#include "ALightActor.h"
#include "Circle.h"
#include "ACameraActor.h"
#include "Preprocessor.h"

extern ACamerasActor camActor;

ALightActor::ALightActor(Light* lightSource, StaticMesh* staticMesh, int currentLightTextureIndex) 
    : lightSource(lightSource)
    , staticMesh(staticMesh)
    , currentLightTextureIndex(currentLightTextureIndex)
{
    lightColors.push_back({ 0,0,0 });
    lightColors.push_back({74,82,7});
    lightColors.push_back({ 82,44,7 });
    lightColors.push_back({ 7,82,19 });
}

void ALightActor::ChangeLightTexture()
{
    currentLightTextureIndex++;
    std::string newTextureName = lightTexturesFolder + std::format("{}", currentLightTextureIndex);

    std::ifstream in(newTextureName + ".bmp");
    if (!in.is_open())
    {
        currentLightTextureIndex = 0;
        newTextureName = lightTexturesFolder + std::format("{}", currentLightTextureIndex);
    }

    staticMesh = new Circle(lightSource->GetCoord(), { 1,0,0 }, newTextureName + ".bmp", 1, 5);
}

COORDS ALightActor::GetLightColor() const noexcept
{
    return lightColors[currentLightTextureIndex];
}

int ALightActor::GetCurrentLightTextureIndex() const noexcept
{
    return currentLightTextureIndex;
}

void ALightActor::BeginPlay()
{

}

void ALightActor::Tick()
{
    if (staticMesh->GetObjType() == objectType::CIRCLE)
    {
        reinterpret_cast<Circle*>(staticMesh)->SetNormVec(camActor.GetCurrentCamera()->GetCameraCoord());
    }
    
    lightSource->SetCoord() = staticMesh->GetCentreCoord();
}