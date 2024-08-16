#pragma once

#define DEFINE_FUNCTION(Name) void Name(Stack& stack)

#define INCLUDE_FUNCTION(FuncName) funcTable.push_back(FuncName)

std::vector<void (*)(class Stack&)> funcTable;

DEFINE_FUNCTION(ExPar);
DEFINE_FUNCTION(ExPyramid);
DEFINE_FUNCTION(ExLight);
DEFINE_FUNCTION(ExPlayer);
DEFINE_FUNCTION(ExTriangle);
DEFINE_FUNCTION(ExModel);
DEFINE_FUNCTION(ExSkybox);
DEFINE_FUNCTION(ExFire);
DEFINE_FUNCTION(ExCircle);
DEFINE_FUNCTION(ExSmoke);
DEFINE_FUNCTION(ExMovementPart);
DEFINE_FUNCTION(ExCubemap);
DEFINE_FUNCTION(ExClipWall);
DEFINE_FUNCTION(ExTrigger);
DEFINE_FUNCTION(ExAreaPortal);
DEFINE_FUNCTION(ExEnvShake);
DEFINE_FUNCTION(ExSkyCamera);
DEFINE_FUNCTION(ExVolumeSkybox);
DEFINE_FUNCTION(ExEnvFade);

class Stack
{
    static inline bool isFuncTableEnable = false;

private:
    std::string code;

public:
    char* codePtr;

public:
    Stack(const std::string& mapName) : codePtr(nullptr)
    {
        if (!isFuncTableEnable)
        {
            isFuncTableEnable = true;
            INCLUDE_FUNCTION(ExPar);
            INCLUDE_FUNCTION(ExPyramid);
            INCLUDE_FUNCTION(ExLight);
            INCLUDE_FUNCTION(ExPlayer);
            INCLUDE_FUNCTION(ExTriangle);
            INCLUDE_FUNCTION(ExModel);
            INCLUDE_FUNCTION(ExSkybox);
            INCLUDE_FUNCTION(ExFire);
            INCLUDE_FUNCTION(ExCircle);
            INCLUDE_FUNCTION(ExSmoke);
            INCLUDE_FUNCTION(ExMovementPart);
            INCLUDE_FUNCTION(ExCubemap);
            INCLUDE_FUNCTION(ExClipWall);
            INCLUDE_FUNCTION(ExTrigger);
            INCLUDE_FUNCTION(ExAreaPortal);
            INCLUDE_FUNCTION(ExEnvShake);
            INCLUDE_FUNCTION(ExSkyCamera);
            INCLUDE_FUNCTION(ExVolumeSkybox);
            INCLUDE_FUNCTION(ExEnvFade);
        }

        std::string line;
        std::ifstream in(mapName);
        if (in.is_open())
        {
            while (std::getline(in, line))
            {
                code.append(line);
            }

            codePtr = const_cast<char*>(code.c_str());
        }
    }

    std::string GetCode()
    {
        return code;
    }

    char* GetCodePtr()
    {
        return codePtr;
    }

    void Step()
    {
        if (codePtr == nullptr || *codePtr == '|')
        {
            return;
        }
        
        int index = atoi(codePtr); while (*codePtr++ != ':') {}
        codePtr--;
        funcTable[index](*this);
    }
};

DEFINE_FUNCTION(ExTriangle) {}
DEFINE_FUNCTION(ExMovementPart) {}
DEFINE_FUNCTION(ExCubemap) {}

DEFINE_FUNCTION(ExPar)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    bool IsRotateAroundZAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    bool IsRotateAroundXAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    bool IsRotateAroundYAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float angleRotationSum = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    int color = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    // Parab mode params
    stack.codePtr++;
    bool isParab = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parabOwnerRange;
    parabOwnerRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parabOwnerRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parabOwnerRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parabOwnerRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parabOwnerRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parabOwnerRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;

    char fileName[256]; int counter = 0;
    std::string textureName;
    while (*stack.codePtr != ';') fileName[counter++] = *stack.codePtr++;
    fileName[counter] = NULL;
    stack.codePtr++;
    textureName = fileName;

    float widthTextureCount = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float heightTextureCount = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    bool isHasCollision = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    COORDS cubemapCentreCoords;
    cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(length, width, height, centreCoords, IsRotateAroundZAxis, IsRotateAroundXAxis, IsRotateAroundYAxis, color);
    if (newObj->IsRotate()) newObj->Rotation(angleRotationSum);

    *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)newObj) = isParab;
    *reinterpret_cast<Range*>(sizeof(StaticMesh) + 28 + (char*)newObj) = parabOwnerRange;
    newObj->SetRange() = parRange;
    newObj->SetCollisionMode(isHasCollision);

    if (textureName != "NULL")
    {
        newObj->SetObjTextureMode(true);
        newObj->SetObjTextureParams(textureName, widthTextureCount, heightTextureCount);
    }

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::PARALLELEPIPED));
    AActor* currObservedObjForTrigger = actors.back();

    if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
    {
        AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
        typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
    }

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }
        
        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);
        
        stack.codePtr += 2;
    }
    
    stack.codePtr++;
    stack.Step();
}

