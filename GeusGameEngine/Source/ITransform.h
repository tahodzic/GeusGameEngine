#pragma once
class ITransform
{
public:
	virtual ~ITransform() { };

	virtual void Roll(const float change) = 0;

	virtual void Pitch(const float change) = 0;

	virtual void Yaw(const float change) = 0;

	virtual void UpdateRollMatrix() = 0;

	virtual void UpdatePitchMatrix() = 0;

	virtual void UpdateYawMatrix() = 0;

	virtual void CalculateRotations() = 0;

	virtual void LocalToWorld() = 0;
};

