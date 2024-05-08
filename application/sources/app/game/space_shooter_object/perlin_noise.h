#include <stdio.h>
#include <cmath>

/**
 * @brief Evaluate fade function at t
 *
 * The fade function is a cubic function that maps the input value t to a value in [0,1] range.
 * The function is defined as:
 *      t^4 * (6*t^3 - 15*t^2 + 10*t) + 10
 *
 * @param t The input value in [0,1] range
 * @return The evaluated fade function value in [0,1] range
 */
float fadeFunction(float t)
{
    /*
     * The function is a cubic polynomial in t.
     * The coefficients are:
     *   a0 = 10
     *   a1 = 0
     *   a2 = -15
     *   a3 = 6
     */
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

/**
 * @brief Evaluate gradient function at (x, y, z) given hash value
 *
 * The gradient function is a simplex noise function that maps a 3D point to a random
 * unit vector. The function is defined as:
 *      (x, y, z) -> (u, v, w) where u, v, w are chosen based on the least significant
 *      2 bits of the hash value (0 <= x, y, z < 16). The specific case is determined
 *      by the least significant 2 bits of the hash value h.
 *
 *      If h is even, u = x, v = y, w = z
 *      If h is odd, u = -x, v = -y, w = -z
 *
 *      If the least significant bit of h is 0, the corresponding coordinate is
 *      unchanged
 *      If the least significant bit of h is 1, the corresponding coordinate is
 *      negated
 *
 * @param hash The hash value to use to determine the gradient
 * @param x The x coordinate of the point
 * @param y The y coordinate of the point
 * @param z The z coordinate of the point
 * @return The random unit vector corresponding to the point (x, y, z)
 */
float gradientFunction(int hash, float x, float y, float z)
{
    // The least significant 4 bits of the hash value determine the case
    int h = hash & 15;

    // u is chosen based on the least significant bit of h
    float u = h & 1 ? -x : x;

    // v is chosen based on the 2nd least significant bit of h
    float v = h & 2 ? -y : y;

    // w is chosen based on the 3rd least significant bit of h
    float w = h & 4 ? -z : z;

    // Return the random unit vector (u, v, w) determined by h
    return u + v + w;
}

/**
 * @brief Compute 1D Perlin noise
 *
 * @param xi The x coordinate of the point to evaluate
 * @return The noise value at the given point
 */
float perlinNoise1D(float xi)
{
    // Find the unit square that contains the point
    int i0 = std::floor(xi); // Integer part of x
    int i1 = i0 + 1; // Integer part of x + 1
    float tx = xi - i0; // Fractional part of x

    // Interpolate the noise value at the four corners of the unit square
    float a = tx*tx; // a = (x - i0)^2
    float b = a*tx; // b = (x - i0)^3
    float v0 = fadeFunction(tx); // v0 = smoothstep(0, 1, x - i0)
    float v1 = fadeFunction(tx - 1); // v1 = smoothstep(0, 1, x - i0 - 1)
    float g0 = gradientFunction(i0, (float)i0, (float)i0, (float)i0); // g0 = random vector at i0
    float g1 = gradientFunction(i1, (float)i1, (float)i1, (float)i1); // g1 = random vector at i1
    return v0 * (a - b) * g0 + v1 * (b - a) * g1; // Interpolate the noise value
}
