#include "sphere.h"

#include "imgui/imgui.h"

void sphere::params()
{
    double rMin = .001;
    double rMax = 2;
    ImGui::SliderScalar("radius", ImGuiDataType_Double, &radius, &rMin, &rMax, "%.3f");
    double pMin = -1;
    double pMax = 1;
    ImGui::SliderScalarN("position", ImGuiDataType_Double, &center, 3, &pMin, &pMax, "%.1f");
    return;
}

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const 
{
    glm::dvec3 oc = r.origin() - center;
    double a = dot(r.direction(),r.direction());
    double half_b = dot(oc, r.direction());
    double c = dot(oc,oc) - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    glm::dvec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;

    return true;
}