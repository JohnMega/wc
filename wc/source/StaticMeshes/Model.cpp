
#include <iostream>
#include <format>
#include "Model.h"
#include "Preprocessor.h"
#include "Triangle.h"

extern double tick;

Model::Model()
	: currentCentreCoord{ 0,0,0 }
	, oldCentreCoord{ 0,0,0 }
	, animInfo{ .tickSum = 0.0, .frameCounter = 0, .currentFrame = 0 , .isAnimated = false }
	, lastRotateAxis(NULL)
	, angleRotateSum(0.0)
	, isModelRender(true)
{
	polygons.emplace_back();
	objType = objectType::MODEL;
}

Model::Model(const Model& other)
{
	polygons.emplace_back();
	animInfo.currentFrame = 0;
	polygons[0] = other.polygons[other.animInfo.currentFrame];
}

void Model::SetScale(float newScale)
{
	COORDS newSurfaceDot1, newSurfaceDot2, newSurfaceDot3;
	COORDS polygonCentre;
	for (int i = 0; i < (animInfo.frameCounter == 0 ? 1 : polygons.size() / polygons[0].size()); ++i)
		for (int j = 0; j < polygons[i].size(); ++j)
		{
			polygonCentre = polygons[i][j]->GetCentreCoord();

			newSurfaceDot1 = currentCentreCoord + vectorNormalize(((Triangle*)polygons[i][j])->GetSurfaceDot1(), currentCentreCoord) * dotDistance(((Triangle*)polygons[i][j])->GetSurfaceDot1(), currentCentreCoord) * (1 + newScale);
			newSurfaceDot2 = currentCentreCoord + vectorNormalize(((Triangle*)polygons[i][j])->GetSurfaceDot2(), currentCentreCoord) * dotDistance(((Triangle*)polygons[i][j])->GetSurfaceDot2(), currentCentreCoord) * (1 + newScale);
			newSurfaceDot3 = currentCentreCoord + vectorNormalize(((Triangle*)polygons[i][j])->GetSurfaceDot3(), currentCentreCoord) * dotDistance(((Triangle*)polygons[i][j])->GetSurfaceDot3(), currentCentreCoord) * (1 + newScale);

			((Triangle*)polygons[i][j])->SetNewSurfaceDots(newSurfaceDot1, newSurfaceDot2, newSurfaceDot3);

		}

	CalcModelRange();
}

float Model::GetStartPolygonDist() const noexcept
{
	return startPolygonDist;
}

void Model::SetStartPolygonDist(float newStartPolygonDist) noexcept
{
	startPolygonDist = newStartPolygonDist;
}

COORDS Model::GetCentreCoord() const noexcept
{
	return currentCentreCoord;
}

COORDS Model::GetOldCentreCoord() const noexcept
{
	return oldCentreCoord;
}

COORDS& Model::SetCentreCoord() noexcept
{
	oldCentreCoord = currentCentreCoord;
	return currentCentreCoord;
}

bool Model::IsModelRender() const noexcept
{
	return isModelRender;
}

void Model::SetModelRenderMode(bool isModelRender) noexcept
{
	this->isModelRender = isModelRender;
}

Range Model::GetModelRange() noexcept
{
	return modelRange;
}

AnimationInfo Model::GetAnimationInfo() const noexcept
{
	return animInfo;
}

AnimationInfo& Model::SetAnimationInfo() noexcept
{
	return animInfo;
}

std::string& Model::SetFileName() noexcept
{
	return fileName;
}

void Model::AnimationHandle() noexcept
{
	if (animInfo.isAnimated)
	{
		animInfo.tickSum += tick;

		if (animInfo.tickSum >= nextAnimFrameDelay)
		{
			animInfo.tickSum = 0;
			animInfo.currentFrame = (animInfo.currentFrame + 1 == animInfo.frameCounter - 1 ? 0 : animInfo.currentFrame + 1);
		}
	}
}

#pragma push_macro("min")
#pragma push_macro("max")
#undef min
#undef max