DEFINE_FUNCTION(ExSkyCamera)
{
    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(1, 1, 1, centreCoords, false, false, false, 4);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::SKY_CAMERA));

    stack.Step();
}

DEFINE_FUNCTION(ExVolumeSkybox)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    bool IsRotateAroundZAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    bool IsRotateAroundXAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    bool IsRotateAroundYAxis = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float angleRotationSum = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(length, width, height, centreCoords, false, false, false, 1);

    *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)newObj) = false;
    newObj->SetRange() = parRange;
    newObj->SetCollisionMode(false);

    newObj->SetObjTextureMode(true);
    newObj->SetObjTextureParams("Textures/toolsskybox.bmp", 5, 5);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::VOLUME_SKYBOX));

    stack.Step();
}

DEFINE_FUNCTION(ExAreaPortal)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(length, width, height, centreCoords, false, false, false, 1);

    *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)newObj) = false;
    newObj->SetRange() = parRange;
    newObj->SetCollisionMode(false);

    newObj->SetObjTextureMode(true);
    newObj->SetObjTextureParams("Textures/toolsareaportal.bmp", 5, 5);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::AREA_PORTAL));

    stack.Step();
}

DEFINE_FUNCTION(ExTrigger)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS observedObjCentreCoord;

    observedObjCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    observedObjCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    observedObjCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(length, width, height, centreCoords, false, false, false, 1);

    *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)newObj) = false;
    newObj->SetRange() = parRange;
    newObj->SetCollisionMode(false);

    newObj->SetObjTextureMode(true);
    newObj->SetObjTextureParams("Textures/toolstrigger.bmp", 5, 5);

    AddActorToStorage<ATriggerActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::TRIGGER));

    ((ATriggerActor*)actors.back())->observedObjCentreCoord = observedObjCentreCoord;

    stack.Step();
}

DEFINE_FUNCTION(ExClipWall)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Parallelepiped* newObj = new Parallelepiped(length, width, height, centreCoords, false, false, false, 1);

    *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)newObj) = false;
    newObj->SetRange() = parRange;
    newObj->SetCollisionMode(true);

    newObj->SetObjTextureMode(true);
    newObj->SetObjTextureParams("Textures/toolsclip.bmp", 5, 5);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::CLIP_WALL));
    AActor* currObservedObjForTrigger = actors.back();

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }

        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);

        stack.codePtr += 2;
    }

    stack.codePtr++;
    stack.Step();
}

DEFINE_FUNCTION(ExFire)
{
    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS cubemapCentreCoords;
    cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Circle* newObj = new Circle(centreCoords, { 1,0,0 }, "Textures/env_fire.bmp", 3, 5);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::ENV_FIRE));

    if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
    {
        AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
        typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
    }

    stack.Step();
}

DEFINE_FUNCTION(ExEnvShake)
{
    stack.codePtr++;
    float shakePower;
    shakePower = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    EnvShake* newObj = new EnvShake(centreCoords, { 1,0,0 }, "Textures/env_shake.bmp", 1, 5, shakePower);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::ENV_SHAKE));
    AActor* currObservedObjForTrigger = actors.back();

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }

        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);

        stack.codePtr += 2;
    }

    stack.codePtr++;
    stack.Step();
}

DEFINE_FUNCTION(ExEnvFade)
{
    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Circle* newObj = new Circle(centreCoords, { 1,0,0 }, "Textures/env_fade.bmp", 1, 5);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::ENV_FADE));
    AActor* currObservedObjForTrigger = actors.back();

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }

        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);

        stack.codePtr += 2;
    }

    stack.codePtr++;
    stack.Step();
}

