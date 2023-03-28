#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

namespace scratch{
    using namespace std;

    struct Model {

        // creating vector for vertices and indices
        vector<GLfloat> vertices;
        vector<GLint> indices;

        // Cheking the number of lines for both vertices and indices
        GLint no_lines_vertices;
        GLint no_lines_indices;

        // Calulating the number of vertices and indices we are given 
        GLint vertices_number;
        GLint indices_number;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

    Model model_loader(const char* filename){
        
        // Open the file to be read from
        ifstream infile;
        infile.open(filename);

        // Creating a model and adding the number of lines of vertices and indices we have
        Model model;
        infile >> model.no_lines_vertices;
        infile >> model.no_lines_indices;

        model.vertices_number = 3 * model.no_lines_vertices;
        model.indices_number = 3 * model.no_lines_indices;

        // Adds the vertex to the vertices vector
        GLfloat vertex;
        for (GLint i = 0; i < model.vertices_number; i++){
            infile >> vertex;
            model.vertices.push_back(vertex);
        }

        // Adds the index to the indices vector
        GLint index;
        for (GLint i = 0; i < model.indices_number; i++){
            infile >> index;
            model.indices.push_back(index);
        }

        // Finding the maximum
        GLfloat max = *max_element(model.vertices.begin(), model.vertices.end());

        for (auto i = 0; i < model.vertices.size(); i++){
            model.vertices[i] /= max;
        }

        return model;

    }

}