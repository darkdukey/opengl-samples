#include "Light.h"

#include <memory>
using namespace std;

shared_ptr<Light> Light::create(const std::string& name, LightType type) {
    return make_shared<Light>(name, type);
}