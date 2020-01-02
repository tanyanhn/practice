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

    std::shared_ptr<std::vector<Obj>> objs;
    std::shared_ptr<int> index;

    glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 10.0f);
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

    Refresh();
}

void GLComponent::left_down(wxMouseEvent &event) {
    int x = event.GetX();
    int y = event.GetY();
    /*
     * x and y represents your mouse location.
     * */
}

void GLComponent::mouse_wheel(wxMouseEvent &event) {
    auto level = event.GetWheelRotation() / event.GetWheelDelta();

    /*
     * Handle mouse_wheel event here.
     * */

    Refresh();
}

void GLComponent::left_released(wxMouseEvent &event) {
}

void GLComponent::right_down(wxMouseEvent &event) {
    int x = event.GetX();
    int y = event.GetY();
    /*
     * x and y represents your mouse location.
     * */
}

void GLComponent::right_released(wxMouseEvent &event) {
}

void GLComponent::key_pressed(wxKeyEvent &event) {
    auto key_code = event.GetKeyCode();

    /*
     * Handle key pressed event here.
     *
     * key_code can represent which key you have pressed
     * */

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

        glm::mat4 mvp(1.0f);

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