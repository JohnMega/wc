#pragma once

#include <string>
#include "StaticMesh.h"
#include "Maths.h"
#include "bitmap.h"

class Parallelepiped : public StaticMesh
{
protected:
    static const int ParMainGroundDotsCount = 4;
    static const int ParMovingSurfacesCount = 4;
    static const int ParSurfacesCount = 6;
    static inline const float extendValue = 0.01F;

    struct ParallelepipedParabMode
    {
        bool isParab; // Dont move it
        bool isEnvParabMode; // Dont move it
        float parabRadius; // Dont move it
        COORDS verCamDirDotProj; // Dont move it
        Range parabOwnerRange; // Dont move it
    };

    struct TextureParams
    {
        std::string textureName = "NULL";
        Bitmap bitmap;
        PixelMatrix bmpPixelMatrix;
        float widthTextureCount = 0, heightTextureCount = 0;
    };

protected:
    float length, width, height; // Dont move it
    bool IsRotateAroundZAxis, IsRotateAroundXAxis, IsRotateAroundYAxis; // Dont move it
    float anglesRotationSum; // Dont move it
    int color; // Dont move it
    ParallelepipedParabMode parallelepipedParabMode; // Dont move it
    bool isParalHasTexture;
    bool isHasCollision;
    TextureParams textureParams;
    float maxNonRotatedParLenght, maxNonRotatedParWidth, maxNonRotatedExtendedParLenght, maxNonRotatedExtendedParWidth;
    COORDS centreCoord;
    COORDS groundParMainDot1, groundParMainDot2, groundParMainDot3, groundParMainDot4;
    COORDS extendedGroundParMainDot1, extendedGroundParMainDot2, extendedGroundParMainDot3, extendedGroundParMainDot4;
    Range parRange;

protected:
    COORDS ParalDotToLocalTextureCoords(COORDS localCentreCoord, COORDS localXVec, COORDS paralDot) const;

    bool IsDotInRange(COORDS dot) const noexcept;

    void SetParRange() noexcept;

    void SetGroundParMainDots(COORDS& groundMainDot1, COORDS& groundMainDot2, COORDS& groundMainDot3, COORDS& groundMainDot4) noexcept;

    void SetExtendedGroundParMainDots() noexcept;

    bool IsDotDisplayAfterFiguresDel(COORDS cameraNormalizeRay, COORDS cameraCoord, COORDS& nearCrossingRayAndFigureCoord, float farCrossingRayAndFigureValue, int& rayHitSurfaceNumber) const noexcept;
    void SurfacesValuesCalc(COORDS checkedDot, COORDS unnecessaryShapeMainDot1, COORDS unnecessaryShapeMainDot2, COORDS unnecessaryShapeMainDot3, COORDS unnecessaryShapeMainDot4, COORDS unnecessaryShapeMainDot5, COORDS unnecessaryShapeMainDot6, float& surfaceValue1, float& reverseSurfaceValue1, float& surfaceValue2, float& reverseSurfaceValue2, float& surfaceValue3, float& reverseSurfaceValue3, float& surfaceValue4, float& reverseSurfaceValue4, float& surfaceValue5, float& reverseSurfaceValue5) const noexcept;

    bool IsDotInRotatedFigure(COORDS checkedDotCoord) const noexcept;

    bool IsRayCrossRotatedFigure(COORDS startRayCoord, COORDS endRayCoord) const noexcept;

    bool IsRotatedFigureShine(COORDS lightDot, COORDS parSurfaceDot, int rayHitSurfaceNumber);

    bool IsRayCrossNotRotatedFigure(COORDS rayStartCoord, COORDS surfaceDot) const override;

    bool IsRayCrossParaboloid(COORDS rayStartCoord, COORDS surfaceDot) const override;

    bool IsDotInCameraParaboloidRadius(COORDS checkedDot, COORDS cameraCoord, COORDS verCamDir, float farCrossRayAndFigureValue);

    void GroundDotRotation(COORDS& mainDot, float angle) const noexcept;

public:
    Parallelepiped(float length, float width, float height, COORDS centreCoord, bool IsRotateAroundZAxis, bool IsRotateAroundXAxis,
        bool IsRotateAroundYAxis, int color) noexcept;

    void Rotation(float angle, size_t flag = 0) noexcept override;

    COORDS GetParalSize() const noexcept;

    std::string GetTextureName() const noexcept;

    float GetWidthTextureCount() const noexcept;

    float GetHeightTextureCount() const noexcept;

    bool IsHasCollision() const noexcept;

    void SetCollisionMode(bool isHasCollision) noexcept;

    COORDS GetCentreCoord() const noexcept override;

    COORDS& SetCentreCoord() noexcept override;

    Range GetRange() const noexcept override;

    Range& SetRange() noexcept override;

    void UpdateRange(size_t flag = 0) noexcept override;

    objectType GetObjType() const noexcept override;

    bool IsRotate() const noexcept override;

    float& GetLenght() noexcept override;

    float& GetWidth() noexcept override;

    float& GetHeight() noexcept override;

    bool IsParaboloid() const noexcept override;

    bool ToParab(COORDS cameraNormalizeRay, COORDS cameraCoord, COORDS& nearCrossingRayAndFigureCoord, float farCrossingRayAndFigureValue) noexcept override;

    int GetColor() const noexcept override;

    COORDS GetColor(COORDS paralDot) const override;

    bool isObjHasTexture() const noexcept override;

    void SetObjTextureParams(const std::string& textureName, float widthTextureCount, float heightTextureCount) noexcept;

    void SetObjTextureMode(bool) noexcept;

    int& SetColor() noexcept override;
};