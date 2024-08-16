
#include "AActor.h"

float& AActor::GetCurrentRotateAngle() noexcept
{
    float temp = 0;
    return temp;
}

bool AActor::isActorHasStaticMesh() const noexcept
{
    return false;
}

StaticMesh* AActor::GetStaticMesh() noexcept
{
    return nullptr;
}

bool AActor::isActorHasLight() const noexcept
{
    return false;
}

bool AActor::isActorHasCubemap() const noexcept
{
    return false;
}

StaticMesh* AActor::GetCubemap() noexcept
{
    StaticMesh staticMesh;
    return &staticMesh;
}

void AActor::AttachCubemap(StaticMesh* cubemap)
{ }

bool AActor::isActorHasTrigger() const noexcept
{
    return false;
}

std::vector<std::pair<StaticMesh*, int>> AActor::GetTrigger() noexcept
{
    StaticMesh staticMesh;
    return { {&staticMesh, -1} };
}

void AActor::AttachTrigger(StaticMesh* trigger, int typeOfTrigger)
{ }

void AActor::DetachTrigger(StaticMesh* trigger)
{ }

Light* AActor::GetLight() noexcept
{
    return nullptr;
}