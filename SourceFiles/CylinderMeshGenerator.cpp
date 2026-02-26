
#include "../HeaderFiles/CylinderMeshGenerator.h"

GenerateCylinderValues::GenerateCylinderValues()
{
	cylinderVertices = {
        // Base (rectangle) - Positioned at Y = 1.5
        // X      Y      Z
        2.0f,  1.5f,  2.0f,   // 0: Back-Left
        5.0f,  1.5f,  2.0f,   // 1: Back-Right
        5.0f,  1.5f,  4.0f,   // 2: Front-Right
        2.0f,  1.5f,  4.0f,   // 3: Front-Left

        // Apex (Pointed top) - Positioned higher at Y = 5.0
        3.5f,  5.0f,  3.0f    // 4: Top Center
	};

	cylinderIndices = {
        // Base
        0, 1, 2,
        0, 2, 3,

        // Sides
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
	};
}