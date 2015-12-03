#pragma once

class glHandler
{
public:
	GLvoid Set2DTexture(GLuint texture, double x, double y);
	GLvoid SetFontInit(GLuint texture_font);
	GLvoid PrintQUADS(int width, int height);
	GLvoid Print2DTextureQUADS(int width, int height);
	GLvoid PrintPeople(people person);
};

GLvoid glHandler::Set2DTexture(GLuint texture, double x, double y){
	glTranslatef(x * LENGTH + START_X * 1.0f, y * LENGTH + START_Y * 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, texture);
}

GLvoid glHandler::SetFontInit(GLuint texture_font)
{
	glLoadIdentity(); 
	glEnable(GL_BLEND); 
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture(GL_TEXTURE_2D, texture_font);
	glColor3f(1.0f, 1.0f, 1.0f);
}

GLvoid glHandler::PrintQUADS(int width, int height) {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2d(-LENGTH * width / 2, -LENGTH * height / 2);
	glVertex2d( LENGTH * width / 2, -LENGTH * height / 2);
	glVertex2d( LENGTH * width / 2,  LENGTH * height / 2);
	glVertex2d(-LENGTH * width / 2,  LENGTH * height / 2);
	glEnd();
}

GLvoid glHandler::Print2DTextureQUADS(int width, int height) {
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(-LENGTH * width / 2, -LENGTH * height / 2);
	glTexCoord2f(1.0f, 1.0f); glVertex2d( LENGTH * width / 2, -LENGTH * height / 2);
	glTexCoord2f(1.0f, 0.0f); glVertex2d( LENGTH * width / 2,  LENGTH * height / 2);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(-LENGTH * width / 2,  LENGTH * height / 2);
	glEnd();
}

GLvoid glHandler::PrintPeople(people person)
{
	glLoadIdentity();
	glTranslatef(person.fx + START_X * 1.0f, person.fy - 0.25 * LENGTH + START_Y * 1.0f, 0.0f);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glBindTexture(GL_TEXTURE_2D, texture_char[person.texture_number + person.direct]);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.99f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.99f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.50f); glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.50f); glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
	glEnd();
	glBlendFunc(GL_ONE, GL_ONE);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.49f); glVertex2d(-LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.49f); glVertex2d(LENGTH / 2.0, -LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 1) / 4.0f, 0.0f);	glVertex2d(LENGTH / 2.0, LENGTH / 2.0);
	glTexCoord2f((person.animation + 2 * person.IsLeft + 0) / 4.0f, 0.0f);	glVertex2d(-LENGTH / 2.0, LENGTH / 2.0);
	glEnd();
}