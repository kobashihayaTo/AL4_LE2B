#pragma once

#include "CollisionPrimitive.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane&
		plane, DirectX::XMVECTOR* inter = nullptr);
};

