
#include "../HeaderFiles/CylinderMeshGenerator.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif

// I'm CRYINGGGG. HOW DO I DRAW A SHAPE MATHEMATICALLYYYYYYY

GenerateCylinderFlatValues::GenerateCylinderFlatValues()
{
    float radius = 1.0f;
    float height = 2.0f;

    int heightSegments = 10;
    int radialSegments = 32;

    float heightStep = height / heightSegments;
    float thetaStep = (2.0f * M_PI) / radialSegments;


    for (int i = 0; i <= heightSegments; i++)
    {
        float y = -height / 2 + i * heightStep;

        for (int j = 0; j <= radialSegments; j++)
        {
            float theta = j * thetaStep;

            float x = radius * cosf(theta);
            float z = radius * sinf(theta);

            cylinderVertices.push_back(x);
            cylinderVertices.push_back(y);
            cylinderVertices.push_back(z);
        }
    }

    int ringVertexCount = radialSegments + 1;


    for (int i = 0; i < heightSegments; i++)
    {
        for (int j = 0; j < radialSegments; j++)
        {
            int current = i * ringVertexCount + j;
            int next = current + ringVertexCount;

            cylinderIndices.push_back(current);
            cylinderIndices.push_back(next);
            cylinderIndices.push_back(current + 1);

            cylinderIndices.push_back(current + 1);
            cylinderIndices.push_back(next);
            cylinderIndices.push_back(next + 1);
        }
    }


    int bottomCenterIndex = cylinderVertices.size() / 3;

    // center
    cylinderVertices.push_back(0.0f);
    cylinderVertices.push_back(-height / 2);
    cylinderVertices.push_back(0.0f);

    // ring
    for (int j = 0; j < radialSegments; j++)
    {
        float theta = j * thetaStep;

        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        cylinderVertices.push_back(x);
        cylinderVertices.push_back(-height / 2);
        cylinderVertices.push_back(z);
    }

    int start = bottomCenterIndex + 1;

    for (int j = 0; j < radialSegments; j++)
    {
        int current = start + j;
        int next = start + (j + 1) % radialSegments;

        cylinderIndices.push_back(bottomCenterIndex);
        cylinderIndices.push_back(current);
        cylinderIndices.push_back(next);
    }

    int topCenterIndex = cylinderVertices.size() / 3;

    // center
    cylinderVertices.push_back(0.0f);
    cylinderVertices.push_back(height / 2);
    cylinderVertices.push_back(0.0f);

    // ring
    for (int j = 0; j < radialSegments; j++)
    {
        float theta = j * thetaStep;

        float x = radius * cosf(theta);
        float z = radius * sinf(theta);

        cylinderVertices.push_back(x);
        cylinderVertices.push_back(height / 2);
        cylinderVertices.push_back(z);
    }

    start = topCenterIndex + 1;

    for (int j = 0; j < radialSegments; j++)
    {
        int current = start + j;
        int next = start + (j + 1) % radialSegments;

        cylinderIndices.push_back(topCenterIndex);
        cylinderIndices.push_back(next);
        cylinderIndices.push_back(current);
    }
}

GenerateCylinderCurvedValues::GenerateCylinderCurvedValues()
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