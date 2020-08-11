#include <engine/camera.hpp>

Camera::Camera (glm::vec3 Pos, glm::vec3 Up, float Yaw, float Pitch) {
  pos        = Pos;
  world_up   = Up;
  yaw        = Yaw;
  pitch      = Pitch;
  front      = glm::vec3(0.0f,0.0f,-1.0f);
  move_speed = SPEED;
  mouse_sens = SENSITIVITY;
  fov       = FOV;
  update_camera_vectors();
}

glm::mat4
Camera::GetViewMatrix (){
  return glm::lookAt(pos, pos + front, up);
}

void
Camera::ProcessKeyboard (Camera_Movement direction, float delta_time) {
  float velocity = move_speed * delta_time;
  switch (direction) {
    case FORWARD:
      pos += front * velocity;
      break;
    case BACKWARD:
      pos -= front * velocity;
      break;
    case LEFT:
      pos -= right * velocity;
      break;
    case RIGHT:
      pos += right * velocity;
      break;
  }
}

void
Camera::ProcessMouse (float xoffset, float yoffset, bool constrain_pitch) {
  xoffset *= mouse_sens;
  yoffset *= mouse_sens;

  yaw   += xoffset;
  pitch += yoffset;

  // make sure that when pitch is OOB, screen doesnt get flipped
  if (constrain_pitch) {
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
  }

  // update front, right, and up vectors using the updated Euler angles
  update_camera_vectors();
}

void
Camera::ProcessScroll (float yoffset) {
  fov -= (float)yoffset;
  if (fov < 1.0f) fov = 1.0f;
  if (fov > 45.0f) fov = 45.0f;
}

void
Camera::update_camera_vectors() {
  glm::vec3 Front;
  Front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  Front.y = sin(glm::radians(pitch));
  Front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
  front = glm::normalize(Front);

  right = glm::normalize(glm::cross(front, world_up));
  up    = glm::normalize(glm::cross(right, front));
}
