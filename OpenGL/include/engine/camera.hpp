#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  10.0f;
const float SENSITIVITY =  0.1f;
const float FOV         =  45.0f;


enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT
};

class Camera {
  public:
    float fov;

    Camera(
      glm::vec3 Pos   = glm::vec3(0.0f,0.0f,0.0f),
      glm::vec3 Up    = glm::vec3(0.0f,0.1f,0.0f),
      float     Yaw   = YAW,
      float     Pitch = PITCH
    );

    glm::mat4 GetViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float delta_time);
    void ProcessMouse(float xoffset, float yoffset, bool constrain_pitch=true);
    void ProcessScroll(float yoffset);

  private:
    // camera attributes
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // euler angles
    float yaw;
    float pitch;

    // camera options
    float move_speed;
    float mouse_sens;

    void update_camera_vectors();
};

#endif
