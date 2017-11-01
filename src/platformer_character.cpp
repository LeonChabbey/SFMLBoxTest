#include <platformer_character.h>
#include <iostream>

PlatformerCharacter::PlatformerCharacter(b2World & world)
{
	//Create the rectangle
	rect.setPosition(center_position - size / 2.f);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Green);
	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = pixel2meter(center_position);
	myBodyDef.fixedRotation = true;
	body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(
		pixel2meter(size.x) / 2.f, pixel2meter(size.y) / 2.f);
	box.shape = &box_shape;
	box.friction = 0.f;

	//Feet sensor
	b2FixtureDef foot;
	b2PolygonShape foot_shape;
	foot.isSensor = true;
	foot_shape.SetAsBox(
		pixel2meter(size.x-4.f) / 2.f, pixel2meter(2.0f) / 2.f,
		b2Vec2(0.f, pixel2meter(size.y)/2), 
		0.f);
	foot.shape = &foot_shape;
	feet_data.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	feet_data.data = this;
	foot.userData = &feet_data;


	//Right side sensor
	b2FixtureDef right_side;
	b2PolygonShape right_side_shape;
	right_side.isSensor = true;
	right_side_shape.SetAsBox(
		pixel2meter(1.f), pixel2meter(size.y) / 3.f,
		b2Vec2(pixel2meter(size.x)/2, 0.f),
		0.f);
	right_side.shape = &right_side_shape;
	right_side_data.contactDataType = ContactDataType::PLATFORM_CHARACTER_RIGHT;
	right_side_data.data = this;
	right_side.userData = &right_side_data;
	

	//Left side sensor
	b2FixtureDef left_side;
	b2PolygonShape left_side_shape;
	left_side.isSensor = true;
	left_side_shape.SetAsBox(
		pixel2meter(1.f), pixel2meter(size.y) / 3.f,
		b2Vec2(pixel2meter(size.x)/-2, 0.f),
		0.f);
	left_side.shape = &left_side_shape;
	left_side_data.contactDataType = ContactDataType::PLATFORM_CHARACTER_LEFT;
	left_side_data.data = this;
	left_side.userData = &left_side_data;

	body->CreateFixture(&box);
	body->CreateFixture(&foot);
	body->CreateFixture(&right_side);
	body->CreateFixture(&left_side);
}

PlatformerCharacter::~PlatformerCharacter()
{
}

void PlatformerCharacter::update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (wall > 0)
			body->ApplyForce(b2Vec2(jump_speed/2, -jump_speed), body->GetWorldCenter(), true);
		else if (wall < 0)
			body->ApplyForce(b2Vec2(-jump_speed / 2, -jump_speed), body->GetWorldCenter(), true);

		if (foot > 0)
			body->ApplyForce(b2Vec2(0, -jump_speed), body->GetWorldCenter(), true);			
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		body->ApplyForce(b2Vec2(-walk_speed, 0), body->GetWorldCenter(), true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		body->ApplyForce(b2Vec2(walk_speed, 0), body->GetWorldCenter(), true);
	}

	center_position = meter2pixel(body->GetPosition());
	rect.setPosition(center_position - size / 2.f);
}

void PlatformerCharacter::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void PlatformerCharacter::onCollisionEnter(ContactDataType thisContactDataType, ContactData* otherFixture)
{
	switch (thisContactDataType) {
	case ContactDataType::PLATFORM_CHARACTER:
		touch_ground();
		break;
	case ContactDataType::PLATFORM_CHARACTER_LEFT:
		increment_wall();
		break;
	case ContactDataType::PLATFORM_CHARACTER_RIGHT:
		decrement_wall();
		break;
	}
}

void PlatformerCharacter::onCollisionExit(ContactDataType thisContactDataType, ContactData * otherFixture)
{
	switch (thisContactDataType) {
	case ContactDataType::PLATFORM_CHARACTER:
		leave_ground();
		break;
	case ContactDataType::PLATFORM_CHARACTER_LEFT:
		decrement_wall();
		break;
	case ContactDataType::PLATFORM_CHARACTER_RIGHT:
		increment_wall();
		break;
	}
}

void PlatformerCharacter::increment_wall()
{
	wall++;
}

void PlatformerCharacter::decrement_wall()
{
	wall--;
}

void PlatformerCharacter::touch_ground()
{
	foot++;
}

void PlatformerCharacter::leave_ground()
{
	foot--;
}
