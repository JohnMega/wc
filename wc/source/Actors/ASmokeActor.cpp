
#include <string>
#include <format>
#include <fstream>
#include "ASmokeActor.h"
#include "ACameraActor.h"

extern ACamerasActor camActor;
extern int currentObservedActorIndex;
extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;

ASmokeActor::ASmokeActor(StaticMesh* staticMesh, Circle* endCircle, int colorIndex)
    : staticMesh(staticMesh)
    , endCircle(endCircle)
    , particleTextureFolder("Textures/env_particles/env_particles")
    , currentColorIndex(colorIndex)
{ }

void ASmokeActor::ChangeParticleColor()
{
    currentColorIndex++;
    std::string newTextureName = particleTextureFolder + std::format("{}", currentColorIndex);

    std::ifstream in(newTextureName + ".bmp");
    if (!in.is_open())
    {
        currentColorIndex = 0;
        newTextureName = particleTextureFolder + std::format("{}", currentColorIndex);
    }

    staticMesh = new Circle(staticMesh->GetCentreCoord(), {1,0,0}, newTextureName + ".bmp", 3, 5);
}

int ASmokeActor::GetCurrentColorIndex() const noexcept
{
    return currentColorIndex;
}

void ASmokeActor::BeginPlay()
{
    endCircle->SetCentreCoord() = { staticMesh->GetCentreCoord().x, staticMesh->GetCentreCoord().y, staticMesh->GetCentreCoord().z + 5};
}

void ASmokeActor::Tick()
{
    reinterpret_cast<Circle*>(staticMesh)->SetNormVec(camActor.GetCurrentCamera()->GetCameraCoord());
}