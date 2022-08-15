#ifndef MC_LOW_TEXTURE_H
#define MC_LOW_TEXTURE_H
namespace mc::low
{
    class Texture
    {
    public:
        Texture(const char *file_name);
        void Load();
        void Use();

    private:
        const char *m_file_name;
        //
        unsigned int m_texture_id{};
    };
}
#endif