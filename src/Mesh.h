#pragma once

#pragma once

#include <map>
#include <vector>

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
        std::vector<uint>& indices,
        std::map<std::string, std::string>& samplerMap);

   private:
    /*  Functions    */
};
