#pragma once
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"
#include "Triangle.h"
#include "GameState.h"
#include "BuildModeState.h"
#include "ASimple.h"
#include "Parallelepiped.h"

extern std::vector<AActor*> actors;
extern std::vector<int> typesOfActors;
extern GameState* currentGameState;
extern GameState* defaultGameState;
extern BuildModeState* buildModeState;

class ATriggerLine : public AActor
{
public:
    struct AdditionalTriggerInfo
    {
        virtual std::string WriteInfo() = 0;
        static AdditionalTriggerInfo* ReadInfo(char*& ptr);
    };

    struct MoveToDotInfo : AdditionalTriggerInfo
    {
    public:
        COORDS endDot;
        float speed;

    public:
        MoveToDotInfo() : endDot({ 0,0,0 }), speed(1.0f)
        { }

        MoveToDotInfo(COORDS endDot, float speed) : endDot(endDot), speed(speed)
        { }

        std::string WriteInfo() override
        {
            return std::to_string(endDot.x) + ";" + std::to_string(endDot.y) + ";" + std::to_string(endDot.z) + ";" + std::to_string(speed);
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            COORDS endDotOutput;
            endDotOutput.x = atof(ptr); while (*ptr++ != ';') {}
            endDotOutput.y = atof(ptr); while (*ptr++ != ';') {}
            endDotOutput.z = atof(ptr); while (*ptr++ != ';') {}

            float speed;
            speed = atof(ptr); while (*ptr++ != '}') {}

            return (new MoveToDotInfo(endDotOutput, speed));
        }
    };

    struct TeleportToDotInfo : AdditionalTriggerInfo
    {
    public:
        COORDS endDot;

    public:
        TeleportToDotInfo() : endDot({ 0,0,0 })
        { }

        TeleportToDotInfo(COORDS endDot) : endDot(endDot)
        { }

        std::string WriteInfo() override
        {
            return std::to_string(endDot.x) + ";" + std::to_string(endDot.y) + ";" + std::to_string(endDot.z);
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            COORDS endDotOutput;
            endDotOutput.x = atof(ptr); while (*ptr++ != ';') {}
            endDotOutput.y = atof(ptr); while (*ptr++ != ';') {}
            endDotOutput.z = atof(ptr); while (*ptr++ != '}') {}

            return (new TeleportToDotInfo(endDotOutput));
        }
    };

    struct ObjectRenderOffInfo : AdditionalTriggerInfo
    {
        ObjectRenderOffInfo()
        { }

        ObjectRenderOffInfo(COORDS endDot)
        { }

        std::string WriteInfo() override
        {
            return " ";
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            ptr += 2;

            return (new ObjectRenderOffInfo);
        }
    };

    struct EnvShakeOnInfo : AdditionalTriggerInfo
    {
        EnvShakeOnInfo()
        { }

        EnvShakeOnInfo(COORDS endDot)
        { }

        std::string WriteInfo() override
        {
            return " ";
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            ptr += 2;

            return (new EnvShakeOnInfo);
        }
    };

    struct EnvShakeOffInfo : AdditionalTriggerInfo
    {
        EnvShakeOffInfo()
        { }

        EnvShakeOffInfo(COORDS endDot)
        { }

        std::string WriteInfo() override
        {
            return " ";
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            ptr += 2;

            return (new EnvShakeOffInfo);
        }
    };

    struct EnvFadeOnInfo : AdditionalTriggerInfo
    {
        EnvFadeOnInfo()
        { }

        EnvFadeOnInfo(COORDS endDot)
        { }

        std::string WriteInfo() override
        {
            return " ";
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            ptr += 2;

            return (new EnvFadeOnInfo);
        }
    };

    struct EnvFadeOffInfo : AdditionalTriggerInfo
    {
        EnvFadeOffInfo()
        { }

        EnvFadeOffInfo(COORDS endDot)
        { }

        std::string WriteInfo() override
        {
            return " ";
        }

        static AdditionalTriggerInfo* ReadInfo(char*& ptr)
        {
            ptr += 2;

            return (new EnvFadeOffInfo);
        }
    };

    using funcPtrType = AdditionalTriggerInfo * (*)(char*&);
    static inline const std::vector<funcPtrType> ReadInfoFuncTable = { (&MoveToDotInfo::ReadInfo), (&TeleportToDotInfo::ReadInfo)
        , (&ObjectRenderOffInfo::ReadInfo), (&EnvShakeOnInfo::ReadInfo), (&EnvShakeOffInfo::ReadInfo), (&EnvFadeOnInfo::ReadInfo)
        , (&EnvFadeOffInfo::ReadInfo) };

private:
    Triangle* linePart1, * linePart2;

public:
    int typeOfTrigger;
    StaticMesh* trigger;
    AActor* observedObj;
    AdditionalTriggerInfo* additTriggerInfo;

private:
    bool IsDotInRange(COORDS dot, Range objRange) const noexcept;

    void DeleteThisActor();

public:
    ATriggerLine(StaticMesh* trigger, int typeOfTrigger, AdditionalTriggerInfo* additTriggerInfo);

    ATriggerLine(StaticMesh* trigger, int typeOfTrigger, AdditionalTriggerInfo* additTriggerInfo, AActor* observedObj);

    void BeginPlay() override;

    void Tick() override;
};