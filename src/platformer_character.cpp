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
	contactData.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactData.data = this;
	foot.userData = &contactData;


	//Left and right sides sensor
	b2FixtureDef sides;
	b2PolygonShape sides_shape;
	sides.isSensor = true;
	sides_shape.SetAsBox(
		pixel2meter(size.x + 2.f) / 2, pixel2meter(size.y) / 4.f,
		b2Vec2(0.f, 0.f),
		0.f);
	sides.shape = &sides_shape;
	contactData.contactDataType = ContactDataType::PLATFORM_CHARACTER;
	contactData.data = this;
	sides.userData = &contactData;

	body->CreateFixture(&box);
	body->CreateFixture(&foot);
	body->CreateFixture(&sides);
}

PlatformerCharacter::~PlatformerCharacter()
{
}

void PlatformerCharacter::update(float move_axis, bool jump_button)
{
	//manage movements
	body->SetLinearVelocity(b2Vec2(walk_speed*move_axis, body->GetLinearVelocity().y));
	if (foot > 0 && jump_button)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jump_speed));
	}
	center_position = meter2pixel(body->GetPosition());
	rect.setPosition(center_position - size / 2.f);
}

void PlatformerCharacter::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void PlatformerCharacter::onCollisionEnter(ContactData* thisFixture, ContactData* otherFixture)
{
	std::cout << "foot:" << foot << "\n" << std::flush;
}

void PlatformerCharacter::onCollisionExit(ContactData* thisFixture, ContactData * otherFixture)
{
}

void PlatformerCharacter::touch_ground()
{
	foot++;
}

void PlatformerCharacter::leave_ground()
{
	foot--;
}
