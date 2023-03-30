#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// #include "load_model.cpp"
// namespace scratch
// {

//     glm::mat4 transform(int transformLoc, auto model, float xPos, float yPos)
//     {
//         glm::mat4 transform = glm::mat4(1.0f);
//         transform = glm::translate(transform, glm::vec3(xPos + model.xTranslate,yPos + model.yTranslate,0.0f));   //position = 0,0,0
        
//         transform = glm::rotate(transform, glm::radians(model.xRotate),glm::vec3(1,0,0));   //rotation x = 0.0 degrees
//         transform = glm::rotate(transform, glm::radians(model.yRotate),glm::vec3(0,1,0));   //rotation y = 0.0 degrees
//         transform = glm::rotate(transform, glm::radians(model.zRotate),glm::vec3(0,0,1));   //rotation z = 0.0 degrees
        
//         transform = glm::scale(transform, glm::vec3(model.xScale,model.yScale,model.zScale));   //scale = 1,1,1

//         return transform;
//     }

// }