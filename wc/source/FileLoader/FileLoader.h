#pragma once
#include <fstream>

#define EXTENSION_CAST_INNER(str) . ## str
#define EXTENSION_CAST(str) EXTENSION_CAST_INNER(str)

#define FILE_EXTENSION_INNER(str, extension) str ## .append(#extension)
#define FILE_EXTENSION(str, extension) FILE_EXTENSION_INNER(str, extension)

void WritePar(size_t index, std::ofstream& out);

void WritePyramid(size_t index, std::ofstream& out);

void WriteLight(size_t index, std::ofstream& out);

void WritePlayer(size_t index, std::ofstream& out);

void showCursor();

void hideCursor(int off = 1);

void LoadMapToFile();