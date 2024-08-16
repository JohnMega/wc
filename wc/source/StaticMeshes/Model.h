#pragma once

#include <vector>
#include <string>
#include "StaticMesh.h"

struct AnimationInfo
{
	float tickSum;
	int frameCounter;
	int currentFrame;
	bool isAnimated;
};

class Model : public StaticMesh
{
	static inline float nextAnimFrameDelay = 0.05f;

private:
	std::string fileName; // Dont move it
	std::vector<std::vector<StaticMesh*>> polygons;
	std::vector<COORDS> modelsCentreCoords;
	std::vector<std::string> rotateAngles;
	COORDS currentCentreCoord;
	COORDS oldCentreCoord;
	Range modelRange;
	AnimationInfo animInfo;
	char lastRotateAxis;
	float angleRotateSum;
	float startPolygonDist;
	bool isModelRender;
	
public:
	Model();

	Model(const Model&);

	std::vector<StaticMesh*>& GetModelPolygons() noexcept override;

	std::vector<std::vector<StaticMesh*>>& GetAnimModelPolygons() noexcept;

	void Rotation(float angle, size_t flag = 0) override;

	std::vector<std::string> GetRotationAnglesSum() const noexcept;

	void SetScale(float newScale);

	float GetStartPolygonDist() const noexcept;

	void SetStartPolygonDist(float newStartPolygonDist) noexcept;

	void CalcModelRange();

	void CentreCoordCalc();

	void PushRotationAnglesSum(std::string str) noexcept;

	char& GetLastRotateAxis() noexcept;

	float& GetLastRotateAngleSum() noexcept;

	COORDS GetCentreCoord() const noexcept override;

	COORDS& SetCentreCoord() noexcept override;

	bool IsModelRender() const noexcept;

	void SetModelRenderMode(bool isModelRender) noexcept;

	std::string& SetFileName() noexcept;

	void AnimationHandle() noexcept;

	Range GetModelRange() noexcept;

	void UpdateRange(size_t flag = 0) noexcept override;

	AnimationInfo GetAnimationInfo() const noexcept;

	AnimationInfo& SetAnimationInfo() noexcept;

	COORDS GetOldCentreCoord() const noexcept;

	bool isObjHasTexture() const noexcept override;
};