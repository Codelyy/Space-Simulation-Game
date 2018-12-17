#include "Text.h"
#include <iostream>

Text::Text()
{

}

void Text::Render2D(Vector2 pos)
{
	SetOrthographicProjection(); //Changes the Projection type to render 2D text
	glDisable(GL_LIGHTING); //Disables the Lighting so the Text isn't affected

	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f); //Sets the Colour of the Text
	glRasterPos2f(pos.X, pos.Y); //Sets the Position of the 2D text
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str()); //Gets and Renders the Text

	glPopMatrix();

	glEnable(GL_LIGHTING); //Enables Lighting again
	RestorePerspectiveProjection(); //Restores the Projection to use for 3D
}

void Text::Render3D(Vector3 pos)
{
	glDisable(GL_LIGHTING); //Disables Lighting so the Text isn't affected by it
	glPushMatrix();

	glColor3f(1.0f, 1.0f, 1.0f);

	glTranslatef(pos.X, pos.Y, pos.Z); //Sets the Position of the Text within 3D space
	glScalef(scale.X, scale.Y, scale.Z); //Sets the Scale of the Text within 3D space

	glRasterPos2f(0.0f, 0.0f);

	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24, (unsigned char*)text.c_str()); //Gets and Renders the Text

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Text::SetText(std::string text)
{
	this->text = text;
}

void Text::SetScale(Vector3 scale)
{
	this->scale = scale;
}

void Text::SetOrthographicProjection()
{
	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void Text::RestorePerspectiveProjection()
{

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}
