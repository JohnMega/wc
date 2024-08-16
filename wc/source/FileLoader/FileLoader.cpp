
#include <iostream>
#include <format>
#include <Windows.h>
#include <conio.h>
#include <string>
#include "FileLoader.h"
#include "GlobalVars.h"
#include "StaticMesh.h"
#include "ObjFileParse.h"
#include "Model.h"
#include "ALightActor.h"
#include "ASmokeActor.h"
#include "Parallelepiped.h"
#include "ASkyboxPart.h"
#include "ATriggerLine.h"
#include "ATriggerActor.h"
#include "Circle.h"
#include "EnvShake.h"
#include "AActor.h"

extern std::vector<class AActor*> actors;
extern std::vector<int> typesOfActors;

extern char key;
extern void GetKey();

void WritePar(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Rotate fields
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 1) << ";";
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 2) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + 16 + (char*)actors[index]->GetStaticMesh()) << ";";

	// Color
	out << *reinterpret_cast<int*>(sizeof(StaticMesh) + 20 + (char*)actors[index]->GetStaticMesh()) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	// Parab mode params
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 24 + (char*)actors[index]->GetStaticMesh()) << ";";

	Range parabOwnerRange = *reinterpret_cast<Range*>(sizeof(StaticMesh) + (32 + sizeof(COORDS)) + (char*)actors[index]->GetStaticMesh());
	out << "{" << parabOwnerRange.xStart << ";" << parabOwnerRange.xEnd << ";"
		<< parabOwnerRange.yStart << ";" << parabOwnerRange.yEnd << ";"
		<< parabOwnerRange.zStart << ";" << parabOwnerRange.zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << ((Parallelepiped*)actors[index]->GetStaticMesh())->GetTextureName() << ";";
	out << ((Parallelepiped*)actors[index]->GetStaticMesh())->GetWidthTextureCount() << ";";
	out << ((Parallelepiped*)actors[index]->GetStaticMesh())->GetHeightTextureCount() << ";";

	out << ((Parallelepiped*)actors[index]->GetStaticMesh())->IsHasCollision() << ";";

	COORDS cubemapCentreCoords = (actors[index]->isActorHasCubemap() ? actors[index]->GetCubemap()->GetCentreCoord() : COORDS{0,0,0} );
	out << '{' << cubemapCentreCoords.x << ';' << cubemapCentreCoords.y << ';' << cubemapCentreCoords.z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WriteClipWall(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WriteAreaPortal(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "}";
}

void WriteTrigger(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << "{" << ((ATriggerActor*)actors[index])->observedObjCentreCoord.x << ";" << ((ATriggerActor*)actors[index])->observedObjCentreCoord.y << ";" << ((ATriggerActor*)actors[index])->observedObjCentreCoord.z << "}" << '\n';
}

void WriteFire(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	
	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	COORDS cubemapCentreCoords = (actors[index]->isActorHasCubemap() ? actors[index]->GetCubemap()->GetCentreCoord() : COORDS{ 0,0,0 });
	out << '{' << cubemapCentreCoords.x << ';' << cubemapCentreCoords.y << ';' << cubemapCentreCoords.z << "}" << '\n';
}

void WriteSkyCamera(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "}\n";
}

void WriteVolumeSkybox(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Rotate fields
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 1) << ";";
	out << *reinterpret_cast<bool*>(sizeof(StaticMesh) + 12 + (char*)actors[index]->GetStaticMesh() + 2) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + 16 + (char*)actors[index]->GetStaticMesh()) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "}\n";
}

