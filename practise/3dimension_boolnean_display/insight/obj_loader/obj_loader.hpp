#include <vector>
#include <glm/vec3.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
namespace ObjLoader {

    struct Face {
        int vertices[3];
        int normals[3];
    };

    class Obj {
      public:
        std::vector<glm::vec3> vertices;

        std::vector<glm::vec3> normals;

        std::vector<Face> faces;

        std::vector<glm::vec3> get_vertices() {
            std::vector<glm::vec3> vs;

            /*
             * RETURN vertices one by one according to Face order
             * */

            return vs;
        }

        std::vector<glm::vec3> get_normals() {
            std::vector<glm::vec3> vns;

            /*
             * RETURN normals one by one according to Face order
             * */

            return vns;
        }

    };

    class ObjLoader {
      private:
        std::string path;

      public:
        explicit ObjLoader(const std::string &path) : path(path) {};

        Obj load() {
            /*
             * LOAD FILE HERE
             * */

            return Obj {
                .vertices =  std::vector<glm::vec3>(),
                .normals =  std::vector<glm::vec3>(),
                .faces =  std::vector<Face>(),
            };
        }
    };
}
#endif