#ifndef DEFAULT_BEHAVIOUR_H
#define DEFAULT_BEHAVIOUR_H

#include <Box2D/Box2D.h>
#include <utility.h>

class DefaultBehaviour
{
protected:
	ContactData contactData;
public:
	DefaultBehaviour();
	~DefaultBehaviour();

	virtual void onCollisionEnter(ContactData*, ContactData*) = 0;
	virtual void onCollisionExit(ContactData*, ContactData*) = 0;
};

#endif // !DEFAULT_BEHAVIOUR_H
