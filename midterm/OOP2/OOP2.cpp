// OOP2.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <stdio.h>
#include <stdlib.h> // itoa
#include <conio.h>
#include <cstring>
#include <windows.h>
#include <iostream>
#include <vector>

#include "Utils.h"
#include "Canvas.h"
#include "GameObject.h"
#include "PlayerScript.h"
#include "EnemyScript.h"
#include "BulletScript.h"
#include "TextUIScript.h"
#include "InputManager.h"


using namespace std;


int main()
{
	Borland::Initialize();
	InputManager* inputManager = InputManager::GetInstance();
	
	auto canvas = Canvas::GetInstance();
	GameObject::Init(30);

	bool exit_flag{ false };

	while (exit_flag == false) { // if player is alive

		canvas->clear();

		inputManager->readEveryFrame();

		/* process game logic for each game object */
		if (GameObject::Update() == false) 
			break;
		canvas->update();

		canvas->render();

	} /* end of while(1) */

	GameObject::Destroy();


	return 0;
}
