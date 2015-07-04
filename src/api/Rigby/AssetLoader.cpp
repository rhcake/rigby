#include <api/AssetLoader.h>
#include <debug.h>
#include <assimp/postprocess.h>

AssetLoader::AssetLoader() {
	importer = new Assimp::Importer();
}


AssetLoader::~AssetLoader() {
	delete importer;
}


RawAsset *AssetLoader::LoadAsset(const char *name) {

	const aiScene* scene = importer->ReadFile(name, 
		aiProcess_Triangulate          	|
		aiProcess_JoinIdenticalVertices	|
		aiProcess_ValidateDataStructure	|
		aiProcess_SortByPType);

	if (!scene) {
		logln("** unable to load asset: [%s]", name);
		return 0;
	}

	logln("meshes: %d", scene->mNumMeshes);

	return new RawAsset(scene);
}