void Model::CalcModelRange()
{
	Range modelPar = { .xStart = 10000, .xEnd = -10000, .yStart = 10000, .yEnd = -10000, .zStart = 10000, .zEnd = -10000 };
	for (int i = 0; i < (animInfo.frameCounter == 0 ? 1 : polygons.size() / polygons[0].size()); ++i)
		for (int j = 0; j < polygons[i].size(); ++j)
		{
			float minX, maxX, minY, maxY, minZ, maxZ;
			Triangle* polygon = (Triangle*)polygons[i][j];
			minX = std::min(polygon->GetSurfaceDot1().x, std::min(polygon->GetSurfaceDot2().x, polygon->GetSurfaceDot3().x));
			maxX = std::max(polygon->GetSurfaceDot1().x, std::max(polygon->GetSurfaceDot2().x, polygon->GetSurfaceDot3().x));
			minY = std::min(polygon->GetSurfaceDot1().y, std::min(polygon->GetSurfaceDot2().y, polygon->GetSurfaceDot3().y));
			maxY = std::max(polygon->GetSurfaceDot1().y, std::max(polygon->GetSurfaceDot2().y, polygon->GetSurfaceDot3().y));
			minZ = std::min(polygon->GetSurfaceDot1().z, std::min(polygon->GetSurfaceDot2().z, polygon->GetSurfaceDot3().z));
			maxZ = std::max(polygon->GetSurfaceDot1().z, std::max(polygon->GetSurfaceDot2().z, polygon->GetSurfaceDot3().z));

			modelPar.xStart = std::min(minX, modelPar.xStart);
			modelPar.xEnd = std::max(maxX, modelPar.xEnd);
			modelPar.yStart = std::min(minY, modelPar.yStart);
			modelPar.yEnd = std::max(maxY, modelPar.yEnd);
			modelPar.zStart = std::min(minZ, modelPar.zStart);
			modelPar.zEnd = std::max(maxZ, modelPar.zEnd);
		}

	modelRange = modelPar;
}

void Model::CentreCoordCalc()
{
	CalcModelRange();

	currentCentreCoord = oldCentreCoord = { (modelRange.xStart + modelRange.xEnd) / 2, (modelRange.yStart + modelRange.yEnd) / 2, (modelRange.zStart + modelRange.zEnd) / 2 };
}

#pragma pop_macro("min")
#pragma pop_macro("max")

void Model::UpdateRange(size_t flag) noexcept
{
	if (!currentCentreCoord.x && !currentCentreCoord.y && !currentCentreCoord.z)
		CentreCoordCalc();

	for (int i = 0; i < (animInfo.frameCounter == 0 ? 1 : polygons.size() / polygons[0].size()); ++i)
		for (int j = 0; j < polygons[i].size(); ++j)
		{
			polygons[i][j]->UpdateRange();
		}

	CalcModelRange();
}

void Model::Rotation(float angle, size_t flag)
{
	for (int i = 0; i < (animInfo.frameCounter == 0 ? 1 : polygons.size() / polygons[0].size()); ++i)
		for (int j = 0; j < polygons[i].size(); ++j)
			polygons[i][j]->Rotation(angle, flag);

	if (flag == Z_AXIS_ROTATION_KEY)
	{
		if (lastRotateAxis == Z_AXIS_ROTATION_KEY || lastRotateAxis == NULL)
			angleRotateSum += angle;
		else
		{
			rotateAngles.push_back(std::format("{}{}", lastRotateAxis, angleRotateSum));
			angleRotateSum = 0; angleRotateSum += angle;
			lastRotateAxis = 0;
		}

		lastRotateAxis = Z_AXIS_ROTATION_KEY;
	}
	if (flag == X_AXIS_ROTATION_KEY)
	{
		if (lastRotateAxis == X_AXIS_ROTATION_KEY || lastRotateAxis == NULL)
			angleRotateSum += angle;
		else
		{
			rotateAngles.push_back(std::format("{}{}", lastRotateAxis, angleRotateSum));
			angleRotateSum = 0; angleRotateSum += angle;
			lastRotateAxis = 0;
		}

		lastRotateAxis = X_AXIS_ROTATION_KEY;
	}
	if (flag == Y_AXIS_ROTATION_KEY)
	{
		if (lastRotateAxis == Y_AXIS_ROTATION_KEY || lastRotateAxis == NULL)
			angleRotateSum += angle;
		else
		{
			rotateAngles.push_back(std::format("{}{}", lastRotateAxis, angleRotateSum));
			angleRotateSum = 0; angleRotateSum += angle;
			lastRotateAxis = 0;
		}

		lastRotateAxis = Y_AXIS_ROTATION_KEY;
	}

	CentreCoordCalc();
}

void Model::PushRotationAnglesSum(std::string str) noexcept
{
	rotateAngles.push_back(str);
}

std::vector<std::string> Model::GetRotationAnglesSum() const noexcept
{
	return rotateAngles;
}

char& Model::GetLastRotateAxis() noexcept
{
	return lastRotateAxis;
}

float& Model::GetLastRotateAngleSum() noexcept
{
	return angleRotateSum;
}

std::vector<std::vector<StaticMesh*>>& Model::GetAnimModelPolygons() noexcept
{
	return polygons;
}

std::vector<StaticMesh*>& Model::GetModelPolygons() noexcept
{
	return polygons[animInfo.currentFrame];
}

bool Model::isObjHasTexture() const noexcept
{
	return true;
}