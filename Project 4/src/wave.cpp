#include "wave.h"
#include <cmath>
#include <random>

// Perlin noise helper functions
float lerp(float a, float b, float t)
{
    return a + t * (b - a);
}

float fade(float t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

float grad(int hash, float x, float y)
{
    int h = hash & 15;  // Only the last 4 bits
    float u = h < 8 ? x : y; // Randomly choose x or y
    float v = h < 4 ? y : (h == 12 || h == 14 ? x : 0.0f);
    return (h & 1 ? -u : u) + (h & 2 ? -v : v);
}

// 2D Perlin noise function
float perlin(float x, float y, const std::vector<int>& permutation)
{
    int X = static_cast<int>(floor(x)) & 255;
    int Y = static_cast<int>(floor(y)) & 255;

    // Relative coordinates in the grid
    float xf = x - floor(x);
    float yf = y - floor(y);

    // Fade curves for x and y
    float u = fade(xf);
    float v = fade(yf);

    // Hash values for the four corners of the grid square
    int aa = permutation[permutation[X] + Y];
    int ab = permutation[permutation[X] + Y + 1];
    int ba = permutation[permutation[X + 1] + Y];
    int bb = permutation[permutation[X + 1] + Y + 1];

    // Dot products with gradient vectors
    float gradAA = grad(aa, xf, yf);
    float gradAB = grad(ab, xf, yf - 1.0f);
    float gradBA = grad(ba, xf - 1.0f, yf);
    float gradBB = grad(bb, xf - 1.0f, yf - 1.0f);

    // Interpolation between the four corners
    float x1 = lerp(gradAA, gradBA, u);
    float x2 = lerp(gradAB, gradBB, u);
    return lerp(x1, x2, v);
}


Wave::Wave(int width, int height) : m_width(width), m_height(height)
{
    // Pre-generate the Perlin noise permutation table
    m_permutation = {151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203, 117, 35, 11, 30, 130, 213, 89, 127, 224, 12, 28, 16, 107, 91, 147, 75, 39, 249, 88, 217, 227, 101, 7, 206, 204, 70, 71, 8, 84, 242, 45, 115, 144, 58, 16, 14, 136, 18, 42, 125, 191, 66, 158, 42, 72, 112, 144, 162, 233, 45, 92, 106, 23, 175, 238, 161, 77, 183, 209, 241, 19, 93, 80, 35, 120, 98, 169, 53, 127, 57, 45, 16, 40, 12, 91, 168, 116, 50, 13, 54, 255, 68, 56, 240, 105, 17, 75, 135, 160, 129, 148};
    m_permutation.insert(m_permutation.end(), m_permutation.begin(), m_permutation.end()); 
}

void Wave::render(SDL_Renderer *renderer)
{
    // Wave parameters
    float frequency = 0.05f;  
    float amplitude = 50.0f;  
    float speed = 0.2f;      
    static float time = 0.0f; 
    time += speed;            


    for (int i = 0; i < m_width; i++)
    {

        float x = i * frequency + time;

   
        float yNoise = 0.0f;
        float layerAmplitude = amplitude;
        float layerFrequency = frequency;

   
        for (int j = 0; j < 3; j++) 
        {
            yNoise += perlin(x * layerFrequency, time * 0.1f, m_permutation) * layerAmplitude;
            layerAmplitude *= 0.5f;   
            layerFrequency *= 2.0f;   
        }


        float y = m_height / 3.5 + yNoise;

        // Draw the line at the generated y value
        SDL_RenderDrawLine(renderer, i, m_height - y, i, m_height);
    }
}
