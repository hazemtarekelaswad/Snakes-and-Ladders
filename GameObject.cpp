#include "GameObject.h"


GameObject::GameObject(const CellPosition & pos)
{
	position = pos; // Sets Position
}

GameObject::GameObject(){}

CellPosition GameObject::GetPosition() const
{
	return position;
}

void GameObject::SetPosition(const CellPosition &pos){
	position = pos;
}

GameObject::~GameObject()
{
}