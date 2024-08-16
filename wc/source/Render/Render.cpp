
#define OOF_IMPL
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <cstdio>

#include "Render.h"
#include "GlobalVars.h"
#include "Preprocessor.h"
#include "Light.h"
#include "StaticMesh.h"
#include "ALightActor.h"
#include "Pixel.h"
#include "GameState.h"
#include "ActorSelectionState.h"
#include "Model.h"
#include "Circle.h"
#include "Triangle.h"
#include "oof.h"

extern std::vector<int> typesOfActors;

char image[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
COORDS imageColors[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
int imageActorsIndexes[SCREEN_HEIGHT - 2][SCREEN_WIDTH - 2];
oof::screen screen(SCREEN_WIDTH - 2, SCREEN_HEIGHT - 2, 1, 1, ' ');

void equationSystemSolving(float firstIntervalStart, float firstIntervalEnd, float secondIntervalStart, float secondIntervalEnd,
    bool& isSolutionExists, float& minValueInSolution, float& maxValueInSolution, float rayLength) noexcept
{
    if (((firstIntervalStart >= secondIntervalStart && firstIntervalStart <= secondIntervalEnd) || (firstIntervalEnd >= secondIntervalStart && firstIntervalEnd <= secondIntervalEnd)) ||
        ((secondIntervalStart >= firstIntervalStart && secondIntervalStart <= firstIntervalEnd) || (secondIntervalEnd >= firstIntervalStart && secondIntervalEnd <= firstIntervalEnd)))
    {
        if (firstIntervalStart >= secondIntervalStart && firstIntervalStart <= secondIntervalEnd)
        {
            if (((firstIntervalStart) > rayLength && ((firstIntervalEnd < secondIntervalEnd) ? (firstIntervalEnd) : (secondIntervalEnd)) > rayLength) ||
                (firstIntervalStart < 0 && ((firstIntervalEnd < secondIntervalEnd) ? (firstIntervalEnd) : (secondIntervalEnd)) < 0))
            {
                isSolutionExists = false;
                return;
            }

            if (firstIntervalEnd >= secondIntervalStart && firstIntervalEnd <= secondIntervalEnd)
            {
                minValueInSolution = min(firstIntervalStart, firstIntervalEnd);
                maxValueInSolution = max(firstIntervalStart, firstIntervalEnd);
            }
            else
            {
                minValueInSolution = min(firstIntervalStart, secondIntervalEnd);
                maxValueInSolution = max(firstIntervalStart, secondIntervalEnd);
            }

            if (minValueInSolution < 0) minValueInSolution = 0;
            if (maxValueInSolution < 0) maxValueInSolution = 0;
        }
        else if (firstIntervalEnd >= secondIntervalStart && firstIntervalEnd <= secondIntervalEnd)
        {
            if (((firstIntervalEnd) > rayLength && ((firstIntervalStart > secondIntervalStart) ? (firstIntervalStart) : (secondIntervalStart)) > rayLength) ||
                ((firstIntervalEnd) < 0 && ((firstIntervalStart > secondIntervalStart) ? (firstIntervalStart) : (secondIntervalStart)) < 0))
            {
                isSolutionExists = false;
                return;
            }

            if (firstIntervalStart >= secondIntervalStart && firstIntervalStart <= secondIntervalEnd)
            {
                minValueInSolution = min(firstIntervalStart, firstIntervalEnd);
                maxValueInSolution = max(firstIntervalStart, firstIntervalEnd);
            }
            else
            {
                minValueInSolution = min(secondIntervalStart, firstIntervalEnd);
                maxValueInSolution = max(secondIntervalStart, firstIntervalEnd);
            }

            if (minValueInSolution < 0) minValueInSolution = 0;
            if (maxValueInSolution < 0) maxValueInSolution = 0;
        }
        else if (secondIntervalStart >= firstIntervalStart && secondIntervalStart <= firstIntervalEnd)
        {
            if (((secondIntervalStart) > rayLength && ((secondIntervalEnd < firstIntervalEnd) ? (secondIntervalEnd) : (firstIntervalEnd)) > rayLength) ||
                ((secondIntervalStart) < 0 && ((secondIntervalEnd < firstIntervalEnd) ? (secondIntervalEnd) : (firstIntervalEnd)) < 0))
            {
                isSolutionExists = false;
                return;
            }

            if (secondIntervalEnd >= firstIntervalStart && secondIntervalEnd <= firstIntervalEnd)
            {
                minValueInSolution = min(secondIntervalStart, secondIntervalEnd);
                maxValueInSolution = max(secondIntervalStart, secondIntervalEnd);
            }
            else
            {
                minValueInSolution = min(secondIntervalStart, firstIntervalEnd);
                maxValueInSolution = max(secondIntervalStart, firstIntervalEnd);
            }

            if (minValueInSolution < 0) minValueInSolution = 0;
            if (maxValueInSolution < 0) maxValueInSolution = 0;
        }
        else if (secondIntervalEnd >= firstIntervalStart && secondIntervalEnd <= firstIntervalEnd)
        {
            if (((secondIntervalEnd) > rayLength && ((secondIntervalStart > firstIntervalStart) ? (secondIntervalStart) : (firstIntervalStart)) > rayLength) ||
                ((secondIntervalEnd) < 0 && ((secondIntervalStart > firstIntervalStart) ? (secondIntervalStart) : (firstIntervalStart)) < 0))
            {
                isSolutionExists = false;
                return;
            }

            if (secondIntervalStart >= firstIntervalStart && secondIntervalStart <= firstIntervalEnd)
            {
                minValueInSolution = min(secondIntervalStart, secondIntervalEnd);
                maxValueInSolution = max(secondIntervalStart, secondIntervalEnd);
            }
            else
            {
                minValueInSolution = min(firstIntervalStart, secondIntervalEnd);
                maxValueInSolution = max(firstIntervalStart, secondIntervalEnd);
            }

            if (minValueInSolution < 0) minValueInSolution = 0;
            if (maxValueInSolution < 0) maxValueInSolution = 0;
        }

        isSolutionExists = true;
    }
}

bool isLightHitsDot(const std::vector<AActor*>& actors, COORDS nearCrossRayAndFigureCoord, COORDS lightCoord, const objectType& rayCrossedObjType, int rayCrossedObjNumber, int rayHitSurfaceNumber)
{
    bool IsLightRayCrossesParallelepiped(const std::vector<AActor*>&actors, COORDS lightCoord, COORDS nearCrossRayAndFigureCoord, int figureNumber, int rayCrossedObjNumber, int rayHitSurfaceNumber);
    void ifIsParallelepiped(const std::vector<AActor*>&actors, Range & tempParRange, const objectType & objType, int figureNumber, int rayCrossedObjNumber) noexcept;
    void RayCrossSystemEquationSolving(const Range & figureRange, COORDS raySourceCoord, COORDS normalizeRay, bool& isEquationSolutionExists, float& nearCrossRayAndFigureValue, float& farCrossRayAndFigureValue, float rayLength = DRAWING_RANGE) noexcept;

    Range tempFigureRange;
    COORDS lightNormalizeRay = vectorNormalize(nearCrossRayAndFigureCoord, lightCoord);
    float lightRayLength = dotDistance(lightCoord, nearCrossRayAndFigureCoord);
    bool isEquationSolutionExists;
    float nearCrossRayAndFigureValue, farCrossRayAndFigureValue;

    for (size_t index = 1; index < actors.size(); ++index)
    {
        IS_ACTOR_HAS_TYPE(actors[index], Light) continue;
        if (typesOfActors[index - 1] == static_cast<int>(objectType::CLIP_WALL) || typesOfActors[index - 1] == static_cast<int>(objectType::TRIGGER)
            || typesOfActors[index - 1] == static_cast<int>(objectType::AREA_PORTAL) || typesOfActors[index - 1] == static_cast<int>(objectType::SKY_CAMERA)
            || typesOfActors[index - 1] == static_cast<int>(objectType::VOLUME_SKYBOX)) continue;

        IS_ACTOR_HAS_TYPE(actors[index], StaticMesh)
        {
            isEquationSolutionExists = false;
            tempFigureRange = actors[index]->GetStaticMesh()->GetRange();

            ifIsParallelepiped(actors, tempFigureRange, rayCrossedObjType, index, rayCrossedObjNumber);
            RayCrossSystemEquationSolving(tempFigureRange, lightCoord, lightNormalizeRay, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, lightRayLength);

            if (isEquationSolutionExists)
            {
                if (IsLightRayCrossesParallelepiped(actors, lightCoord, nearCrossRayAndFigureCoord, index, rayCrossedObjNumber, rayHitSurfaceNumber))
                    return false;
            }
        }
    }

    return true;
}

void ifIsParallelepiped(const std::vector<AActor*>& actors, Range& tempParRange, const objectType& rayCrossedObjType, int figureNumber, int rayCrossedObjNumber) noexcept
{
    static const float ExtendedValue = 0.1F;

    if (rayCrossedObjType == objectType::PARALLELEPIPED)
    {
        if (figureNumber == rayCrossedObjNumber && !actors[figureNumber]->GetStaticMesh()->IsRotate())
        {
            tempParRange.xStart -= ExtendedValue;
            tempParRange.xEnd += ExtendedValue;
            tempParRange.yStart -= ExtendedValue;
            tempParRange.yEnd += ExtendedValue;
            tempParRange.zStart -= ExtendedValue;
            tempParRange.zEnd += ExtendedValue;
        }
    }
}

bool IsLightRayCrossesParallelepiped(const std::vector<AActor*>& actors, COORDS lightCoord, COORDS tempDotCoord, int figureNumber, int rayCrossedObjNumber, int rayHitSurfaceNumber)
{
    if (actors[figureNumber]->GetStaticMesh()->IsParaboloid())
    {
        if (figureNumber != rayCrossedObjNumber)
        {
            if (actors[figureNumber]->GetStaticMesh()->IsRayCrossParaboloid(lightCoord, tempDotCoord))
                return true;
            else
                return false;
        }
    }

    if (!actors[figureNumber]->GetStaticMesh()->IsRotate())
    {
        if (figureNumber == rayCrossedObjNumber)
        {
            if (actors[figureNumber]->GetStaticMesh()->IsRayCrossNotRotatedFigure(lightCoord, tempDotCoord))
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
    {
        if (figureNumber == rayCrossedObjNumber)
        {
            if (actors[figureNumber]->GetStaticMesh()->IsRotatedFigureShine(lightCoord, tempDotCoord, rayHitSurfaceNumber))
            {
                return true;
            }
            else
                return false;
        }
        else
        {
            if (actors[figureNumber]->GetStaticMesh()->IsRayCrossRotatedFigure(lightCoord, tempDotCoord))
                return true;
            else
                return false;
        }
    }

    return false;
}

COORDS LimpidColorHandle(const std::vector<AActor*>& actors, COORDS cameraCoord, COORDS cameraNormalizeRay, COORDS finalNearCrossRayAndFigureCoord, int& nearestLimpidObjNumb, bool& isLimpid)
{
    COORDS resultRGBLimpidColor = { 0,0,0 };
    COORDS resultRGBNoLimpidColor = { 0,0,0 };
    int nearestLimpidObjIndex = -1, nearestNoLimpidObjIndex = -1;
    float minLimpidColorDist = 10000, minNoLimpidColorDist = 10000;

    for (size_t index = 0; index < actors.size(); ++index)
    {
        IS_ACTOR_HAS_TYPE(actors[index], StaticMesh)
        {
            objectType currentActorObjType = actors[index]->GetStaticMesh()->GetObjType();
            if (typesOfActors[index - 1] == static_cast<int>(objectType::CLIP_WALL))
            {
                float nearCrossRayAndFigureValue, farCrossRayAndFigureValue;
                bool isEquationSolutionExists = false;
                RayCrossSystemEquationSolving(actors[index]->GetStaticMesh()->GetRange(), cameraCoord, cameraNormalizeRay, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue);

                if (isEquationSolutionExists)
                {
                    COORDS nearCrossRayAndFigureCoord = { cameraNormalizeRay.x * (nearCrossRayAndFigureValue)+cameraCoord.x, cameraNormalizeRay.y * (nearCrossRayAndFigureValue)+cameraCoord.y, cameraNormalizeRay.z * (nearCrossRayAndFigureValue)+cameraCoord.z };

                    if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < dotDistance(cameraCoord, finalNearCrossRayAndFigureCoord))
                    {
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) == 0) continue;
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minLimpidColorDist)
                        {
                            minLimpidColorDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                            nearestLimpidObjIndex = index;
                        }

                        resultRGBLimpidColor += actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord);
                    }
                }
            }
            else if (typesOfActors[index - 1] == static_cast<int>(objectType::TRIGGER))
            {
                float nearCrossRayAndFigureValue, farCrossRayAndFigureValue;
                bool isEquationSolutionExists = false;
                RayCrossSystemEquationSolving(actors[index]->GetStaticMesh()->GetRange(), cameraCoord, cameraNormalizeRay, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue);

                if (isEquationSolutionExists)
                {
                    COORDS nearCrossRayAndFigureCoord = { cameraNormalizeRay.x * (nearCrossRayAndFigureValue)+cameraCoord.x, cameraNormalizeRay.y * (nearCrossRayAndFigureValue)+cameraCoord.y, cameraNormalizeRay.z * (nearCrossRayAndFigureValue)+cameraCoord.z };

                    if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < dotDistance(cameraCoord, finalNearCrossRayAndFigureCoord))
                    {
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) == 0) continue;

                        if (actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord) != COORDS{ 248,153,0 })
                        {
                            isLimpid = false;
                            if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minNoLimpidColorDist)
                            {
                                minNoLimpidColorDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                                nearestNoLimpidObjIndex = index;

                                resultRGBNoLimpidColor = actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord);
                            }
                        }
                        else
                        {
                            if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minLimpidColorDist)
                            {
                                minLimpidColorDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                                nearestLimpidObjIndex = index;
                            }

                            resultRGBLimpidColor += actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord);
                        }
                    }
                }
            }
            else if (typesOfActors[index - 1] == static_cast<int>(objectType::AREA_PORTAL))
            {
                float nearCrossRayAndFigureValue, farCrossRayAndFigureValue;
                bool isEquationSolutionExists = false;
                RayCrossSystemEquationSolving(actors[index]->GetStaticMesh()->GetRange(), cameraCoord, cameraNormalizeRay, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue);

                if (isEquationSolutionExists)
                {
                    COORDS nearCrossRayAndFigureCoord = { cameraNormalizeRay.x * (nearCrossRayAndFigureValue)+cameraCoord.x, cameraNormalizeRay.y * (nearCrossRayAndFigureValue)+cameraCoord.y, cameraNormalizeRay.z * (nearCrossRayAndFigureValue)+cameraCoord.z };

                    if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < dotDistance(cameraCoord, finalNearCrossRayAndFigureCoord))
                    {
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) == 0) continue;

                        if (actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord) != COORDS{ 0,248,219 })
                        {
                            isLimpid = false;
                            if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minNoLimpidColorDist)
                            {
                                minNoLimpidColorDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                                nearestNoLimpidObjIndex = index;

                                resultRGBNoLimpidColor = actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord);
                            }
                        }
                        else
                        {
                            if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minLimpidColorDist)
                            {
                                minLimpidColorDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                                nearestLimpidObjIndex = index;
                            }

                            resultRGBLimpidColor += actors[index]->GetStaticMesh()->GetColor(nearCrossRayAndFigureCoord);
                        }
                    }
                }
            }
            else if (currentActorObjType == objectType::CIRCLE)
            {
                if (((Circle*)actors[index]->GetStaticMesh())->GetLimpidMode() == false) continue;

                COORDS dotProjection = ((Circle*)actors[index]->GetStaticMesh())->isRayIntersectCircle(cameraCoord, cameraNormalizeRay * DRAWING_RANGE + cameraCoord);
                if (dotProjection.x == 0 && dotProjection.y == 0 && dotProjection.z == 0) continue;
                if (!(dotProjection.x >= min(cameraCoord.x, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).x) && dotProjection.x <= max(cameraCoord.x, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).x)
                    && dotProjection.y >= min(cameraCoord.y, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).y) && dotProjection.y <= max(cameraCoord.y, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).y)
                    && dotProjection.z >= min(cameraCoord.z, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).z) && dotProjection.z <= max(cameraCoord.z, (cameraNormalizeRay * DRAWING_RANGE + cameraCoord).z)))
                    continue;

                COORDS pixelRGBColor;
                if (actors[index]->GetStaticMesh()->isObjHasTexture())
                {
                    pixelRGBColor = actors[index]->GetStaticMesh()->GetColor(dotProjection);
                    if (pixelRGBColor.x == 0 && pixelRGBColor.y == 0 && pixelRGBColor.z == 0) continue;
                }

                if (dotDistance(cameraCoord, dotProjection) < dotDistance(cameraCoord, finalNearCrossRayAndFigureCoord))
                {
                    if (dotDistance(cameraCoord, dotProjection) == 0) continue;
                    if (dotDistance(cameraCoord, dotProjection) < minLimpidColorDist)
                    {
                        minLimpidColorDist = dotDistance(cameraCoord, dotProjection);
                        nearestLimpidObjIndex = index;
                    }

                    resultRGBLimpidColor += actors[index]->GetStaticMesh()->GetColor(dotProjection);
                }
            }
        }
    }

    nearestLimpidObjNumb = (minLimpidColorDist < minNoLimpidColorDist ? nearestLimpidObjIndex : nearestNoLimpidObjIndex);
    return (isLimpid ? resultRGBLimpidColor : resultRGBNoLimpidColor);
}

