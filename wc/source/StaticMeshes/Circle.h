#pragma once

#include <iostream>
#include "bitmap.h"
#include "Maths.h"
#include "StaticMesh.h"

class Circle : public StaticMesh
{
private:
	COORDS normVec;
	COORDS centreCoord;
	COORDS surfaceDot1, surfaceDot2;

	Bitmap bitmap;
	PixelMatrix bmpPixelMatrix;
	std::string textureName;
	COORDS localCentreCoord;
	COORDS localXVec, localYVec;

	float rad;
	int color;
	bool isCircleRotate;
	bool isLimpid;

private:
	COORDS CircleDotToLocalCoords(COORDS circleDot) const;

	void UpdateTextureVars();

public:
	Circle(COORDS centreCoord, COORDS normVec, const std::string& bmpName, float rad, int color);

	COORDS& SetCentreCoord() noexcept override;

	COORDS GetCentreCoord() const noexcept override;

	COORDS GetNormVec() const noexcept;

	void SetLimpidMode(bool limpidMode) noexcept;

	bool GetLimpidMode() const noexcept;

	Range GetCircleRange() const noexcept;

	void SetNormVec(COORDS dot);

	void SetRad(float newRad);

	float GetRad() const noexcept;

	void SetCircleRotateMode(bool circleRotateMode);

	bool GetCircleRotateMode() const noexcept;

	COORDS isRayIntersectCircle(COORDS startRayDot, COORDS endRayDot);

	bool isObjHasTexture() const noexcept override;

	void ChangeTexture(const std::string& newTextureName);

	std::string GetTextureName() const noexcept;

	COORDS GetColor(COORDS circleDot) const override;
};