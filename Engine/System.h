#pragma once

///////////////////////////////GameObject///////////////////////////////

#include "GameObject/Camera.h"
#include "GameObject/CameraTransitionObject.h"
#include "GameObject/GameObject.h"
#include "GameObject/Light.h"
#include "GameObject/PolyLine.h"
#include "GameObject/RootObject.h"
#include <fstream>

///////////////////////////////ResourceManager///////////////////////////////

#include "ResourceManager/Audio.h"
#include "ResourceManager/CreateStage.h"
#include "ResourceManager/CsvReader.h"
#include "ResourceManager/Easing.h"
#include "ResourceManager/Fade.h"
#include "ResourceManager/Global.h"
#include "ResourceManager/ImageManager.h"
#include "ResourceManager/ModelManager.h"
#include "ResourceManager/Sound.h"
#include "ResourceManager/Text.h"
#include "ResourceManager/Time.h"
#include "ResourceManager/VFX.h"

/////////////////////////////Manager///////////////////////////////////

#include "../Manager/BasePointManager/BasePointManager.h"
#include "../Manager/ButtonManager/ButtonManager.h"
#include "../Manager/EffectManager/EffectManager.h"
#include "../Manager/FrameWorkUpdateManager/FrameWorkUpdateManager.h"
#include "../Manager/TextManager/TextManager.h"
#include "../Manager/GameManager/GameManager.h"
#include "../Manager/JsonManager/JsonManager.h"
#include "../Manager/SceneManager/SceneManager.h"
#include "../Manager/EffectManager/OtherEffectManager/OtherEffectManager.h"

/////////////////////////////Component///////////////////////////////////

#include "Component/EasingMove.h"
#include "Component/Gauge.h"
#include "Component/Model.h"
#include "Component/Posture.h"
#include "Component/Transform/Transform.h"
#include "Component/Collider/BoxCollider.h"
#include "Component/Collider/SphereCollider.h"

/////////////////////////////json///////////////////////////////////

#include "nlohmann/json.hpp"
using json = nlohmann::json;

/////////////////////////////GUI///////////////////////////////////

#include "GUI/ImGuiSet.h"

/////////////////////////////DirectX///////////////////////////////////

#include "DirectX/Input.h"
#include "DirectX/Sprite.h"
#include "DirectX/Texture.h"