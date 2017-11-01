#include <platform.h>
#include <iostream>

Platform::Platform(b2World & world, sf::Vector2f position, sf::Vector2f size)
{
	center_position = position;
	this->size = size;
	//Create the rectangle
	rect.setPosition(center_position - size / 2.f);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Red);
	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_staticBody;
	myBodyDef.position = pixel2meter(center_position);
	body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(pixel2meter(size.x) / 2.f, pixel2meter(size.y) / 2.f);
	box.shape = &box_shape;
	boxData.contactDataType = ContactDataType::PLATFORM;
	boxData.data = this;
	box.userData = &boxData;
	body->CreateFixture(&box);
}

Platform::~Platform()
{
	std::cout << "blblb" << "\n" << std::flush;
}

void Platform::onCollisionEnter(ContactDataType* thisContactDataType, ContactData* otherFixture)
{
	std::cout << "test" << "\n" << std::flush;
}

void Platform::onCollisionExit(ContactDataType* thisContactDataType, ContactData * otherFixture)
{
}

void Platform::draw(sf::RenderWindow & window)
{
	window.draw(rect);
}
