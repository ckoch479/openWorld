#include "reactPhysicsListener.h"

void reactPhysicsListener::onContact(const rp3d::CollisionCallback::CallbackData& data)
{
	
	for(unsigned int i = 0; i < data.getNbContactPairs(); i++)
	{
		//rp3d::CollisionCallback::ContactPair newPair = data.getContactPair(i);
		

		//std::cout << "contact happened\n";

		

		
	}
}