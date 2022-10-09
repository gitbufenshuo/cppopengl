#include <mc/asset/art_logic_simple.h>

namespace mc::asset
{
    const std::string ArtLogicSimple::s_class_name{"mc::asset::ArtLogicSimple"};
    std::shared_ptr<ArtLogic> ArtLogicSimple::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicSimple>()};
        return res;
    }
    void ArtLogicSimple::Register(ArtLogicFactory &arf)
    {
        arf.Register(s_class_name, createFunc);
    }
    // public virtual
    ArtLogicSimple::~ArtLogicSimple()
    {
    }
    std::shared_ptr<ArtLogic> ArtLogicSimple::Clone()
    {
        return std::make_shared<ArtLogicSimple>(*this);
    }
    void ArtLogicSimple::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        //
        m_sp->Uniform("uni_View", eg->GetCamera()->GetViewMat());
        m_sp->Uniform("uni_Proj", eg->GetCamera()->GetProjMat());
        m_sp->Uniform("uni_Model", gb->GetTransform()->GetWorldMat());
    }
    void ArtLogicSimple::SetShaderProgram(std::shared_ptr<ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicSimple::AddTexture(std::shared_ptr<Texture> texture)
    {
    }
    const std::string &ArtLogicSimple::ShowMe()
    {
        std::cout << s_class_name << std::endl;
        return s_class_name;
    }
}