#include "HelloWorld.h"

HelloWorld::HelloWorld(std::string name)
	: Scene(name)
{

}

void HelloWorld::InitScene(float windowWidth, float windowHeight)
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
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize();
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2{ float(windowWidth), float(windowHeight) });
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		
		//Indentifier
		unsigned int bitHolder = EntityIdentifier::CameraBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera");
		ECS::SetIsMainCamera(entity, true);
	
	}
	//creates a new entity
	{
		auto entity = ECS::CreateEntity();

		//Creates New orthographic camera
		ECS::AttachComponent<HealthBar>(entity);
		ECS::GetComponent<HealthBar>(entity).SetHealth(0.7f);

		//sets up identifier
		unsigned int bitHolder = EntityIdentifier::HealthBarBit();
		ECS::SetUpIdentifier(entity, bitHolder, "HealthBar Entity");
	}
	//Setup New entity
	{
		//creates the new entity
		auto entity = ECS::CreateEntity();

		//Adding components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets Up components
		std::string fileName = "HelloWorld.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 50);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-25.f, -25.f, 100.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Hello World Sign");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(25.f, 25.f, 98.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Markiplier");
	}
	{
		//creates the new entity
		auto entity = ECS::CreateEntity();

		//Adding components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Sets Up components
		std::string fileName = "markiplier-e-meme-dank-dankmeme-lord-farquaad.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 100);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(25.f, -50.f, 99.f));


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Markiplier");
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-20.f, 15.f, 98.f));



		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Markiplier");
	}
	//{
	//	//creates the new entity
	//	auto entity = ECS::CreateEntity();

	//	//Adding components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<AnimationController>(entity);

	//	//Sets Up components
	//	std::string fileName = "SNES-SuperMarioWorld-Mario.png";


	//	auto &animController = ECS::GetComponent<AnimationController>(entity);
	//	animController.InitUVs(fileName);
	//	//adds first animation
	//	animController.AddAnimation(Animation());
	//	//Sets active animation
	//	animController.SetActiveAnim(0);
	//	//gets first animation
	//	auto& anim = animController.GetAnimation(0);
	//	anim.AddFrame(vec2(1.f, 36.f), vec2(50.f, 1.f));
	//	anim.AddFrame(vec2(51.f, 36.f), vec2(100.f, 1.f));
	//	anim.AddFrame(vec2(101.f, 36.f), vec2(150.f, 1.f));
	//	anim.AddFrame(vec2(151.f, 36.f), vec2(200.f, 1.f));
	//	anim.AddFrame(vec2(201.f, 36.f), vec2(250.f, 1.f));
	//	anim.AddFrame(vec2(251.f, 36.f), vec2(300.f, 1.f));
	//	anim.AddFrame(vec2(301.f, 36.f), vec2(349.f, 1.f));

	//	//make it repeat
	//	anim.SetRepeating(true);
	//	//sets the time between frames
	//	anim.SetSecPerFrame(0.05f);

	//}
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
		//set active anim
		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 36, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 50.f, 100.f));
		//ECS::GetComponent<Sprite>(entity).SetUVs(vec2())


		//Sets up the identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Mario");

	}

}
