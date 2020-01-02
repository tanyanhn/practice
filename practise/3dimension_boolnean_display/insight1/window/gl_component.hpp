#include <utility>

#include <utility>

#ifndef GL_COMPONENT_H
#define GL_COMPONENT_H

#include "../obj_loader/obj_loader.hpp"

#define wxUSE_MOUSEWHEEL        1

#include <wx-3.0/wx/wx.h>
#include <wx-3.0/wx/sizer.h>
#include <wx/time.h>
#include <GL/glew.h>
#include <wx-3.0/wx/glcanvas.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/string_cast.hpp>

#include <memory>
#include <cmath>

#define PI 3.14159265358979323846


double norm(glm::vec3 v){
    return sqrt(dot(v, v));
}

double computeangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 direction){
    //float l1[3];
    double x = dot(cross(direction, v1), v2);
    double y = dot(v1, v2);
    //l1[0] = v1[0]; l1[1] = v1[1]; l1[2] = v1[2];
    //l2[0] = v2[0]; l2[1] = v2[1]; l2[2] = v2[2];
    /*if(l1[2] > 0){
        return angle = PI / 2 + atan(sqrt(l1[0] * l1[0] + l1[1] * l1[1]) / l1[2]);
    }
    else if(l1[2] < 0){
        return angle = PI / 2 - atan(sqrt(l1[0] * l1[0] + l1[1] * l1[1]) / l1[2]);
    }
    else
    return PI /2;*/
    if(x == 0){
        return PI;
    }
    else if(x > 0){
        return acos(y / (norm(v1) * norm(v2)) );
    }
    else if(x < 0){
        return 2 * PI - acos(y / (norm(v1) * norm(v2)) );
    }
}

glm::vec3 cross(glm::vec3 v1, glm::vec3 v2){
    return glm::vec3(v1[1] * v2[2] - v1[2] * v2[1],
                     v1[2] * v2[0] - v1[0] * v2[2],
                     v1[0] * v2[1] - v1[1] * v2[0]);
}

