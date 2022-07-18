#pragma once

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list : public hittable
{
public:
    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) {add(object);}
    ~hittable_list() {}

    void clear() {objects.clear();}
    void add(std::shared_ptr<hittable> object) {objects.push_back(object);}
    void add(std::shared_ptr<hittable> object, char* ID);

    virtual void params() override;
    virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

    std::vector<std::shared_ptr<hittable>> objects;
    std::vector<char*> IDs;
};