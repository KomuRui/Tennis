#pragma once
#include "../../../Engine/GameObject/GameObject.h"

/// <summary>
/// 様々なエフェクトを管理する
/// </summary>
namespace OtherEffectManager
{
	//着地エフェクト
	void LandingEffect(string effectName, const XMFLOAT3& pos, const float& lifeTime);
}