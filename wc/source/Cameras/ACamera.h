#pragma once

struct COORDS;

class ACamera
{
    static inline const COORDS StartHorCameraDirection = { 1, 0.01, 0 };
    static inline const COORDS StartVerCameraDirection = { 1, 0.01, 0.05 };

protected:
    static const int HorAngleOnNewSurfaceErrorValue = -1;

protected:
    float HorAngleOnNewSurface;
    COORDS cameraCoord;
    COORDS horCameraDirection;
    COORDS verCameraDirection;
    COORDS rightCameraDirection;

public:
    ACamera();
    explicit ACamera(COORDS cameraCoord);

    virtual void Move() {};

    void CalcCameraHorAngleOnNewSurface();

    COORDS GetVerCamDir() const noexcept;

    COORDS& SetVerCamDir() noexcept;

    COORDS GetHorCamDir() const noexcept;

    COORDS& SetHorCamDir() noexcept;

    COORDS GetCameraCoord() const noexcept;

    COORDS& SetCameraCoord() noexcept;

    float GetCameraHorAngleOnNewSurface() const noexcept;
};