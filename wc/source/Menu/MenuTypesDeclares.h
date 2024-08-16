#pragma once

#include <iostream>
#include <Windows.h>

#include "Maths.h"
#include "Preprocessor.h"
#include "ACamera.h"
#include "ASpectatorCamera.h"
#include "Pixel.h"
#include "StaticMesh.h"
#include "Parallelepiped.h"
#include "Pyramid.h"
#include "Triangle.h"
#include "Light.h"
#include "AActor.h"
#include "Delegate.h"
#include "ATriggerActor.h"
#include "ABaseActor.h"
#include "ALightActor.h"
#include "Model.h"
#include "FileLoader.h"

#define LAST_MENU_CLASS_NAME MenuClass

#define GET_LAST_MENU_CLASS_NAME_INNER(ProgName) CheckAdd##ProgName##ToStorage
#define GET_LAST_MENU_CLASS_NAME(ProgName) GET_LAST_MENU_CLASS_NAME_INNER(ProgName)

#define START_OF_DECLARE_MENU_ENUM_TYPES(MenuTypeName) \
enum class MenuTypeName##_MENU_TYPE : char { 

#define DECLARE_MENU_ENUM_TYPE(EnumName) EnumName,

#define END_OF_DECLARE_MENU_ENUM_TYPES() \
	END_OF_LIST };

