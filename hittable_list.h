#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory> 
#include <vector> 

using std::shared_ptr; 
using std::make_shared;

class hittable_list: public hittable { 
    public: 
    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() {objects.clear();}  
    void add(shared_ptr<hittable> object) {objects.push_back(object);};
    
    virtual bool hit(
            const Ray& r, double tmin, double tmax, hit_record& rec) const override; 

    public:
        std::vector<shared_ptr<hittable>> objects; 
}; 

bool hittable_list::hit(const Ray& r, double tmin, double tmax, hit_record& rec) const { 
    hit_record temp_rec; 
    bool hit_anything = false; 
    auto closest_so_far = tmax; 

    // Iterate through all the objects in the scene
    for (const auto& object : objects){ 
        if (object->hit(r, tmin, closest_so_far, temp_rec)){ 
            hit_anything = true; 
            closest_so_far = temp_rec.t; 
            rec = temp_rec;
        }
    }

    return hit_anything; 
}

#endif