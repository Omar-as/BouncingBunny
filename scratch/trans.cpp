#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace scratch
{

    void transform(int transformLoc, int modelIndex)
    {
        // Bunny:
        if (modelIndex == 0)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform,glm::vec3(-0.839f,0.7f,0.0f)); //position = 0,0,0
            transform = glm::rotate(transform,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(180.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(270.0f),glm::vec3(0,0,1));//rotation z = 0.0 degrees
            transform = glm::scale(transform,glm::vec3(0.3f,0.3f,0.3f));//scale = 1,1,1
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        }
        // Cube:
        else if (modelIndex == 1)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform,glm::vec3(-0.89f,0.89f,0.0f)); //position = 0,0,0
            transform = glm::rotate(transform,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(180.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(270.0f),glm::vec3(0,0,1));//rotation z = 0.0 degrees
            transform = glm::scale(transform,glm::vec3(0.1f,0.1f,0.1f));//scale = 1,1,1
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        }
        // Sphere:
        else if (modelIndex == 2)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform,glm::vec3(-0.89f,0.89f,0.0f)); //position = 0,0,0
            transform = glm::rotate(transform,glm::radians(90.0f),glm::vec3(1,0,0));//rotation x = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(180.0f),glm::vec3(0,1,0));//rotation y = 0.0 degrees
            transform = glm::rotate(transform,glm::radians(270.0f),glm::vec3(0,0,1));//rotation z = 0.0 degrees
            transform = glm::scale(transform,glm::vec3(0.1f,0.1f,0.1f));//scale = 1,1,1
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
        }

    }

}