#include "Node.h"

Node::Node():Entity3D(){
	setScale(1.0f, 1.0f, 1.0f);
}

Node::~Node(){
	if (!children.empty())
		children.clear();

	delete &children;
}

void Node::addChild(Entity3D* newChild){
	newChild->setParent(this);
	children.push_back(newChild);
	updateBV();
	updateWorldTransformation();
}

Entity3D* Node::getChildMesh(string name){
	for (vector<Entity3D*>::iterator it = children.begin(); it != children.end(); ++it){
		if ((*it)->getName() == name){
			return (*it);
		}
	}

	return NULL;
}

Node* Node::getChildNode(string name){
	for (vector<Entity3D*>::iterator it = children.begin(); it != children.end(); ++it){
		if ((*it)->getName() == name){
			return dynamic_cast<Node*>(*it);
		}
	}

	return NULL;
}

void Node::removeChild(Entity3D* newChild){
	for (vector<Entity3D*>::iterator it = children.begin(); it != children.end(); ++it){
		if ((*it) == newChild){
			children.erase(it);
			break;
		}
	}
}

void Node::updateWorldTransformation(){

	//Variables de World se usan en el calculo de la AABB del Mesh

	worldScaleX = 0;
	worldScaleY = 0;
	worldScaleZ = 0;

	worldPosX = 0;
	worldPosY = 0;
	worldPosZ = 0;

	if (parent == NULL){
		worldPosX = m_fPosX;
		worldPosY = m_fPosY;
		worldPosZ = m_fPosZ;

		worldScaleX = m_fScaleX;
		worldScaleY = m_fScaleY;
		worldScaleZ = m_fScaleZ;
	}else{
		worldPosX = m_fPosX * parent->WorldScaleX() + parent->WorldPosX();
		worldPosY = m_fPosY * parent->WorldScaleY() + parent->WorldPosY();
		worldPosZ = m_fPosZ * parent->WorldScaleZ() + parent->WorldPosZ();

		worldScaleX = m_fScaleX * parent->WorldScaleX();
		worldScaleY = m_fScaleY * parent->WorldScaleY();
		worldScaleZ = m_fScaleZ * parent->WorldScaleZ();
	}

	Entity3D::updateWorldTransformation();

	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->updateWorldTransformation();
}

void Node::draw(vector<string>& vec){
	string push;
	push = name + "\n"  + "  ";
	vec.push_back(push);
	for (unsigned int i = 0; i < children.size(); i++)
		children[i]->draw(vec);

	vec.push_back("\n");
}

void Node::draw(Renderer& rkRenderer, CollisionResult eParentResult, const Frustum& rkFrustum, vector<string>& vec){
	if (eParentResult != AllOutside){
		string push;
		push = name + "\n" + "  ";
		if (parent == NULL)
			push = name + "(Root)" + "\n";
		vec.push_back(push);
		if (eParentResult == AllInside){
			for (unsigned int i = 0; i < children.size(); i++){
				children[i]->draw(vec);
			}

			vec.push_back("\n");

		}else if (eParentResult == PartiallyInside){
			for (unsigned int i = 0; i < children.size(); i++){
				children[i]->draw(rkRenderer, rkFrustum.aabbInFrustum(children[i]->getAABB()), rkFrustum, vec);
			}

			vec.push_back("\n");

		}
	}
	
}

const vector<Entity3D*>& Node::childs() const{
	return children;
}

void Node::updateBV(){
	name;	//pa' testear

	//Se borra la AABB para empezar desde 0
	aabb.emptyAABB();

	//Se updatea la AABB de todos los children y se guardan el punto mas chico y el mas grande
	for (unsigned int i = 0; i < children.size(); i++){
		children[i]->updateBV();
		aabb.addPoint(children[i]->getAABB().min);
		aabb.addPoint(children[i]->getAABB().max);
	}	
}