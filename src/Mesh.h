#pragma once

#pragma once

#include <map>
#include <vector>

#include "Material.h"
#include "Node.h"
#include "types.h"

class Mesh : public Node {
   public:
    /*  Mesh Data  */
    std::vector<Vertex> _vertices;
    std::vector<uint> _indices;
    /*  Functions  */
    Mesh(
        std::vector<Vertex>& vertices,
        std::vector<uint>& indices);

    void setMaterial(const Material& m);

   private:
    /*  Functions    */
};
