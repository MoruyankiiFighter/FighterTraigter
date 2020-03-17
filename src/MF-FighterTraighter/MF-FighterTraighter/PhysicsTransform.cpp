#include "PhysicsTransform.h"
#include "Training.h"
PhysicsTransform::PhysicsTransform(Vector2D position, Vector2D speed, double width, double height, double rotation, b2World* world, bool dyn)
	: Transform(position, speed, width, height, rotation)
{
	world_ = world;

	b2BodyDef bodydef;
	bodydef.position.Set(position.getX(), position.getY());
	//position_ = bodydef.position();
	if (dyn)  bodydef.type = b2_dynamicBody;
	body_ = world->CreateBody(&bodydef);
	b2PolygonShape shape;
	shape.SetAsBox(width * wMult_/2 , height * hMult_/2 );

	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.00001;			//densidad 0, para que no cambie segun el ancho y el alto por ahora
	body_->CreateFixture(&fixturedef);
	body_->SetFixedRotation(true);
}


PhysicsTransform::~PhysicsTransform() {
	//world_->DestroyBody(body_);
}

void PhysicsTransform::init() {
	body_->SetUserData(this->entity_);	//tener acceso a la entidad para hacer cosas con las colisiones

}

//al anadir mas hitbox puede dar fallo
void PhysicsTransform::setHeight(double height) {
	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width_ / 2, height / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0;

	body_->CreateFixture(&fixturedef);

	height_ = height;
}

//al anadir mas hitbox puede dar fallo
void PhysicsTransform::setWidth(double width) {

	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height_ / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0;

	body_->CreateFixture(&fixturedef);
	width_ = width;
}

//al anadir mas hitbox puede dar fallo
void PhysicsTransform::setWidthHeight(double width, double height) {

	body_->DestroyFixture(body_->GetFixtureList());

	b2PolygonShape shape;
	shape.SetAsBox(width / 2, height / 2);
	b2FixtureDef fixturedef;
	fixturedef.shape = &shape;
	fixturedef.density = 0.0;

	body_->CreateFixture(&fixturedef);
	width_ = width;
	height_ = height;
}
