#pragma once

#include <iostream>
#include "Vector4.h"

struct Matrix4x4 {
    union {
        struct {
            float m[4][4];
        };
    };

    Matrix4x4() { for (int i = 0; i < 4; ++i) for (int j = 0; j < 4; ++j) m[i][j] = 0.0f; }

    Vector4 operator*(const Vector4& v) const {
        Vector4 result;
        for (int i = 0; i < 4; ++i) {
            result.x += m[0][i] * v.data[i];
            result.y += m[1][i] * v.data[i];
            result.z += m[2][i] * v.data[i];
            result.w += m[3][i] * v.data[i];
        } return result;
    }
};