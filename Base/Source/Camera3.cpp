#include "Camera3.h"
#include "Mtx44.h"

static const float CAMERA_SPEED = 200.f;

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	// Initialise the camera movement flags
	for (int i = 0; i < 255; i++)
		myKeys[i] = false;
}

void Camera3::Update(double dt)
{
	int k = 'a';
	if(myKeys['w'])
	{
		MoveForward(dt);
		myKeys['w'] = false;
	}
	if(myKeys['a'])
	{
		MoveLeft(dt);
		myKeys['a'] = false;
	}
	if(myKeys['s'])
	{
		MoveBackward(dt);
		myKeys['s'] = false;
	}
	if(myKeys['d'])
	{
		MoveRight(dt);
		myKeys['d'] = false;
	}

}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

// Update Camera status
void Camera3::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
}

void Camera3::MoveForward(const double dt)
{
	Vector3 view = (target - position);
	view.y = 0;
	view.Normalize();
	position += view * CAMERA_SPEED * (float)dt;
	target += view * CAMERA_SPEED * (float)dt;
}

void Camera3::MoveBackward(const double dt)
{
	Vector3 view = (target - position);
	view.y = 0;
	view.Normalize();
	position -= view * CAMERA_SPEED * (float)dt;
	target -= view * CAMERA_SPEED * (float)dt;
}

void Camera3::MoveLeft(const double dt)
{
	Vector3 view = (target - position);
	view.y = 0;
	view.Normalize();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * CAMERA_SPEED * (float)dt;
	target -= right * CAMERA_SPEED * (float)dt;
}

void Camera3::MoveRight(const double dt)
{
	Vector3 view = (target - position);
	view.y = 0;
	view.Normalize();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * CAMERA_SPEED * (float)dt;
	target += right * CAMERA_SPEED * (float)dt;
}