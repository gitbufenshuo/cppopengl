#include <vector>

#ifndef MODEL_H
#define MODEL_H
namespace mc::low
{
    class Model
    {
    public:
        Model(const char *file_name);
        void Upload();
        void Use();
        int GetEBOCount() const;

    private:
        unsigned int m_vao{};
        unsigned int m_vbo{};
        unsigned int m_ebo{};
        std::vector<float> m_v_data;
        const char *m_file_name;
        std::vector<int> m_s_data;
        std::vector<int> m_e_data;
        bool m_uploaded{false};
    };
}
#endif