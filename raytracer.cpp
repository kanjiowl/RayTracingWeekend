#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"

#include <iostream> 

using namespace std;

// double hit_sphere(const point3& center, double radius, const Ray& r){
//     vec3 oc = r.origin() - center;
//     auto a = dot(r.direction(), r.direction());
//     auto b = 2.0 * dot(oc, r.direction());
//     auto c = dot(oc, oc) - radius * radius;
//     auto discriminant = b*b - 4*a*c;
//     if (discriminant < 0){
//         return -1.0; 
//     } else {
//         return (-b - sqrt(discriminant)) / (2.0 * a); 
//     }
// }

color ray_color(const Ray &r, const hittable& world){
    hit_record rec; 
    if (world.hit(r, 0, infinity ,rec)){ 
        return 0.5 * (rec.normal + color(1,1,1)); 
    }
    // auto t  = hit_sphere(point3(0,0, -1), 0.5, r); 
    // if (t > 0.0){
    //     vec3 N = unit_vector(r.at(t) - vec3(0, 0, -1)); 
    //     return 0.5* color(N.x()+1 , N.y() +1 , N.z() + 1);
    // }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}


int main(){
    // image size
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);


    // world
    hittable_list world; 
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));
    
    // clCamera
    // Camera convention : x = horizontal , y = vertical, z = going into the monitor
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0,0, 0); // centre of the world/ eye
    auto horizontal  = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical / 2 - vec3(0, 0, focal_length); // viewport is at z = -1

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >=0; --j){
        for (int  i = 0 ; i < image_width; ++i){
            auto u = double(i) / (image_width -1);
            auto v = double(j) / (image_height - 1);

            // create a ray for a pixel
            Ray r(origin , lower_left_corner + u*horizontal + v*vertical - origin);

            // color each pixel
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
        }
    }
}

