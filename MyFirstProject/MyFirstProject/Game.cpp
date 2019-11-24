#include "Game.h"

#include <random>

vec2 m_velocity = vec2(0.f, 0.f);x

Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	m_scenes.push_back(new HelloWorld("New saved scene"));
	m_scenes.push_back(new Scene("First Loaded Scene"));
	m_scenes.push_back(new AssignmentMentChallenge1("TestyBoi"));
	m_activeScene = m_scenes[2];

	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowWidth()));

	//*m_activeScene = File::LoadJSON("New saved scene.json");

	m_register = m_activeScene->GetScene();
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion)
		MouseMotion(BackEnd::GetMotionEvent());

	if (m_click)
		MouseClick(BackEnd::GetClickEvent());

	if (m_wheel)
		MouseWheel(BackEnd::GetWheelEvent());
}

void Game::AcceptInput()
{
	XInputManager::Update();

	//Just calls all the other input functions 
	//GamepadInput(); INPUT FOR THE CONTROLLER!!

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	//Gamepad stroke(pressed)
	XInputController* tempCon;
	for (int  i = 0; i < 3; i++)
	{
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i);
			tempCon->SetStickDeadZone(0.1f);

			GamepadStroke(tempCon);
			GamepadUp(tempCon);
			GamepadDown(tempCon);
			GamepadStick(tempCon);
			GamepadTrigger(tempCon);

		}
	}
}

void Game::GamepadStroke(XInputController* con)
{
	//Gamepad button stroke Press
	if (con->IsButtonStroked(Buttons::A))
	{
		printf("A stroke\n");
	}

}

void Game::GamepadUp(XInputController* con)
{
	if (con->IsButtonReleased(Buttons::RB)) 
	{
		printf("RB Released\n");
	}
}

void Game::GamepadDown(XInputController* con)
{
	if (con->IsButtonPressed(Buttons::THUMB_LEFT)) 
	{
		printf("Left Thumb\n");
	}
}

void Game::GamepadStick(XInputController* con)
{
		//Gamepad stick stuffs
	Stick sticks[2];
	con->GetSticks(sticks);	

	if (sticks[0].x < -0.1f)
	{
		printf("Pointing left\n");
	}
	if (sticks[0].x > 0.1f)
	{
		printf("Pointing left\n");
	}
	if (sticks[0].y < -0.1f)
	{
		printf("Pointing down\n");
	}
	if (sticks[0].y > 0.1f)
	{
		printf("Pointing left\n");
	}
}

void Game::GamepadTrigger(XInputController* con)
{
	//Gamepad triggers
	Triggers triggers;
	con->GetTriggers(triggers);
	if (triggers.RT > 0.5f && triggers.RT < 0.8f)
	{
		printf("Half press trigger\n");
	}

	if (triggers.RT > 0.8f)
	{
		printf("Full Press trigger\n");
	}

}

void Game::KeyboardHold()
{
	//Keyboard button held
	/*if (Input::GetKey(Key::F4))
	{
		printf("F4 has been Held \n");
	}*/
	float speed = 300.f;

	vec3 position = m_register->get<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	vec2 acceleration = vec2(0.f, -1.f);

	if (Input::GetKey(Key::W))
	{
		acceleration.y = 1.f;
	}
	if (Input::GetKey(Key::A))
	{
		acceleration.x = -1.f;
	}
	if (Input::GetKey(Key::S))
	{
		acceleration.y = -2.f;
	}
	if (Input::GetKey(Key::D))
	{
		acceleration.x = 1.f;
	}
	//updates velocity
	if (!(m_velocity.GetMagnitude() > 10.f)) 
	{
		m_velocity = m_velocity + (acceleration * Timer::deltaTime);
	}
	//updates position 
	position = position + (vec3(m_velocity.x, m_velocity.y, 0.f) * Timer::deltaTime);
	//sets updated position
	m_register->get<Transform>(EntityIdentifier::MainPlayer()).SetPosition(position);

}

void Game::KeyboardDown()
{
	//Keyboard button down
	if (Input::GetKeyDown(Key::F4))
	{
		printf("F4 has been Pressed \n");
	}
	/*if (Input::GetKeyDown(Key::Space)) 
	{
		if (ECS::GetComponent<AnimationController>(1).GetActiveAnim() == 0)
		{
			ECS::GetComponent<AnimationController>(1).SetActiveAnim(1);
		}
		else 
		{
			ECS::GetComponent<AnimationController>(1).SetActiveAnim(0);
		}

	}*/
}

void Game::KeyboardUp()
{
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
	if (Input::GetKeyUp(Key::F4))
	{
		printf("F4 has been Released \n");
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	printf("Mouse moved (%f,%f)\n", float(evnt.x), float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		printf("Left mouse Clicked at (%f, %f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT))
	{
		printf("Right mouse Clicked at (%f, %f)\n", float(evnt.x), float(evnt.y));
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE))
	{
		printf("Middle mouse Clicked at (%f, %f)\n", float(evnt.x), float(evnt.y));
	}


	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	printf("Mouse Scroll %f\n", float(evnt.y));
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
