#include "b2PhysicsBody.h"

b2PhysicsBody::b2PhysicsBody()
{
	_bodyDef.type = b2_staticBody;
	_bodyDef.position.Set(0, 0);
	_body = nullptr;
}

b2PhysicsBody::~b2PhysicsBody()
{
}

void b2PhysicsBody::setBodyType(b2BodyType bodyType )
{
	_bodyDef.type = bodyType;
}

void b2PhysicsBody::setShapeAndMaterial(b2Shape* shape, const b2PhysicsMaterial &material)
{
	_shapeDef.shape = shape;
	_shapeDef.density = material.density;
	_shapeDef.friction = material.friction;
	_shapeDef.restitution = material.restitution;
}

void b2PhysicsBody::initBox(const Size &size, const b2PhysicsMaterial &material)
{
	auto shape = new b2PolygonShape();
	shape->SetAsBox(size.width / 2 / PTM_RATIO, size.height / 2 / PTM_RATIO);
	this->setShapeAndMaterial(shape, material);
}

void b2PhysicsBody::initChain(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	for (int32 i = 0; i < count; i++)
		vertices[i].Set(vertices[i].x / PTM_RATIO, vertices[i].y / PTM_RATIO);
	this->initChain2(vertices, count, material);
}

void b2PhysicsBody::initChain2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	auto shape = new b2ChainShape();
	shape->CreateChain(vertices, count);
	this->setShapeAndMaterial(shape, material);
}

void b2PhysicsBody::initPolygon(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	for (int32 i = 0; i < count; i++)
		vertices[i].Set(vertices[i].x / PTM_RATIO, vertices[i].y / PTM_RATIO);
	this->initPolygon2(vertices, count,  material);
}

void b2PhysicsBody::initPolygon2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	auto shape = new b2PolygonShape();
	shape->Set(vertices, count);
	this->setShapeAndMaterial(shape, material);
}

void b2PhysicsBody::initCircle(float radius, const b2PhysicsMaterial &material)
{
	auto shape = new b2CircleShape();
	shape->m_radius = 30.0 / PTM_RATIO;
	this->setShapeAndMaterial(shape, material);
}

void b2PhysicsBody::initEdgeShape(b2Vec2 v1, b2Vec2 v2, const b2PhysicsMaterial &material)
{
	v1.Set(v1.x / PTM_RATIO, v1.y / PTM_RATIO);
	v2.Set(v2.x / PTM_RATIO, v2.y / PTM_RATIO);
	auto shape = new b2EdgeShape();
	shape->Set(v1, v2);
	this->setShapeAndMaterial(shape, material);
}

void b2PhysicsBody::initEdgeShape2(const b2Vec2 v1, const b2Vec2 v2, const b2PhysicsMaterial &material)
{
	auto shape = new b2EdgeShape();
	shape->Set(v1, v2);
	this->setShapeAndMaterial(shape, material);
}

b2PhysicsBody* b2PhysicsBody::createBox(const Size &size, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initBox(size, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createChain(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initChain(vertices, count, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createChain2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initChain2(vertices, count, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createPolygon(b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initPolygon(vertices, count, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createPolygon2(const b2Vec2 * vertices, int32 count, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initPolygon2(vertices, count, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createCircle(float radius, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initCircle(radius, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createEdgeShape(b2Vec2 v1, b2Vec2 v2, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initEdgeShape(v1, v2, material);
	return b2physicsBody;
}

b2PhysicsBody* b2PhysicsBody::createEdgeShape2(const b2Vec2 v1, const b2Vec2 v2, const b2PhysicsMaterial &material)
{
	b2PhysicsBody* b2physicsBody = new b2PhysicsBody();
	b2physicsBody->initEdgeShape2(v1, v2, material);
	return b2physicsBody;
}

void b2PhysicsBody::setb2Position(float x, float y)
{
	_bodyDef.position.Set(x / PTM_RATIO, y / PTM_RATIO);
}

void b2PhysicsBody::setb2Transform(float x, float y)
{
	_body->SetTransform(b2Vec2(x / PTM_RATIO, y / PTM_RATIO),
		_body->GetAngle());
}

void b2PhysicsBody::setb2Transform(float x, float y, float angle)
{
	_body->SetTransform(b2Vec2(x / PTM_RATIO, y / PTM_RATIO),
		angle);
}

void b2PhysicsBody::setb2TransformX(float x)
{
	_body->SetTransform(b2Vec2(x / PTM_RATIO, _body->GetPosition().y),
		_body->GetAngle());
}

void b2PhysicsBody::setb2TransformY(float y)
{
	_body->SetTransform(b2Vec2(_body->GetPosition().x, y / PTM_RATIO),
		_body->GetAngle());
}

void b2PhysicsBody::setb2TransformAngle(float angle)
{
	_body->SetTransform(b2Vec2(_body->GetPosition().x, _body->GetPosition().y),
		_body->GetAngle());
}

void b2PhysicsBody::setb2PositionX(float x)
{
	_bodyDef.position.Set(x / PTM_RATIO, _bodyDef.position.y);
}

void b2PhysicsBody::setb2PositionY(float y)
{
	_bodyDef.position.Set(_bodyDef.position.x, y / PTM_RATIO);
}

Vec2 b2PhysicsBody::getb2Position()
{
	if (_body != nullptr)
		return Vec2(_body->GetPosition().x * PTM_RATIO, _body->GetPosition().y * PTM_RATIO);
	else
		return Vec2(_bodyDef.position.x * PTM_RATIO, _bodyDef.position.y * PTM_RATIO);
}

void b2PhysicsBody::setVelocityX(float Vx){
	this->getBody()->SetLinearVelocity(b2Vec2(Vx, this->getBody()->GetLinearVelocity().y));
}

void b2PhysicsBody::setVelocityY(float Vy){
	this->getBody()->SetLinearVelocity(b2Vec2(this->getBody()->GetLinearVelocity().x, Vy));
}

float b2PhysicsBody::getVelocityX(){
	return this->getBody()->GetLinearVelocity().x;
}

float b2PhysicsBody::getVelocityY(){
	return this->getBody()->GetLinearVelocity().y;
}