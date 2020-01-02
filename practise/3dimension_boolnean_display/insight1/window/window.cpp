#define wxUSE_MOUSEWHEEL        1

#include <wx-3.0/wx/wx.h>
#include <wx-3.0/wx/sizer.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

#include "gl_component.hpp"

class Insight : public wxApp {
    virtual bool OnInit();

    wxFrame *frame{};
    wxFrame *menu{};
    wxPropertyGrid *list{};
    GLComponent *gl_pane{};

    std::shared_ptr<std::vector<Obj>> objs = std::make_shared<std::vector<Obj>>();
    std::shared_ptr<int> index = std::make_shared<int>(0);
  public:
    void on_open_button_click(wxCommandEvent &evt);

    void on_list_item_focused(wxPropertyGridEvent &evt);

    void on_property_change(wxPropertyGridEvent &evt);

    void refresh_object();

    void on_update_list(wxCommandEvent &evt) {
        refresh_object();
    };
};

//DECLARE_APP(Insight)
IMPLEMENT_APP(Insight)

bool Insight::OnInit() {
    frame = new wxFrame((wxFrame *) nullptr, -1, wxT("Insight"), wxPoint(50, 50), wxSize(400, 200));
    menu = new wxFrame((wxFrame *) nullptr, -1, wxT("Menu"), wxPoint(50, 50), wxSize(200, 400));

    {
        auto *sizer = new wxBoxSizer(wxHORIZONTAL);
        int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
        gl_pane = new GLComponent((wxFrame *) frame, args, objs, index);
        gl_pane->Bind(UPDATE_LIST, &Insight::on_update_list, this);

        sizer->Add(gl_pane, 1, wxEXPAND);

        frame->SetSizer(sizer);
        frame->SetAutoLayout(true);
        frame->Show();
    }

    {
        list = new wxPropertyGrid(menu, wxID_ANY);
        list->Bind(wxEVT_PG_CHANGED, &Insight::on_property_change, this);
        list->Bind(wxEVT_PG_SELECTED, &Insight::on_list_item_focused, this);

        auto *menu_sizer = new wxBoxSizer(wxVERTICAL);
        auto *open_button = new wxButton(menu, wxID_EXIT, wxT("Open"));
        open_button->Bind(wxEVT_BUTTON, &Insight::on_open_button_click, this);
        menu_sizer->Add(open_button, 0, wxEXPAND);
        menu_sizer->Add(list, 1, wxEXPAND);
        menu->SetSizer(menu_sizer);
        menu->SetAutoLayout(true);
        menu->Show();
    }

    return true;
}

void Insight::on_open_button_click(wxCommandEvent &evt) {
    wxFileDialog file_dialog(menu, wxT("obj file chooser"), wxT(""), wxT(""), wxT("*.obj"),
                             wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (file_dialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    std::string path = std::string(file_dialog.GetPath().mb_str());
    auto obj = ObjLoader::ObjLoader(path).load();
    objs->push_back({
                            .path =  path,
                            .vertices =  obj.get_vertices(),
                            .normals =  obj.get_normals(),
                    });

    refresh_object();
    gl_pane->Refresh();
}

void Insight::on_list_item_focused(wxPropertyGridEvent &evt) {
    auto property = list->GetSelectedProperty();
    if(property != nullptr) {
        auto name = std::string(property->GetName());
        std::string part;
        std::stringstream ps(name);
        std::getline(ps, part, '/');

        if (part.length() > 0) {
            *index = std::stoi(part);
            if (*index < 0) *index = 0;
        }
    }

}

void Insight::refresh_object() {
    list->Clear();

    for (auto i = 0; i < objs->size(); i++) {
        auto obj = &objs->at(i);

        list->Append(new wxPropertyCategory(obj->path));
        list->Append(new wxColourProperty("rgb", std::to_string(i) + "/rgb",
                                          wxColour(obj->color[0] * 255, obj->color[1] * 255, obj->color[2] * 255)
        ));
        list->Append(new wxFloatProperty("alpha", std::to_string(i) + "/alpha", obj->color[3]));
        list->Append(new wxFloatProperty("x", std::to_string(i) + "/x", obj->translate_vec[0]));
        list->Append(new wxFloatProperty("y", std::to_string(i) + "/y", obj->translate_vec[1]));
        list->Append(new wxFloatProperty("z", std::to_string(i) + "/z", obj->translate_vec[2]));
        list->Append(new wxFloatProperty("zoom", std::to_string(i) + "/zoom", obj->zoom));
    }
}

void Insight::on_property_change(wxPropertyGridEvent &evt) {
    for (auto i = 0; i < objs->size(); i++) {
        auto obj = &objs->at(i);

        {
            auto alpha_property = (wxFloatProperty *) list->GetPropertyByName(std::to_string(i) + "/alpha");
            auto alpha = alpha_property->GetValue().GetDouble();

            auto property = (wxColourProperty *) list->GetPropertyByName(std::to_string(i) + "/rgb");
            auto color = property->GetVal().m_colour;
            obj->color = glm::vec4(color.Red() * 1.0f / 255.0f, color.Green() * 1.0f / 255.0f,
                                   color.Blue() * 1.0f / 255.0f, alpha);
        }

        {
            auto property = (wxFloatProperty *) list->GetPropertyByName(std::to_string(i) + "/x");
            auto x = property->GetValue().GetDouble();
            obj->translate_vec[0] = x;
        }

        {
            auto property = (wxFloatProperty *) list->GetPropertyByName(std::to_string(i) + "/y");
            auto y = property->GetValue().GetDouble();
            obj->translate_vec[1] = y;
        }

        {
            auto property = (wxFloatProperty *) list->GetPropertyByName(std::to_string(i) + "/z");
            auto z = property->GetValue().GetDouble();
            obj->translate_vec[2] = z;
        }

        {
            auto property = (wxFloatProperty *) list->GetPropertyByName(std::to_string(i) + "/zoom");
            auto zoom = property->GetValue().GetDouble();
            obj->zoom = zoom;
        }
    }

    gl_pane->Refresh();
}