double dot(glm::vec3 v1, glm::vec3 v2){
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

struct Obj {
    std::string path;

    std::vector<glm::vec3> vertices, normals;
    glm::vec3 translate_vec = glm::vec3(0.0f);

    float zoom = 1.0f;
    glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
};

class GLComponent : public wxGLCanvas {
  private:
    wxGLContext *m_context;

    GLuint vertex_buffer, normal_buffer, vertex_shader, fragment_shader, program;
    GLint mvp_location, pos_location, normal_location, col_location, camera_position_location;

    bool gl_inited = false;
    bool leftisDown = false;
    bool rightisDown = false;

    std::shared_ptr<std::vector<Obj>> objs;
    std::shared_ptr<int> index;

    glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 mouse_position = glm::vec3(0.0f, 0.0f, 0.0f);
    float wheel = 1.0f;
    bool ifwheel = false;
    glm::vec3 translate_vec = glm::vec3(0.0f, 0.0f, 0.0f);
  public:
    GLComponent(wxFrame *parent, int *args, std::shared_ptr<std::vector<Obj>> objs, std::shared_ptr<int> index);

    ~GLComponent() override;

    void resized(wxSizeEvent &evt);

    int getWidth();

    int getHeight();

    void render(wxPaintEvent &evt);

    void init_gl();

    void mouse_moved(wxMouseEvent &event);

    void mouse_wheel(wxMouseEvent &event);

    void left_down(wxMouseEvent &event);

    void left_released(wxMouseEvent &event);

    void right_down(wxMouseEvent &event);

    void right_released(wxMouseEvent &event);

    void key_pressed(wxKeyEvent &event);

    void key_released(wxKeyEvent &event);

    DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(GLComponent, wxGLCanvas)
EVT_MOTION(GLComponent::mouse_moved)
EVT_LEFT_DOWN(GLComponent::left_down)
EVT_LEFT_UP(GLComponent::left_released)
EVT_RIGHT_DOWN(GLComponent::right_down)
EVT_RIGHT_UP(GLComponent::right_released)
EVT_SIZE(GLComponent::resized)
EVT_KEY_DOWN(GLComponent::key_pressed)
EVT_KEY_UP(GLComponent::key_released)
EVT_MOUSEWHEEL(GLComponent::mouse_wheel)
EVT_PAINT(GLComponent::render)
END_EVENT_TABLE()


static const char *vertex_shader_text =

#include "shader.vert"
    static const char *fragment_shader_text =

#include "shader.frag"

    void GLComponent::mouse_moved(wxMouseEvent &event) {
    int x = event.GetX();
    int y = event.GetY();
    /*
     * x and y represents your mouse location.
     * */
    if(leftisDown){
        //camera_position[0] += 10 *(x - mouse_position[0]);
        //camera_position[1] += 10* (y - mouse_position[1]);
        //if(x > 0)
            mouse_position[0] +=  (2 * x / getWidth() );
        // else if(x < 0)
            //    mouse_position[0] -=  (2 * x / getWidth() );
        //if(y > 0)
            mouse_position[1] +=  (2 * y / getHeight());
        //else if(y < 0)
            //    mouse_position[1] -=  (2 * y / getHeight());
    }
    if(rightisDown){
        //if(x > 0)
            mouse_position[2] +=  (2 * x / getWidth() );
        // else if(x < 0)
        //    mouse_position[2] -=  (2 * x / getWidth() );
        //mouse_position[2] +=  (2 * x / getWidth());
    }
    // exit(0);
    Refresh();
}

void GLComponent::left_down(wxMouseEvent &event) {
    int x = event.GetX();
    int y = event.GetY();
    /*
     * x and y represents your mouse location.
     * */
    leftisDown = true;
    //camera_position[1] += 1.0f;
    // mouse_position[0] = x;
    //mouse_position[1] = y;
    //exit(0);
}

void GLComponent::mouse_wheel(wxMouseEvent &event) {
    auto level = event.GetWheelRotation() / event.GetWheelDelta();

    /*
     * Handle mouse_wheel event here.
     * */
    if(level > 0)
        wheel *= 0.9;
    else if(level < 0)
        wheel *= 1.1;
    //ifwheel = true;

    Refresh();
}

void GLComponent::left_released(wxMouseEvent &event) {
    leftisDown = false;
    //mouse_position[0] = 0;
    //mouse_position[1] = 0;
    Refresh();
}

void GLComponent::right_down(wxMouseEvent &event) {
    int x = event.GetX();
    int y = event.GetY();
    /*
     * x and y represents your mouse location.
     * */
    rightisDown = true;
}

void GLComponent::right_released(wxMouseEvent &event) {
    rightisDown = false;
}

void GLComponent::key_pressed(wxKeyEvent &event) {
    auto key_code = event.GetKeyCode();

    /*
     * Handle key pressed event here.
     *
     * key_code can represent which key you have pressed
     * */
    if(key_code == 87)
        translate_vec[1] += 0.1;
    if(key_code == 83)
        translate_vec[1] -= 0.1;
    if(key_code == 65)
        translate_vec[0] -= 0.1;
    if(key_code == 68)
        translate_vec[0] += 0.1;
    if(key_code == 81)
        translate_vec[2] -= 0.1;
    if(key_code == 69)
        translate_vec[2] += 0.1;

    Refresh();
}

void GLComponent::key_released(wxKeyEvent &event) {}

GLComponent::GLComponent(wxFrame *parent, int *args, std::shared_ptr<std::vector<Obj>> objs, std::shared_ptr<int> index)
        : wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
          objs(std::move(objs)), index(std::move(index)) {
    m_context = new wxGLContext(this);

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

GLComponent::~GLComponent() {
    delete m_context;
}

void GLComponent::resized(wxSizeEvent &evt) {
//	wxGLCanvas::OnSize(evt);

    Refresh();
}

int GLComponent::getWidth() {
    return GetSize().x;
}

int GLComponent::getHeight() {
    return GetSize().y;
}

void GLComponent::init_gl() {
    SetCurrent(*m_context);

    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cerr << "GLEW INIT ERROR " << glewGetErrorString(err) << std::endl;
        exit(EXIT_FAILURE);
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glGenBuffers(1, &vertex_buffer);
    glGenBuffers(1, &normal_buffer);
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, nullptr);
    glCompileShader(vertex_shader);
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, nullptr);
    glCompileShader(fragment_shader);
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    mvp_location = glGetUniformLocation(program, "mvp");
    col_location = glGetUniformLocation(program, "col");
    camera_position_location = glGetUniformLocation(program, "cameraPosition");

    pos_location = glGetAttribLocation(program, "pos");
    normal_location = glGetAttribLocation(program, "normal");

    glEnableVertexAttribArray(pos_location);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(pos_location, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), nullptr);

    glEnableVertexAttribArray(normal_location);
    glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
    glVertexAttribPointer(normal_location, 3, GL_FLOAT, GL_FALSE,
                          3 * sizeof(GLfloat), nullptr);
}

