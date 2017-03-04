#include "ContactListener.h"


ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}

void ContactListener::BeginContact(b2Contact* contact){
	//check if fixture A was a PhysicsEntity

	b2Fixture *fixtureA, *fixtureB;
	fixtureA = contact->GetFixtureA();
	fixtureB = contact->GetFixtureB();
	std::vector<b2Vec2> intersectionPoints;

	PhysicsEntity* bodyAUserData = static_cast<PhysicsEntity*>(fixtureA->GetBody()->GetUserData());
	PhysicsEntity* bodyBUserData = static_cast<PhysicsEntity*>(fixtureB->GetBody()->GetUserData());

	bodyAUserData->startContact(bodyBUserData);
	bodyBUserData->startContact(bodyAUserData);

	if (findIntersectionOfFixtures(fixtureA, fixtureB, intersectionPoints)){

	}
}

void ContactListener::EndContact(b2Contact* contact){

	PhysicsEntity* bodyAUserData = static_cast<PhysicsEntity*>(contact->GetFixtureA()->GetBody()->GetUserData());
	PhysicsEntity* bodyBUserData = static_cast<PhysicsEntity*>(contact->GetFixtureB()->GetBody()->GetUserData());

	bodyAUserData->endContact(bodyBUserData);
	bodyBUserData->endContact(bodyAUserData);
}

bool ContactListener::inside(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 p) {
	return (cp2.x - cp1.x)*(p.y - cp1.y) > (cp2.y - cp1.y)*(p.x - cp1.x);
}

b2Vec2 ContactListener::intersection(b2Vec2 cp1, b2Vec2 cp2, b2Vec2 s, b2Vec2 e) {
	b2Vec2 dc(cp1.x - cp2.x, cp1.y - cp2.y);
	b2Vec2 dp(s.x - e.x, s.y - e.y);
	float n1 = cp1.x * cp2.y - cp1.y * cp2.x;
	float n2 = s.x * e.y - s.y * e.x;
	float n3 = 1.0 / (dc.x * dp.y - dc.y * dp.x);
	return b2Vec2((n1*dp.x - n2*dc.x) * n3, (n1*dp.y - n2*dc.y) * n3);
}

//http://rosettacode.org/wiki/Sutherland-Hodgman_polygon_clipping#JavaScript
//Note that this only works when fB is a convex polygon, but we know all 
//fixtures in Box2D are convex, so that will not be a problem
bool ContactListener::findIntersectionOfFixtures(b2Fixture* fA, b2Fixture* fB, std::vector<b2Vec2>& outputVertices)
{
	//currently this only handles polygon vs polygon
	if (fA->GetShape()->GetType() != b2Shape::e_polygon ||
		fB->GetShape()->GetType() != b2Shape::e_polygon)
		return false;

	b2PolygonShape* polyA = (b2PolygonShape*)fA->GetShape();
	b2PolygonShape* polyB = (b2PolygonShape*)fB->GetShape();

	//fill subject polygon from fixtureA polygon
	for (int i = 0; i < polyA->GetVertexCount(); i++)
		outputVertices.push_back(fA->GetBody()->GetWorldPoint(polyA->GetVertex(i)));

	//fill clip polygon from fixtureB polygon
	std::vector<b2Vec2> clipPolygon;
	for (int i = 0; i < polyB->GetVertexCount(); i++)
		clipPolygon.push_back(fB->GetBody()->GetWorldPoint(polyB->GetVertex(i)));

	b2Vec2 cp1 = clipPolygon[clipPolygon.size() - 1];
	for (int j = 0; j < clipPolygon.size(); j++) {
		b2Vec2 cp2 = clipPolygon[j];
		if (outputVertices.empty())
			return false;
		std::vector<b2Vec2> inputList = outputVertices;
		outputVertices.clear();
		b2Vec2 s = inputList[inputList.size() - 1]; //last on the input list
		for (int i = 0; i < inputList.size(); i++) {
			b2Vec2 e = inputList[i];
			if (inside(cp1, cp2, e)) {
				if (!inside(cp1, cp2, s)) {
					outputVertices.push_back(intersection(cp1, cp2, s, e));
				}
				outputVertices.push_back(e);
			}
			else if (inside(cp1, cp2, s)) {
				outputVertices.push_back(intersection(cp1, cp2, s, e));
			}
			s = e;
		}
		cp1 = cp2;
	}

	return !outputVertices.empty();
}