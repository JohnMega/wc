#pragma once
#include <vector>
#include <utility>
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"

extern std::vector<AActor*> actors;
extern int currentObservedActorIndex;

class ABaseActor : public AActor
{
    struct OutInformation
    {
        COORDS centreCoord;
        float length, width, height;
    };

private:
    UPROPERTY(StaticMesh, staticMesh)
    StaticMesh* staticMesh;

    DEFINE_CUBEMAP()
    DEFINE_TRIGGER()

    OutInformation outInformation;
    bool isStaticMeshInfoOuted;
    float currentRotateAngle = 0;

private:
    void OutStaticMeshInfo();

public:
    ABaseActor(StaticMesh* staticMesh);

    float& GetCurrentRotateAngle() noexcept override;

    void BeginPlay() override;

    void Tick() override;
};