void WriteEnvShake(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << ((EnvShake*)actors[index]->GetStaticMesh())->GetShakePower() << ";";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WriteEnvFade(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WriteSkybox(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";

	// Color
	out << *reinterpret_cast<int*>(sizeof(StaticMesh) + 20 + (char*)actors[index]->GetStaticMesh()) << ";";

	// Range
	out << "{" << actors[index]->GetStaticMesh()->GetRange().xStart << ";" << actors[index]->GetStaticMesh()->GetRange().xEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().yStart << ";" << actors[index]->GetStaticMesh()->GetRange().yEnd << ";"
		<< actors[index]->GetStaticMesh()->GetRange().zStart << ";" << actors[index]->GetStaticMesh()->GetRange().zEnd << "};";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << ((Parallelepiped*)actors[index]->GetStaticMesh())->GetTextureName() << ";";

	out << ((ASkyboxPart*)actors[index])->GetNumberOfSkyboxPart() << ";" << '\n';
}

void WriteModel(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << *reinterpret_cast<std::string*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh()) << ";";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << ((Model*)actors[index]->GetStaticMesh())->GetStartPolygonDist() << ";";

	if(((Model*)actors[index]->GetStaticMesh())->GetAnimationInfo().isAnimated == false)
		out << dotDistance(((Model*)actors[index]->GetStaticMesh())->GetCentreCoord(), ((Triangle*)((Model*)actors[index]->GetStaticMesh())->GetModelPolygons()[0])->GetSurfaceDot1()) / ((Model*)actors[index]->GetStaticMesh())->GetStartPolygonDist() - 1 << ";";
	else
		out << dotDistance(((Model*)actors[index]->GetStaticMesh())->GetCentreCoord(), ((Triangle*)((Model*)actors[index]->GetStaticMesh())->GetAnimModelPolygons()[0][0])->GetSurfaceDot1()) / ((Model*)actors[index]->GetStaticMesh())->GetStartPolygonDist() - 1 << ";";


	if (reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetLastRotateAngleSum() != 0)
	{
		reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->PushRotationAnglesSum(std::format("{}{}", reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetLastRotateAxis(), reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetLastRotateAngleSum()));
		reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetLastRotateAxis() = NULL;
		reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetLastRotateAngleSum() = 0;
	}

	out << "{";
	for (size_t i = 0; i < reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetRotationAnglesSum().size(); ++i)
		out << reinterpret_cast<Model*>(actors[index]->GetStaticMesh())->GetRotationAnglesSum()[i] << ";";

	out << "};";

	COORDS cubemapCentreCoords = (actors[index]->isActorHasCubemap() ? actors[index]->GetCubemap()->GetCentreCoord() : COORDS{ 0,0,0 });
	out << '{' << cubemapCentreCoords.x << ';' << cubemapCentreCoords.y << ';' << cubemapCentreCoords.z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WritePyramid(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	// Size fields
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 0) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 4) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 8) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 12) << ";";
	out << *reinterpret_cast<float*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 16) << ";";

	// Color
	out << *reinterpret_cast<int*>(sizeof(StaticMesh) + (char*)actors[index]->GetStaticMesh() + 20) << ";";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	COORDS cubemapCentreCoords = (actors[index]->isActorHasCubemap() ? actors[index]->GetCubemap()->GetCentreCoord() : COORDS{ 0,0,0 });
	out << '{' << cubemapCentreCoords.x << ';' << cubemapCentreCoords.y << ';' << cubemapCentreCoords.z << "};";

	out << "{";
	for (size_t i = 0; i < actors[index]->GetTrigger().size(); ++i)
	{
		if (actors[index]->GetTrigger()[i].first == nullptr) continue;

		ATriggerLine* currTriggerLine = nullptr;
		for (size_t j = 1; j < actors.size(); ++j)
		{
			if (typesOfActors[j - 1] == static_cast<int>(logicActorType::TRIGGER_LINE))
				if (((ATriggerLine*)actors[j])->trigger == actors[index]->GetTrigger()[i].first && ((ATriggerLine*)actors[j])->observedObj == actors[index]
					&& ((ATriggerLine*)actors[j])->typeOfTrigger == actors[index]->GetTrigger()[i].second)
				{
					currTriggerLine = (ATriggerLine*)actors[j];
					break;
				}
		}

		out << "{" << actors[index]->GetTrigger()[i].first->GetCentreCoord().x << ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().y
			<< ";" << actors[index]->GetTrigger()[i].first->GetCentreCoord().z << ";" << actors[index]->GetTrigger()[i].second << ";" << currTriggerLine->additTriggerInfo->WriteInfo() << "};";
	}

	out << "}|" << '\n';
}

