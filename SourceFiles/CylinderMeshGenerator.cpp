
#include "../HeaderFiles/CylinderMeshGenerator.h"

GenerateCylinderValues::GenerateCylinderValues()
{
    cylinderVertices = {
    -1.0f,-1.0f,-1.0f,
     1.0f,-1.0f,-1.0f,
     1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,

     0.0f, 1.0f, 0.0f
    };

    cylinderIndices = {
        0,2,1,
        0,3,2,

        0,1,4,
        1,2,4,
        2,3,4,
        3,0,4
    };
}