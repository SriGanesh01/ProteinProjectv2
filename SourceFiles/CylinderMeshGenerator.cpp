
#include "../HeaderFiles/CylinderMeshGenerator.h"

GenerateCylinderFlatValues::GenerateCylinderFlatValues()
{
    cylinderVertices = {
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,

     0.0f, 1.0f, 0.0f
    };

    cylinderIndices = {
        // Base (facing downward)
        0,1,2,
        0,2,3,

        // Sides
        0,4,1,
        1,4,2,
        2,4,3,
        3,4,0
    };
}