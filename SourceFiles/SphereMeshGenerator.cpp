#include "../HeaderFiles/SphereMeshGenerator.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846f
#endif


GenerateSphereValues::GenerateSphereValues()
{
    float radius = 1.0f;
    int latitudeCount = 64;
    int longitudeCount = 128;

    float latitudeStep = (M_PI) / latitudeCount;
    float longitudeStep = (2 *M_PI) / longitudeCount;

    for (int i = 0; i <= latitudeCount; i++)
    {
        /*float latitudeAnglePhi = M_PI / 2 - i * latitudeStep;

        float z = radius * cos(latitudeAnglePhi);*/
        float phi = i * latitudeStep;

        float z = radius * cosf(phi);
        
        for (int j = 0; j <= longitudeCount; j++)
        {
            /*float longitudeAngleTheta = j * longitudeStep;
            float x = radius * sin(latitudeAnglePhi) * cos(longitudeAngleTheta);
            float y = radius * sin(latitudeAnglePhi) * sin(longitudeAngleTheta);*/

            
            float theta = j * longitudeStep;

            float x = radius * sinf(phi) * cosf(theta);
            float y = radius * sinf(phi) * sinf(theta);
            
            
            sphereVertices.push_back(x);
            sphereVertices.push_back(y);
            sphereVertices.push_back(z);
        }
    }

    for (int i = 0; i < latitudeCount; ++i) {
        int k1 = i * (longitudeCount + 1);
        int k2 = k1 + longitudeCount + 1;

        for (int j = 0; j < longitudeCount; ++j, ++k1, ++k2) {
            if (i != 0) {
                sphereIndices.push_back(k1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k1 + 1);
            }
            if (i != (latitudeCount - 1)) {
                sphereIndices.push_back(k1 + 1);
                sphereIndices.push_back(k2);
                sphereIndices.push_back(k2 + 1);
            }
        }
    }

}