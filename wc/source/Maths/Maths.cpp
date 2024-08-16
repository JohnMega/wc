
#include <Windows.h>
#include "Maths.h"

float dotDistance(COORDS firstDot, COORDS secondDot)
{
    return sqrt((secondDot.x - firstDot.x) * (secondDot.x - firstDot.x) + (secondDot.y - firstDot.y) * (secondDot.y - firstDot.y) + (secondDot.z - firstDot.z) * (secondDot.z - firstDot.z));
}

float dotProduct(COORDS vec1, COORDS cameraNormalizeRay) noexcept
{
    return (vec1.x * cameraNormalizeRay.x + vec1.y * cameraNormalizeRay.y + vec1.z * cameraNormalizeRay.z);
}

float fromRadToDegrees(float radians) noexcept
{
    return ((radians * 180) / PI);
}

float fromDegreesToRad(float degrees) noexcept
{
    return ((degrees * PI) / 180);
}

float GetAngleBetweenVectors(COORDS generalDotOfVect, COORDS firstDotOfVect, COORDS secondDotOfVect)
{
    COORDS vec1 = { firstDotOfVect.x - generalDotOfVect.x, firstDotOfVect.y - generalDotOfVect.y, firstDotOfVect.z - generalDotOfVect.z };
    COORDS cameraNormalizeRay = { secondDotOfVect.x - generalDotOfVect.x, secondDotOfVect.y - generalDotOfVect.y, secondDotOfVect.z - generalDotOfVect.z };

    float scal = vec1.x * cameraNormalizeRay.x + vec1.y * cameraNormalizeRay.y + vec1.z * cameraNormalizeRay.z;

    float absvec1 = sqrt(pow(vec1.x, 2) + pow(vec1.y, 2) + pow(vec1.z, 2));
    float absvec2 = sqrt(pow(cameraNormalizeRay.x, 2) + pow(cameraNormalizeRay.y, 2) + pow(cameraNormalizeRay.z, 2));

    float acosRes = (scal) / (absvec1 * absvec2);
    if (acosRes > 1) acosRes = 1;
    if (acosRes < -1) acosRes = -1;

    return fromRadToDegrees(acos(acosRes));
}

float mixedProduct(COORDS dot1, COORDS dot2, COORDS dot3)
{
    return (dot1.x * (dot2.y * dot3.z - dot2.z * dot3.y) - dot1.y * (dot2.x * dot3.z - dot2.z * dot3.x) + dot1.z * (dot2.x * dot3.y - dot2.y * dot3.x));
}

float crossProduct(COORDS dot1, COORDS dot2)
{
    return ((dot1.y * dot2.z - dot1.z * dot2.y) - (dot1.x * dot2.z - dot1.z * dot2.x) + (dot1.x * dot2.y - dot1.y * dot2.x));
}

COORDS crossProductVec(COORDS dot1, COORDS dot2)
{
    return { (dot1.y * dot2.z - dot1.z * dot2.y), -(dot1.x * dot2.z - dot1.z * dot2.x), (dot1.x * dot2.y - dot1.y * dot2.x) };
}

COORDS VecZAxisRotation(COORDS vec, float angle)
{
    return COORDS{ GetVectorRotateXYOnAngle(vec, angle).x, GetVectorRotateXYOnAngle(vec, angle).y, vec.z };
}

COORDS VecXAxisRotation(COORDS vec, float angle)
{
    return COORDS{ vec.x, vec.y * cos(fromDegreesToRad(angle)) + vec.z * sin(fromDegreesToRad(angle)), -vec.y * sin(fromDegreesToRad(angle)) + vec.z * cos(fromDegreesToRad(angle)) };
}

COORDS VecYAxisRotation(COORDS vec, float angle)
{
    return COORDS{ vec.x * cos(fromDegreesToRad(angle)) + vec.z * sin(fromDegreesToRad(angle)), vec.y, -vec.x * sin(fromDegreesToRad(angle)) + vec.z * cos(fromDegreesToRad(angle)) };
}

COORDS GetVectorRotateXYOnAngle(COORDS vecCoord, float angle) noexcept
{
    return COORDS{ vecCoord.x * cos(fromDegreesToRad(angle)) - vecCoord.y * sin(fromDegreesToRad(angle)), vecCoord.x * sin(fromDegreesToRad(angle)) + vecCoord.y * cos(fromDegreesToRad(angle)), vecCoord.z * cos(fromDegreesToRad(angle)) };
}

