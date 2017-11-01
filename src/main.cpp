#include <SFML/Graphics.hpp>
#include <platformer_character.h>
#include <platform.h>
#include <utility.h>
#include <iostream>
#include <list>

#include <default_behaviour.h>
#include <Box2D/Box2D.h>

class MyContactListener : public b2ContactListener
{
	void BeginContact(b2Contact* contact) 
	{
		ContactData* fixtureAContactData = static_cast<ContactData*>(contact->GetFixtureA()->GetUserData());
		ContactData* fixtureBContactData = static_cast<ContactData*>(contact->GetFixtureB()->GetUserData());

		if (fixtureAContactData == nullptr || fixtureBContactData == nullptr)
			return;

		DefaultBehaviour* fixtureA = static_cast<DefaultBehaviour*>(fixtureAContactData->data);
		DefaultBehaviour* fixtureB = static_cast<DefaultBehaviour*>(fixtureBContactData->data);
	
		fixtureA->onCollisionEnter(fixtureAContactData->contactDataType, fixtureBContactData);
		fixtureB->onCollisionEnter(fixtureBContactData->contactDataType, fixtureAContactData);
	}

	void EndContact(b2Contact* contact) {
		ContactData* fixtureAContactData = static_cast<ContactData*>(contact->GetFixtureA()->GetUserData());
		ContactData* fixtureBContactData = static_cast<ContactData*>(contact->GetFixtureB()->GetUserData());

		if (fixtureAContactData == nullptr || fixtureBContactData == nullptr)
			return;

		DefaultBehaviour* fixtureA = static_cast<DefaultBehaviour*>(fixtureAContactData->data);
		DefaultBehaviour* fixtureB = static_cast<DefaultBehaviour*>(fixtureBContactData->data);

		fixtureA->onCollisionExit(fixtureAContactData->contactDataType, fixtureBContactData);
		fixtureB->onCollisionExit(fixtureBContactData->contactDataType, fixtureAContactData);
	}
};

int main()
{

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World myWorld = b2World(gravity);
	//at global scope
	MyContactListener myContactListenerInstance;

	//in FooTest constructor
	myWorld.SetContactListener(&myContactListenerInstance);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(framerate);
	

	float32 timeStep = 1 / framerate;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position

	PlatformerCharacter character(myWorld);

	std::list<Platform*> platforms;
	platforms.push_back(new Platform(myWorld));
	platforms.push_back(new Platform(myWorld, sf::Vector2f(400.f, 0.f)));
	platforms.push_back(new Platform(myWorld, sf::Vector2f(0.f, 300.f), sf::Vector2f(100.f, 600.f)));
	platforms.push_back(new Platform(myWorld, sf::Vector2f(800.f, 300.f), sf::Vector2f(100.f, 600.f)));
	platforms.push_back(new Platform(myWorld, sf::Vector2f(150.f, 200.f), sf::Vector2f(200.f, 50.f)));
	platforms.push_back(new Platform(myWorld, sf::Vector2f(650.f, 400.f), sf::Vector2f(200.f, 50.f)));
	
	/*std::list<Platform> platforms =
	{
		Platform(myWorld),
		Platform(myWorld, sf::Vector2f(400.f,0.f)),
		Platform(myWorld, sf::Vector2f(0.f,300.f), sf::Vector2f(100.f,600.f)),
		Platform(myWorld, sf::Vector2f(800.f,300.f), sf::Vector2f(100.f,600.f)),
		Platform(myWorld, sf::Vector2f(150.f,200.f), sf::Vector2f(200.f,50.f)),
		Platform(myWorld, sf::Vector2f(650.f,400.f), sf::Vector2f(200.f,50.f)),
	};*/
	
	while (window.isOpen())
	{
		myWorld.Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		
		character.update();
		
		window.clear();
		character.draw(window);
		for (Platform* platform : platforms)
		{
			platform->draw(window);
		}
		window.display();
	}

	system("pause");
	return 0;
}