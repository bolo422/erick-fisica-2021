#include "test.h"
#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

class MyTest : public Test //você cria a sua classe derivada da classe base Test
{

private:
	float restitutionCount = 0;
	float frictionCount = 0;
	bool rampaCriada = false;

public:
	MyTest() {
		//////////// EXERCÍCIO 7	
		bool exercicio7 = false;
		if (exercicio7) {
			// Left Wall
			b2BodyDef WallLeftBodyDef;
			WallLeftBodyDef.position.Set(-70.0f, 28.0f);
			b2Body* WallLeftBody = m_world->CreateBody(&WallLeftBodyDef);
			b2PolygonShape WallLeftBox;
			WallLeftBox.SetAsBox(1.0f, 50.0f);
			WallLeftBody->CreateFixture(&WallLeftBox, 0.0f);

			// Right Wall
			b2BodyDef WallRightBodyDef;
			WallRightBodyDef.position.Set(70.0f, 28.0f);
			b2Body* WallRightBody = m_world->CreateBody(&WallRightBodyDef);
			b2PolygonShape WallRightBox;
			WallRightBox.SetAsBox(1.0f, 50.0f);
			WallRightBody->CreateFixture(&WallRightBox, 0.0f);

			// Roof
			b2BodyDef RoofBodyDef;
			RoofBodyDef.position.Set(0.0f, 77.0f);
			b2Body* RoofBody = m_world->CreateBody(&RoofBodyDef);
			b2PolygonShape RoofBox;
			RoofBox.SetAsBox(70.0f, 1.0f);
			RoofBody->CreateFixture(&RoofBox, 0.0f);
		}
		/////////

		//Exercício 7
		bool criarParedes = true;
		if (criarParedes) {

			float mult = 2.0f;
			b2Vec2* sd = new b2Vec2(-50.0f * mult, 25.0f * mult);
			b2Vec2* se = new b2Vec2(50.0f * mult, 25.0f * mult);
			b2Vec2* id = new b2Vec2(50.0f * mult, -25.0f * mult);
			b2Vec2* ie = new b2Vec2(-50.0f * mult, -25.0f * mult);

			b2Body* edge1 = createEdge(*sd, *se);
			b2Body* edge2 = createEdge(*se, *id);
			b2Body* edge3 = createEdge(*id, *ie);
			b2Body* edge4 = createEdge(*ie, *sd);
		}
		/////////////


	}

	void Step(Settings& settings) override
	{
		//Chama o passo da simulação e o algoritmo de rendering
		Test::Step(settings);

		//show some text in the main screen
		g_debugDraw.DrawString(5, m_textLine, "Este e' um template para os exercicios!! :)");
		m_textLine += 15;
	}

	static Test* Create()  //a classe Test que instancia um objeto da sua nova classe
						   //o autor da Box2D usa um padrão de projeto chamado Factory
						   //para sua arquitetura de classes
	{
		return new MyTest;
	}

