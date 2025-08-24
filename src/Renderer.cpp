#include <Renderer.h>
#include <Camera.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <ObjLoader.h>
#include <MenuUI.h>

Renderer::Renderer() {
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

void Renderer::draw(float angle, const Camera& camera, const glm::vec3& sphereColor ) {
	
	glClearColor(0.02f, 0.4f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	camera.applyView();

	//glRotatef(angle, 0.0f, 1.0f, 0.0f);

	// Set material color to the current sphereColor
	GLfloat mat_diffuse[] = { sphereColor.r, sphereColor.g, sphereColor.b, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);	

	ObjLoader obj;



	// --- Draw checkerboard floor ---
	glPushMatrix();
	glDisable(GL_LIGHTING); // Optional: flat colors look better for checkerboard

	const int size = 100;      // 20x20 tiles
	const float tileSize = 1.0f;
	const float floorY = -3.0f;

	for (int x = -size / 2; x < size / 2; ++x) {
		for (int z = -size / 2; z < size / 2; ++z) {
			// Alternate colors
			bool isWhite = (x + z) % 2 == 0;
			glColor3f(isWhite ? 1.0f : 0.0f, isWhite ? 1.0f : 0.0f, isWhite ? 1.0f : 0.0f);

			// Draw quad
			glBegin(GL_QUADS);
			glVertex3f(x * tileSize, floorY, z * tileSize);
			glVertex3f((x + 1) * tileSize, floorY, z * tileSize);
			glVertex3f((x + 1) * tileSize, floorY, (z + 1) * tileSize);
			glVertex3f(x * tileSize, floorY, (z + 1) * tileSize);
			glEnd();
		}
	}

	glEnable(GL_LIGHTING);
	glPopMatrix();



	gluSphere(quad, 1.0, 48, 48);
}

