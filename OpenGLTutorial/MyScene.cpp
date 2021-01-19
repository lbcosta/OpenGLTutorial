#include "MyScene.h"

#include <iostream>

MyScene::MyScene()
{

}

MyScene::~MyScene()
{
	std::cout << "MyScene DESTRUCTOR!" << std::endl;
}

void MyScene::update()
{
	// Afeta o resultado final na tela
	std::cout << "MyScene update" << std::endl;
}