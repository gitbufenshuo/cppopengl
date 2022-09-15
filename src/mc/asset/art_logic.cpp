#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <filesystem>
#include <iostream>

// glad
#include <glad/glad.h>

// asset
#include <mc/asset/asset_manager.h>
#include <mc/asset/model.h>
#include <mc/asset/md5sum.h>

// tools
#include <mc/tools/md5.h>
// log
#include <mc/log/log.h>

namespace mc::asset
{
    using stdpath = std::filesystem::path;
    const std::string ArtLogic::s_scope{"art_logic"};

    ArtLogic::ArtLogic(AssetManager &am, const std::string &r_name) : m_r_name{r_name},
                                                                      m_file_path{(stdpath{am.GetBaseDir()} / stdpath{s_scope} / stdpath{r_name}).string()}

    {
        std::ifstream t(m_file_path.data());
        if (!m_pb_data.ParseFromIstream(&t))
        {
            SPD_WARN("mc::asset::ArtLogic()", m_file_path);
            return;
        }
        {
            mc::tools::MD5Sum(r_name, m_key.data);
            am.Reg<ArtLogic>(m_key, this);
        }
    }
    ArtLogic::~ArtLogic()
    {
        std::cout << " ArtLogic Clear" << std::endl;
    }
    MD5SUM ArtLogic::GetKey() { return m_key; }
    const std::string &ArtLogic::GetLogicName()
    {
        return m_pb_data.logic_class();
    }
    const std::string &ArtLogic::GetBinData()
    {
        return m_pb_data.properties();
    }

}

namespace mc::asset
{
    void ArtLogicFactory::Register(const std::string &class_name, CreateFunc cf)
    {
        // 为什么不用 哈希表呢，因为这玩意不会很多
        // 也不会用的很多，不属于热点代码
        // 如果最后变成热点代码
        // 届时再改成 unordered map
        for (const auto &one_entry : m_holder)
        {
            if (0 == one_entry.first.compare(class_name))
            {
                return;
            }
        }
        //
        m_holder.push_back(std::pair{class_name, cf});
    }
    ArtLogicFactory::CreateFunc ArtLogicFactory::getFunc(const std::string &class_name)
    {
        for (const auto &one_entry : m_holder)
        {
            if (0 == one_entry.first.compare(class_name))
            {
                return one_entry.second;
            }
        }
        return nullptr;
    }

    std::shared_ptr<ArtLogic> ArtLogicFactory::Create(const std::string &class_name, const std::string &bin_data)
    {
        auto func{getFunc(class_name)};
        if (!func)
        {
            return std::shared_ptr<ArtLogic>{nullptr};
        }
        //
        return func(bin_data);
    }
}

namespace mc::asset
{
    std::shared_ptr<ArtLogic> ArtLogicPhong::createFunc(const std::string &bin_data)
    {
        auto res{std::make_shared<ArtLogicPhong>()};
        // "1,1,1,1,1,1,1,1,1,1"
        std::string col;
        std::stringstream row_stream{bin_data};
        int index{0};
        while (std::getline(row_stream, col, ','))
        {
            switch (index++)
            {
            case 0:
                res->m_ambient.x = std::stof(col);
                break;
            case 1:
                res->m_ambient.y = std::stof(col);
                break;
            case 2:
                res->m_ambient.z = std::stof(col);
                break;
            case 3:
                res->m_diffuse.x = std::stof(col);
                break;
            case 4:
                res->m_diffuse.y = std::stof(col);
                break;
            case 5:
                res->m_diffuse.z = std::stof(col);
                break;
            case 6:
                res->m_specular.x = std::stof(col);
                break;
            case 7:
                res->m_specular.y = std::stof(col);
                break;
            case 8:
                res->m_specular.z = std::stof(col);
                break;
            case 9:
                res->m_shininess = std::stof(col);
                break;

            default:
                break;
            }
        }
        return res;
    }
    void ArtLogicPhong::Register(ArtLogicFactory &af)
    {
        af.Register("mc::asset::ArtLogicPhong", createFunc);
    }

    // public virtual
    ArtLogicPhong::~ArtLogicPhong()
    {
    }
    void ArtLogicPhong::PostUniform(mc::low::Engine *eg, mc::low::GameObject *gb)
    {
        m_sp->Use();
        if (m_texture)
        {
            m_texture->Use();
        }
        // 传一些 uniform
        {
            m_sp->Uniform("ma_View", eg->GetCamera()->GetViewMat());
            m_sp->Uniform("ma_Proj", eg->GetCamera()->GetProjMat());
            m_sp->Uniform("lightPos", eg->GetLightPos());
            m_sp->Uniform("lightColor", eg->GetLightColor());
        }
        {
            m_sp->Uniform("material.ambient", m_ambient);
            m_sp->Uniform("material.diffuse", m_diffuse);
            m_sp->Uniform("material.specular", m_specular);
            m_sp->Uniform("material.shininess", m_shininess);
        }
        {
            m_sp->Uniform("ma_Model", gb->GetTransform()->GetWorldMat());
        }
    }
    void ArtLogicPhong::SetShaderProgram(std::shared_ptr<ShaderProgram> sp)
    {
        m_sp = sp;
    }
    void ArtLogicPhong::AddTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
    }
    void ArtLogicPhong::ShowMe()
    {
        std::cout << "mc::asset::ArtLogicPhong" << std::endl;
    }

}