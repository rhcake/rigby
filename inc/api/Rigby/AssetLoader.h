#pragma once

#include <assimp/Importer.hpp>
#include <api/Rigby/RawAsset.h>

class AssetLoader {
public:
	AssetLoader();
	~AssetLoader();
	RawAsset *LoadAsset(const char *name);
private:
	Assimp::Importer *importer;
};