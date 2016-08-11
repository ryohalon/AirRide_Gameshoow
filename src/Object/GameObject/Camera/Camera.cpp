#include "Camera.h"
#include "../../../Share/Share.h"
#include "../../../Input/InputEvent.h"

using namespace ci;
using namespace ci::app;

ar::Camera::Camera()
{
}

void ar::Camera::setup()
{
	camera = CameraPersp(WIDTH, HEIGHT,
						 60.0f,
						 1.0f, 1000.0f);
	lookpoint = Vec3f(1, 1, 1);
}

void ar::Camera::update()
{
	moveUpdate();
	rotateUpdate();
	cameraDecision(transform.position,
				   lookpoint);


	gl::setMatrices(camera);
}

void ar::Camera::draw()
{
}

void ar::Camera::cameraDecision(const ci::Vec3f & position_, const ci::Vec3f & lookpoint_)
{
	gl::pushModelView();
	camera.setEyePoint(position_ + move_distance);
	camera.setCenterOfInterestPoint(lookpoint_ + move_distance);
	gl::popModelView();
}

void ar::Camera::moveUpdate(int invert_)
{
	Vec3f vec = Vec3f::zero();
	const float speed = 0.2f;

	inputVector(vec, speed);
	vec = vec * invert_;
	translate(vec);
}

void ar::Camera::translate(const Vec3f& vec_)
{
	transform.translate(vec_, transform.angle);
}

void ar::Camera::inputVector(Vec3f& vec_, float velocity_)
{
	inputFrontVector(vec_, velocity_);
	inputBackVector(vec_, velocity_);
	inputRightVector(vec_, velocity_);
	inputLeftVector(vec_, velocity_);
}

void ar::Camera::inputFrontVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_w))
		vec_.z += velocity_;
}

void ar::Camera::inputBackVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_s))
		vec_.z -= velocity_;
}

void ar::Camera::inputRightVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_d))
		vec_.x -= velocity_;
}

void ar::Camera::inputLeftVector(Vec3f& vec_, float velocity_)
{
	if (env.isPress(KeyEvent::KEY_a))
		vec_.x += velocity_;
}

float ar::Camera::verticalValue(float rotatespeed_)
{
	return rotatespeed_ * env.getAxis("Vertical_UD", 0.15f);
}

float ar::Camera::horizontalValue(float rotatespeed_)
{
	return rotatespeed_ * env.getAxis("Horizontal_LR", 0.15f);
}

void ar::Camera::rotateUpdate()
{
	pointOfView(1.0f);
	angleRotate();
}


void ar::Camera::pointOfView(float interval_)
{
	lookpoint = transform.rotateMatrix(transform.angle + angle_distance, interval_);
	lookpoint += transform.position;
}

void ar::Camera::angleRotate()
{
	verticalAngleRotate(rotate_speed);
	horizontalAngleRotate(rotate_speed);

	horizontalRotateLimit(horizontal_up_limit, horizontal_low_limit);
}

void ar::Camera::verticalAngleRotate(float rotatespeed_)
{
	transform.angle.y += horizontalValue(rotatespeed_);
	transform.angle.y = std::fmod(transform.angle.y, 2 * (float)M_PI);
}

void ar::Camera::horizontalAngleRotate(float rotatespeed_)
{
	transform.angle.x += verticalValue(rotatespeed_);
}


void ar::Camera::horizontalRotateLimit(float up_limit_, float low_limit_)
{
	transform.angle.x = std::min(low_limit_, std::max(up_limit_, transform.angle.x));
}