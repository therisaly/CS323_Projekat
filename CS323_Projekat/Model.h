#pragma once
#pragma warning(disable : 4996)

#include <math.h>
#include <time.h>
#include <istream>
#include <string>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include "stb_image.h"
#include "Vec3.h"

#include <fstream>
#include <map>
#include <vector>

//Simple struct that defines an Image object,
//that's used for loading images for textures
struct Image {
    unsigned char* img; //raw pixel data
    int w, h, channels;

    Image(const char* filename) {

        //Data will be used for defining texture
        img = stbi_load(filename, &w, &h, &channels, 3); // Force 4 channels (RGBA)
        if (!img) {
            printf("Failed to load image: %s\n", filename);
        }
    }

    ~Image() {
        if (img) stbi_image_free(img);
    }
};



class Model {
public:
    Model() = default;
    ~Model()
    {
        for (Material& material : materials) {
            delete material.ambient;
            delete material.diffuse;
            delete material.specular;
        }

        materials.clear();
        map_material.clear();

        for (float* f : vertices)
            delete f;
        vertices.clear();
        for (float* f : texcoords)
            delete f;
        texcoords.clear();
        for (float* f : normals)
            delete f;
        normals.clear();
        faces.clear(); 
    }
    //Used for detirmining which add_face method to use
    //when storing face data
    //f 1 2 3 - (only vertex indices)
    //f 1/1 2/2 3/3 - (vertex and texture coordinates)
    //f 1//1 2//2 3//3 - (vertex and normals)
    static int count_char(std::string& str, char ch) {
        int c = 0;
        int length = str.length() - 1;
        for (int i = 0; i < length; i++) {
            if (str[i] == ch)
                c++;
        }
        return c;
    }

    //if it has double slash, it includes normals
    static bool has_double_slash(std::string& str) {
        int length = str.length() - 2;
        for (int i = 0; i < length; i++) {
            if (str[i] == '/' && str[i + 1] == '/')
                return true;
        }
        return false;
    }

    class Material {
    public:
        float* ambient;
        float* diffuse;
        float* specular;
        GLuint texture;

        Material(float* ambient, float* diffuse, float* specular) {
            this->ambient = ambient;
            this->diffuse = diffuse;
            this->specular = specular;
            this->texture = 0;
        }
    };

    class Face {
    public:
        int edge;
        int* vertices;
        int* texcoords;
        int normal;

        Face(int edge, int* vertices, int* texcoords, int normal = -1) {
            this->edge = edge;
            this->vertices = vertices;
            this->texcoords = texcoords;
            this->normal = normal;
        }
    };

    std::string prefix;
    std::vector<Material> materials;
    std::map<std::string, int> map_material;

    std::vector<float*> vertices;
    std::vector<float*> texcoords;
    std::vector<float*> normals;
    std::vector<Face> faces;

    Vef3 dimensions;
    Vef3 center;

    GLuint list;

