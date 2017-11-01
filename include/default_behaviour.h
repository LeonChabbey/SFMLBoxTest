#ifndef DEFAULT_BEHAVIOUR_H
#define DEFAULT_BEHAVIOUR_H

#include <Box2D/Box2D.h>
#include <utility.h>

class DefaultBehaviour
{
protected:
	ContactData boxData;
public:
	DefaultBehaviour();
	~DefaultBehaviour();

	virtual void onCollisionEnter(ContactDataType, ContactData*) = 0;
	virtual void onCollisionExit(ContactDataType, ContactData*) = 0;
};

#endif // !DEFAULT_BEHAVIOUR_H
