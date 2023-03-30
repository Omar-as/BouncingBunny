#include <iostream>

namespace scratch
{
    using namespace std;

    // Returns the row of the colors array
    float* colors(int index)
    {

        // color array
        static float color_collection[][3] = 
        {
            {1.0000000000f, 0.7568627451f, 0.0274509804f}, // Yellow
            {0.2980392157f, 0.6862745098f, 0.3137254902f}, // Green
            {0.9568627451f, 0.2627450980f, 0.2117647059f}, // Red
        };

        // counter-like index
        index = index % (sizeof(color_collection)/sizeof(color_collection[0]));

        // returning the colors RGB with the index
        static float row[4];
        row[0] = color_collection[index][0];
        row[1] = color_collection[index][1];
        row[2] = color_collection[index][2];
        index++;
        row[3] = float(index);

        return row;
    }

    // Updates the color shown on screen
    void update_colors(int vertexColorLocation, float redVal, float greenVal, float blueVal) {
        glUniform4f(vertexColorLocation, redVal, greenVal, blueVal, 1.0f);
    }

}