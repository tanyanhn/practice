#include <vector>
#include <glm/vec3.hpp>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

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

             for(auto i = faces.begin(); i != faces.end(); i++){
                for(auto j = 0; j < 3; j++)
                    vs.push_back(vertices[(*i).vertices[j] - 1]);
            }

            return vs;
        }

        std::vector<glm::vec3> get_normals() {
            std::vector<glm::vec3> vns;

            /*
             * RETURN normals one by one according to Face order
             * */

             for(auto i = faces.begin(); i != faces.end(); i++){
                for(auto j = 0; j < 3; j++)
                    vns.push_back(normals[(*i).normals[j] - 1]);
            }

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
            vector<glm::vec3> vert;
            vector<glm::vec3> norm;
            vector<Face> face;

            ifstream in(path.c_str());
            if(!in.is_open())
                cout << "load wrong";
            string obj_s;
            while(in.good()){
                in >> obj_s;
                if(obj_s.empty() || (obj_s[0] == '#')){
                    in.ignore(1024, '\n');
                    continue;
                }
                if(obj_s == "v"){
                    float x, y, z;
                    in >> x >> y >> z;
                    vert.push_back(glm::vec3(x, y, z));
                }
                if(obj_s == "vn"){
                    float x, y, z;
                    in >> x >> y >> z;
                    norm.push_back(glm::vec3(x, y, z));
                }
                if(obj_s == "f"){
                    Face f;
                    int t;
                    char s;
                    for(auto j = 0; j < 3; j++){
                        in >> f.vertices[j];
                        in >> s;
                        if(s != '/')
                            cout << "load f wrong";
                        in >> t;
                        in >> s;
                        if(s != '/')
                            cout << "load f wrong";
                        in >> f.normals[j];
                    }
                    face.push_back(f);
                }
            }
            /*Obj o;
            o.vertices = vert;
            o.normals = norm;
            o.faces = face;
            return o;*/

            return Obj {
                .vertices =  std::vector<glm::vec3>(vert),
                .normals =  std::vector<glm::vec3>(norm),
                .faces =  std::vector<Face>(face),
                };
        }
    };
}
#endif