wxDEFINE_EVENT(UPDATE_LIST, wxCommandEvent);

void GLComponent::render(wxPaintEvent &evt) {
    if (!IsShown()) return;
    if (!gl_inited) {
        gl_inited = true;

        init_gl();
    }

    wxCommandEvent event(UPDATE_LIST);
    wxPostEvent(this, event);

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int width = getWidth();
    int height = getHeight();

    glViewport(0, 0, width, height);

    glUseProgram(program);

    for (auto obj: *objs) {
        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * obj.vertices.size(), &obj.vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, normal_buffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * obj.normals.size(), &obj.normals[0], GL_STATIC_DRAW);

        //if(ifwheel){
            if(wheel > 0)
                obj.zoom *= wheel;
            //else if(wheel < 0)
            //    obj.zoom *= 1.1;
            //mouse_position[2] += PI;
            //mouse_position[1] += PI;
            //mouse_position[0] += PI;
            //ifwheel = false;
            //}

        glm::mat4 mvp(1.0f);
        glm::mat4 m(1.0f);
        //mvp = mvp * glm::scale(m, glm::vec3(2.0f, 2.0f, 2.0f));
        glm::vec3 v(0.0f);
        glm::vec3 z_buffer_direct(0.0f, 0.0f, -1.0f);
        if(camera_position[0] == 0){
            v[0] = 1.0f;
            // v[1] = 0.0f;
            //v[2] = 0.0f;
        }
        else if(camera_position[1] == 0){
            v[1] = 1.0f;
        }
        else {
            v = cross(camera_position, z_buffer_direct);
        }
        double angle = computeangle(camera_position, z_buffer_direct, v);
        mvp = glm::translate(mvp, obj.translate_vec + translate_vec);
        mvp = mvp * glm::scale(m,  glm::vec3(obj.zoom));
        // mvp - glm::scale(mvp, glm::vec3(2.0f));
        mvp = mvp * glm::rotate(glm::mat4(1.0f), float(angle /*+ (atan(sqrt(18) / 3))*/), v);
        mvp = mvp * glm::rotate(glm::mat4(1.0f), float(mouse_position[0]/10 /*+ (atan(sqrt(18) / 3))*/), glm::vec3(0.0f, 1.0f, 0.0f));
        mvp = mvp * glm::rotate(glm::mat4(1.0f), float(mouse_position[1]/10 /*+ (atan(sqrt(18) / 3))*/), glm::vec3(1.0f, 0.0f, 0.0f));
        mvp = mvp * glm::rotate(glm::mat4(1.0f), float(mouse_position[2]/10 /*+ (atan(sqrt(18) / 3))*/), glm::vec3(0.0f, 0.0f, 1.0f));
        /*glm::vec4 vc(0.0f, 0.0f, 10.0f, 1.0f);
        vc = glm::rotate(glm::mat4(1.0f), float(PI + (atan(sqrt(18) / 3))), v) * vc;
        camera_position[0] = vc[0];
        camera_position[1] = vc[1];
        camera_position[2] = vc[2];
        //mvp = mvp * glm::orientation(glm::normalize(glm::vec4(3, 3, 3, 1)), glm::normalize(glm::vec4(0, 0, -sqrt(27), 1)));

        /*
         * Calculate mvp matrix here
         * */

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        glUniform4fv(col_location, 1, glm::value_ptr(obj.color));
        glUniform3fv(camera_position_location, 1, glm::value_ptr(camera_position));

        glDrawArrays(GL_TRIANGLES, 0, obj.vertices.size());
    }

    SwapBuffers();
}

#endif