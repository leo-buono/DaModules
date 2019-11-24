#include "AssignmentChallenge1.h"



AssignmentMentChallenge1::AssignmentMentChallenge1(std::string name)
	: Scene(name)
{

}


void AssignmentMentChallenge1::InitScene(float windowWidth, float windowHeight)
{
	m_sceneReg = new entt::registry;


	ECS::AttachRegister(m_sceneReg);
	float aspectRatio = windowWidth / windowHeight;
	{
		//Camera entity
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainCamera(entity);


		//Orthographic Camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2{ float(windowWidth), float(windowHeight) });
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//attaches camera to the vertical scroll
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffset(15.f);
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffset(15.f);

		//Indentifier
		unsigned int bitHolder = EntityIdentifier::VertScrollCameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Scrolling Camera");
		ECS::SetIsMainCamera(entity, true);

	}
	{
		//anim file
		auto swing = File::LoadJSON("MarioSwing.json");

		//create entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//sets up components
		std::string fileName = "SNES-SuperMarioWorld-Mario.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds animation 1
		animController.AddAnimation(swing["HammerSwing"]);
		//adds animation 2
		animController.AddAnimation(swing["MarioSwim"]);
		//set active anim
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 36, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 50.f, 100.f));
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2())


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Mario");

	}
	{
		//create entity
		auto entity = ECS::CreateEntity();

		//add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		//file name
		std::string fileName = "mario.png";

		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//adds first animation
		animController.AddAnimation(Animation());
		//Sets active animation
		animController.SetActiveAnim(0);
		//gets first animation
		auto& anim = animController.GetAnimation(0);
		anim.AddFrame(vec2(1.f, 21.f), vec2(14.f, 1.f));
		anim.AddFrame(vec2(16.f, 21.f), vec2(29.f, 1.f));

		//make it repeat
		anim.SetRepeating(true);
		//sets the time between frame
		anim.SetSecPerFrame(0.05f);


		//position
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 14, 21, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 15.f, 98.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Mario Running");

	}
	{
		//creates the new entity
		auto entity = ECS::CreateEntity();

		//Adding components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets Up components
		std::string fileName = "markiplier-e-meme-dank-dankmeme-lord-farquaad.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 50);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(50.f, 25.f, 98.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Markiplier");
	}
	{
		//creates the new entity
		auto entity = ECS::CreateEntity();

		EntityIdentifier::MainPlayer(entity);


		//Adding components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets Up components
		std::string fileName = "joe.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 70);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-50.f, -25.f, 97.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Joe");
		ECS::SetIsMainPlayer(entity, true);
	}
	//camera focuses on Mainplayer
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}
