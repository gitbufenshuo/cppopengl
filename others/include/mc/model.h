#include <vector>

#ifndef MODEL_H
#define MODEL_H
namespace mc::low
{
    class Model
    {
    public:
        Model(const char *file_name, bool append = false);
        Model(bool init_vao = false);

    public:
        void Upload();
        void Use();
        int GetEBOCount() const;
        unsigned int GetEBOType() const;
        void SetAttr(int loc, int size, int stride, void *pointer);
        void SetGLID(unsigned int vbo, unsigned int ebo, unsigned int ebo_type, int ebo_size);
        void TestChangeData1(float);

    public:
        static Model *GenerateHugeQuad(int edge);

    private:
        unsigned int m_vao{};
        unsigned int m_vbo{};
        unsigned int m_vbo1{}; // 第二个vbo, 暂时这么写
        unsigned int m_ebo{};
        unsigned int m_ebo_type{};
        int m_ebo_size{};
        std::vector<float> m_v_data;
        std::vector<float> m_v_data1; // 第二个 vbo 的真实 data
        const char *m_file_name;
        std::vector<int> m_s_data;  // 第一个vbo的属性
        std::vector<int> m_s_data1; // 第二个vbo的属性
        std::vector<int> m_e_data;
        bool m_uploaded{false};
    };
}
#endif