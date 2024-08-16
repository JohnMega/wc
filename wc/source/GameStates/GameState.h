#pragma once

class GameState
{
public:
	virtual void OnKeyEsc();

	virtual void OnEnterKey();

	virtual void OnArrowUpDownKey()
	{ }

	virtual void OnObjControlKey()
	{ }

	virtual void OnBaseLenghtKey()
	{ }

	virtual void OnBaseWidthKey()
	{ }

	virtual void OnHeightKey()
	{ }

	virtual void OnAdditionalLengthKey()
	{ }

	virtual void OnAdditionalWidthKey()
	{ }

	virtual void OnZAxisRotationKey()
	{ }

	virtual void OnXAxisRotationKey()
	{ }

	virtual void OnYAxisRotationKey()
	{ }

	virtual void OnLightPowerAndParabRadKey();

	virtual void OnDeleteKey();

	virtual void OnFreezeKey()
	{ }

	virtual void OnSpawnParabKey()
	{ }

	virtual void OnColorChangeKey()
	{ }

	virtual void OnRayFromCameraKey();
};