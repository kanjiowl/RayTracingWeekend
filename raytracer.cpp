#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"

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

color ray_color(const Ray &r, const hittable& world, int depth){
    hit_record rec; 
    if (depth <= 0){
        return color(0, 1, 0); 
    }
    if (world.hit(r, 0, infinity ,rec)){  
        point3 target = rec.p + rec.normal + random_in_unit_sphere(); 
        return 0.5 * ray_color(Ray(rec.p, target - rec.p), world, depth-1); 
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
    const int samples_per_pixel = 100; 
    int max_depth = 50; 
    // world
    hittable_list world; 
    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0,-100.5,-1), 100));
    
    Camera camera; 

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for (int j = image_height-1; j >=0; --j){
        for (int  i = 0 ; i < image_width; ++i){
            color pixel_color(0,0,0);
            for (int s = 0 ; s < samples_per_pixel; s++){ 
                auto u = (i + random_double()) / (image_width -1);
                auto v = (j + random_double()) / (image_height - 1);

                // create a ray for each sample
                Ray r = camera.get_ray(u, v);
                pixel_color += ray_color(r, world, max_depth);
            }

            // color each pixel
            // color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
}

