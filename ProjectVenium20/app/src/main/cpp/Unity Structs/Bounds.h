#pragma once

#include "Vector3.hpp"

struct Bounds {
    union {
        struct {
            Vector3 center;
            Vector3 size;
        }; float data[6];
    };

    Bounds() : center(Vector3()), size(Vector3()) {}

    Bounds(const Vector3& center, const Vector3& size) : center(center), size(size) {}

    float Height() const {
        return size.Y;
    }
};