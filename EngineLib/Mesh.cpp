#include "Mesh.h"

Mesh::Mesh(){}

Mesh::Mesh(Renderer& rkRenderer) :meshRenderer(&rkRenderer){
	meshIB = meshRenderer->createIndexBuffer();
	meshVB = meshRenderer->createVertexBuffer(sizeof(TexVertex), TextureFVF);
	meshVBnotex = meshRenderer->createVertexBuffer(sizeof(ColorVertex), CustomFVF);
	canDraw = true;
}

Mesh::~Mesh(){
	delete meshIB;
	meshIB = NULL;
	delete meshVB;
	meshVB = NULL;
	delete meshVBnotex;
	meshVBnotex = NULL;
}

void Mesh::setRenderer(Renderer& rkRenderer){
	meshRenderer = &rkRenderer;
	meshIB = meshRenderer->createIndexBuffer();
	meshVB = meshRenderer->createVertexBuffer(sizeof(TexVertex), TextureFVF);
	meshVBnotex = meshRenderer->createVertexBuffer(sizeof(ColorVertex), CustomFVF);
}

void Mesh::setMeshData(const ColorVertex* pakVertices, D3DPRIMITIVETYPE ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices, size_t uiIndexCount){

	meshVBnotex->setVertexData(pakVertices, uiVertexCount);
	meshIB->setIndexData(pusIndices, uiIndexCount);

	meshPrimitive = ePrimitive;
}

void Mesh::setMeshData(const TexVertex* pakVertices, D3DPRIMITIVETYPE ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices, size_t uiIndexCount){

	myVerts = pakVertices;
	vertsSize = uiVertexCount;

	meshVB->setVertexData(pakVertices, uiVertexCount);
	meshIB->setIndexData(pusIndices, uiIndexCount);

	meshPrimitive = ePrimitive;
}

void Mesh::draw(vector<string>& vec, int& vNum, int& pNum, D3DXVECTOR3 camPos, BSPTree& bsp){

	name;
	canDraw = bsp.CheckTree(camPos, aabb.min, aabb.max);

	int otherInt = 0;

	if (canDraw) {
		string push;
		push = name + " " + " - Vertices: " + to_string(vertsSize / 3);

		vNum += vertsSize / 3;

		meshIB->bind();
		meshVB->bind();

		meshRenderer->setCurrentTexture(text);

		meshRenderer->setMatrix(m_pkWorldMatrix);
		meshRenderer->drawCurrentBuffers(meshPrimitive, pNum, otherInt);

		push += " - Polygons: " + to_string(otherInt) + "\n ";
		vec.push_back(push);
	}

	canDraw = true;
}

void Mesh::draw(Renderer& rkRenderer, CollisionResult eParentResult, const Frustum& rkFrustum, vector<string>& vec, int& vNum, int& pNum, D3DXVECTOR3 camPos, BSPTree& bsp){
	
	name;
	canDraw = bsp.CheckTree(camPos, aabb.min, aabb.max);

	//canDraw = bsp.CheckTree(camPos, (D3DXVECTOR3(m_fPosX * parent->WorldScaleX() + parent->WorldPosX(),
	//	m_fPosY * parent->WorldScaleY() + parent->WorldPosY(),
	//	m_fPosZ * parent->WorldScaleZ() + parent->WorldPosZ())));

	//check = bsp.Check(D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));

	int otherInt = 0;

	//bool canDraw = false;

	/*if ((check > 0 && d > 0) || (check < 0 && d < 0) || (d == 0))
		canDraw = true;*/

	if (eParentResult != AllOutside){
		if(canDraw){
			string push;
			if(eParentResult == PartiallyInside) {
				push = name + " - Partially - Vertices: " + to_string(vertsSize / 2);
			}else{
				push = name + " - Vertices: " + to_string(vertsSize / 3);
			}

			vNum += vertsSize / 3;

			meshIB->bind();
			meshVB->bind();

			meshRenderer->setCurrentTexture(text);

			meshRenderer->setMatrix(m_pkWorldMatrix);
			meshRenderer->drawCurrentBuffers(meshPrimitive, pNum, otherInt);

			push += " - Polygons: " + to_string(otherInt) + "\n ";
			vec.push_back(push);
		}
	}

	canDraw = true;
}

void Mesh::drawColored(){

	meshRenderer->setMatrix(m_pkTransformationMatrix);

	meshIB->bind();
	meshVBnotex->bind();

	//meshRenderer->drawCurrentBuffers(meshPrimitive);
}

void Mesh::setTextureId(int iTextureId, Texture blah){
	textureID = iTextureId;
	text = blah;
}

D3DXVECTOR3 Mesh::getMin(){
	return aabb.min;
}

D3DXVECTOR3 Mesh::getMax(){
	return aabb.max;
}

void Mesh::createBV(float x, float y, float z){
	name; //Pa' testear

	//Se recibe un vertice y se agrega a la AABB
	D3DXVECTOR3 point(x, y, z);
	aabb.addBasePoint(point);
}

void Mesh::updateBV(){

	//Punto base minimo/maximo de la AABB * la escala en World del Mesh + la posicion en World del Mesh

	float minX, minY, minZ, maxX, maxY, maxZ;

	if (parent) {
		minX = aabb.basemin.x * m_fScaleX * parent->WorldScaleX() + m_fPosX * parent->WorldScaleX() + parent->WorldPosX();
		minY = aabb.basemin.y * m_fScaleY * parent->WorldScaleY() + m_fPosY * parent->WorldScaleY() + parent->WorldPosY();
		minZ = aabb.basemin.z * m_fScaleZ * parent->WorldScaleZ() + m_fPosZ * parent->WorldScaleZ() + parent->WorldPosZ();

		maxX = aabb.basemax.x * m_fScaleX * parent->WorldScaleX() + m_fPosX * parent->WorldScaleX() + parent->WorldPosX();
		maxY = aabb.basemax.y * m_fScaleY * parent->WorldScaleY() + m_fPosY * parent->WorldScaleY() + parent->WorldPosY();
		maxZ = aabb.basemax.z * m_fScaleZ * parent->WorldScaleZ() + m_fPosZ * parent->WorldScaleZ() + parent->WorldPosZ();
	}else {
		minX = aabb.basemin.x * m_fScaleX + m_fPosX;
		minY = aabb.basemin.y * m_fScaleY + m_fPosY;
		minZ = aabb.basemin.z * m_fScaleZ + m_fPosZ;

		maxX = aabb.basemax.x * m_fScaleX + m_fPosX;
		maxY = aabb.basemax.y * m_fScaleY + m_fPosY;
		maxZ = aabb.basemax.z * m_fScaleZ + m_fPosZ;
	}
	
	
	name; //Pa' testear

	//Se agregan los puntos a la AABB
	D3DXVECTOR3 v;
	v.x = minX;
	v.y = minY;
	v.z = minZ;
	aabb.overwriteMin(v);
	v.x = maxX;
	v.y = maxY;
	v.z = maxZ;
	aabb.overwriteMax(v);
}