    //Create a texture object
    GLuint LoadTexture(const char* filename) {
        Image img(filename);
        if (!img.img) return 0; // Return 0 if image loading failed

        GLuint texture;
        glGenTextures(1, &texture);

        //Bind textures, tell OpenGL "any subsequent operation has to do with this one"
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //Specify mipmaps, how many channels per pixel to use, that the data is made up of unsigned bytes for each channel
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img.w, img.h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.img);
        glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture
        return texture;
    }


    void load_material(const char* filename) {
        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);


        if (!in.is_open()) {
            printf("Cannot load material %s\n", filename);
            return;
        }

        //load material data
        while (!in.eof()) {
            std::getline(in, line);
            lines.push_back(line);
        }
        in.close();

        Material* m = nullptr; //pointer to material being processed
        int count_material = 0; //tracks number of materials being processed
        char str[40]; //buffer
        std::string material; //name
        float* a = nullptr, * d = nullptr, * s = nullptr; //float arrays for ambient, diffuse and specular

        for (std::string& line : lines) {

            //When a line starts with newmtl,
            //it indicates the start of a new material definition
            if (line[0] == 'n' && line[1] == 'e') {

                //The material name is extracted using sscanf,
                //and the material name is added to a map (map_material),
                //which associates the material name with its index (count_material)
                sscanf(line.c_str(), "newmtl %s", str);
                material = str;
                map_material[material] = count_material;
                count_material++;

                //Ambient, diffuse, and specular color values are initialized with default values
                a = new float[4] {0.2f, 0.2f, 0.2f, 1.0f};
                d = new float[4] {0.8f, 0.8f, 0.8f, 1.0f};
                s = new float[4] {0.0f, 0.0f, 0.0f, 1.0f};

                //A new Material object is created with the initialized colors and added to the materials vector.
                //The pointer m is updated to point to this new material.
                materials.push_back(Material(a, d, s));
                m = &materials[materials.size() - 1];
            }
            //Lines starting with Ka, Kd, or Ks represent the ambient, diffuse, and specular colors, respectively
            //These values are extracted and stored in the corresponding float arrays a, d, and s.
            else if (line[0] == 'K') {
                switch (line[1]) {
                case 'a':
                    sscanf(line.c_str(), "Ka %f %f %f", &a[0], &a[1], &a[2]);
                    break;
                case 'd':
                    sscanf(line.c_str(), "Kd %f %f %f", &d[0], &d[1], &d[2]);
                    break;
                case 's':
                    sscanf(line.c_str(), "Ks %f %f %f", &s[0], &s[1], &s[2]);
                    break;
                }
            }
            //Lines starting with map_Kd define the texture associated with the material.
            else if (line[0] == 'm' && line[1] == 'a') {
                sscanf(line.c_str(), "map_Kd %s", str);
                std::string file = prefix + str;
                m->texture = LoadTexture(file.c_str());
            }

            //If you encounter a usemtl line, you get the name of the material (e.g., "Material1").
            //You then look up this material in your map_material to get the correct Material object.
            //When you read a face definition(e.g., f 1 / 1 / 1 2 / 2 / 2 3 / 3 / 3), 
            // you associate that face with the material you just loaded.
        }
    }

    void add_face_3v(std::string& line) {
        int v0, v1, v2;
        sscanf(line.c_str(), "f %d %d %d", &v0, &v1, &v2);
        int* v = new int[3] {v0 - 1, v1 - 1, v2 - 1};
        faces.push_back(Face(3, v, NULL));
    }

    void add_face_3vt(std::string& line) {
        int v0, v1, v2, t0, t1, t2;
        sscanf(line.c_str(), "f %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2);
        int* v = new int[3] {v0 - 1, v1 - 1, v2 - 1};
        int* t = new int[3] {t0 - 1, t1 - 1, t2 - 1};
        faces.push_back(Face(3, v, t));
    }

    void add_face_3vn(std::string& line) {
        int v0, v1, v2, n;
        sscanf(line.c_str(), "f %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n);
        int* v = new int[3] {v0 - 1, v1 - 1, v2 - 1};
        faces.push_back(Face(3, v, NULL, n - 1));
    }

    void add_face_3vtn(std::string& line) {
        int v0, v1, v2, t0, t1, t2, n;
        sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n);
        int* v = new int[3] {v0 - 1, v1 - 1, v2 - 1};
        int* t = new int[3] {t0 - 1, t1 - 1, t2 - 1};
        faces.push_back(Face(3, v, t, n - 1));
    }

    void add_face_4v(std::string& line) {
        int v0, v1, v2, v3;
        sscanf(line.c_str(), "f %d %d %d %d", &v0, &v1, &v2, &v3);
        int* v = new int[4] {v0 - 1, v1 - 1, v2 - 1, v3 - 1};
        faces.push_back(Face(4, v, NULL));
    }

    void add_face_4vt(std::string& line) {
        int v0, v1, v2, v3, t0, t1, t2, t3;
        sscanf(line.c_str(), "f %d/%d %d/%d %d/%d %d/%d", &v0, &t0, &v1, &t1, &v2, &t2, &v3, &t3);
        int* v = new int[4] {v0 - 1, v1 - 1, v2 - 1, v3 - 1};
        int* t = new int[4] {t0 - 1, t1 - 1, t2 - 1, t3 - 1};
        faces.push_back(Face(4, v, t));
    }

    void add_face_4vn(std::string& line) {
        int v0, v1, v2, v3, n;
        sscanf(line.c_str(), "f %d//%d %d//%d %d//%d %d//%d", &v0, &n, &v1, &n, &v2, &n, &v3, &n);
        int* v = new int[4] {v0 - 1, v1 - 1, v2 - 1, v3 - 1};
        faces.push_back(Face(4, v, NULL, n - 1));
    }

    void add_face_4vtn(std::string& line) {
        int v0, v1, v2, v3, t0, t1, t2, t3, n;
        sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v0, &t0, &n, &v1, &t1, &n, &v2, &t2, &n, &v3,
            &t3, &n);
        int* v = new int[4] {v0 - 1, v1 - 1, v2 - 1, v3 - 1};
        int* t = new int[4] {t0 - 1, t1 - 1, t2 - 1, t3 - 1};
        faces.push_back(Face(4, v, t, n - 1));
    }

