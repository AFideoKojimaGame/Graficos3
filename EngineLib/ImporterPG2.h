#ifndef IMPORTERPG2_H
#define IMPORTERPG2_H

#include "Mesh.h"

using namespace std;

struct aiNode;
struct aiScene;

struct aiMesh;
struct aiMaterial;

class ImporterPG2{
	public:
		DllExport ImporterPG2(Renderer& rkRenderer);
		DllExport ~ImporterPG2();
		DllExport bool importScene(const std::string& rkFilename, Node& orkSceneRoot);

	private:
		DllExport void importNode(aiNode* child, Node& parent, const aiScene* scene);
		DllExport void importMesh(aiNode* child, Node& parent, const aiScene* scene);

		vector <Texture> m_Textures;
		Renderer& importRenderer;
};

#endif