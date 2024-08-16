#pragma once

#include <Windows.h>
#include "Preprocessor.h"
#include "AActor.h"
#include "Model.h"
#include "ObjFileParse.h"
#include "AMovementParts.h"

extern int currentObservedActorIndex;

class AMovementScales : public AMovementParts
{
private:
    std::string partName;

private:
    void SelectedMode() override;

    std::string GetPartName() override;

public:
    AMovementScales();
};