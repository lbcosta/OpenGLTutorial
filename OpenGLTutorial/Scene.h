#pragma once
class Scene
{
public:
	virtual ~Scene(){ }
	virtual void update() = 0;
};