DEFINE_FUNCTION(ExSmoke)
{
    stack.codePtr += 2;
    COORDS particlesSpawnDot;

    particlesSpawnDot.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    particlesSpawnDot.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    particlesSpawnDot.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS endCircleCentreCoords;

    endCircleCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    endCircleCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    endCircleCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;
    float rad;
    rad = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    int colorIndex;
    colorIndex = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    Circle* endCircle = new Circle(endCircleCentreCoords + particlesSpawnDot, { 0,0,1 }, "Textures/Obsolete/Obsolete.bmp", rad, 5);
    AddActorToStorage<ASmokeActor>(actors, new Circle(particlesSpawnDot, { 1,0,0 }, "Textures/env_particles/env_particles" + std::format("{}.bmp", colorIndex), 3, 5), endCircle, colorIndex);
    typesOfActors.push_back(static_cast<int>(objectType::ENV_PARTICLES));
    AddActorToStorage<ABaseActor>(actors, endCircle);
    ((Circle*)actors.back()->GetStaticMesh())->SetCircleRotateMode(false);
    typesOfActors.push_back(static_cast<int>(objectType::CIRCLE));

    stack.Step();
}

DEFINE_FUNCTION(ExCircle)
{
    stack.codePtr++;
    float rad = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}
    stack.codePtr++;

    char fileName[256]; int counter = 0;
    std::string textureName;
    while (*stack.codePtr != ';') fileName[counter++] = *stack.codePtr++;
    fileName[counter] = NULL;
    stack.codePtr++;
    textureName = fileName;

    stack.codePtr++;
    COORDS normVec;

    normVec.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    normVec.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    normVec.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}
    stack.codePtr++;

    bool circleRotateMode = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}
    bool circleLimpidMode = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    COORDS cubemapCentreCoords;
    cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Circle* newObj = new Circle(centreCoords, normVec, textureName, rad, 5);
    newObj->SetCircleRotateMode(circleRotateMode);
    newObj->SetLimpidMode(circleLimpidMode);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::CIRCLE));

    if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
    {
        AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
        typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
    }

    stack.Step();
}

DEFINE_FUNCTION(ExSkybox)
{
    stack.codePtr++;
    float length = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float width = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    int color = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    Range parRange;
    parRange.xStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.xEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.yEnd = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zStart = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    parRange.zEnd = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;

    char fileName[256]; int counter = 0;
    std::string textureName;
    while (*stack.codePtr != ';') fileName[counter++] = *stack.codePtr++;
    fileName[counter] = NULL;
    stack.codePtr++;
    textureName = fileName;

    int numberOfSkyboxPart;
    numberOfSkyboxPart = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    SkyboxPart* newObj = new SkyboxPart(length, width, height, centreCoords, color);
    newObj->SetRange() = parRange;

    if (textureName != "NULL")
    {
        newObj->SetObjTextureMode(true);
        newObj->SetObjTextureParams(textureName);
    }

    AddActorToStorage<ASkyboxPart>(actors, newObj, numberOfSkyboxPart);
    typesOfActors.push_back(static_cast<int>(objectType::SKYBOX));

    stack.Step();
}

DEFINE_FUNCTION(ExPyramid)
{
    stack.codePtr++;
    float lowerBaselength = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float lowerBasewidth = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float height = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float upperBaseLength = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    float upperBaseWidth = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    int color = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    stack.codePtr++;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;
    COORDS cubemapCentreCoords;
    cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Pyramid* newObj = new Pyramid(lowerBaselength, lowerBasewidth, height, upperBaseLength, upperBaseWidth, centreCoords, color);

    AddActorToStorage<ABaseActor>(actors, newObj);
    typesOfActors.push_back(static_cast<int>(objectType::PYRAMID));
    AActor* currObservedObjForTrigger = actors.back();

    if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
    {
        AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
        typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
    }

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }

        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);

        stack.codePtr += 2;
    }

    stack.codePtr++;
    stack.Step();
}

DEFINE_FUNCTION(ExLight)
{
    // Light
    stack.codePtr++;
    int IValue = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    COORDS lightCentreCoords;

    stack.codePtr++;
    lightCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    lightCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    lightCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;
    int currentLightTextureIndex = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

    Light* light = new Light(IValue, lightCentreCoords);

    AddActorToStorage<ALightActor>(actors, light, new Circle(light->GetCoord(), { 1,0,0 }, "Textures/env_light/env_light" + std::format("{}.bmp", currentLightTextureIndex), 1, 5), currentLightTextureIndex);
    typesOfActors.push_back(static_cast<int>(objectType::LIGHT));

    stack.Step();
}

