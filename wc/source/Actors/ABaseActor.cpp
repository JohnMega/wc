
#include <string>
#include <iomanip>
#include <Windows.h>
#include "ABaseActor.h"
#include "ACameraActor.h"
#include "Circle.h"

extern ACamerasActor camActor;
extern std::vector<int> typesOfActors;

ABaseActor::ABaseActor(StaticMesh* staticMesh) 
    : staticMesh(staticMesh)
    , isStaticMeshInfoOuted(false)
    , currentCubemap(nullptr)
{ }

float& ABaseActor::GetCurrentRotateAngle() noexcept
{
    return currentRotateAngle;
}

void ABaseActor::OutStaticMeshInfo()
{
    bool isOutInfoCentreChanges = (staticMesh->GetCentreCoord() != outInformation.centreCoord);
    bool isOutInfoParalChanges = (staticMesh->GetLenght() != outInformation.length || staticMesh->GetWidth() != outInformation.width || staticMesh->GetHeight() != outInformation.height);

    if (actors[currentObservedActorIndex]->GetStaticMesh() == staticMesh)
    {
        if (isOutInfoCentreChanges)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 0 });
            std::cout << "                                 ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 0 });
            std::cout << "Centre: " << std::setprecision(5) << staticMesh->GetCentreCoord().x << ' ' << staticMesh->GetCentreCoord().y << ' ' << staticMesh->GetCentreCoord().z;
        }

        if (staticMesh->GetObjType() == objectType::PARALLELEPIPED && isOutInfoParalChanges)
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 1 });
            std::cout << "                                 ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 1 });
            std::cout << "Length: " << staticMesh->GetLenght();

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 2 });
            std::cout << "                                 ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 2 });
            std::cout << "Width: " << staticMesh->GetWidth();

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 3 });
            std::cout << "                                 ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 23, 3 });
            std::cout << "Height: " << staticMesh->GetHeight();
        }
    }
}

void ABaseActor::BeginPlay()
{ }

void ABaseActor::Tick()
{
    OutStaticMeshInfo();
    CubemapActiveCheck();

    if (actors[currentObservedActorIndex]->GetStaticMesh() == staticMesh)
    {
        outInformation.centreCoord = staticMesh->GetCentreCoord();

        if (staticMesh->GetObjType() == objectType::PARALLELEPIPED)
        {
            outInformation.length = staticMesh->GetLenght();
            outInformation.width = staticMesh->GetWidth();
            outInformation.height = staticMesh->GetHeight();
        }
    }
    else
    {
        outInformation.centreCoord = {0,0,0};
        outInformation.length = 0;
        outInformation.width = 0;
        outInformation.height = 0;
    }

    if (staticMesh->GetObjType() == objectType::MODEL)
    {
        reinterpret_cast<Model*>(staticMesh)->AnimationHandle();
    }
    else if (staticMesh->GetObjType() == objectType::CIRCLE)
    {
        reinterpret_cast<Circle*>(staticMesh)->SetNormVec(camActor.GetCurrentCamera()->GetCameraCoord());
    }
}