COORDS GetVectorRotateZOnAngle(COORDS vecCoord, float angle)
{
    return COORDS{ (((float)sqrt(pow(vecCoord.x, 2) + pow(vecCoord.y, 2)) * cos(fromDegreesToRad(angle)) - vecCoord.z * sin(fromDegreesToRad(angle))) / (float)sqrt(pow(vecCoord.x, 2) + pow(vecCoord.y, 2))) * vecCoord.x,
    (((float)sqrt(pow(vecCoord.x, 2) + pow(vecCoord.y, 2)) * cos(fromDegreesToRad(angle)) - vecCoord.z * sin(fromDegreesToRad(angle))) / (float)sqrt(pow(vecCoord.x, 2) + pow(vecCoord.y, 2))) * vecCoord.y,
    (float)sqrt(pow(vecCoord.x, 2) + pow(vecCoord.y, 2)) * sin(fromDegreesToRad(angle)) + vecCoord.z * cos(fromDegreesToRad(angle)) };
}

COORDS dotProjectionOnSurface(COORDS surfaceDot1, COORDS surfaceDot2, COORDS mainDot) noexcept
{
    // surfaceDot3 = {0,0,0}

    float a = surfaceDot1.y * surfaceDot2.z - surfaceDot1.z * surfaceDot2.y;
    float b = surfaceDot1.z * surfaceDot2.x - surfaceDot1.x * surfaceDot2.z;
    float c = surfaceDot1.x * surfaceDot2.y - surfaceDot2.x * surfaceDot1.y;

    float t = (-a * mainDot.x - b * mainDot.y - c * mainDot.z) / (pow(a, 2) + pow(b, 2) + pow(c, 2));

    return COORDS{ mainDot.x + a * t, mainDot.y + b * t, mainDot.z + c * t };
}

COORDS vectorNormalize(COORDS vecEnd, COORDS vecStart)
{
    float len = (dotDistance(vecStart, vecEnd) == 0 ? 0.01 : dotDistance(vecStart, vecEnd));

    return COORDS{ (vecEnd.x - vecStart.x) / len, (vecEnd.y - vecStart.y) / len, (vecEnd.z - vecStart.z) / len };
}

