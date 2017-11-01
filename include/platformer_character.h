#ifndef PLATFORMER_CHAR_H
#define PLATFORMER_CHAR_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <utility.h>
#include <default_behaviour.h>

class PlatformerCharacter : public DefaultBehaviour
{
public:
	PlatformerCharacter(b2World&);
	~PlatformerCharacter();
	void update();
	void draw(sf::RenderWindow&);
	void onCollisionEnter(ContactDataType, ContactData*);
	void onCollisionExit(ContactDataType, ContactData*);
	void increment_wall();
	void decrement_wall();
	void touch_ground();
	void leave_ground();
private:
	int foot = 0;
	int wall = 0;
	b2Body* body;
	sf::RectangleShape rect;
	sf::Vector2f center_position = sf::Vector2f(400.f, 300.f);
	sf::Vector2f size = sf::Vector2f(64.f,64.f);
	const float walk_speed = 5.0f;
	const float jump_speed = 300.f;
	ContactData feet_data;
	ContactData left_side_data;
	ContactData right_side_data;
};

#endif // !PLATFORMER_CHAR_H
