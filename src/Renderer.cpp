#include "RenderObject.h"
#include "glad/glad.h"
#include "imgui.h"
#include <Renderer.h>
#include <Camera.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include <../Deprecated/ObjLoader.h>
#include <MenuUI.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer()
	: modelShader(
			"Assets/Shaders/basic.vert",
			"Assets/Shaders/basic.frag") {



		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		GLfloat light_pos[] = { 0.0f, 0.0f, 2.0f, 1.0f };
		GLfloat light_color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0, 800.0 / 600.0, 0.1, 100.0);
		glMatrixMode(GL_MODELVIEW);

		quad = gluNewQuadric();
		gluQuadricNormals(quad, GLU_SMOOTH);
	}

Renderer::~Renderer() {
	gluDeleteQuadric(quad);
}

void Renderer::drawObject(const RenderObject& object, const Camera& camera) {
	if (!object.model)
		return;

	modelShader.use();

	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, object.position);

	model = glm::rotate(
			model,
			glm::radians(object.rotation.x),
			glm::vec3(1.0f, 0.0f, 0.0f)
			);

	model = glm::rotate(
			model,
			glm::radians(object.rotation.y),
			glm::vec3(0.0f, 1.0f, 0.0f)
			);

	model = glm::rotate(
			model,
			glm::radians(object.rotation.z),
			glm::vec3(0.0f, 0.0f, 1.0f)
			);

	model = glm::scale(model, object.scale);

	glm::vec3 cameraPosition(
			camera.camX,
			camera.camY,
			camera.camZ
			);

	glm::vec3 cameraDirection(
			camera.getDirX(),
			camera.getDirY(),
			camera.getDirZ()
			);

	glm::mat4 view = glm::lookAt(
			cameraPosition,
			cameraPosition + cameraDirection,
			glm::vec3(0.0f, 1.0f, 0.0f)
			);

	glm::mat4 projection = glm::perspective(
			glm::radians(60.0f),
			1920.0f / 1080.0f,
			0.1f,
			100.0f
			);

	modelShader.setMat4("model", model);
	modelShader.setMat4("view", view);
	modelShader.setMat4("projection", projection);

	object.model->Draw(modelShader);
	glUseProgram(0);

}

void Renderer::draw(
		float angle,
		const Camera& camera,
		const glm::vec3& sphereColor)
{
	(void)angle;

	// Legacy fixed-function rendering should not use the model shader.
	glUseProgram(0);

	glClearColor(0.02f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	camera.applyView();

	GLfloat matDiffuse[] = {
		sphereColor.r,
		sphereColor.g,
		sphereColor.b,
		1.0f
	};

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

	// Checkerboard floor
	glPushMatrix();

	glDisable(GL_LIGHTING);

	const int size = 100;
	const float tileSize = 1.0f;
	const float floorY = -3.0f;

/*	for (int x = -size / 2; x < size / 2; ++x)
	{
		for (int z = -size / 2; z < size / 2; ++z)
		{
			bool isWhite = ((x + z) % 2 == 0);

			glColor3f(
					isWhite ? 0.65f : 0.0f,
					isWhite ? 1.0f : 0.0f,
					isWhite ? 1.0f : 0.0f
				 );

			glBegin(GL_QUADS);

			glVertex3f(
					x * tileSize,
					floorY,
					z * tileSize
				  );

			glVertex3f(
					(x + 1) * tileSize,
					floorY,
					z * tileSize
				  );

			glVertex3f(
					(x + 1) * tileSize,
					floorY,
					(z + 1) * tileSize
				  );

			glVertex3f(
					x * tileSize,
					floorY,
					(z + 1) * tileSize
				  );

			glEnd();
		}
	}*/

	glEnable(GL_LIGHTING);

	glPopMatrix();

	// First sphere
	glPushMatrix();

	gluSphere(quad, 1.0, 48, 48);

	glPopMatrix();

	// Second sphere
	glPushMatrix();

	glTranslatef(i / 100.0f, 0.0f, 0.0f);

	gluSphere(quad, 1.0f, 48, 48);

	glPopMatrix();

	glFlush();
}


void Renderer::updateMovement(){

	this->i += 1;
	this->playerY += .1;
}
