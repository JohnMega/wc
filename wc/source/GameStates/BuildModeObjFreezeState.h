#pragma once

#include "BuildModeState.h"

class BuildModeObjFreezeState : public BuildModeState
{
public:
	void OnArrowUpDownKey() override;

	void OnObjControlKey() override;

	void OnBaseLenghtKey() override;

	void OnBaseWidthKey() override;

	void OnHeightKey() override;

	void OnAdditionalLengthKey() override;

	void OnAdditionalWidthKey() override;

	void OnZAxisRotationKey() override;

	void OnXAxisRotationKey() override;

	void OnYAxisRotationKey() override;

	void OnLightPowerAndParabRadKey() override;

	void OnFreezeKey() override;

	void OnSpawnParabKey() override;

	void OnColorChangeKey() override;
};