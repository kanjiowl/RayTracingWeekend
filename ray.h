#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray {
    public:
        Ray() {}
        Ray(const point3& origin, const vec3& direction) : orig(origin) , dir(direction) {}
        point3 origin() const {return orig;}
        vec3 direction() const {return dir;}

        // returns the 3d coordinate of a point on the ray
        point3 at(double t) const {
            return orig + t * dir;
        }

    public:
        point3 orig;
        vec3 dir;
};
#endif