#define DECLARE_ADDITION_ENUM_FEATURES(MenuTypeName, VarMenuTypeName) \
MenuTypeName##_MENU_TYPE curr##VarMenuTypeName##MenuState; \
\
MenuTypeName##_MENU_TYPE& operator++( MenuTypeName##_MENU_TYPE& type ) \
{ \
	type = static_cast<MenuTypeName##_MENU_TYPE>(static_cast<int>(type) + 1); \
	if (type == MenuTypeName##_MENU_TYPE::END_OF_LIST) \
		type = static_cast<MenuTypeName##_MENU_TYPE>(0); \
	return type; \
}

#define DECLARE_NEW_MENU_TYPE_INNER(ProgName, MenuName, MenuTypeName, VarMenuTypeName, EnumName) \
bool isInBuildModeOn##ProgName = false; \
\
class GET_LAST_MENU_CLASS_NAME(ProgName) : public LAST_MENU_CLASS_NAME \
{ \
using Super = LAST_MENU_CLASS_NAME; \
public: \
	virtual void DrawMenuTypes() override \
	{ \
		LAST_MENU_CLASS_NAME::DrawMenuTypes(); \
		\
		if(currentMenuType == MENU_TYPES::##MenuTypeName##_MENU) \
		{ \
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ProgName##Info.x, ProgName##Info.y }); \
				std::cout << #MenuName; \
		} \
	} \
	virtual void DrawMenuStars() override \
	{ \
		LAST_MENU_CLASS_NAME::DrawMenuStars(); \
			\
			if(currentMenuType == MENU_TYPES::##MenuTypeName##_MENU) \
			{ \
			if (curr##VarMenuTypeName##MenuState == MenuTypeName##_MENU_TYPE::##EnumName) \
			{ \
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ProgName##Info.x - 2, ProgName##Info.y }); \
				std::cout << "*"; \
			}\
			else \
			{ \
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ProgName##Info.x - 2, ProgName##Info.y }); \
				std::cout << " "; \
			} \
			} \
	} \
	virtual void ClearMenuTypes() override \
	{ \
		LAST_MENU_CLASS_NAME::ClearMenuTypes(); \
		\
		if(currentMenuType == MENU_TYPES::##MenuTypeName##_MENU) \
		{ \
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { ProgName##Info.x - 2, ProgName##Info.y }); \
			std::cout << "                         "; \
		} \
	} \
	virtual void CheckAddMenuTypesToStorage() override; \
};

#define DECLARE_NEW_MENU_TYPE(ProgName, MenuName, MenuTypeName, VarMenuTypeName, EnumName) \
    DECLARE_NEW_MENU_TYPE_INNER(ProgName, MenuName, MenuTypeName, VarMenuTypeName, EnumName)

#define DECLARE_FORMARD_DECLARATIONS_INNER(ProgName, MenuName, EnumName, XPos, YPos) \
struct \
{ \
short x = XPos; \
short y = YPos; \
} ProgName##Info;

#define DECLARE_FORMARD_DECLARATIONS(ProgName, MenuName, EnumName, XPos, YPos) \
	DECLARE_FORMARD_DECLARATIONS_INNER(ProgName, MenuName, EnumName, XPos, YPos)

#define DECLARE_MENU_CLASS() \
class MenuClass \
{ \
public: \
	virtual void DrawMenuTypes() { } \
	virtual void DrawMenuStars() { } \
	virtual void ClearMenuTypes() { } \
	virtual void CheckAddMenuTypesToStorage() { } \
};

/////////////////////////////////////////////////

enum class MENU_TYPES { EDITOR_MENU, SPAWN_CUBE_MENU, SPAWN_SPRITE_MENU, SPAWN_TRIGGER_MENU };
static MENU_TYPES currentMenuType = MENU_TYPES::EDITOR_MENU;
DECLARE_MENU_CLASS()

// General Menu Declare
START_OF_DECLARE_MENU_ENUM_TYPES(EDITOR)
	DECLARE_MENU_ENUM_TYPE(SPAWN_CUBE)
	DECLARE_MENU_ENUM_TYPE(SPAWN_PYRAMID)
	DECLARE_MENU_ENUM_TYPE(SPAWN_LIGHT)
	DECLARE_MENU_ENUM_TYPE(SPAWN_PLAYER)
	DECLARE_MENU_ENUM_TYPE(SPAWN_MODEL)
	DECLARE_MENU_ENUM_TYPE(SPAWN_ENV_FIRE)
	DECLARE_MENU_ENUM_TYPE(SPAWN_SPRITE)
	DECLARE_MENU_ENUM_TYPE(SPAWN_ENV_PARTICLES)
	DECLARE_MENU_ENUM_TYPE(SPAWN_ENV_CUBEMAP)
	DECLARE_MENU_ENUM_TYPE(SPAWN_CLIP_WALL)
	DECLARE_MENU_ENUM_TYPE(SPAWN_TRIGGER)
	DECLARE_MENU_ENUM_TYPE(SPAWN_AREA_PORTAL)
	DECLARE_MENU_ENUM_TYPE(SPAWN_ENV_SHAKE)
	DECLARE_MENU_ENUM_TYPE(SPAWN_SKY_CAMERA)
	DECLARE_MENU_ENUM_TYPE(SPAWN_VOLUME_SKYBOX)
	DECLARE_MENU_ENUM_TYPE(SPAWN_ENV_FADE)
	DECLARE_MENU_ENUM_TYPE(LOAD_TO_FILE)
	DECLARE_MENU_ENUM_TYPE(LOAD_MAP)
END_OF_DECLARE_MENU_ENUM_TYPES()

DECLARE_FORMARD_DECLARATIONS(LoadMap, Load Map, LOAD_MAP, SCREEN_WIDTH + 5, 1)
DECLARE_FORMARD_DECLARATIONS(SpawnCube, Spawn Cube, SPAWN_CUBE, SCREEN_WIDTH + 5, 5)
DECLARE_FORMARD_DECLARATIONS(SpawnPyramid, Spawn Pyramid, SPAWN_PYRAMID, SCREEN_WIDTH + 5, 6)
DECLARE_FORMARD_DECLARATIONS(SpawnLight, Spawn Light, SPAWN_LIGHT, SCREEN_WIDTH + 5, 7)
DECLARE_FORMARD_DECLARATIONS(SpawnPlayer, Spawn Player, SPAWN_PLAYER, SCREEN_WIDTH + 5, 8)
DECLARE_FORMARD_DECLARATIONS(SpawnModel, Spawn Model, SPAWN_MODEL, SCREEN_WIDTH + 5, 9)
DECLARE_FORMARD_DECLARATIONS(SpawnEnvFire, Spawn Env Fire, SPAWN_ENV_FIRE, SCREEN_WIDTH + 5, 10)
DECLARE_FORMARD_DECLARATIONS(SpawnSprite, Spawn Sprite, SPAWN_SPRITE, SCREEN_WIDTH + 5, 11)
DECLARE_FORMARD_DECLARATIONS(SpawnEnvParticles, Spawn Env Particles, SPAWN_ENV_PARTICLES, SCREEN_WIDTH + 5, 12)
DECLARE_FORMARD_DECLARATIONS(SpawnEnvCubemap, Spawn Env Cubemap, SPAWN_ENV_CUBEMAP, SCREEN_WIDTH + 5, 13)
DECLARE_FORMARD_DECLARATIONS(SpawnClipWall, Spawn Clip Wall, SPAWN_CLIP_WALL, SCREEN_WIDTH + 5, 14)
DECLARE_FORMARD_DECLARATIONS(SpawnTrigger, Spawn Trigger, SPAWN_TRIGGER, SCREEN_WIDTH + 5, 15)
DECLARE_FORMARD_DECLARATIONS(SpawnAreaPortal, Spawn Area Portal, SPAWN_AREA_PORTAL, SCREEN_WIDTH + 5, 16)
DECLARE_FORMARD_DECLARATIONS(SpawnEnvShake, Spawn Env Shake, SPAWN_ENV_SHAKE, SCREEN_WIDTH + 5, 17)
DECLARE_FORMARD_DECLARATIONS(SpawnSkyCamera, Spawn Sky Camera, SPAWN_SKY_CAMERA, SCREEN_WIDTH + 5, 18)
DECLARE_FORMARD_DECLARATIONS(SpawnVolumeSkybox, Spawn Volume Skybox, SPAWN_VOLUME_SKYBOX, SCREEN_WIDTH + 5, 19)
DECLARE_FORMARD_DECLARATIONS(SpawnEnvFade, Spawn Env Fade, SPAWN_ENV_FADE, SCREEN_WIDTH + 5, 20)
DECLARE_FORMARD_DECLARATIONS(LoadToFile, Load to file, LOAD_TO_FILE, SCREEN_WIDTH + 5, 22)


// Spawn Cube Menu Declare
START_OF_DECLARE_MENU_ENUM_TYPES(SPAWN_CUBE)
	DECLARE_MENU_ENUM_TYPE(ENV_PARAB)
	DECLARE_MENU_ENUM_TYPE(ENV_COLLISION)
	DECLARE_MENU_ENUM_TYPE(ENV_CUBE_TEXTURE)
END_OF_DECLARE_MENU_ENUM_TYPES()

DECLARE_FORMARD_DECLARATIONS(EnvParab, env_parab, ENV_PARAB, SpawnCubeInfo.x + 18, SpawnCubeInfo.y)
DECLARE_FORMARD_DECLARATIONS(EnvCollision, env_collision, ENV_COLLISION, SpawnCubeInfo.x + 18, SpawnCubeInfo.y + 2)
DECLARE_FORMARD_DECLARATIONS(EnvCubeTexture, env_texture, ENV_CUBE_TEXTURE, SpawnCubeInfo.x + 18, SpawnCubeInfo.y + 4)


// Spawn Sprite Menu Declare
START_OF_DECLARE_MENU_ENUM_TYPES(SPAWN_SPRITE)
	DECLARE_MENU_ENUM_TYPE(ENV_STATIC)
	DECLARE_MENU_ENUM_TYPE(ENV_LIMPID)
	DECLARE_MENU_ENUM_TYPE(ENV_SPRITE_TEXTURE)
END_OF_DECLARE_MENU_ENUM_TYPES()

DECLARE_FORMARD_DECLARATIONS(EnvStatic, env_static, ENV_STATIC, SpawnSpriteInfo.x + 24, SpawnSpriteInfo.y)
DECLARE_FORMARD_DECLARATIONS(EnvLimpid, env_limpid, ENV_LIMPID, SpawnSpriteInfo.x + 24, SpawnSpriteInfo.y + 2)
DECLARE_FORMARD_DECLARATIONS(EnvSpriteTexture, env_texture, ENV_SPRITE_TEXTURE, SpawnSpriteInfo.x + 24, SpawnSpriteInfo.y + 4)


// Spawn Trigger Menu Declare
START_OF_DECLARE_MENU_ENUM_TYPES(SPAWN_TRIGGER)
	DECLARE_MENU_ENUM_TYPE(MOVE_TO_DOT)
	DECLARE_MENU_ENUM_TYPE(TELEPORT_TO_DOT)
	DECLARE_MENU_ENUM_TYPE(OBJECT_RENDER_OFF)
	DECLARE_MENU_ENUM_TYPE(ENV_SHAKE_ON)
	DECLARE_MENU_ENUM_TYPE(ENV_SHAKE_OFF)
	DECLARE_MENU_ENUM_TYPE(ENV_FADE_ON)
	DECLARE_MENU_ENUM_TYPE(ENV_FADE_OFF)
	DECLARE_MENU_ENUM_TYPE(SET_OBSERVED_OBJECT)
END_OF_DECLARE_MENU_ENUM_TYPES()

DECLARE_FORMARD_DECLARATIONS(MoveToDot, Move to dot, MOVE_TO_DOT, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y)
DECLARE_FORMARD_DECLARATIONS(TeleportToDot, Teleport to dot, TELEPORT_TO_DOT, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 2)
DECLARE_FORMARD_DECLARATIONS(ObjectRenderOff, Object Render Off, OBJECT_RENDER_OFF, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 4)
DECLARE_FORMARD_DECLARATIONS(EnvShakeOn, Env Shake On, ENV_SHAKE_ON, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 6)
DECLARE_FORMARD_DECLARATIONS(EnvShakeOff, Env Shake Off, ENV_SHAKE_OFF, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 8)
DECLARE_FORMARD_DECLARATIONS(EnvFadeOn, Env Fade On, ENV_FADE_ON, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 10)
DECLARE_FORMARD_DECLARATIONS(EnvFadeOff, Env Fade Off, ENV_FADE_OFF, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 12)
DECLARE_FORMARD_DECLARATIONS(SetObservedObject, Set Observed Object, SET_OBSERVED_OBJECT, SpawnTriggerInfo.x + 24, SpawnCubeInfo.y + 14)