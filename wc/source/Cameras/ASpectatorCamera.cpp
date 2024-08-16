
#include <Windows.h>
#include "Maths.h"
#include "ACamera.h"
#include "ASpectatorCamera.h"

extern char key;
extern POINT NewMouseCoords;
extern POINT OldMouseCoords;
extern bool isInBuildMode;
extern void MoveCurrentFigure(int);

void ASpectatorCamera::Move() noexcept
{
    if (NewMouseCoords.x < OldMouseCoords.x) CamRotateOnXYAxis(360 - abs(NewMouseCoords.x - OldMouseCoords.x) / 3);
    if (NewMouseCoords.x > OldMouseCoords.x) CamRotateOnXYAxis(abs(NewMouseCoords.x - OldMouseCoords.x) / 3);
    if (NewMouseCoords.y < OldMouseCoords.y) CamRotateOnZAxis(abs(NewMouseCoords.y - OldMouseCoords.y) / 3);
    if (NewMouseCoords.y > OldMouseCoords.y) CamRotateOnZAxis(360 - abs(NewMouseCoords.y - OldMouseCoords.y) / 3);
    OldMouseCoords = NewMouseCoords;

    if (key == FORWARD)
        cameraCoord += COORDS{verCameraDirection.x, verCameraDirection.y, verCameraDirection.z};

    if (key == BACK)
        cameraCoord -= COORDS{verCameraDirection.x, verCameraDirection.y, verCameraDirection.z};

    if (key == RIGHT)
    {
        rightCameraDirection = GetVectorRotateXYOnAngle(verCameraDirection, 90);
        cameraCoord += COORDS{rightCameraDirection.x, rightCameraDirection.y, rightCameraDirection.z};
    }

    if (key == LEFT)
    {
        rightCameraDirection = GetVectorRotateXYOnAngle(verCameraDirection, 90);
        cameraCoord -= COORDS{rightCameraDirection.x, rightCameraDirection.y, rightCameraDirection.z};
    }

    key = NULL;

#ifdef DEBUG
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 2, 3 });
    std::cout << "                          ";
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 2, 3 });
    std::cout << HorAngleOnNewSurface;
#endif
}

void ASpectatorCamera::CamRotateOnZAxis(float angle)
{
    static const float VerCamDirZAxisMaxAllowValue = 0.95;
    static const float VerCamDirZAxisMinAllowValue = -0.95;
    static const float VerCamDirZAxisNotAllowIntervalStart = -0.05;
    static const float VerCamDirZAxisNotAllowIntervalEnd = 0.05;

    if ((NewMouseCoords.y < OldMouseCoords.y) ? verCameraDirection.z < VerCamDirZAxisMaxAllowValue : verCameraDirection.z > VerCamDirZAxisMinAllowValue)
    {
        verCameraDirection = GetVectorRotateZOnAngle(verCameraDirection, angle);

        CalcCameraHorAngleOnNewSurface();

        //while (HorAngleOnNewSurface == HorAngleOnNewSurfaceErrorValue || (verCameraDirection.z >= VerCamDirZAxisNotAllowIntervalStart && verCameraDirection.z <= VerCamDirZAxisNotAllowIntervalEnd))
        while (HorAngleOnNewSurface == HorAngleOnNewSurfaceErrorValue)
        {
            verCameraDirection = GetVectorRotateZOnAngle(verCameraDirection, angle);
            CalcCameraHorAngleOnNewSurface();
        }
    }
}

void ASpectatorCamera::CamRotateOnXYAxis(float angle)
{
    horCameraDirection = GetVectorRotateXYOnAngle(horCameraDirection, angle);
    verCameraDirection = { GetVectorRotateXYOnAngle(verCameraDirection, angle).x, GetVectorRotateXYOnAngle(verCameraDirection, angle).y, GetVectorRotateXYOnAngle(verCameraDirection, angle).z / cos(fromDegreesToRad(angle)) };

    CalcCameraHorAngleOnNewSurface();

    bool isHorAngleOnNewSurfaceHaveBadV = (HorAngleOnNewSurface >= 359 || HorAngleOnNewSurface <= 1) || (HorAngleOnNewSurface >= 89 && HorAngleOnNewSurface <= 91) || (HorAngleOnNewSurface >= 179 && HorAngleOnNewSurface <= 181) || (HorAngleOnNewSurface >= 269 && HorAngleOnNewSurface <= 271);
    //while (HorAngleOnNewSurface == HorAngleOnNewSurfaceErrorValue || isHorAngleOnNewSurfaceHaveBadV)
    while (HorAngleOnNewSurface == HorAngleOnNewSurfaceErrorValue)
    {
        horCameraDirection = GetVectorRotateXYOnAngle(horCameraDirection, angle);
        verCameraDirection = { GetVectorRotateXYOnAngle(verCameraDirection, angle).x, GetVectorRotateXYOnAngle(verCameraDirection, angle).y, GetVectorRotateXYOnAngle(verCameraDirection, angle).z / cos(fromDegreesToRad(angle)) };
        CalcCameraHorAngleOnNewSurface();

        isHorAngleOnNewSurfaceHaveBadV = (HorAngleOnNewSurface >= 359 || HorAngleOnNewSurface <= 1) || (HorAngleOnNewSurface >= 89 && HorAngleOnNewSurface <= 91) || (HorAngleOnNewSurface >= 179 && HorAngleOnNewSurface <= 181) || (HorAngleOnNewSurface >= 269 && HorAngleOnNewSurface <= 271);
    }
}