#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace scratch
{
    using namespace std;

    struct Model 
    {
        // creating vector for vertices and indices
        vector<GLfloat> vertices;
        vector<GLint> indices;

        // Cheking the number of lines for both vertices and indices
        GLint no_lines_vertices;
        GLint no_lines_indices;

        // Calulating the number of vertices and indices we are given 
        GLint vertices_number;
        GLint indices_number;

        // Lowest Y point in the model
        GLfloat minYval;

        // Vertex array object/Vertex buffer object/Edge buffer object. for each model
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

    Model model_loader(const char* filename)
    {
        // Open the file to be read from
        ifstream infile;
        infile.open(filename);

        // Creating a model and adding the number of lines of vertices and indices we have
        Model model;
        infile >> model.no_lines_vertices;
        infile >> model.no_lines_indices;

        // Calculates the vertices and indices numbers
        model.vertices_number = 3 * model.no_lines_vertices;
        model.indices_number = 3 * model.no_lines_indices;

        // Adds the vertex to the vertices vector
        GLfloat vertex;
        for (GLint i = 0; i < model.vertices_number; i++)
        {
            infile >> vertex;
            model.vertices.push_back(vertex);
        }

        // Adds the index to the indices vector
        GLint index;
        for (GLint i = 0; i < model.indices_number; i++)
        {
            infile >> index;
            model.indices.push_back(index);
        }
        
        // Calculates the min Y vertex value
        auto min = model.vertices[1];
        for (size_t i = 1; i < model.vertices.size() - 2; i += 3){
            if (min > model.vertices[i]){
                min = model.vertices[i];
            }
        }
        model.minYval = min;

        return model;
    }

}