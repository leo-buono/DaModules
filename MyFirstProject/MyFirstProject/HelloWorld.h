	#pragma once

#include "Scene.h"
class HelloWorld : public Scene
{
public: 
	HelloWorld(std::string name);

	void InitScene(float windowWidth, float windowHeight) override;
private:

};



