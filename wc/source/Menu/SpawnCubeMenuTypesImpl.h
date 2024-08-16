#pragma once

DECLARE_ADDITION_ENUM_FEATURES(SPAWN_CUBE, SpawnCube)

#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME SpawnCubeMenuStarController
class SpawnCubeMenuStarController : public MenuClass
{
public:
	virtual void DrawMenuStars() override
	{
		if (currentMenuType == MENU_TYPES::SPAWN_CUBE_MENU) ++currSpawnCubeMenuState;
	}
};

DECLARE_NEW_MENU_TYPE(EnvParab, env_parab, SPAWN_CUBE, SpawnCube, ENV_PARAB)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvParab)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if(currentMenuType == MENU_TYPES::SPAWN_CUBE_MENU && currSpawnCubeMenuState == SPAWN_CUBE_MENU_TYPE::ENV_PARAB)
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED
		|| actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::SKYBOX)
	{
		int index = (currentObservedParalIndex == -1 ? currentObservedActorIndex : currentObservedParalIndex);

		*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[index]->GetStaticMesh()) = (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[index]->GetStaticMesh()) ? false : true);
		if (*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[index]->GetStaticMesh()))
			currentObservedParalIndex = currentObservedActorIndex;
		else
			currentObservedParalIndex = -1;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvParabInfo.x - 2), EnvParabInfo.y });
	std::cout << "                            ";
}

DECLARE_NEW_MENU_TYPE(EnvCollision, env_collision, SPAWN_CUBE, SpawnCube, ENV_COLLISION)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvCollision)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_CUBE_MENU && currSpawnCubeMenuState == SPAWN_CUBE_MENU_TYPE::ENV_COLLISION)
		if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
		{
			((Parallelepiped*)actors[currentObservedActorIndex]->GetStaticMesh())->SetCollisionMode(!((Parallelepiped*)actors[currentObservedActorIndex]->GetStaticMesh())->IsHasCollision());
		}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvCollisionInfo.x - 2), EnvCollisionInfo.y });
	std::cout << "                            ";
}

DECLARE_NEW_MENU_TYPE(EnvCubeTexture, env_texture, SPAWN_CUBE, SpawnCube, ENV_CUBE_TEXTURE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvCubeTexture)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	auto GetKeyboardStr = [](int cursorPosX, int cursorPosY) -> std::vector<char>
		{
			key = NOTHING_KEY;
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			showCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { short(cursorPosX), short(cursorPosY) });

			std::vector<char> result;
			while (key != '\r')
			{
				key = _getche();

				if (key == '\r') break;

				result.push_back(key);
			}

			hideCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(cursorPosX), short(cursorPosY) });
			for (int i = 0; i < 35; ++i)
				std::cout << " ";

			return result;
		};

	if (currentMenuType == MENU_TYPES::SPAWN_CUBE_MENU && currSpawnCubeMenuState == SPAWN_CUBE_MENU_TYPE::ENV_CUBE_TEXTURE)
	if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED
		|| actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::SKYBOX)
	{
		bool isSkybox = actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::SKYBOX;

		std::vector<char> textureName = GetKeyboardStr(EnvCubeTextureInfo.x - 2, EnvCubeTextureInfo.y + 1);
		textureName.push_back('\0');
		std::string fileName = "Textures/" + std::string(textureName.data());

		float widthTextureCount, heightTextureCount;
		if (!isSkybox)
		{
			std::vector<char> widthTextureCountStr = GetKeyboardStr(EnvCubeTextureInfo.x - 2, EnvCubeTextureInfo.y + 2);
			widthTextureCount = atof(widthTextureCountStr.data());
			std::vector<char> heightTextureCountStr = GetKeyboardStr(EnvCubeTextureInfo.x - 2, EnvCubeTextureInfo.y + 3);
			heightTextureCount = atof(heightTextureCountStr.data());
		}
		else
		{
			widthTextureCount = heightTextureCount = 1;
		}

		((Parallelepiped*)actors[currentObservedActorIndex]->GetStaticMesh())->SetObjTextureMode(true);
		((Parallelepiped*)actors[currentObservedActorIndex]->GetStaticMesh())->SetObjTextureParams(fileName, widthTextureCount, heightTextureCount);
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvCubeTextureInfo.x - 2), EnvCubeTextureInfo.y });
	std::cout << "                            ";
}

MenuClass* SpawnCubeMenuClass = new LAST_MENU_CLASS_NAME;
#undef LAST_MENU_CLASS_NAME
#define LAST_MENU_CLASS_NAME MenuClass