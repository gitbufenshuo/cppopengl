#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

// stb image
#include <image/stb_image_write.h>

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/internal/ftobjs.h>

// mc low headers
#include <mc/engine.h>

// log
#include <mc/log/log.h>

// tools
#include <mc/tools/files.h>

namespace
{
    void print_req(FT_Face face)
    {
        FT_Size_RequestRec req;
        req.type = FT_SIZE_REQUEST_TYPE_NOMINAL;
        req.width = 16 * 64;
        req.height = 16 * 64;
        req.horiResolution = 72;
        req.vertResolution = 0;
        FT_Long swidth = FT_REQUEST_WIDTH(&req);
        FT_Long sheight = FT_REQUEST_HEIGHT(&req);
        std::cout << swidth << " " << sheight << std::endl;
    }
    void print_Face(FT_Face face)
    {
        std::cout << "face->num_glyphs " << face->num_glyphs << std::endl;
        std::cout << "face->face_flags " << face->face_flags << std::endl;
        std::cout << "face->units_per_EM " << face->units_per_EM << std::endl;
        std::cout << "face->num_fixed_sizes " << face->num_fixed_sizes << std::endl;
        std::cout << "face->available_sizes " << face->available_sizes << std::endl;
        std::cout << "face->ascender " << face->ascender << std::endl;
        std::cout << "face->descender " << face->descender << std::endl;
        std::cout << "face->height " << face->height << std::endl;
        std::cout << "face Scalable " << FT_IS_SCALABLE(face) << std::endl;
        //
        // FT_UShort  x_ppem;      /* horizontal pixels per EM               */
        // FT_UShort  y_ppem;      /* vertical pixels per EM                 */

        // FT_Fixed   x_scale;     /* scaling values used to convert font    */
        // FT_Fixed   y_scale;     /* units to 26.6 fractional pixels        */

        // FT_Pos     ascender;    /* ascender in 26.6 frac. pixels          */
        // FT_Pos     descender;   /* descender in 26.6 frac. pixels         */
        // FT_Pos     height;      /* text height in 26.6 frac. pixels       */
        // FT_Pos     max_advance; /* max horizontal advance, in 26.6 pixels */

        std::cout << "face->size->metrics.x_ppem " << (face->size->metrics).x_ppem << std::endl;
        std::cout << "face->size->metrics.y_ppem " << (face->size->metrics).y_ppem << std::endl;
        std::cout << "face->size->metrics.x_scale " << (face->size->metrics).x_scale << std::endl;
        std::cout << "face->size->metrics.y_scale " << (face->size->metrics).y_scale << std::endl;
        std::cout << "face->size->metrics.ascender " << (face->size->metrics).ascender << std::endl;
        std::cout << "face->size->metrics.descender " << (face->size->metrics).descender << std::endl;
        std::cout << "face->size->metrics.height " << (face->size->metrics).height << std::endl;
        std::cout << "face->size->metrics.max_advance " << (face->size->metrics).max_advance << std::endl;
        // print_req(face);
    }
    void printSlot(FT_GlyphSlot slot, char input)
    {
        std::cout << std::endl;
        std::cout << input << " "
                  << "slot->advance " << slot->advance.x << ", " << slot->advance.y << std::endl;
        std::cout << input << " "
                  << "slot->biamap.pixelmode " << static_cast<unsigned short>(slot->bitmap.pixel_mode) << std::endl;
        std::cout << input << " "
                  << "slot->biamap.width " << slot->bitmap.width << std::endl;
        std::cout << input << " "
                  << "slot->biamap.rows " << slot->bitmap.rows << std::endl;
        std::cout << input << " "
                  << "slot->bitmap_top " << slot->bitmap_top << std::endl;
        std::cout << input << " "
                  << "slot->bitmap_left " << slot->bitmap_left << std::endl;
    }
    /**
     * @brief
     *
     * @param dest 目的指针
     * @param src  源指针
     * @param dw 目的width
     * @param dh 目的height
     * @param sw 源width
     * @param sh 源height
     * @param x 目的地偏移x
     * @param y 目的地偏移y
     */
    void copybuffer(unsigned char *dest, unsigned char *src, int dw, int dh, int sw, int sh, int x, int baseliney, int stop)
    {
        int y = baseliney - stop;
        int dstart = y * dw + x;
        for (int syindex = 0; syindex < sh; ++syindex)
        {
            for (int sxindex = 0; sxindex < sw; ++sxindex)
            {
                if (x + sxindex >= dw || y + syindex >= dh)
                {
                    continue;
                }
                dest[dstart + syindex * dw + sxindex] = src[sw * syindex + sxindex];
            }
        }
    }
    void drawCode(FT_Face face, char input)
    {
        FT_Load_Char(face, input, FT_LOAD_RENDER);
        printSlot(face->glyph, input);
        // mmap to file
        // mc::tools::Files::WriteFile("freetype.byte", face->glyph->bitmap.buffer, face->glyph->bitmap.width * face->glyph->bitmap.rows);
        // unsigned char buffer[30 * 100];
        // for (int x{0}; x < 30 * 100; ++x)
        // {
        //     buffer[x] = (x % 30) < 15 ? (0 + x / 30) : 255;
        // }
        // stbi_write_jpg("test.jpg", 30, 100, 1, buffer, 100);
        char filename[100];
        filename[0] = 'f';
        filename[1] = '_';
        int fidx = 2;
        filename[0 + fidx] = input;
        filename[1 + fidx] = '.';
        filename[2 + fidx] = 'j';
        filename[3 + fidx] = 'p';
        filename[4 + fidx] = 'g';
        filename[5 + fidx] = 0;
        stbi_write_jpg(filename, face->glyph->bitmap.width, face->glyph->bitmap.rows, 1, face->glyph->bitmap.buffer, 100);
    }