	// EXERCÍCIO 6 - Cubo
	b2Body* createBox(b2Vec2 pos, b2Vec2 dim, b2Vec2 lvel, float grav, float density, float friction, float restitution, bool isDynamic)
	{
		b2BodyDef bodyDef;
		bodyDef.linearVelocity.Set(lvel.x, lvel.y);
		bodyDef.gravityScale = grav;

		if (isDynamic)	bodyDef.type = b2_dynamicBody;
		else			bodyDef.type = b2_staticBody;

		bodyDef.position.Set(pos.x,pos.y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2PolygonShape dynamicBox;
		dynamicBox.SetAsBox(dim.x,dim.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &dynamicBox;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		body->CreateFixture(&fixtureDef);
		return body;
	}

	// EXERCÍCIO 6 - Círculo
	b2Body* createCircle(b2Vec2 pos, float radius, b2Vec2 lvel, float grav, float density, float friction, float restitution, bool isDynamic)
	{
		b2BodyDef bodyDef;
		bodyDef.linearVelocity.Set(lvel.x, lvel.y);
		bodyDef.gravityScale = grav;

		if (isDynamic)	bodyDef.type = b2_dynamicBody;
		else			bodyDef.type = b2_staticBody;
		bodyDef.position.Set(pos.x, pos.y);
		b2Body* body = m_world->CreateBody(&bodyDef);

		// Define another box shape for our dynamic body.
		b2CircleShape circle;
		circle.m_radius = radius;
		//dynamicBox.SetAsBox(dim.x, dim.y);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &circle;
		fixtureDef.density = density;
		fixtureDef.friction = friction;
		fixtureDef.restitution = restitution;
		body->CreateFixture(&fixtureDef);

		return body;
	}

	// EXERCÍCIO 6 - Linha
	b2Body* createEdge(b2Vec2 p1, b2Vec2 p2)
	{
		b2Body* novoObjeto;
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		b2Body* body = m_world->CreateBody(&bodyDef);

		b2EdgeShape shape;
		shape.SetTwoSided(p1, p2);
		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		body->CreateFixture(&fixtureDef);
		return body;
	}

	//EXERCÍCIO 13 - "Pato" (Diamante)
	b2Body* createDiamond(float posX, float posY, float scaleFactor)
	{
		b2Body* novoObjeto;
		//Primeiro, criamos a definição do corpo
		b2BodyDef bodyDef;
		bodyDef.position.Set(posX, posY);
		bodyDef.type = b2_dynamicBody;
		b2PolygonShape* formas = new b2PolygonShape[8]; 
		b2FixtureDef* partes = new b2FixtureDef[8]; 
		//////////////////////////////////////////////
		b2Vec2* c1 = new b2Vec2[3];
		c1[0] = b2Vec2(1 * scaleFactor, 7 * scaleFactor);
		c1[1] = b2Vec2(2 * scaleFactor, 5 * scaleFactor);
		c1[2] = b2Vec2(0 * scaleFactor, 5 * scaleFactor);
		formas[0].Set(c1, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[0].shape = &formas[0];
		//Setamos outras propriedades da fixture
		partes[0].density = 10.0;
		partes[0].friction = 0.5;
		partes[0].restitution = 0.5;
		//////////////////////////////////////////////
		b2Vec2* c2 = new b2Vec2[3];
		c2[0] = b2Vec2(1 * scaleFactor, 7 * scaleFactor);
		c2[1] = b2Vec2(2 * scaleFactor, 5 * scaleFactor);
		c2[2] = b2Vec2(3 * scaleFactor, 7 * scaleFactor);
		formas[1].Set(c2, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[1].shape = &formas[1];
		//Setamos outras propriedades da fixture
		partes[1].density = 10.0;
		partes[1].friction = 0.5;
		partes[1].restitution = 0.5;
		//////////////////////////////////////////////
		b2Vec2* c3 = new b2Vec2[3];
		c3[0] = b2Vec2(4 * scaleFactor, 5 * scaleFactor);
		c3[1] = b2Vec2(2 * scaleFactor, 5 * scaleFactor);
		c3[2] = b2Vec2(3 * scaleFactor, 7 * scaleFactor);
		formas[2].Set(c3, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[2].shape = &formas[2];
		//Setamos outras propriedades da fixture
		partes[2].density = 10.0;
		partes[2].friction = 0.5;
		partes[2].restitution = 0.5;
		////////////////////////////////////////////////
		b2Vec2* c4 = new b2Vec2[3];
		c4[0] = b2Vec2(4 * scaleFactor, 5 * scaleFactor);
		c4[1] = b2Vec2(5 * scaleFactor, 7 * scaleFactor);
		c4[2] = b2Vec2(3 * scaleFactor, 7 * scaleFactor);
		formas[3].Set(c4, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[3].shape = &formas[3];
		//Setamos outras propriedades da fixture
		partes[3].density = 10.0;
		partes[3].friction = 0.5;
		partes[3].restitution = 0.5;
		////////////////////////////////////////////////
		b2Vec2* c5 = new b2Vec2[3];
		c5[0] = b2Vec2(4 * scaleFactor, 5 * scaleFactor);
		c5[1] = b2Vec2(5 * scaleFactor, 7 * scaleFactor);
		c5[2] = b2Vec2(6 * scaleFactor, 5 * scaleFactor);
		formas[4].Set(c5, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[4].shape = &formas[4];
		//Setamos outras propriedades da fixture
		partes[4].density = 10.0;
		partes[4].friction = 0.5;
		partes[4].restitution = 0.5;
		////////////////////////////////////////////////
		b2Vec2* b1 = new b2Vec2[3];
		b1[0] = b2Vec2(0 * scaleFactor, 5 * scaleFactor);
		b1[1] = b2Vec2(2 * scaleFactor, 5 * scaleFactor);
		b1[2] = b2Vec2(3 * scaleFactor, 0 * scaleFactor);
		formas[5].Set(b1, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[5].shape = &formas[5];
		//Setamos outras propriedades da fixture
		partes[5].density = 10.0;
		partes[5].friction = 0.5;
		partes[5].restitution = 0.5;
		////////////////////////////////////////////////
		b2Vec2* b2 = new b2Vec2[3];
		b2[0] = b2Vec2(2 * scaleFactor, 5 * scaleFactor);
		b2[1] = b2Vec2(4 * scaleFactor, 5 * scaleFactor);
		b2[2] = b2Vec2(3 * scaleFactor, 0 * scaleFactor);
		formas[6].Set(b2, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[6].shape = &formas[6];
		//Setamos outras propriedades da fixture
		partes[6].density = 10.0;
		partes[6].friction = 0.5;
		partes[6].restitution = 0.5;
		////////////////////////////////////////////////
		b2Vec2* b3 = new b2Vec2[3];
		b3[0] = b2Vec2(4 * scaleFactor, 5 * scaleFactor);
		b3[1] = b2Vec2(6 * scaleFactor, 5 * scaleFactor);
		b3[2] = b2Vec2(3 * scaleFactor, 0 * scaleFactor);
		formas[7].Set(b3, 3);
		//Depois, criamos uma fixture que vai conter a forma do corpo
		partes[7].shape = &formas[7];
		//Setamos outras propriedades da fixture
		partes[7].density = 10.0;
		partes[7].friction = 0.5;
		partes[7].restitution = 0.5;
		////////////////////////////////////////////////


		//Por fim, criamos o corpo...
		novoObjeto = m_world->CreateBody(&bodyDef);
		//... e criamos a fixture do corpo  
		for (int i = 0; i < 8; i++)
			novoObjeto->CreateFixture(&partes[i]);
		return novoObjeto;
	}

	//exercíico 6 + 8 + 9
	void Keyboard(int key) override
	{
		
		switch (key)
		{
		case GLFW_KEY_B:
			if (key == GLFW_KEY_B) {
				srand(time(NULL));

				b2Vec2* boxPos = new b2Vec2(rand() % 180 - 90, rand() % 80 - 40);
				b2Vec2* boxDim = new b2Vec2(rand() % 10 + 1, rand() % 10 + 1);
				b2Vec2* boxLVel = new b2Vec2(rand() % 360 + 1, rand() % 360 + 1);
				float boxGravity = rand() % 40 - 20;
				float boxDensity = rand() % 10 + 1;
				float boxFriction = (rand() % 10 + 1) / 10;
				float boxRestitution = (rand() % 10 + 1) / 10;
				bool boxIsDynamic = true;
				b2Body* box = createBox(*boxPos, *boxDim, *boxLVel, boxGravity, boxDensity, boxFriction, boxRestitution, boxIsDynamic);
			}
			break;

		case GLFW_KEY_C:
			if (key == GLFW_KEY_C) {
				srand(time(NULL));
				b2Vec2* circlePos = new b2Vec2(rand() % 180 - 90, rand() % 80 - 40);
				float circleRadius = rand() % 10 + 1;
				b2Vec2* circleLVel = new b2Vec2(rand() % 360 + 1, rand() % 360 + 1);
				float circleGravity = rand() % 40 - 20;
				float circleDensity = rand() % 10 + 1;
				float circleFriction = (rand() % 10 + 1) / 10;
				float circleRestitution = (rand() % 10 + 1) / 10;
				bool circleIsDynamic = true;

				b2Body* circle = createCircle(*circlePos, circleRadius, *circleLVel, circleGravity, circleDensity, circleFriction, circleRestitution, circleIsDynamic);
			}
			break;

		case GLFW_KEY_L:
			if (key == GLFW_KEY_L) {
				srand(time(NULL));
				b2Vec2* p1 = new b2Vec2(rand() % 200 - 100, rand() % 100 - 50);
				b2Vec2* p2 = new b2Vec2(rand() % 200 - 100, rand() % 100 - 50);
				b2Body* edge = createEdge(*p1, *p2);
			}
			break;

		// Exercício 9
		case GLFW_KEY_V:
			if (key == GLFW_KEY_V) {
				b2Vec2* boxPos = new b2Vec2(0,0);
				b2Vec2* boxDim = new b2Vec2(1,1);
				b2Vec2* boxLVel = new b2Vec2(0,0);
				float boxGravity = 1;
				float boxDensity = 1;
				float boxFriction = 1;
				float boxRestitution = restitutionCount;

				//
				int printRest = restitutionCount * 100;
				printf("%d\n", printRest);
				//

				if (restitutionCount < 1)
				restitutionCount += 0.1f;

				bool boxIsDynamic = true;
				b2Body* box = createBox(*boxPos, *boxDim, *boxLVel, boxGravity, boxDensity, boxFriction, boxRestitution, boxIsDynamic);
			}
			break;

		// Exercício 10
		case GLFW_KEY_G:
			if (key == GLFW_KEY_G) {

				if (!rampaCriada) {
					b2Vec2* p1 = new b2Vec2(100,0);
					b2Vec2* p2 = new b2Vec2(-100,-50);
					b2Body* edge = createEdge(*p1, *p2);
					rampaCriada = true;
				}

				b2Vec2* boxPos = new b2Vec2(90, 3);
				b2Vec2* boxDim = new b2Vec2(1, 1);
				b2Vec2* boxLVel = new b2Vec2(0, 0);
				float boxGravity = 1;
				float boxDensity = 1;
				float boxFriction = frictionCount;
				float boxRestitution = 0;

				//
				int printFric = frictionCount * 100;
				printf("%d\n", printFric);
				//

				if (frictionCount < 1)
					frictionCount += 0.1f;

				bool boxIsDynamic = true;
				b2Body* box = createBox(*boxPos, *boxDim, *boxLVel, boxGravity, boxDensity, boxFriction, boxRestitution, boxIsDynamic);
			}
			break;

		case GLFW_KEY_H:
			if (key == GLFW_KEY_H) {
				for (size_t i = 1; i < 7; i++)
				{
					b2Vec2* boxPos = new b2Vec2(10, (i*4)-20);
					b2Vec2* boxDim = new b2Vec2(2.0f, 2.0f);
					b2Vec2* boxLVel = new b2Vec2(0, 0);
					float boxGravity = 1;
					float boxDensity = 1;
					float boxFriction = 1;
					float boxRestitution = 0;
					bool boxIsDynamic = true;
					b2Body* box = createBox(*boxPos, *boxDim, *boxLVel, boxGravity, boxDensity, boxFriction, boxRestitution, boxIsDynamic);

					b2Vec2* circlePos = new b2Vec2(-10, (i * 4));
					float circleRadius = 2.0f;
					b2Vec2* circleLVel = new b2Vec2(0,0);
					float circleGravity = 1;
					float circleDensity = 1;
					float circleFriction = 1;
					float circleRestitution = 0;
					bool circleIsDynamic = true;

					b2Body* circle = createCircle(*circlePos, circleRadius, *circleLVel, circleGravity, circleDensity, circleFriction, circleRestitution, circleIsDynamic);
				}
			}
			break;

		case GLFW_KEY_J:
			if (key == GLFW_KEY_J) {
				for (int i = 1; i < 11; i++)
				{
					for (int j = 1; j < 11; j++)
					{
						b2Vec2* boxPos = new b2Vec2((i * 2), (j * 2)-50);
						b2Vec2* boxDim = new b2Vec2(1.0f, 1.0f);
						b2Vec2* boxLVel = new b2Vec2(0, 0);
						float boxGravity = 1;
						float boxDensity = 1;
						float boxFriction = 1;
						float boxRestitution = 0;
						bool boxIsDynamic = false;
						b2Body* box = createBox(*boxPos, *boxDim, *boxLVel, boxGravity, boxDensity, boxFriction, boxRestitution, boxIsDynamic);

					}
					
					
				}
			}
			break;

		case GLFW_KEY_K:
			if (key == GLFW_KEY_K) {
				
				float x = 0;
				float y = 0;
				float scale = 1;

				b2Body* diamond = createDiamond(x, y, scale);

			}
			break;


		
		}




	}

};

//Aqui fazemos o registro do novo teste 
static int testIndex = RegisterTest("Examples", "MyTest", MyTest::Create);