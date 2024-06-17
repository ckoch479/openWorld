#pragma once
#include <iostream>
#include <vector>

#include <reactphysics3d/reactphysics3d.h>

#ifndef REACTPHYSICSLISTENER_H
#define REACTPHYSICSLISTENER_H


class reactPhysicsListener : public rp3d::EventListener
{
public:

	reactPhysicsListener() {};
	~reactPhysicsListener() {};

	virtual void onContact(const rp3d::CollisionCallback::CallbackData& data) override;

private:

};

#endif