
#include "Circle.h"

COORDS Circle::CircleDotToLocalCoords(COORDS circleDot) const
{
	float x = dotDistance(localCentreCoord, circleDot) * cos(fromDegreesToRad(GetAngleBetweenVectors(localCentreCoord, circleDot, localXVec)));
	float y = dotDistance(localCentreCoord, circleDot) * sin(fromDegreesToRad(GetAngleBetweenVectors(localCentreCoord, circleDot, localXVec)));

	return { x, y, 0 };
}

Circle::Circle(COORDS centreCoord, COORDS normVec, const std::string& bmpName, float rad, int color)
	: centreCoord(centreCoord)
	, normVec(normVec)
	, textureName(bmpName)
	, rad(rad)
	, color(color)
	, isCircleRotate(true)
	, isLimpid(false)
{
	UpdateTextureVars();

	bitmap.open(bmpName);
	bmpPixelMatrix = bitmap.toPixelMatrix();

	objType = objectType::CIRCLE;
}

void Circle::UpdateTextureVars()
{
	COORDS up = GetVectorRotateZOnAngle(normVec, 90);
	COORDS down = up * (-1);
	COORDS left = { up.y * normVec.z - up.z * normVec.y, up.z * normVec.x - up.x * normVec.z, up.x * normVec.y - up.y * normVec.x };
	COORDS right = left * (-1);

	surfaceDot1 = left + centreCoord;
	surfaceDot2 = up + centreCoord;

	localCentreCoord = (right * rad + centreCoord) + up * rad;
	localXVec = vectorNormalize(localCentreCoord + left * rad, localCentreCoord) + localCentreCoord;
	localYVec = vectorNormalize(localCentreCoord + down * rad, localCentreCoord) + localCentreCoord;
}

COORDS& Circle::SetCentreCoord() noexcept
{
	return centreCoord;
}

COORDS Circle::GetCentreCoord() const noexcept
{
	return centreCoord;
}

COORDS Circle::GetNormVec() const noexcept
{
	return normVec;
}

void Circle::SetNormVec(COORDS dot)
{
	if(isCircleRotate)
		normVec = vectorNormalize(dot, centreCoord);

	UpdateTextureVars();
}

void Circle::SetLimpidMode(bool limpidMode) noexcept
{
	isLimpid = limpidMode;
}

bool Circle::GetLimpidMode() const noexcept
{
	return isLimpid;
}

Range Circle::GetCircleRange() const noexcept
{
	return { centreCoord.x - rad, centreCoord.x + rad
		, centreCoord.y - rad, centreCoord.y + rad
		, centreCoord.z - rad, centreCoord.z + rad };
}

void Circle::SetRad(float newRad)
{
	rad = newRad;
}

float Circle::GetRad() const noexcept
{
	return rad;
}

void Circle::SetCircleRotateMode(bool circleRotateMode)
{
	isCircleRotate = circleRotateMode;
}

bool Circle::GetCircleRotateMode() const noexcept
{
	return isCircleRotate;
}

COORDS Circle::isRayIntersectCircle(COORDS startRayDot, COORDS endRayDot)
{
	COORDS dotProjection = GetCrossingSurfaceAndLineCoords(centreCoord, surfaceDot1, surfaceDot2, normVec, startRayDot, endRayDot);

	if (dotDistance(centreCoord, dotProjection) <= rad)
		return dotProjection;
	else
		return { 0, 0, 0 };
}

void Circle::ChangeTexture(const std::string& newTextureName)
{
	textureName = newTextureName;
	bitmap.open(newTextureName);
	bmpPixelMatrix = bitmap.toPixelMatrix();
}

bool Circle::isObjHasTexture() const noexcept
{
	return true;
}

std::string Circle::GetTextureName() const noexcept
{
	return textureName;
}

COORDS Circle::GetColor(COORDS circleDot) const
{
	COORDS newCircleDot = CircleDotToLocalCoords(circleDot);
	COORDS scalingNewCircleDot = { newCircleDot.x * (bitmap.wight / (rad * 2)), newCircleDot.y * (bitmap.height / (rad * 2)), newCircleDot.z };

	int line, column;

	try
	{
		line = scalingNewCircleDot.y > bmpPixelMatrix.size() || scalingNewCircleDot.y < 0 ? 0 : (int)scalingNewCircleDot.y;
		column = scalingNewCircleDot.x > bmpPixelMatrix.at(line).size() || scalingNewCircleDot.x < 0 ? 0 : (int)scalingNewCircleDot.x;
		bmpPixelMatrix.at(line).at(column);
	}
	catch (...)
	{
		line = column = 0;
	}

	BmpPixel currentPolygonRGBColor = bmpPixelMatrix[line][column];
	return { (float)currentPolygonRGBColor.red, (float)currentPolygonRGBColor.green, (float)currentPolygonRGBColor.blue };
}