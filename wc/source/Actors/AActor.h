#pragma once

#include "Light.h"
#include "StaticMesh.h"

class AActor
{
public:
    virtual ~AActor() = default;

    virtual bool isActorHasStaticMesh() const noexcept;

    virtual StaticMesh* GetStaticMesh() noexcept;

    virtual bool isActorHasLight() const noexcept;

    virtual Light* GetLight() noexcept;

    virtual bool isActorHasCubemap() const noexcept;

    virtual StaticMesh* GetCubemap() noexcept;

    virtual void AttachCubemap(StaticMesh* cubemap);

    virtual bool isActorHasTrigger() const noexcept;

    virtual std::vector<std::pair<StaticMesh*, int>> GetTrigger() noexcept;

    virtual void AttachTrigger(StaticMesh* trigger, int typeOfTrigger);

    virtual void DetachTrigger(StaticMesh* trigger);

    virtual float& GetCurrentRotateAngle() noexcept;

    virtual void BeginPlay() = 0;

    virtual void Tick() = 0;
};