void LoadStaticModel(std::string modelFileName, std::string objFileNameWithExtensions, Model* model, bool& isModelAnimated);

DEFINE_FUNCTION(ExPlayer)
{
    stack.codePtr += 2;
    COORDS centreCoords;

    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    Model* model = new Model;
    bool isModelAnimated;
    LoadStaticModel("playerstart", "Models/playerstart/playerstart", model, isModelAnimated);

    model->SetCentreCoord() = centreCoords;
    model->UpdateRange();

    typesOfActors.push_back(static_cast<int>(objectType::PLAYER));

    stack.Step();
}

DEFINE_FUNCTION(ExModel)
{
    stack.codePtr++;

    std::string modelFileName, objFileNameWithExtensions = "Models/";
    char fileName[256]; int counter = 0;
    while (*stack.codePtr != ';') fileName[counter++] = *stack.codePtr++;
    fileName[counter] = NULL;
    stack.codePtr++;
    modelFileName = fileName;
    objFileNameWithExtensions += modelFileName;

    stack.codePtr++;
    COORDS centreCoords;
    centreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    centreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    stack.codePtr++;
    float startPolygonDist;
    startPolygonDist = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    float scale;
    scale = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}

    AActor* currObservedObjForTrigger = nullptr;
    Model* model = new Model;
    bool isModelAnimated;
    std::ifstream in(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)));
    if (in.is_open())
    {
        ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)).c_str(), objFileNameWithExtensions.c_str());
        isModelAnimated = false;

        for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
        {
            model->GetModelPolygons().push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
            ((Triangle*)model->GetModelPolygons().back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
        }

        model->UpdateRange();
        model->SetFileName() = fileName;
        AddActorToStorage<ABaseActor>(actors, model);
        typesOfActors.push_back(static_cast<int>(objectType::MODEL));
        currObservedObjForTrigger = actors.back();

        size_t verticesSize = objParseInfo.vertices.size();
        size_t facesSize = objParseInfo.faceIndex.size();
        size_t texturesSize = objParseInfo.textures.size();
        size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
        for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
        for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
        for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
        for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
    }
    else
    {
        std::string modelAnimFrame = objFileNameWithExtensions + std::string("0000");
        std::ifstream in(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)));
        if (!in.is_open())
        {
            LoadStaticModel("Error", "Models/Error/Error", model, isModelAnimated);
            typesOfActors.push_back(static_cast<int>(objectType::MODEL));
            currObservedObjForTrigger = actors.back();

            stack.codePtr++;
            while (*stack.codePtr != '}')
            {
                char rotationAxis = *stack.codePtr++;
                float angle = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
                model->Rotation(angle, rotationAxis);
            }

            model->SetCentreCoord() = centreCoords;
            model->UpdateRange();

            stack.codePtr++;

            stack.codePtr += 2;
            COORDS cubemapCentreCoords;
            cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
            cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
            cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

            if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
            {
                AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
                typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
            }

            stack.codePtr += 3;
            while (*stack.codePtr != '|')
            {
                COORDS triggerCentreCoord;
                int typeOfTrigger;
                triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
                triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
                triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
                typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

                AActor* currentTrigger = nullptr;
                for (size_t i = 0; i < actors.size(); ++i)
                {
                    if (actors[i]->isActorHasStaticMesh())
                        if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                        {
                            currentTrigger = actors[i];
                            break;
                        }
                }

                AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
                typesOfActors.push_back(-1);

                stack.codePtr += 2;
            }

            model->SetStartPolygonDist(startPolygonDist);
            model->SetScale(scale);

            stack.codePtr++;
            stack.Step();

            return;
        }

        isModelAnimated = true;
    }

    if (isModelAnimated)
    {
        model->SetAnimationInfo().isAnimated = true;

        while (true)
        {
            std::string modelAnimFrame = objFileNameWithExtensions + std::format("{:04}", model->GetAnimationInfo().frameCounter);

            std::ifstream in(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)));
            if (!in.is_open())
            {
                model->UpdateRange();
                model->SetFileName() = fileName;
                AddActorToStorage<ABaseActor>(actors, model);
                typesOfActors.push_back(static_cast<int>(objectType::MODEL));
                currObservedObjForTrigger = actors.back();
                break;
            }

            model->SetAnimationInfo().frameCounter++;
            ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)).c_str(), modelAnimFrame.c_str());

            for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
            {
                if (model->GetAnimationInfo().frameCounter > 1)
                    model->GetAnimModelPolygons().emplace_back();

                model->GetAnimModelPolygons()[model->GetAnimationInfo().frameCounter - 1].push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
                ((Triangle*)model->GetAnimModelPolygons()[model->GetAnimationInfo().frameCounter - 1].back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
            }

            size_t verticesSize = objParseInfo.vertices.size();
            size_t facesSize = objParseInfo.faceIndex.size();
            size_t texturesSize = objParseInfo.textures.size();
            size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
            for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
            for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
            for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
            for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
        }
    }

    stack.codePtr++;
    while (*stack.codePtr != '}')
    {
        char rotationAxis = *stack.codePtr++;
        float angle = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        model->Rotation(angle, rotationAxis);
    }

    model->SetCentreCoord() = centreCoords;
    model->UpdateRange();

    stack.codePtr++;

    stack.codePtr += 2;
    COORDS cubemapCentreCoords;
    cubemapCentreCoords.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
    cubemapCentreCoords.z = atof(stack.codePtr); while (*stack.codePtr++ != '}') {}

    if (!(cubemapCentreCoords.x == 0 && cubemapCentreCoords.y == 0 && cubemapCentreCoords.z == 0))
    {
        AddActorToStorage<ACubemapActor>(actors, new Cubemap(cubemapCentreCoords, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5), actors.back());
        typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));
    }

    stack.codePtr += 3;
    while (*stack.codePtr != '|')
    {
        COORDS triggerCentreCoord;
        int typeOfTrigger;
        triggerCentreCoord.x = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.y = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        triggerCentreCoord.z = atof(stack.codePtr); while (*stack.codePtr++ != ';') {}
        typeOfTrigger = atoi(stack.codePtr); while (*stack.codePtr++ != ';') {}

        AActor* currentTrigger = nullptr;
        for (size_t i = 0; i < actors.size(); ++i)
        {
            if (actors[i]->isActorHasStaticMesh())
                if (actors[i]->GetStaticMesh()->GetCentreCoord() == triggerCentreCoord)
                {
                    currentTrigger = actors[i];
                    break;
                }
        }

        AddActorToStorage<ATriggerLine>(actors, currentTrigger->GetStaticMesh(), typeOfTrigger, ATriggerLine::ReadInfoFuncTable[typeOfTrigger](stack.codePtr), currObservedObjForTrigger);
        typesOfActors.push_back(-1);

        stack.codePtr += 2;
    }

    model->SetStartPolygonDist(startPolygonDist);
    model->SetScale(scale);

    //system("cls");
    //std::cout << model->GetCentreCoord().x << ' ' << model->GetCentreCoord().y << ' ' << model->GetCentreCoord().z; exit(1);

    stack.codePtr++;
    stack.Step();
}

