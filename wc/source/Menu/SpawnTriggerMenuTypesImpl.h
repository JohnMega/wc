#pragma once

DECLARE_ADDITION_ENUM_FEATURES(SPAWN_TRIGGER, SpawnTrigger)

#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME SpawnTriggerMenuStarController
class SpawnTriggerMenuStarController : public MenuClass
{
public:
	virtual void DrawMenuStars() override
	{
		if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU) ++currSpawnTriggerMenuState;
	}
};

void ClearAllTriggetText()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SetObservedObjectInfo.x - 2), SetObservedObjectInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(MoveToDotInfo.x - 2), MoveToDotInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(TeleportToDotInfo.x - 2), TeleportToDotInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvShakeOnInfo.x - 2), EnvShakeOnInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvShakeOffInfo.x - 2), EnvShakeOffInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvFadeOnInfo.x - 2), EnvFadeOnInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(EnvFadeOffInfo.x - 2), EnvFadeOffInfo.y });
	std::cout << "                            ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(ObjectRenderOffInfo.x - 2), ObjectRenderOffInfo.y });
	std::cout << "                            ";
}

DECLARE_NEW_MENU_TYPE(MoveToDot, Move to dot, SPAWN_TRIGGER, SpawnTrigger, MOVE_TO_DOT)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(MoveToDot)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();
	ClearAllTriggetText();

	if(currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::MOVE_TO_DOT)
	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			currentGameState = buildModeState;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 1)});
			float xCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 1) });
			std::cout << "                         ";

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 2) });
			float yCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 2) });
			std::cout << "                         ";

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 3) });
			float zCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 3) });
			std::cout << "                         ";

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 4) });
			float speed = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { MoveToDotInfo.x, short(MoveToDotInfo.y + 4) });
			std::cout << "                         ";

			AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
				, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::MOVE_TO_DOT), new ATriggerLine::MoveToDotInfo({xCoord,yCoord,zCoord}, speed));
			typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;
			
			key = NOTHING_KEY;
		}
}

DECLARE_NEW_MENU_TYPE(TeleportToDot, Teleport to dot, SPAWN_TRIGGER, SpawnTrigger, TELEPORT_TO_DOT)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(TeleportToDot)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::TELEPORT_TO_DOT)
	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
	{
		ClearAllTriggetText();
		currentGameState = buildModeState;

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 1) });
		float xCoord = atof(MyCin().c_str());
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 1) });
		std::cout << "                         ";

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 2) });
		float yCoord = atof(MyCin().c_str());
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 2) });
		std::cout << "                         ";

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 3) });
		float zCoord = atof(MyCin().c_str());
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { TeleportToDotInfo.x, short(TeleportToDotInfo.y + 3) });
		std::cout << "                         ";

		AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
			, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::TELEPORT_TO_DOT), new ATriggerLine::TeleportToDotInfo({ xCoord,yCoord,zCoord }));
		typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

		currentObservedActorIndex = actors.size() - 3;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(ObjectRenderOff, Object Render Off, SPAWN_TRIGGER, SpawnTrigger, OBJECT_RENDER_OFF)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(ObjectRenderOff)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::OBJECT_RENDER_OFF)
	if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
	{
		ClearAllTriggetText();
		currentGameState = buildModeState;

		AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
			, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::OBJECT_RENDER_OFF), new ATriggerLine::ObjectRenderOffInfo);
		typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

		currentObservedActorIndex = actors.size() - 3;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(EnvShakeOn, Env Shake On, SPAWN_TRIGGER, SpawnTrigger, ENV_SHAKE_ON)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvShakeOn)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::ENV_SHAKE_ON)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			currentGameState = buildModeState;

			AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
				, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::ENV_SHAKE_ON), new ATriggerLine::EnvShakeOnInfo);
			typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;

			key = NOTHING_KEY;
		}
}

DECLARE_NEW_MENU_TYPE(EnvShakeOff, Env Shake Off, SPAWN_TRIGGER, SpawnTrigger, ENV_SHAKE_OFF)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvShakeOff)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::ENV_SHAKE_OFF)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			currentGameState = buildModeState;

			AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
				, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::ENV_SHAKE_OFF), new ATriggerLine::EnvShakeOffInfo);
			typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;

			key = NOTHING_KEY;
		}
}

DECLARE_NEW_MENU_TYPE(EnvFadeOn, Env Fade On, SPAWN_TRIGGER, SpawnTrigger, ENV_FADE_ON)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvFadeOn)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::ENV_FADE_ON)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			currentGameState = buildModeState;

			AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
				, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::ENV_FADE_ON), new ATriggerLine::EnvFadeOnInfo);
			typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;

			key = NOTHING_KEY;
		}
}

DECLARE_NEW_MENU_TYPE(EnvFadeOff, Env Fade Off, SPAWN_TRIGGER, SpawnTrigger, ENV_FADE_OFF)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(EnvFadeOff)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::ENV_FADE_OFF)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			currentGameState = buildModeState;

			AddActorToStorage<ATriggerLine>(actors, actors[currentObservedActorIndex]->GetStaticMesh()
				, static_cast<int>(SPAWN_TRIGGER_MENU_TYPE::ENV_FADE_OFF), new ATriggerLine::EnvFadeOffInfo);
			typesOfActors.push_back(static_cast<int>(logicActorType::TRIGGER_LINE));

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;

			key = NOTHING_KEY;
		}
}

DECLARE_NEW_MENU_TYPE(SetObservedObject, Set Observed Object, SPAWN_TRIGGER, SpawnTrigger, SET_OBSERVED_OBJECT)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SetObservedObject)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currentMenuType == MENU_TYPES::SPAWN_TRIGGER_MENU && currSpawnTriggerMenuState == SPAWN_TRIGGER_MENU_TYPE::SET_OBSERVED_OBJECT)
		if (typesOfActors[currentObservedActorIndex - 1] == static_cast<int>(objectType::TRIGGER))
		{
			ClearAllTriggetText();
			//currentGameState = buildModeState;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 1) });
			float xCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 1) });
			std::cout << "                         ";

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 2) });
			float yCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 2) });
			std::cout << "                         ";

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 3) });
			float zCoord = atof(MyCin().c_str());
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SetObservedObjectInfo.x, short(SetObservedObjectInfo.y + 3) });
			std::cout << "                         ";

			float minDist = 10000;
			int index = 0;
			for (size_t i = 1; i < actors.size(); ++i)
			{
				if (actors[i]->isActorHasStaticMesh())
				{
					if (dotDistance(COORDS{ xCoord, yCoord, zCoord }, actors[i]->GetStaticMesh()->GetCentreCoord()) < minDist)
					{
						minDist = dotDistance(COORDS{ xCoord, yCoord, zCoord }, actors[i]->GetStaticMesh()->GetCentreCoord());
						index = i;
					}
				}
			}

			((ATriggerActor*)actors[currentObservedActorIndex])->observedObjCentreCoord = actors[index]->GetStaticMesh()->GetCentreCoord();

			currentObservedActorIndex = actors.size() - 3;
			currMenuState = EDITOR_STATE::GAME;

			key = NOTHING_KEY;
		}
}

MenuClass* SpawnTriggerMenuClass = new LAST_MENU_CLASS_NAME;
#undef LAST_MENU_CLASS_NAME
#define LAST_MENU_CLASS_NAME MenuClass