#pragma once

DECLARE_ADDITION_ENUM_FEATURES(EDITOR, Editor)

#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME EditorMenuStarController
class EditorMenuStarController : public MenuClass 
{
public:
	virtual void DrawMenuStars() override
	{
		if (currentMenuType == MENU_TYPES::EDITOR_MENU) ++currEditorMenuState;
	}
};

DECLARE_NEW_MENU_TYPE(LoadMap, Load Map, EDITOR, Editor, LOAD_MAP)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(LoadMap)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::LOAD_MAP)
	{
		static const int otherActorsStartIndex = 13;
		int actorsSize = actors.size();
		for (size_t i = otherActorsStartIndex; i < actorsSize; ++i)
			actors.pop_back();

		static const int otherTypesOfActorsStartIndex = 12;
		int typesOfActorsSize = typesOfActors.size();
		for (size_t i = otherTypesOfActorsStartIndex; i < typesOfActorsSize; ++i)
			typesOfActors.pop_back();

		movementArrowsActor->DisablePartsOnObject();
		rotatedCirclesActor->DisablePartsOnObject();
		movementScalesActor->DisablePartsOnObject();

		key = NOTHING_KEY;
		LoadMapToGame();

		currentObservedParalIndex = -1;
		currentGameState = defaultGameState;
		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnCube, Spawn Cube, EDITOR, Editor, SPAWN_CUBE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnCube)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_CUBE)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnCube = true;
		AddActorToStorage<ABaseActor>(actors, new Parallelepiped(5, 5, 5, { 0, 0, 0 }, false, false, false, 3));
		typesOfActors.push_back(static_cast<int>(EDITOR_MENU_TYPE::SPAWN_CUBE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnPyramid, Spawn Pyramid, EDITOR, Editor, SPAWN_PYRAMID)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnPyramid)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_PYRAMID)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnPyramid = true;
		AddActorToStorage<ABaseActor>(actors, new Pyramid(5, 5, 3, 2, 2, { 0, 0, 0 }, 6));
		typesOfActors.push_back(static_cast<int>(EDITOR_MENU_TYPE::SPAWN_PYRAMID));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnLight, Spawn Light, EDITOR, Editor, SPAWN_LIGHT)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnLight)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_LIGHT)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnLight = true;
		AddActorToStorage<ALightActor>(actors, new Light({ 1000, {0, 0,0} }), new Circle({ 0,0,0 }, { 1,0,0 }, "Textures/env_light/env_light0.bmp", 1, 5));
		typesOfActors.push_back(static_cast<int>(EDITOR_MENU_TYPE::SPAWN_LIGHT));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnPlayer, Spawn Player, EDITOR, Editor, SPAWN_PLAYER)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnPlayer)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_PLAYER)
	{
		std::string fileName = "playerstart";
		std::string objFileNameWithExtensions = "Models/playerstart/";
		objFileNameWithExtensions += fileName;

		Model* model = new Model;
		ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)).c_str(), objFileNameWithExtensions.c_str());

		for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
		{
			model->GetModelPolygons().push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
			((Triangle*)model->GetModelPolygons().back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
		}

		model->UpdateRange();
		model->SetFileName() = fileName;
		AddActorToStorage<ABaseActor>(actors, model);
		typesOfActors.push_back(static_cast<int>(objectType::PLAYER));

		size_t verticesSize = objParseInfo.vertices.size();
		size_t facesSize = objParseInfo.faceIndex.size();
		size_t texturesSize = objParseInfo.textures.size();
		size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
		for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
		for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
		for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
		for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();

		currentObservedParalIndex = -1;
		currentGameState = buildModeState;
		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnModel, Spawn Model, EDITOR, Editor, SPAWN_MODEL)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnModel)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	auto GetObjFileName = [](std::string& fileName)
		{
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			showCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnModelInfo.x + 12), SpawnModelInfo.y });
			std::cout << "Enter file name: ";

			std::vector<char> strStorage;
			while (key != '\r')
			{
				key = _getche();

				if (key == '\r') break;

				strStorage.push_back(key);
			}

			strStorage.push_back('\0');
			fileName = strStorage.data();

			hideCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnModelInfo.x + 12), SpawnModelInfo.y });
			for (int i = 0; i < 40; ++i)
				std::cout << " ";
		};

	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_MODEL)
	{
		key = NOTHING_KEY;
		std::string fileName;
		GetObjFileName(fileName);

		std::string objFileName = fileName;
		std::string objFileNameWithExtensions = "Models/";
		objFileNameWithExtensions += fileName;
		bool isModelAnimated;
		
		Model* model = new Model;
		std::ifstream in(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)));
		if (in.is_open())
		{
			ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(objFileNameWithExtensions), EXTENSION_CAST(obj)).c_str(), objFileNameWithExtensions.c_str());
			isModelAnimated = false;

			for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
			{
				model->GetModelPolygons().push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
				((Triangle*)model->GetModelPolygons().back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
			}
			
			model->UpdateRange();
			model->SetFileName() = fileName;
			AddActorToStorage<ABaseActor>(actors, model);
			typesOfActors.push_back(static_cast<int>(objectType::MODEL));
			
			model->SetStartPolygonDist(dotDistance(model->GetCentreCoord(), ((Triangle*)model->GetModelPolygons()[0])->GetSurfaceDot1()));

			size_t verticesSize = objParseInfo.vertices.size();
			size_t facesSize = objParseInfo.faceIndex.size();
			size_t texturesSize = objParseInfo.textures.size();
			size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
			for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
			for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
			for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
			for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
		}
		else
		{
			std::string modelAnimFrame = objFileNameWithExtensions + std::string("0000");
			std::ifstream in(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)));
			if (!in.is_open())
			{
				key = NOTHING_KEY;
				return;
			}

			isModelAnimated = true;
		}

		if (isModelAnimated)
		{
			model->SetAnimationInfo().isAnimated = true;

			while (true)
			{
				std::string modelAnimFrame = objFileNameWithExtensions + std::format("{:04}", model->GetAnimationInfo().frameCounter);

				std::ifstream in(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)));
				if (!in.is_open())
				{
					model->UpdateRange();
					model->SetFileName() = fileName;
					AddActorToStorage<ABaseActor>(actors, model);
					typesOfActors.push_back(static_cast<int>(objectType::MODEL));

					model->SetStartPolygonDist(dotDistance(model->GetCentreCoord(), ((Triangle*)model->GetAnimModelPolygons()[0][0])->GetSurfaceDot1()));

					break;
				}

				model->SetAnimationInfo().frameCounter++;
				ObjParseInfo objParseInfo = ObjParse(FILE_EXTENSION(std::string(modelAnimFrame), EXTENSION_CAST(obj)).c_str(), modelAnimFrame.c_str());

				for (size_t i = 0; i < objParseInfo.faceIndex.size(); ++i)
				{
					if (model->GetAnimationInfo().frameCounter > 1)
						model->GetAnimModelPolygons().emplace_back();

					model->GetAnimModelPolygons()[model->GetAnimationInfo().frameCounter - 1].push_back(new Triangle(objParseInfo.vertices[objParseInfo.faceIndex[i][0].x], objParseInfo.vertices[objParseInfo.faceIndex[i][0].y], objParseInfo.vertices[objParseInfo.faceIndex[i][0].z], model, objParseInfo.faceIndex[i][1]));
					((Triangle*)model->GetAnimModelPolygons()[model->GetAnimationInfo().frameCounter - 1].back())->SetTextureParams(objParseInfo.facesTextureNames[i], objParseInfo.textures[objParseInfo.faceIndex[i][1].x], objParseInfo.textures[objParseInfo.faceIndex[i][1].y], objParseInfo.textures[objParseInfo.faceIndex[i][1].z]);
				}

				size_t verticesSize = objParseInfo.vertices.size();
				size_t facesSize = objParseInfo.faceIndex.size();
				size_t texturesSize = objParseInfo.textures.size();
				size_t texturesNamesSize = objParseInfo.facesTextureNames.size();
				for (size_t i = 0; i < verticesSize; ++i) objParseInfo.vertices.pop_back();
				for (size_t i = 0; i < facesSize; ++i) objParseInfo.faceIndex.pop_back();
				for (size_t i = 0; i < texturesSize; ++i) objParseInfo.textures.pop_back();
				for (size_t i = 0; i < texturesNamesSize; ++i) objParseInfo.facesTextureNames.pop_back();
			}
		}

		currentObservedParalIndex = -1;
		currentGameState = buildModeState;
		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnEnvFire, Spawn Env Fire, EDITOR, Editor, SPAWN_ENV_FIRE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnEnvFire)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_ENV_FIRE)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnEnvFire = true;
		AddActorToStorage<ABaseActor>(actors, new Circle({ 0,0,0 }, { 1,0,0 }, "Textures/env_fire.bmp", 3, 5));
		typesOfActors.push_back(static_cast<int>(objectType::ENV_FIRE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnSprite, Spawn Sprite, EDITOR, Editor, SPAWN_SPRITE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnSprite)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_SPRITE)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnSprite = true;
		AddActorToStorage<ABaseActor>(actors, new Circle({ 0,0,0 }, { 1,0,0 }, "Textures/Obsolete/Obsolete.bmp", 3, 5));
		typesOfActors.push_back(static_cast<int>(objectType::CIRCLE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnEnvParticles, Spawn Env Particles, EDITOR, Editor, SPAWN_ENV_PARTICLES)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnEnvParticles)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_ENV_PARTICLES)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnEnvParticles = true;
		Circle* endCircle = new Circle({ 0,0,0 }, { 0,0,1 }, "Textures/Obsolete/Obsolete.bmp", 3, 5);
		AddActorToStorage<ASmokeActor>(actors, new Circle(camActor.GetCurrentCamera()->GetVerCamDir() * moveCurrentFigureConstant + camActor.GetCurrentCamera()->GetCameraCoord(), { 1,0,0 }, "Textures/env_particles/env_particles0.bmp", 3, 5), endCircle);
		typesOfActors.push_back(static_cast<int>(objectType::ENV_PARTICLES));
		AddActorToStorage<ABaseActor>(actors, endCircle);
		((Circle*)actors.back()->GetStaticMesh())->SetCircleRotateMode(false);
		typesOfActors.push_back(static_cast<int>(objectType::CIRCLE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnEnvCubemap, Spawn Env Cubemap, EDITOR, Editor, SPAWN_ENV_CUBEMAP)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnEnvCubemap)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_ENV_CUBEMAP)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnEnvCubemap = true;
		AddActorToStorage<ACubemapActor>(actors, new Cubemap({ 0,0,0 }, { 1,0,0 }, "Textures/env_cubemap.bmp", 1, 5));
		typesOfActors.push_back(static_cast<int>(objectType::ENV_CUBEMAP));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnClipWall, Spawn Clip Wall, EDITOR, Editor, SPAWN_CLIP_WALL)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnClipWall)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_CLIP_WALL)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnClipWall = true;
		Parallelepiped* clipWallStaticMesh = new Parallelepiped(5, 5, 5, { 0, 0, 0 }, false, false, false, 3);
		AddActorToStorage<ABaseActor>(actors, clipWallStaticMesh);
		typesOfActors.push_back(static_cast<int>(objectType::CLIP_WALL));

		clipWallStaticMesh->SetObjTextureMode(true);
		clipWallStaticMesh->SetObjTextureParams("Textures/toolsclip.bmp", 5, 5);

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnTrigger, Spawn Trigger, EDITOR, Editor, SPAWN_TRIGGER)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnTrigger)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_TRIGGER)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnTrigger = true;
		Parallelepiped* triggerStaticMesh = new Parallelepiped(5, 5, 5, { 0, 0, 0 }, false, false, false, 3);
		AddActorToStorage<ATriggerActor>(actors, triggerStaticMesh);
		typesOfActors.push_back(static_cast<int>(objectType::TRIGGER));

		triggerStaticMesh->SetObjTextureMode(true);
		triggerStaticMesh->SetObjTextureParams("Textures/toolstrigger.bmp", 5, 5);

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnAreaPortal, Spawn Area Portal, EDITOR, Editor, SPAWN_AREA_PORTAL)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnAreaPortal)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_AREA_PORTAL)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnAreaPortal = true;
		Parallelepiped* areaPortalStaticMesh = new Parallelepiped(5, 5, 5, { 0, 0, 0 }, false, false, false, 3);
		AddActorToStorage<ABaseActor>(actors, areaPortalStaticMesh);
		typesOfActors.push_back(static_cast<int>(objectType::AREA_PORTAL));

		areaPortalStaticMesh->SetObjTextureMode(true);
		areaPortalStaticMesh->SetObjTextureParams("Textures/toolsareaportal.bmp", 5, 5);

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnEnvShake, Spawn Env Shake, EDITOR, Editor, SPAWN_ENV_SHAKE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnEnvShake)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	auto GetShakePower = [](float& shakePower)
		{
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			showCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnEnvShakeInfo.x + 17), SpawnEnvShakeInfo.y });
			std::cout << "Enter shake power: ";

			std::vector<char> strStorage;
			while (key != '\r')
			{
				key = _getche();

				if (key == '\r') break;

				strStorage.push_back(key);
			}

			strStorage.push_back('\0');
			shakePower = atof(strStorage.data());

			hideCursor();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(SpawnEnvShakeInfo.x + 17), SpawnEnvShakeInfo.y });
			for (int i = 0; i < 30; ++i)
				std::cout << " ";
		};

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_ENV_SHAKE)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnEnvShake = true;

		key = NOTHING_KEY;
		float shakePower;
		GetShakePower(shakePower);
		AddActorToStorage<ABaseActor>(actors, new EnvShake({ 0,0,0 }, { 1,0,0 }, "Textures/env_shake.bmp", 1, 5, shakePower));
		typesOfActors.push_back(static_cast<int>(objectType::ENV_SHAKE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnSkyCamera, Spawn Sky Camera, EDITOR, Editor, SPAWN_SKY_CAMERA)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnSkyCamera)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_SKY_CAMERA)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnSkyCamera = true;
		AddActorToStorage<ABaseActor>(actors, new Parallelepiped(1, 1, 1, { 0, 0, 0 }, false, false, false, 4));
		typesOfActors.push_back(static_cast<int>(objectType::SKY_CAMERA));
		
		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnVolumeSkybox, Spawn Volume Skybox, EDITOR, Editor, SPAWN_VOLUME_SKYBOX)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnVolumeSkybox)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_VOLUME_SKYBOX)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnVolumeSkybox = true;
		Parallelepiped* skyboxMesh = new Parallelepiped(5, 5, 5, { 0, 0, 0 }, false, false, false, 4);
		AddActorToStorage<ABaseActor>(actors, skyboxMesh);
		typesOfActors.push_back(static_cast<int>(objectType::VOLUME_SKYBOX));

		skyboxMesh->SetObjTextureMode(true);
		skyboxMesh->SetObjTextureParams("Textures/toolsskybox.bmp", 5, 5);

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(SpawnEnvFade, Spawn Env Fade, EDITOR, Editor, SPAWN_ENV_FADE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(SpawnEnvFade)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::SPAWN_ENV_FADE)
	{
		if (currentObservedParalIndex != -1)
			if (actors[currentObservedActorIndex]->GetStaticMesh()->GetObjType() == objectType::PARALLELEPIPED)
				*reinterpret_cast<bool*>(sizeof(StaticMesh) + 25 + (char*)actors[currentObservedParalIndex]->GetStaticMesh()) = false;

		currentGameState = buildModeState;
		currentObservedParalIndex = -1;

		isInBuildModeOnSpawnEnvFade = true;

		key = NOTHING_KEY;
		AddActorToStorage<ABaseActor>(actors, new Circle({ 0,0,0 }, { 1,0,0 }, "Textures/env_fade.bmp", 1, 5));
		typesOfActors.push_back(static_cast<int>(objectType::ENV_FADE));

		currentObservedActorIndex = actors.size() - 1;
		currMenuState = EDITOR_STATE::GAME;

		key = NOTHING_KEY;
	}
}

DECLARE_NEW_MENU_TYPE(LoadToFile, Load to file, EDITOR, Editor, LOAD_TO_FILE)
#undef LAST_MENU_CLASS_NAME 
#define LAST_MENU_CLASS_NAME GET_LAST_MENU_CLASS_NAME(LoadToFile)
void LAST_MENU_CLASS_NAME::CheckAddMenuTypesToStorage()
{
	Super::CheckAddMenuTypesToStorage();

	if (currEditorMenuState == EDITOR_MENU_TYPE::LOAD_TO_FILE)
	{
		key = NOTHING_KEY;
		LoadMapToFile();
	}
}

MenuClass* generalMenuClass = new LAST_MENU_CLASS_NAME;
#undef LAST_MENU_CLASS_NAME
#define LAST_MENU_CLASS_NAME MenuClass