void LoadStaticModel(std::string modelFileName, std::string objFileNameWithExtensions, Model* model, bool& isModelAnimated)
{
    ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)).c_str(), objFileNameWithExtensions.c_str());
    isModelAnimated = false;

    for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
    {
        model->GetModelPolygons().push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
        ((Triangle*)model->GetModelPolygons().back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
    }

    model->UpdateRange();
    model->SetFileName() = modelFileName;
    AddActorToStorage<ABaseActor>(actors, model);

    size_t verticesSize = objParseInfo.vertices.size();
    size_t facesSize = objParseInfo.faceIndex.size();
    size_t texturesSize = objParseInfo.textures.size();
    size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
    for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
    for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
    for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
    for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
}

void LoadMapToGame()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	showCursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 5, 2 });
	std::cout << "Enter the file name: ";

	std::vector<char> strStorage;
	while (key != '\r')
	{
		key = _getche();

		if (key == '\r') break;

		strStorage.push_back(key);
	}

	strStorage.push_back('\0');
	std::string fileName = strStorage.data();

	hideCursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 5, 2 });
	for (int i = 0; i < 50; ++i)
		std::cout << " ";

    Stack stack(FILE_EXTENSION(fileName, EXTENSION_CAST(bsp)));
    stack.Step();
}