#include <memory>
#include <mc/camera_skybox.h>

namespace mc::low
{
    const char *Skybox::s_vcode{R"(
        #version 330 core
        layout(location = 0) in vec3 aPos;

        out vec3 io_UV;

        uniform mat4 uni_View;
        uniform mat4 uni_Proj;

        void main() {
            io_UV = aPos;

            vec4 pos = uni_Proj * uni_View * vec4(aPos, 1.0);
            gl_Position = pos.xyww;
        }
    )"};
    const char *Skybox::s_fcode{R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 io_UV;

        uniform samplerCube skybox;

        void main()
        {    
            FragColor = texture(skybox, io_UV);
        }
    )"};
    Skybox::Skybox(Engine *eg)
    {
        m_engine = eg;
    }

    void Skybox::SetArtLogic(std::shared_ptr<mc::asset::ArtLogic> arl)
    {
        m_art_logic = arl;
    }

    void Skybox::AddTexture(std::shared_ptr<mc::asset::Texture> tx)
    {
        m_art_logic->AddTexture(tx);
    }

    void Skybox::SetShaderProgram(std::shared_ptr<mc::asset::ShaderProgram> prog)
    {
        m_program = prog;
    }
    void Skybox::SetModel(std::shared_ptr<mc::asset::Model> model)
    {
        m_model = model;
        std::cout << "m_model addr" << m_model.get() << std::endl;
    }
    void Skybox::Draw()
    {
        std::cout << "m_model addr" << m_model.get() << std::endl;
        m_art_logic->PostUniform(m_engine, nullptr);
        m_model->Use();
    }

}
