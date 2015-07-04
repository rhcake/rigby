#pragma once


#include <assimp/scene.h>


class RawAsset {
public:
	RawAsset(const aiScene *scene);
private:
	const aiScene *scene;
};