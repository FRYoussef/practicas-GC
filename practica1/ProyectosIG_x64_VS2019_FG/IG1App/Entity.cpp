#include "Entity.h"
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Abs_Entity::upload(dmat4 const& modelViewMat) const 
{ 
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(modelViewMat));  // transfers modelView matrix to the GPU
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

RGBAxis::RGBAxis(GLdouble l): Abs_Entity()
{
  mMesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

RGBAxis::~RGBAxis() 
{ 
	delete mMesh; mMesh = nullptr; 
};
//-------------------------------------------------------------------------

void RGBAxis::render(dmat4 const& modelViewMat) const 
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		mMesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------

CPolygon::CPolygon(GLuint numL, GLdouble rd) {
	this->numL = numL;
	this->rd = rd;
	mMesh = Mesh::generatePolygon(numL, rd);
}

void CPolygon::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glLineWidth(2);
		glColor3d(mColor.r, mColor.g, mColor.b);
		mMesh->render();

		//Resetear attrs
		glLineWidth(1);
		glColor3d(1, 1, 1);
	}
}

Sierpinski::Sierpinski(GLuint numP, GLdouble rd) {
	this->numP = numP;
	this->rd = rd;
	mMesh = Mesh::generateSierpinski(numP, rd);
}

void Sierpinski::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPointSize(2);
		glColor4dv(value_ptr(mColor));
		mMesh->render();

		//Resetear attrs
		glPointSize(1);
		glColor4d(1, 1, 1, 1);
	}
}

TriangleRGB::TriangleRGB(GLdouble rd): traslationAng(0.0), rotationAng(25.0) {
	this->rd = rd;
	mMesh = Mesh::generateTriangleRGB(rd);
}

void TriangleRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();

		//Resetear attrs
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void TriangleRGB::update() {
	// rotar sobre el eje 
	rotationAng += 2.5;
	traslationAng += 3.0;
	GLdouble p_X = 250.0 * cos(radians(traslationAng));
	GLdouble p_Y = 250.0 * sin(radians(traslationAng));

	mModelMat = glm::translate(dmat4(1), dvec3(p_X, p_Y, 0));
	mModelMat = glm::rotate(mModelMat, radians(rotationAng), dvec3(0, 0, 1));
}

RectangleRGB::RectangleRGB(GLdouble w, GLdouble h) {
	this->w = w;
	this->h = h;
	mMesh = Mesh::generateRGBRectangle(w, h);
}

void RectangleRGB::render(dmat4 const& modelViewMat) const
{
	if (mMesh != nullptr) {
		dmat4 aMat = modelViewMat * mModelMat;  // glm matrix multiplication
		upload(aMat);
		glPolygonMode(GL_BACK, GL_LINE);
		mMesh->render();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}