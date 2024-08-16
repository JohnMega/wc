#pragma once

#include <Windows.h>
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"
#include "ObjFileParse.h"

extern int currentObservedActorIndex;

class AMovementParts : public AActor
{
protected:
    enum class PARTS_STATES : char { SELECT_MODE, SELECTED };

protected:
    std::string partName;
    int partXActorIndex, partYActorIndex, partZActorIndex;
    ObjParseInfo partXObjParseInfo, partYObjParseInfo, partZObjParseInfo;
    int currentPartIndex = -1;
    PARTS_STATES currentPartsState;

    StaticMesh* currentObservedObj;
    int currentObservedObjIndex;

    POINT partNewMouseCoords;
    POINT partOldMouseCoords;

protected:
    void SpawnPartModel(std::string partName);

    void SetSelectedColorOnPart(int partIndex, ObjParseInfo partObjParseInfo);

    void SetStandartColorOnPart(int partIndex, ObjParseInfo partObjParseInfo);

    void SelectMode();

    virtual void SelectedMode() = 0;

    virtual std::string GetPartName();

    virtual void UpdatePartsCentreCoords();

    void ClearAllPartInfo();

public:
    AMovementParts();

    void EnablePartsOnObject(StaticMesh* object);

    void DisablePartsOnObject();

    void BeginPlay() override;

    void Tick() override;
};