#pragma once

#include <iostream>

struct Vector4 {
    union {
        struct {
            float x, y, z, w;
        }; float data[4];
    };

    Vector4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    Vector3 ToVector3() const {
        return Vector3(x, y, z);
    }

    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    Vector4 operator/(float scalar) const {
        if (scalar != 0) {
            float reciprocalScalar = 1.0f / scalar;
            return Vector4(x * reciprocalScalar, y * reciprocalScalar, z * reciprocalScalar, w * reciprocalScalar);
        } else return *this;  // Return original vector to avoid undefined behavior
    }

    Vector4& operator/=(float scalar) {
        if (scalar != 0) {
            float reciprocalScalar = 1.0f / scalar;
            x *= reciprocalScalar;
            y *= reciprocalScalar;
            z *= reciprocalScalar;
            w *= reciprocalScalar;
        } return *this;
    }
};