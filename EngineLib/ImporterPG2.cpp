#include"ImporterPG2.h"

#pragma comment(lib, "assimp.lib")
#include <Importer.hpp>      // C++ importer interface
#include <scene.h>           // Output data structure
#include <postprocess.h>     // Post processing fla

#include "Node.h"

using namespace Assimp;

ImporterPG2::ImporterPG2(Renderer& rkRenderer) : importRenderer(rkRenderer){}

ImporterPG2::~ImporterPG2(){
	m_Textures.clear();
}

bool ImporterPG2::importScene(const std::string& rkFilename, Node& orkSceneRoot){
	
	Importer importer;
	aiString* path = new aiString;
	path->Set(rkFilename);

	const aiScene* scene = importer.ReadFile(rkFilename,
											 aiProcess_CalcTangentSpace |
											 aiProcess_Triangulate |
										 	 aiProcess_JoinIdenticalVertices |
											 aiProcess_SortByPType);

	if (!scene)
		return false;

	if (!scene->HasMeshes())
		return false;

	aiNode* iRoot = scene->mRootNode;

	if (iRoot->mNumChildren <= 0 && iRoot->mNumMeshes <= 0)
		return false;

	importNode(iRoot, orkSceneRoot, scene);

	return true;
}

void ImporterPG2::importNode(aiNode* child, Node& parent, const aiScene* scene){
	
	/*aiVector3t<float> position;
	aiQuaterniont<float> rotation;
	aiVector3t<float> scale;
	child->mTransformation.Decompose(scale, rotation, position);*/

	float expMat[4][4];
	expMat[0][0] = child->mTransformation.a1;
	expMat[0][1] = child->mTransformation.a2;
	expMat[0][2] = child->mTransformation.a3;
	expMat[0][3] = child->mTransformation.a4;

	expMat[1][0] = child->mTransformation.b1;
	expMat[1][1] = child->mTransformation.b2;
	expMat[1][2] = child->mTransformation.b3;
	expMat[1][3] = child->mTransformation.b4;

	expMat[2][0] = child->mTransformation.c1;
	expMat[2][1] = child->mTransformation.c2;
	expMat[2][2] = child->mTransformation.c3;
	expMat[2][3] = child->mTransformation.c4;

	expMat[3][0] = child->mTransformation.d1;
	expMat[3][1] = child->mTransformation.d2;
	expMat[3][2] = child->mTransformation.d3;
	expMat[3][3] = child->mTransformation.d4;

	parent.importMatrix(expMat);

	if (child->mNumChildren != 0){
		Node* newNode = new Node();

		/*newNode->setPos(position.x, position.y, position.z);
		newNode->setRotation(rotation.x, rotation.y, rotation.z);
		newNode->setScale(scale.x, scale.y, scale.z);*/

		newNode->setName(child->mName.C_Str());

		for (unsigned int k = 0; k < child->mNumChildren; k++){
			importNode(child->mChildren[k], *newNode, scene);
		}

		parent.addChild(newNode);
	}

	for (unsigned int l = 0; l < child->mNumMeshes; l++){

		Mesh* newMesh = new Mesh(importRenderer);

		const aiMesh* rootMesh = scene->mMeshes[child->mMeshes[l]];

		TexVertex* meshVertex = new TexVertex[rootMesh->mNumVertices];

		if (rootMesh->HasTextureCoords(0)) {
			for (unsigned int i = 0; i < rootMesh->mNumVertices; i++) {
				meshVertex[i] = { rootMesh->mVertices[i].x,
					rootMesh->mVertices[i].y,
					rootMesh->mVertices[i].z,
					rootMesh->mTextureCoords[0][i].x,
					rootMesh->mTextureCoords[0][i].y };

				newMesh->createBV(rootMesh->mVertices[i].x, rootMesh->mVertices[i].y, rootMesh->mVertices[i].z);
			}
		}else {
			for (unsigned int i = 0; i < rootMesh->mNumVertices; i++) {
				meshVertex[i] = { rootMesh->mVertices[i].x,
					rootMesh->mVertices[i].y,
					rootMesh->mVertices[i].z
				};

				newMesh->createBV(rootMesh->mVertices[i].x, rootMesh->mVertices[i].y, rootMesh->mVertices[i].z);
			}
		}
		
		unsigned short* indices = new unsigned short[rootMesh->mNumFaces * 3];

		for (unsigned int j = 0; j < rootMesh->mNumFaces; j++){
			const aiFace& meshFace = rootMesh->mFaces[j];
			assert(meshFace.mNumIndices == 3);

			for (int k = 0; k < 3; k++){
				indices[j * 3 + k] = meshFace.mIndices[k];
			}
		}

		if (scene->HasMaterials()){

				const aiMaterial* material = scene->mMaterials[rootMesh->mMaterialIndex];
				aiString texturePath;
				material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath);

				string actualPath = texturePath.C_Str();
				string finalPath = "Assets/" + actualPath;
				if (!actualPath.empty())
					actualPath.erase(0, 1);

				Texture gil = importRenderer.loadTexture(finalPath, D3DCOLOR_XRGB(100, 10, 250));
				newMesh->setTextureId(rootMesh->mMaterialIndex, gil);
		}

		/*newMesh->setPos(position.x, position.y, position.z);
		newMesh->setRotation(rotation.x, rotation.y, rotation.z);
		newMesh->setScale(scale.x, scale.y, scale.z);*/

		newMesh->importMatrix(expMat);

		newMesh->setName(child->mName.C_Str());

		newMesh->setMeshData(meshVertex, D3DPT_TRIANGLELIST, rootMesh->mNumVertices,
			indices, rootMesh->mNumFaces * 3);

		parent.addChild(newMesh);
		
		delete[] meshVertex;
		meshVertex = NULL;
	}
}