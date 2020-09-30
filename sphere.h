#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public hittable{
    public:
        Sphere() {}; 
        Sphere(point3 cen, double r, shared_ptr<material> m): center(cen), radius(r) , mat_ptr(m) {}; 
        virtual bool hit(
        const Ray& r, double tmin, double tmax, hit_record& rec) const override;

    public:
        point3 center; 
        double radius; 
        shared_ptr<material> mat_ptr;
}; 

// Check if there was a hit
bool Sphere::hit(const Ray& r, double tmin, double tmax, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius * radius;
    auto discriminant = b*b - a*c;
    
    if (discriminant > 0){ 
        auto root = sqrt(discriminant); 
        
        auto temp = (-b - root) / a; // checking the first root (closest to the origin)

        if (temp < tmax && temp > tmin){
            rec.t = temp; 
            rec.p = r.at(rec.t);
            vec3 outward_normal = (rec.p - center) / radius ; // normalized unit vector 
            rec.set_face_normal(r, outward_normal); 
            rec.mat_ptr = mat_ptr;
            return  true; 
        }   

        temp  = (-b + root) / a; 
        if (temp  < tmax && temp > tmin){ 
            rec.t = temp;    
            rec.p = r.at(rec.t); 
            vec3 outward_normal= (rec.p - center) / radius; 
            rec.set_face_normal(r, outward_normal); 
            rec.mat_ptr = mat_ptr;
            return true; 
        }
    }
    return false; 
}
#endif