#pragma once

DECLARE_ADDITION_ENUM_FEATURES(SPAWN_SPRITE, SpawnSprite)

#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME SpawnSpriteMenuStarController
class SpawnSpriteMenuStarController : public MenuClass
{
public:
	virtual void DrawMenuStars() override
	{
		if (currentMenuType == MENU_TYPES::SPAWN_SPRITE_MENU) ++currSpawnSpriteMenuState;
	}
};

DECLARE_NEW_MENU_TYPE(EnvStatic, env_static, SPAWN_SPRITE, SpawnSprite, ENV_STATIC)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvStatic)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_SPRITE_MENU && currSpawnSpriteMenuState == SPAWN_SPRITE_MENU_TYPE::ENV_STATIC)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
		{
			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetNormVec(actors[currentObservedActorIndex]->GetStaticMesh()->GetCentreCoord() + COORDS{1,0,0});
			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetCircleRotateMode(!((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->GetCircleRotateMode());
		}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnSpriteInfo.x + 22), SpawnSpriteInfo.y });
	std::cout << "                            ";
}

DECLARE_NEW_MENU_TYPE(EnvLimpid, env_limpid, SPAWN_SPRITE, SpawnSprite, ENV_LIMPID)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvLimpid)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_SPRITE_MENU && currSpawnSpriteMenuState == SPAWN_SPRITE_MENU_TYPE::ENV_LIMPID)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
		{
			((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->SetLimpidMode(true);
		}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnSpriteInfo.x + 22), short(SpawnSpriteInfo.y + 2) });
	std::cout << "                            ";
}

DECLARE_NEW_MENU_TYPE(EnvSpriteTexture, env_texture, SPAWN_SPRITE, SpawnSprite, ENV_SPRITE_TEXTURE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvSpriteTexture)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if(currentMenuType == MENU_TYPES::SPAWN_SPRITE_MENU && currSpawnSpriteMenuState == SPAWN_SPRITE_MENU_TYPE::ENV_SPRITE_TEXTURE)
	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::CIRCLE))
	{
		key = NOTHING_KEY;
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
		showCursor();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnSpriteInfo.x + 22), short(SpawnSpriteInfo.y + 5) });

		std::vector<char> textureName;
		while (key != '\r')
		{
			key = _getche();

			if (key == '\r') break;

			textureName.push_back(key);
		}

		textureName.push_back('\0');
		std::string fileName = "Textures/" + std::string(textureName.data());

		hideCursor();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnSpriteInfo.x + 22), short(SpawnSpriteInfo.y + 5) });
		for (int i = 0; i < 35; ++i)
			std::cout << " ";

		((Circle*)actors[currentObservedActorIndex]->GetStaticMesh())->ChangeTexture(fileName);
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnSpriteInfo.x + 22), short(SpawnSpriteInfo.y + 4) });
	std::cout << "                            ";
}

MenuClass* SpawnSpriteMenuClass = new LAST_MENU_CLASS_NAME;
#undef LAST_MENU_CLASS_NAME
#define LAST_MENU_CLASS_NAME MenuClass