void WriteLight(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";
	
	// Light power
	out << *reinterpret_cast<int*>(actors[index]->GetLight()) << ";";
	
	out << "{" << actors[index]->GetLight()->GetCoord().x << ";" << actors[index]->GetLight()->GetCoord().y << ";" << actors[index]->GetLight()->GetCoord().z << "};";

	out << ((ALightActor*)actors[index])->GetCurrentLightTextureIndex() << ";" << '\n';
}

void WriteCircle(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	// Light power
	out << ((Circle*)actors[index]->GetStaticMesh())->GetRad() << ";";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << ((Circle*)actors[index]->GetStaticMesh())->GetTextureName() << ";";

	out << "{" << ((Circle*)actors[index]->GetStaticMesh())->GetNormVec().x << ";" << ((Circle*)actors[index]->GetStaticMesh())->GetNormVec().y << ";" << ((Circle*)actors[index]->GetStaticMesh())->GetNormVec().z << "};";
	out << ((Circle*)actors[index]->GetStaticMesh())->GetCircleRotateMode() << ";";
	out << ((Circle*)actors[index]->GetStaticMesh())->GetLimpidMode() << ";";

	COORDS cubemapCentreCoords = (actors[index]->isActorHasCubemap() ? actors[index]->GetCubemap()->GetCentreCoord() : COORDS{ 0,0,0 });
	out << '{' << cubemapCentreCoords.x << ';' << cubemapCentreCoords.y << ';' << cubemapCentreCoords.z << "}" << '\n';
}

void WriteSmoke(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << "{" << actors[index + 1]->GetStaticMesh()->GetCentreCoord().x - actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index + 1]->GetStaticMesh()->GetCentreCoord().y - actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index + 1]->GetStaticMesh()->GetCentreCoord().z - actors[index]->GetStaticMesh()->GetCentreCoord().z << "};";

	out << ((Circle*)actors[index + 1]->GetStaticMesh())->GetRad() << ';';

	out << ((ASmokeActor*)actors[index])->GetCurrentColorIndex() << ';' << '\n';
}

void WritePlayer(size_t index, std::ofstream& out)
{
	out << typesOfActors[index - 1] << ":";

	out << "{" << actors[index]->GetStaticMesh()->GetCentreCoord().x << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().y << ";" << actors[index]->GetStaticMesh()->GetCentreCoord().z << "}\n";
}

void showCursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = true;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void hideCursor(int off)
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = off;
	cci.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void LoadMapToFile()
{
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	showCursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 5, 23 });
	std::cout << "Enter the file name: ";

	std::string fileName = MyCin();

	hideCursor();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { SCREEN_WIDTH + 5, 23 });
	for (int i = 0; i < 50; ++i)
		std::cout << " ";

	std::ofstream out;
	out.open(FILE_EXTENSION(fileName, EXTENSION_CAST(bsp)));
	if (out.is_open())
	{
		for (size_t i = 1; i < actors.size(); ++i)
			if (typesOfActors[i - 1] == static_cast<int>(objectType::PLAYER))
			{
				WritePlayer(i, out);
				break;
			}

		for (size_t i = 1; i < actors.size(); ++i)
			if (typesOfActors[i - 1] == static_cast<int>(objectType::TRIGGER))
			{
				WriteTrigger(i, out);
			}

		for (size_t i = 1; i < actors.size(); ++i)
			if (typesOfActors[i - 1] == static_cast<int>(objectType::PARALLELEPIPED)) WritePar(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::PYRAMID)) WritePyramid(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::LIGHT)) WriteLight(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::MODEL)) WriteModel(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::SKYBOX)) WriteSkybox(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::ENV_FIRE)) WriteFire(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::CIRCLE))
			{
				if (typesOfActors[i - 2] == static_cast<int>(objectType::ENV_PARTICLES)) continue;

				WriteCircle(i, out);
			}
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::ENV_PARTICLES)) WriteSmoke(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::CLIP_WALL)) WriteClipWall(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::AREA_PORTAL)) WriteAreaPortal(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::ENV_SHAKE)) WriteEnvShake(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::SKY_CAMERA)) WriteSkyCamera(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::VOLUME_SKYBOX)) WriteVolumeSkybox(i, out);
			else if (typesOfActors[i - 1] == static_cast<int>(objectType::ENV_FADE)) WriteEnvFade(i, out);
	}
	out << '|';

	out.close();
}