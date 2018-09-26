#include"../../include/camera/camera.h"
#include"../../include/root.h"
namespace myrender
{
	Camera::Camera()
	{
	}
	Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		this->Position = position;
		this->WorldUp = up;
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	Camera::Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch):Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVTY), Zoom(ZOOM)
	{
		this->Position = glm::vec3(posX, posY, posZ);
		this->WorldUp = glm::vec3(upX, upY, upZ);
		this->Yaw = yaw;
		this->Pitch = pitch;
		this->updateCameraVectors();
	}
	Camera::~Camera()
	{
	}
	glm::mat4 Camera::GetViewMatrix()
	{
		return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
   }
	void Camera::ProcessKeyboard(GLfloat key)
	{
		auto camera = Root::getInstance()->getRender()->GetCamera();
		GLfloat deltaTime = Root::getInstance()->getViewPort()->GetDeltaTime();
		GLfloat velocity = camera->MovementSpeed * deltaTime;
		if (key == KeyBoardCode::KEY_W)
			camera->Position += camera->Front * velocity;
		if (key == KeyBoardCode::KEY_S)
			camera->Position -= camera->Front * velocity;
		if (key == KeyBoardCode::KEY_A)
			camera->Position -= camera->Right * velocity;
		if (key == KeyBoardCode::KEY_D)
			camera->Position += camera->Right * velocity;
	}

	void Camera::ProcessMousemove(MouseMoveEvent e)
	{
		auto camera = Root::getInstance()->getRender()->GetCamera();
		camera->_processMouseMovement(e.GetXOffset(), e.GetYOffset(),true);
	}

	void Camera::ProcessMousescroll(MouseScrollEvent e)
	{
		auto camera = Root::getInstance()->getRender()->GetCamera();
		camera->_processMouseScroll(e.GetZoom());
	}

	void Camera::_processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch=true)
	{
		xoffset *= this->MouseSensitivity;
		yoffset *= this->MouseSensitivity;

		this->Yaw += xoffset;
		this->Pitch += yoffset;

		// Make sure that when pitch is out of bounds, screen doesn't get flipped
		if (constrainPitch)
		{
			if (this->Pitch > 89.0f)
				this->Pitch = 89.0f;
			if (this->Pitch < -89.0f)
				this->Pitch = -89.0f;
		}

		// Update Front, Right and Up Vectors using the updated Eular angles
		this->updateCameraVectors();
	}
	void Camera::_processMouseScroll(GLfloat yoffset)
	{
		if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
			this->Zoom -= yoffset/10;
		if (this->Zoom <= 1.0f)
			this->Zoom = 1.0f;
		if (this->Zoom >= 45.0f)
			this->Zoom = 45.0f;
	}

	void Camera::RegisterKeyboardCallback()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->RegistKeyboardCallback(Camera::ProcessKeyboard);
	}
	void Camera::RegisterMousemoveCallback()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->RegistMouseMoveCallback(Camera::ProcessMousemove);
	}
	void Camera::RegisterMousescrollCallback()
	{
		auto viewport = Root::getInstance()->getViewPort();
		viewport->RegistMouseScroolCallback(Camera::ProcessMousescroll);
	}
	void Camera::updateCameraVectors()
	{
		// Calculate the new Front vector
		glm::vec3 front;
		front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		front.y = sin(glm::radians(this->Pitch));
		front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
		this->Front = glm::normalize(front);
		// Also re-calculate the Right and Up vector
		this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		this->Up = glm::normalize(glm::cross(this->Right, this->Front));
	}
}