    FT_ULong getCodePointFromBytes(const char *input, int &bytenum)
    {
        // https://juejin.cn/post/7083791405054689287
        FT_ULong res{0};
        auto b1 = static_cast<unsigned char>(input[0]);
        if (!(b1 & 0x80))
        {
            // 0xxxxxxx
            res = input[0];
            bytenum = 1;
            return res;
        }
        if ((b1 & 0xe0) == 0xc0)
        {
            bytenum = 2;
            // 110xxxxx 10xxxxxx
            res = ((b1 & 0x16) >> 2);
            res = res << 8;
            auto b2 = static_cast<unsigned char>(input[1]);

            return res | ((b1 & 0x03) << 6) | (b2 & 0x3f);
        }
        if ((b1 & 0xf0) == 0xe0)
        {
            bytenum = 3;
            res = (b1 & 0x0f) << 4;
            auto b2 = static_cast<unsigned char>(input[1]);
            res = res | ((b2 & 0x3c) >> 2);
            res = res << 8;
            //
            auto b3 = static_cast<unsigned char>(input[2]);
            return res | (((b2 & 0x03) << 6) | (b3 & 0x3f));
        }
        return 0;
    }

    void drawString(FT_Face face, const char *input)
    {

        constexpr int dw{120};
        constexpr int dh{64};
        unsigned char buffer[dw * dh];
        std::fill(buffer, buffer + dw * dh, 0);
        int dataSize = strlen(input);
        int dx = 0;
        int byteNum;
        for (int index = 0; index < dataSize; index += byteNum)
        {
            auto codePoint = getCodePointFromBytes(input + index, byteNum);
            std::cout << "codePoint : " << codePoint << " codeSize: " << byteNum << std::endl;
            FT_Load_Char(face, codePoint, FT_LOAD_RENDER);
            //
            // printSlot(face->glyph, input[index]);
            dx += face->glyph->bitmap_left;
            copybuffer(buffer, face->glyph->bitmap.buffer, dw, dh,
                       face->glyph->bitmap.width, face->glyph->bitmap.rows, dx, 30, face->glyph->bitmap_top);
            dx += (face->glyph->advance.x / 64);
        }
        stbi_write_jpg("freetype_string.jpg", dw, dh, 1, buffer, 100);
    }
}

/**
 * @brief 纯粹学习 freetype 用
 *
 */
namespace game::example_list::freetype
{
    int Main()
    {
        FT_Library library;
        FT_Face face;

        FT_Error error = FT_Init_FreeType(&library);
        if (error)
        {
            std::cout << "FT_Init_FreeType bad" << std::endl;
        }
        error = FT_New_Face(library,
                            "../others/resource/font/1620207082885638.ttf",
                            0,
                            &face);
        if (error == FT_Err_Unknown_File_Format)
        {
            std::cout << "FT_Err_Unknown_File_Format" << std::endl;
        }
        else if (error)
        {
            std::cout << "error: " << error << std::endl;
        }
        //
        FT_Set_Char_Size(face,    /* handle to face object           */
                         0,       /* char_width in 1/64th of points  */
                         32 * 64, /* char_height in 1/64th of points */
                         72,      /* horizontal device resolution    */
                         0);      /* vertical device resolution      */
        print_Face(face);

        drawString(face, "游戏引擎");

        return 0;
    }
}