public:

    void load(const char* filename) {

        //The code extracts the file path (prefix) from the given filename,
        //so that when it needs to load a material file (e.g., .mtl file),
        //it knows where to find it. This is necessary if the .obj file references a material with a relative path.
        std::string tmp = filename;
        prefix = "";
        int n = tmp.find_last_of('/') + 1;
        if (n > 0)
            prefix = tmp.substr(0, n);

        std::string line;
        std::vector<std::string> lines;
        std::ifstream in(filename);
        if (!in.is_open()) {
            printf("Cannot load model %s\n", filename);
            return;
        }

        while (!in.eof()) {
            std::getline(in, line);
            lines.push_back(line);
        }
        in.close();

        float a, b, c;
        char str[40];

        float sum_x = 0.0f, sum_y = 0.0f, sum_z = 0.0f;

        float min[3], max[3];

        min[0] = min[1] = min[2] = std::numeric_limits<float>::infinity();
        max[0] = max[1] = max[2] = -std::numeric_limits<float>::infinity();

        //The code reads the vertices (v), texture coordinates (vt), and normals (vn), 
        //processing each one into respective data structures.
        for (std::string& line : lines) {
            if (line[0] == 'v') {
                if (line[1] == ' ') {
                    sscanf(line.c_str(), "v %f %f %f", &a, &b, &c);
                    if (a > 0.0f)
                        sum_x += a;
                    else
                        sum_x -= a;
                    if (b > 0.0f)
                        sum_y += b;
                    else
                        sum_y -= b;
                    if (c > 0.0f)
                        sum_z += c;
                    else
                        sum_z -= c;
                    vertices.push_back(new float[3] {a, b, c});

                    //calculate dimensions
                    if (a < min[0]) min[0] = a;
                    if (b < min[1]) min[1] = b;
                    if (c < min[2]) min[2] = c;

                    if (a > max[0]) max[0] = a;
                    if (b > max[1]) max[1] = b;
                    if (c > max[2]) max[2] = c; 
                }
                else if (line[1] == 't') {
                    sscanf(line.c_str(), "vt %f %f", &a, &b);
                    texcoords.push_back(new float[2] {a, b});
                }
                else {
                    sscanf(line.c_str(), "vn %f %f %f", &a, &b, &c);
                    normals.push_back(new float[3] {a, b, c});
                }
            }
            //Based on the number of slashes (/) in the face definition,
            //the code determines whether the face uses only vertices (v), 
            //or includes texture coordinates (vt), normals (vn), or both.
            else if (line[0] == 'f') {
                int edge = count_char(line, ' ');
                int count_slash = count_char(line, '/');
                if (count_slash == 0) {
                    if (edge == 3)
                        add_face_3v(line);
                    else
                        add_face_4v(line);
                }
                else if (count_slash == edge) {
                    if (edge == 3)
                        add_face_3vt(line);
                    else
                        add_face_4vt(line);
                }
                else if (count_slash == edge * 2) {
                    if (has_double_slash(line)) {
                        if (edge == 3)
                            add_face_3vn(line);
                        else
                            add_face_4vn(line);
                    }
                    else {
                        if (edge == 3)
                            add_face_3vtn(line);
                        else
                            add_face_4vtn(line);
                    }
                }
            }
            //The .obj file can reference an external material file using mtllib, 
            //and the load_material function is called to load these materials.
            else if (line[0] == 'm' && line[1] == 't') {
                sscanf(line.c_str(), "mtllib %s", &str);
                std::string file = prefix + str;
                load_material(file.c_str());
            }
            else if (line[0] == 'u' && line[1] == 's') {
                sscanf(line.c_str(), "usemtl %s", &str);
                std::string material = str;
                if (map_material.find(material) != map_material.end())
                    faces.push_back(Face(-1, NULL, NULL, map_material[material]));
            }
        }

        center.x = (min[0] + max[0]) / 2.0f;
        center.y = (min[1] + max[1]) / 2.0f;
        center.z = (min[2] + max[2]) / 2.0f;

        dimensions.x = max[0] - min[0];
        dimensions.y = max[1] - min[1];
        dimensions.z = max[2] - min[2];

        bool has_texcoord = false;

        //The function generates an OpenGL display list (glGenLists), 
        //which is a collection of OpenGL commands that can be executed as a group.
        //This list contains the actual drawing code for the faces of the model
        list = glGenLists(1);
        glNewList(list, GL_COMPILE);
        for (Face& face : faces) {
            if (face.edge == -1) {
                has_texcoord = false;

                //For each face, it sets the appropriate material properties (ambient, diffuse, specular) and binds the texture (if applicable).
                glLightfv(GL_LIGHT0, GL_AMBIENT, materials[face.normal].ambient);
                glLightfv(GL_LIGHT0, GL_DIFFUSE, materials[face.normal].diffuse);
                glLightfv(GL_LIGHT0, GL_SPECULAR, materials[face.normal].specular);
                if (materials[face.normal].texture != 0) {
                    has_texcoord = true;
                    glBindTexture(GL_TEXTURE_2D, materials[face.normal].texture);
                }
                continue;
            }
            if (face.normal != -1)
                glNormal3fv(normals[face.normal]);
            else
                glDisable(GL_LIGHTING);
            if (has_texcoord) {
                glBegin(GL_POLYGON);
                for (int i = 0; i < face.edge; i++) {
                    glTexCoord2fv(texcoords[face.texcoords[i]]);
                    glVertex3fv(vertices[face.vertices[i]]);
                }
                glEnd();
            }
            else {
                glBegin(GL_POLYGON);
                for (int i = 0; i < face.edge; i++)
                    glVertex3fv(vertices[face.vertices[i]]);
                glEnd();
            }
            if (face.normal == -1)
                glEnable(GL_LIGHTING);
        }
        glEndList();

        printf("Model: %s\n", filename);
        printf("Vertices: %d\n", vertices.size());
        printf("Texcoords: %d\n", texcoords.size());
        printf("Normals: %d\n", normals.size());
        printf("Faces: %d\n", faces.size());
        printf("Materials: %d\n", materials.size());
        printf("Center: %f, %f, %f\n", center.x, center.y, center.z);
        printf("Dimensions: %f, %f, %f\n", dimensions.x, dimensions.y, dimensions.z);

    }

    void draw() { glCallList(list); }
};


