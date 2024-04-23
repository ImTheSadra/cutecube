#include <vector>
#include <cmath>
#include <SDL2/SDL.h>

using namespace std;

class Point {
public:
    double x, y, z;

    Point() {
        this->x = 0;
        this->y = 0;
        this->z = 0;
    }

    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Point(double x, double y) {
        this->x = x;
        this->y = y;
        this->z = 0;
    }

    double operator[](int i) const {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        return this->z;
    }

    double& operator[](int i) {
        if (i == 0) return this->x;
        if (i == 1) return this->y;
        return this->z;
    }
};

typedef vector<double> Vector;
typedef vector<Vector> Matrix;

Matrix dot(const Matrix& a, const Matrix& b) {
    Matrix result = Matrix(a.size(), Vector(b[0].size(), 0));
    for (int i=0; i<a.size(); i++) {
        for (int j=0; j<b[0].size(); j++) {
            for (int k=0; k<b.size(); k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return result;
}

Point transform(const Matrix& matrix, const Point& point) {
    Matrix p = {{point.x}, {point.y}, {point.z}};
    Matrix r = dot(matrix, p);
    return Point(r[0][0], r[1][0], r[2][0]);
}

Point translate(const Point& shift, const Point& point) {
    return Point(
        point.x + shift.x,
        point.y + shift.y,
        point.z + shift.z
    );
}

Matrix getRotationMatrix(double ax,double ay,double az) {
    Matrix rotationX = {
        {1, 0, 0},
        {0, cos(ax), -sin(ax)},
        {0, sin(ax),  cos(ax)}
    };

    Matrix rotationY = {
        {cos(ay), 0, sin(ay)},
        {0, 1, 0},
        {-sin(ay), 0, cos(ay)}
    };

    Matrix rotationZ = {
        {cos(az), -sin(az), 0},
        {sin(az),  cos(az), 0},
        {0, 0, 1}
    };

    return dot(rotationZ, dot(rotationY, rotationX));
}