void RayCastingFromCamera(const std::vector<AActor*>& actors, const ACamera& playerCamera, COORDS rightUpCamCoord, COORDS cameraDownVec, COORDS cameraLeftVec, int yStart, int yEnd)
{
    COORDS cameraCoord = playerCamera.GetCameraCoord();
    COORDS verCamDir = playerCamera.GetVerCamDir();

    COORDS cameraNormalizeRay, nearCrossRayAndFigureCoord, finalNearCrossRayAndFigureCoord = { 0,0,0 };
    objectType finalObjType = objectType::TRIANGLE;
    float nearCrossRayAndFigureValue = -1, farCrossRayAndFigureValue = -1, finalNearCrossRayAndFigureValue = -1, minDotAndCameraDist = -1;
    bool isEquationSolutionExists;
    int rayCrossedObjNumber = -1, rayCrossedPolygonNumber = -1, finalRayHitSurfaceNumber = -1, rayHitSurfaceNumber = -1;

    //for (int yScreenPixelNumb = ((firstOrSecondPartOfScreen) ? SCREEN_HEIGHT : SCREEN_HEIGHT * 2); yScreenPixelNumb >= ((firstOrSecondPartOfScreen) ? 0 : SCREEN_HEIGHT); --yScreenPixelNumb)
    for (int yScreenPixelNumb = yStart; yScreenPixelNumb >= yEnd; --yScreenPixelNumb)
    {
        if (yScreenPixelNumb == 24 || yScreenPixelNumb == 28 || yScreenPixelNumb == 34 || yScreenPixelNumb == 37
            || yScreenPixelNumb == 41 || yScreenPixelNumb == 47 || yScreenPixelNumb == 51 || yScreenPixelNumb >= 54) continue;

        for (size_t xScreenPixelNumb = 0; xScreenPixelNumb < (SCREEN_WIDTH); ++xScreenPixelNumb)
        {
            if (xScreenPixelNumb == 0 || xScreenPixelNumb == 1 || xScreenPixelNumb == 2 || xScreenPixelNumb == 3 || xScreenPixelNumb == 63) continue;

            static const float minDotAndCameraDistValue = 10000;
            cameraNormalizeRay = CameraNormalizeRayCoordCalc(xScreenPixelNumb, yScreenPixelNumb, cameraDownVec, cameraLeftVec, rightUpCamCoord, verCamDir, cameraCoord);
            minDotAndCameraDist = minDotAndCameraDistValue;
            rayHitSurfaceNumber = -1;

            // if this pixel already drawn
            Pixel intermediatePixel(cameraNormalizeRay * 10 + cameraCoord); // 10 is a random number
            intermediatePixel.CalcDotCoordsOnScreen(playerCamera);
            if (static_cast<int>(round(intermediatePixel.GetScreenPosX())) > 1 && static_cast<int>(round(intermediatePixel.GetScreenPosX())) < (SCREEN_WIDTH)-1 && static_cast<int>(round(intermediatePixel.GetScreenPosY())) > 1 && static_cast<int>(round(intermediatePixel.GetScreenPosY())) < SCREEN_HEIGHT - 1)
                if (image[static_cast<int>(round(intermediatePixel.GetScreenPosY())) - 1][static_cast<int>(round(intermediatePixel.GetScreenPosX())) - 1] != ' ')
                    continue;

            for (size_t index = 0; index < actors.size(); ++index)
            {
                IS_ACTOR_HAS_TYPE(actors[index], StaticMesh)
                {
                    objectType currentActorObjType = actors[index]->GetStaticMesh()->GetObjType();
                    if (currentActorObjType == objectType::CIRCLE)
                    {
                        if (((Circle*)actors[index]->GetStaticMesh())->GetLimpidMode() == true) continue;

                        COORDS dotProjection = ((Circle*)actors[index]->GetStaticMesh())->isRayIntersectCircle(cameraCoord, cameraNormalizeRay * 100 + cameraCoord);
                        if (dotProjection.x == 0 && dotProjection.y == 0 && dotProjection.z == 0) continue;
                        if (!(dotProjection.x >= min(cameraCoord.x, (cameraNormalizeRay * 1000 + cameraCoord).x) && dotProjection.x <= max(cameraCoord.x, (cameraNormalizeRay * 1000 + cameraCoord).x)
                            && dotProjection.y >= min(cameraCoord.y, (cameraNormalizeRay * 1000 + cameraCoord).y) && dotProjection.y <= max(cameraCoord.y, (cameraNormalizeRay * 1000 + cameraCoord).y)
                            && dotProjection.z >= min(cameraCoord.z, (cameraNormalizeRay * 1000 + cameraCoord).z) && dotProjection.z <= max(cameraCoord.z, (cameraNormalizeRay * 1000 + cameraCoord).z)))
                            continue;

                        COORDS pixelRGBColor;
                        if (actors[index]->GetStaticMesh()->isObjHasTexture())
                        {
                            pixelRGBColor = actors[index]->GetStaticMesh()->GetColor(dotProjection);
                            if (pixelRGBColor.x == 0 && pixelRGBColor.y == 0 && pixelRGBColor.z == 0) continue;
                        }

                        nearCrossRayAndFigureCoord = dotProjection;
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minDotAndCameraDist)
                        {
                            finalObjType = objectType::CIRCLE;
                            minDotAndCameraDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                            finalNearCrossRayAndFigureCoord = nearCrossRayAndFigureCoord;
                            rayCrossedObjNumber = index;
                        }
                    }
                    else if (actors[index]->GetStaticMesh()->GetObjType() == objectType::TRIANGLE)
                    {
                        float lenn = actors[index]->GetStaticMesh()->TriangleSurfaceDotCalc(cameraCoord, cameraNormalizeRay, minDotAndCameraDistValue);
                        if (lenn <= 0) continue;

                        nearCrossRayAndFigureCoord = cameraNormalizeRay * lenn + cameraCoord;
                        if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minDotAndCameraDist)
                        {
                            finalObjType = objectType::ENV_FIRE;
                            minDotAndCameraDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                            finalNearCrossRayAndFigureCoord = nearCrossRayAndFigureCoord;
                            rayCrossedObjNumber = index;
                        }
                    }
                    else if (currentActorObjType == objectType::MODEL)
                    {
                        if (((Model*)actors[index]->GetStaticMesh())->IsModelRender() == false) continue;

                        isEquationSolutionExists = false;
                        float tempStart, tempEnd;
                        RayCrossSystemEquationSolving(((Model*)actors[index]->GetStaticMesh())->GetModelRange(), cameraCoord, cameraNormalizeRay, isEquationSolutionExists, tempStart, tempEnd);

                        Model checkedModel = *((Model*)actors[index]->GetStaticMesh());
                        if (isEquationSolutionExists)
                            for (size_t i = 0; i < checkedModel.GetModelPolygons().size(); ++i)
                            {
                                Triangle checkedTriangle = *((Triangle*)checkedModel.GetModelPolygons()[i]);
                                float lenn = checkedTriangle.TriangleSurfaceDotCalc(cameraCoord, cameraNormalizeRay, minDotAndCameraDistValue);
                                if (lenn <= 0) continue;

                                nearCrossRayAndFigureCoord = cameraNormalizeRay * lenn + cameraCoord;
                                if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minDotAndCameraDist)
                                {
                                    finalObjType = objectType::TRIANGLE;
                                    minDotAndCameraDist = (typesOfActors[index - 1] == (int)objectType::MOVEMENT_PART ? -1 : dotDistance(cameraCoord, nearCrossRayAndFigureCoord));
                                    finalNearCrossRayAndFigureCoord = nearCrossRayAndFigureCoord;
                                    rayCrossedObjNumber = index;
                                    rayCrossedPolygonNumber = i;
                                }
                            }
                    }
                    else if (typesOfActors[index - 1] == static_cast<int>(objectType::CLIP_WALL))
                    { }
                    else if (typesOfActors[index - 1] == static_cast<int>(objectType::TRIGGER))
                    { }
                    else if (typesOfActors[index - 1] == static_cast<int>(objectType::AREA_PORTAL))
                    { }
                    else
                    {
                        isEquationSolutionExists = false;
                        RayCrossSystemEquationSolving(actors[index]->GetStaticMesh()->GetRange(), cameraCoord, cameraNormalizeRay, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue);

                        if (isEquationSolutionExists)
                        {
                            nearCrossRayAndFigureCoord = { cameraNormalizeRay.x * (nearCrossRayAndFigureValue)+cameraCoord.x, cameraNormalizeRay.y * (nearCrossRayAndFigureValue)+cameraCoord.y, cameraNormalizeRay.z * (nearCrossRayAndFigureValue)+cameraCoord.z };
                            if (!IsRayCrossesParallelepiped(actors, cameraNormalizeRay, cameraCoord, index, farCrossRayAndFigureValue, nearCrossRayAndFigureCoord, rayHitSurfaceNumber))
                                continue;

                            if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) < minDotAndCameraDist)
                            {
                                if (dotDistance(cameraCoord, nearCrossRayAndFigureCoord) == 0) continue;

                                finalObjType = actors[index]->GetStaticMesh()->GetObjType();
                                minDotAndCameraDist = dotDistance(cameraCoord, nearCrossRayAndFigureCoord);
                                finalNearCrossRayAndFigureCoord = nearCrossRayAndFigureCoord;
                                finalNearCrossRayAndFigureValue = nearCrossRayAndFigureValue;
                                finalRayHitSurfaceNumber = rayHitSurfaceNumber;
                                rayCrossedObjNumber = index;
                            }
                        }
                    }
                }
            }

            if (minDotAndCameraDist != minDotAndCameraDistValue)
            {
                Pixel resultPixel(finalNearCrossRayAndFigureCoord);
                resultPixel.CalcDotCoordsOnScreen(playerCamera);

                // if this pixel already drawn
                if (static_cast<int>(round(resultPixel.GetScreenPosX())) > 1 && static_cast<int>(round(resultPixel.GetScreenPosX())) < (SCREEN_WIDTH)-1 && static_cast<int>(round(resultPixel.GetScreenPosY())) > 1 && static_cast<int>(round(resultPixel.GetScreenPosY())) < SCREEN_HEIGHT - 1)
                {
                    if (image[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1] != ' ')
                        continue;
                }

                float lightPower, finalLightPower = 0;

                // calc light power for pixel dot
                COORDS resultRGBColor = { 0,0,0 };
                if(actors[rayCrossedObjNumber]->isActorHasCubemap())
                {
                    for (size_t i = 0; i < actors.size(); ++i)
                    {
                        IS_ACTOR_HAS_TYPE(actors[i], Light)
                        {
                            lightPower = actors[i]->GetLight()->GetLightPower(finalNearCrossRayAndFigureCoord);

                            if (isLightHitsDot(actors, finalNearCrossRayAndFigureCoord, actors[i]->GetLight()->GetCoord(), finalObjType, rayCrossedObjNumber, finalRayHitSurfaceNumber))
                            {
                                finalLightPower += lightPower;

                                if (ceil(lightPower) >= 3)
                                    resultRGBColor += ((ALightActor*)actors[i])->GetLightColor();
                            }
                        }
                    }
                }
                else
                    finalLightPower = '@';

                static const int MaxLightPowerValue = 13;
                static const int MinLightPowerValue = 0;

                if (finalLightPower > MaxLightPowerValue) finalLightPower = MaxLightPowerValue;
                else if (finalLightPower < MinLightPowerValue) finalLightPower = MinLightPowerValue;

                static const int BrightestLightStartValue = 9;
                static const int BrightLightStartValue = 5;
                static const int BrightLightExtendColorValue = 8;
                static const int BrightestLightColorValue = 14;

                int resultConsoleColor;
                if (actors[rayCrossedObjNumber]->GetStaticMesh()->GetObjType() == objectType::MODEL)
                    resultConsoleColor = actors[rayCrossedObjNumber]->GetStaticMesh()->GetModelPolygons()[rayCrossedPolygonNumber]->GetColor();
                else
                    resultConsoleColor = actors[rayCrossedObjNumber]->GetStaticMesh()->GetColor();


                if(actors[rayCrossedObjNumber]->isActorHasCubemap())
                    if (finalLightPower > BrightestLightStartValue && finalLightPower <= MaxLightPowerValue)
                        resultConsoleColor = BrightestLightColorValue;
                    else if (finalLightPower > BrightLightStartValue && finalLightPower <= BrightestLightStartValue && resultConsoleColor <= 7)
                        resultConsoleColor += BrightLightExtendColorValue;


                if (actors[rayCrossedObjNumber]->GetStaticMesh()->isObjHasTexture())
                {
                    if (finalObjType == objectType::TRIANGLE)
                        resultRGBColor += actors[rayCrossedObjNumber]->GetStaticMesh()->GetModelPolygons()[rayCrossedPolygonNumber]->GetColor(finalNearCrossRayAndFigureCoord);
                    else
                        resultRGBColor += actors[rayCrossedObjNumber]->GetStaticMesh()->GetColor(finalNearCrossRayAndFigureCoord);
                }
                else
                    resultRGBColor += ConsoleRBGColors.GeneralRGBConsoleColors[resultConsoleColor - 1];

                // Parallelepiped parab mode
                if (actors[rayCrossedObjNumber]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
                {
                    if (actors[rayCrossedObjNumber]->GetStaticMesh()->IsDotInCameraParaboloidRadius(finalNearCrossRayAndFigureCoord, cameraCoord, verCamDir, farCrossRayAndFigureValue))
                    {
                        resultConsoleColor = 15;
                        resultRGBColor += ConsoleRBGColors.GeneralRGBConsoleColors[resultConsoleColor - 1];
                    }
                }

                if (static_cast<int>(round(resultPixel.GetScreenPosX())) > 1 && static_cast<int>(round(resultPixel.GetScreenPosX())) < (SCREEN_WIDTH)-1 && static_cast<int>(round(resultPixel.GetScreenPosY())) > 1 && static_cast<int>(round(resultPixel.GetScreenPosY())) < SCREEN_HEIGHT - 1)
                {
                    int nearestLimpidObjNumb = -1; bool isLimpid = true;
                    if (typesOfActors[rayCrossedObjNumber - 1] != static_cast<int>(objectType::MOVEMENT_PART))
                    {
                        COORDS limpidColor = LimpidColorHandle(actors, cameraCoord, cameraNormalizeRay, finalNearCrossRayAndFigureCoord, nearestLimpidObjNumb, isLimpid);
                        resultRGBColor += (!isLimpid ? resultRGBColor * (-1) + limpidColor : limpidColor);
                    }

                    resultRGBColor = { resultRGBColor.x > 255 ? 255 : resultRGBColor.x, resultRGBColor.y > 255 ? 255 : resultRGBColor.y, resultRGBColor.z > 255 ? 255 : resultRGBColor.z };
                    finalLightPower = (nearestLimpidObjNumb != -1 ? 13 : finalLightPower);

                    image[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1] = ((image[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1] == ' ') ? gradNew[(int)(13 - ceil(finalLightPower))] : image[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1]);
                    imageColors[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1] = resultRGBColor;
                    imageActorsIndexes[static_cast<int>(round(resultPixel.GetScreenPosY())) - 1][static_cast<int>(round(resultPixel.GetScreenPosX())) - 1] = (nearestLimpidObjNumb != -1 ? nearestLimpidObjNumb : rayCrossedObjNumber);
                }
            }
        }
    }
}

