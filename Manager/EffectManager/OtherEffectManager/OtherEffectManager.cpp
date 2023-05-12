#include "OtherEffectManager.h"
#include "../../../Engine/ResourceManager/Global.h"
#include "../../GameManager/GameManager.h"
#include "../../../Engine/ResourceManager/VFX.h"

/// <summary>
/// 様々なエフェクトを管理する
/// </summary>
namespace OtherEffectManager
{
	//着地エフェクト
	int LandingEffect(const XMFLOAT3& pos , const float& lifeTime)
	{
		EmitterData data2;
		data2.textureFileName = "Image/Effect/defaultParticle.png";
		data2.position = pos;
		data2.delay = 0;
		data2.number = 1;
		data2.speed = 0.0f;
		data2.rotate.x = 90;
		data2.isBillBoard = false;
		data2.lifeTime = lifeTime * 60;
		data2.size = XMFLOAT2(3, 3);
		data2.color = XMFLOAT4(1, 0, 0, 1);
		return VFX::Start(data2);
	}
}