COORDS GetCrossingSurfaceAndLineCoords(COORDS surfaceDot1, COORDS surfaceDot2, COORDS surfaceDot3, COORDS lineStartCoord, COORDS lineEndCoord) noexcept
{
    float normVecX, normVecY, normVecZ;

    normVecX = (surfaceDot2.y - surfaceDot1.y) * (surfaceDot3.z - surfaceDot1.z) - (surfaceDot3.y - surfaceDot1.y) * (surfaceDot2.z - surfaceDot1.z);
    normVecY = (surfaceDot2.z - surfaceDot1.z) * (surfaceDot3.x - surfaceDot1.x) - (surfaceDot3.z - surfaceDot1.z) * (surfaceDot2.x - surfaceDot1.x);
    normVecZ = (surfaceDot2.x - surfaceDot1.x) * (surfaceDot3.y - surfaceDot1.y) - (surfaceDot3.x - surfaceDot1.x) * (surfaceDot2.y - surfaceDot1.y);

    COORDS normVec = { normVecX, normVecY, normVecZ };

    COORDS vec1 = surfaceDot1 - lineStartCoord;
    COORDS cameraNormalizeRay = lineEndCoord - lineStartCoord;

    float dotPrVec1 = dotProduct(vec1, normVec);
    float dotPrVec2 = dotProduct(cameraNormalizeRay, normVec);

    return lineStartCoord + COORDS{ (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.x, (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.y, (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.z };
}

COORDS GetCrossingSurfaceAndLineCoords(COORDS surfaceDot1, COORDS surfaceDot2, COORDS surfaceDot3, COORDS normVec, COORDS lineStartCoord, COORDS lineEndCoord) noexcept
{
    COORDS vec1 = surfaceDot1 - lineStartCoord;
    COORDS cameraNormalizeRay = lineEndCoord - lineStartCoord;

    float dotPrVec1 = dotProduct(vec1, normVec);
    float dotPrVec2 = dotProduct(cameraNormalizeRay, normVec);

    return lineStartCoord + COORDS{ (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.x, (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.y, (dotPrVec1 / dotPrVec2) * cameraNormalizeRay.z };
}

float GetSurfaceValue(COORDS surfaceDot1, COORDS surfaceDot2, COORDS surfaceDot3, COORDS checkedDot) noexcept
{
    return (((checkedDot.x - surfaceDot1.x) * (surfaceDot2.y - surfaceDot1.y) * (surfaceDot3.z - surfaceDot1.z) + (checkedDot.y - surfaceDot1.y) * (surfaceDot2.z - surfaceDot1.z) * (surfaceDot3.x - surfaceDot1.x) + (surfaceDot2.x - surfaceDot1.x) * (surfaceDot3.y - surfaceDot1.y) * (checkedDot.z - surfaceDot1.z)) -
        ((surfaceDot3.x - surfaceDot1.x) * (surfaceDot2.y - surfaceDot1.y) * (checkedDot.z - surfaceDot1.z) + (surfaceDot2.z - surfaceDot1.z) * (surfaceDot3.y - surfaceDot1.y) * (checkedDot.x - surfaceDot1.x) + (checkedDot.y - surfaceDot1.y) * (surfaceDot2.x - surfaceDot1.x) * (surfaceDot3.z - surfaceDot1.z)));
}

bool IsRayHitFigureSurfaceDot(COORDS surfaceDot1, COORDS surfaceDot2, COORDS surfaceDot3,
    COORDS rayStartCoord, COORDS checkedSurfaceDot, COORDS figureCentreCoord)
{
    float surfaceNormVecX, surfaceNormVecY, surfaceNormVecZ;

    surfaceNormVecX = (surfaceDot2.y - surfaceDot1.y) * (surfaceDot3.z - surfaceDot1.z) - (surfaceDot3.y - surfaceDot1.y) * (surfaceDot2.z - surfaceDot1.z);
    surfaceNormVecY = (surfaceDot2.z - surfaceDot1.z) * (surfaceDot3.x - surfaceDot1.x) - (surfaceDot3.z - surfaceDot1.z) * (surfaceDot2.x - surfaceDot1.x);
    surfaceNormVecZ = (surfaceDot2.x - surfaceDot1.x) * (surfaceDot3.y - surfaceDot1.y) - (surfaceDot3.x - surfaceDot1.x) * (surfaceDot2.y - surfaceDot1.y);

    static const int NormVecDecreaseValue = 1000;
    COORDS surfaceNormVec;

    surfaceNormVec = { surfaceNormVecX / NormVecDecreaseValue, surfaceNormVecY / NormVecDecreaseValue, surfaceNormVecZ / NormVecDecreaseValue };
    COORDS surfaceNormVecEndCoord = { checkedSurfaceDot.x - figureCentreCoord.x + surfaceNormVec.x, checkedSurfaceDot.y - figureCentreCoord.y + surfaceNormVec.y, checkedSurfaceDot.z - figureCentreCoord.z + surfaceNormVec.z };

    surfaceNormVec = { -surfaceNormVecX / NormVecDecreaseValue, -surfaceNormVecY / NormVecDecreaseValue, -surfaceNormVecZ / NormVecDecreaseValue };
    COORDS reverseSurfaceNormVecEndCoord = { checkedSurfaceDot.x - figureCentreCoord.x + surfaceNormVec.x, checkedSurfaceDot.y - figureCentreCoord.y + surfaceNormVec.y, checkedSurfaceDot.z - figureCentreCoord.z + surfaceNormVec.z };

    if (dotDistance(surfaceNormVecEndCoord, { 0,0,0 }) < dotDistance(reverseSurfaceNormVecEndCoord, { 0,0,0 }))
        surfaceNormVec = { -surfaceNormVecX, -surfaceNormVecY, -surfaceNormVecZ };
    else
        surfaceNormVec = { surfaceNormVecX, surfaceNormVecY, surfaceNormVecZ };

    surfaceNormVecEndCoord = { checkedSurfaceDot.x - figureCentreCoord.x + surfaceNormVec.x, checkedSurfaceDot.y - figureCentreCoord.y + surfaceNormVec.y, checkedSurfaceDot.z - figureCentreCoord.z + surfaceNormVec.z };

    if (GetAngleBetweenVectors(checkedSurfaceDot - figureCentreCoord, rayStartCoord - figureCentreCoord, surfaceNormVecEndCoord) > 90)
        return true;

    return false;
}

bool IsSign(float firstValue, float secondValue) noexcept
{
    return (((firstValue >= 0 && secondValue >= 0) || (firstValue <= 0 && secondValue <= 0)) ? true : false);
}

float minNumb(float num1, float num2, float num3) noexcept
{
    return min(num1, min(num2, num3));
}

float maxNumb(float num1, float num2, float num3) noexcept
{
    return max(num1, max(num2, num3));
}