COORDS CameraNormalizeRayCoordCalc(int xScreenPixelNumb, int yScreenPixelNumb, COORDS cameraVecUpOrDown, COORDS cameraVecLeftOrRight, COORDS rightUpCamCoord, COORDS verCamDir, COORDS cameraCoord)
{
    static const int RayDistanceValue = 100;

    COORDS newCameraCoord = rightUpCamCoord + cameraVecUpOrDown * ((SCREEN_HEIGHT * 2) - yScreenPixelNumb);
    COORDS newCameraCoord2 = newCameraCoord + cameraVecLeftOrRight * xScreenPixelNumb;

    return vectorNormalize({ verCamDir.x * RayDistanceValue + newCameraCoord2.x, verCamDir.y * RayDistanceValue + newCameraCoord2.y, verCamDir.z * RayDistanceValue + newCameraCoord2.z }, cameraCoord);
}

void RayCrossSystemEquationSolving(const Range& figureRange, COORDS raySourceCoord, COORDS normalizeRay,
    bool& isEquationSolutionExists, float& nearCrossRayAndFigureValue, float& farCrossRayAndFigureValue, float rayLength) noexcept
{
    float minX = min((figureRange.xStart - raySourceCoord.x) / normalizeRay.x, (figureRange.xEnd - raySourceCoord.x) / normalizeRay.x);
    float maxX = max((figureRange.xStart - raySourceCoord.x) / normalizeRay.x, (figureRange.xEnd - raySourceCoord.x) / normalizeRay.x);
    float minY = min((figureRange.yStart - raySourceCoord.y) / normalizeRay.y, (figureRange.yEnd - raySourceCoord.y) / normalizeRay.y);
    float maxY = max((figureRange.yStart - raySourceCoord.y) / normalizeRay.y, (figureRange.yEnd - raySourceCoord.y) / normalizeRay.y);
    float minZ = min((figureRange.zStart - raySourceCoord.z) / normalizeRay.z, (figureRange.zEnd - raySourceCoord.z) / normalizeRay.z);
    float maxZ = max((figureRange.zStart - raySourceCoord.z) / normalizeRay.z, (figureRange.zEnd - raySourceCoord.z) / normalizeRay.z);

    if (((minX >= minY && minX <= maxY) || (maxX >= minY && maxX <= maxY)) ||
        ((minY >= minX && minY <= maxX) || (maxY >= minX && maxY <= maxX)))
    {
        if ((minX >= minY && minX <= maxY) && maxX < maxY)
            equationSystemSolving(minX, maxX, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((minX >= minY && minX <= maxY) && maxX >= maxY)
            equationSystemSolving(minX, maxY, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((maxX >= minY && maxX <= maxY) && minX > minY)
            equationSystemSolving(minX, maxX, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((maxX >= minY && maxX <= maxY) && minX <= minY)
            equationSystemSolving(minY, maxX, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((minY >= minX && minY <= maxX) && maxY < maxX)
            equationSystemSolving(minY, maxY, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((minY >= minX && minY <= maxX) && maxY >= maxX)
            equationSystemSolving(minY, maxX, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((maxY >= minX && maxY <= maxX) && minY > minX)
            equationSystemSolving(minY, maxY, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);

        else if ((maxY >= minX && maxY <= maxX) && minY <= minX)
            equationSystemSolving(minX, maxY, minZ, maxZ, isEquationSolutionExists, nearCrossRayAndFigureValue, farCrossRayAndFigureValue, rayLength);
    }
}

bool IsRayCrossesParallelepiped(const std::vector<AActor*>& actors, COORDS cameraNormalizeRay, COORDS cameraCoord, int figureNumber,
    float farCrossRayAndFigureValue, COORDS& dotCoord, int& rayHitSurfaceNumber) noexcept
{
    if (actors[figureNumber]->GetStaticMesh()->IsRotate())
    {
        if (!actors[figureNumber]->GetStaticMesh()->IsDotDisplayAfterFiguresDel(cameraNormalizeRay, cameraCoord, dotCoord, farCrossRayAndFigureValue, rayHitSurfaceNumber))
            return false;
    }

    if (actors[figureNumber]->GetStaticMesh()->IsParaboloid())
    {
        if (!actors[figureNumber]->GetStaticMesh()->ToParab(cameraNormalizeRay, cameraCoord, dotCoord, farCrossRayAndFigureValue))
            return false;
    }

    return true;
}

void Rendering(const std::vector<AActor*>& actors, const ACamera& playerCamera)
{
    COORDS verCamDir = playerCamera.GetVerCamDir();

    COORDS cameraVecUp = GetVectorRotateZOnAngle(verCamDir, 90);
    COORDS cameraVecDown = GetVectorRotateZOnAngle(verCamDir, 270);
    COORDS cameraVecLeft = { cameraVecUp.y * verCamDir.z - cameraVecUp.z * verCamDir.y, cameraVecUp.z * verCamDir.x - cameraVecUp.x * verCamDir.z, cameraVecUp.x * verCamDir.y - cameraVecUp.y * verCamDir.x };
    COORDS cameraVecRight = { -cameraVecLeft.x, -cameraVecLeft.y, -cameraVecLeft.z };

    COORDS rightUpCamCoord = cameraVecRight * (SCREEN_WIDTH)+cameraVecUp * SCREEN_HEIGHT * 2 + playerCamera.GetCameraCoord();

    int coresCount = std::thread::hardware_concurrency();
    std::vector<std::thread> camThreads;
    float step = 1.2 / (float)coresCount;
    for (int i = 0; i < coresCount; ++i)
    {
        std::thread thr(RayCastingFromCamera, actors, playerCamera, rightUpCamCoord, cameraVecDown * 3, cameraVecLeft * 2, SCREEN_HEIGHT * (0.8 + (step * (i + 1))), SCREEN_HEIGHT * (0.8 + (step * i)));
        camThreads.push_back(std::move(thr));
    }

    for (int i = 0; i < coresCount; ++i)
    {
        camThreads[i].join();
    }
}

extern GameState* currentGameState;
extern ActorSelectionState* actorSelectionState;
void ShowImage()
{
    std::string str;
    DWORD cWritten;

    for (size_t i = 0; i < SCREEN_HEIGHT - 2; ++i)
    {
        for (size_t j = 0; j < (SCREEN_WIDTH) - 2; ++j)
        {
            if (j > 0 && j <= (SCREEN_WIDTH) - 2 - 1)
            {
                if (image[i][j + 1] == ' ')
                {
                    if (j != 21 && j != 22 && j != 36 && j != 37) continue;

                    image[i][j + 1] = image[i][j];
                    imageColors[i][j + 1] = imageColors[i][j];
                    imageActorsIndexes[i][j + 1] = imageActorsIndexes[i][j];
                }
            }
        }
    }

    // Cam ray actors choice section
    if (currentGameState == (GameState*)actorSelectionState)
    {
        if (image[(SCREEN_HEIGHT - 2) / 2][(SCREEN_WIDTH - 2) / 2] != ' ')
        {
            int currRayCamActorsIndex = imageActorsIndexes[(SCREEN_HEIGHT - 2) / 2][(SCREEN_WIDTH - 2) / 2];

            if (typesOfActors[currRayCamActorsIndex - 1] != static_cast<int>(objectType::MOVEMENT_PART) && typesOfActors[currRayCamActorsIndex - 1] != static_cast<int>(objectType::TRIANGLE))
                for (size_t i = 0; i < SCREEN_HEIGHT - 2; ++i)
                    for (size_t j = 0; j < (SCREEN_WIDTH)-2; ++j)
                    {
                        if (imageActorsIndexes[i][j] == currRayCamActorsIndex)
                            imageColors[i][j] = { 255, 255, 255 };
                    }
        }
    }

    for (size_t i = 0; i < SCREEN_HEIGHT - 2; ++i)
        for (size_t j = 0; j < (SCREEN_WIDTH)-2; ++j)
        {
            screen.get_cell(j, i).m_letter = image[i][j];
            screen.get_cell(j, i).m_format.m_fg_color.red = imageColors[i][j].x;
            screen.get_cell(j, i).m_format.m_fg_color.green = imageColors[i][j].y;
            screen.get_cell(j, i).m_format.m_fg_color.blue = imageColors[i][j].z;
        }

    std::cout << screen.get_string() << oof::reset_formatting();
}

void ClearImage()
{
    for (size_t i = 0; i < SCREEN_HEIGHT - 2; ++i)
        for (size_t j = 0; j < (SCREEN_WIDTH)-2; ++j)
        {
            image[i][j] = ' ';
            imageActorsIndexes[i][j] = -2;
        }
}