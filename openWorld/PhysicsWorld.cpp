#include "PhysicsWorld.h"

void PhysicsWorld::eulerIntergration(physicsObject& object, Force& force, float dt)
{
	float accelerationX = force.direction.x * (force.magnitude / object.body->mass);
	float accelerationY = force.direction.y * (force.magnitude / object.body->mass);;
	float accelerationZ = force.direction.z * (force.magnitude / object.body->mass);;



	object.body->velocity.x += accelerationX * dt;
	object.body->velocity.y += accelerationY * dt;
	object.body->velocity.z += accelerationZ * dt;

	object.body->position.x += object.body->velocity.x * dt;
	object.body->position.y += object.body->velocity.y * dt;
	object.body->position.z += object.body->velocity.z * dt;

}
//
//physicsObject* PhysicsWorld::addPhysicsObject(RigidBody body, Collider collider)
//{
//
//}
//
//RigidBody* PhysicsWorld::createRigidBody(glm::vec3 Positon, glm::vec3 velocity, float mass)
//{
//
//}
//
//Collider* PhysicsWorld::createCollider(AABB collider)
//{
//
//}

//Collider* PhysicsWorld::createCollider(CircleCollider collider)
//{
//
//}
//
//Collider* PhysicsWorld::createCollider(Collider collider)
//{
//
//}

void PhysicsWorld::stepPhysicsSimulation(float dt)
{

}