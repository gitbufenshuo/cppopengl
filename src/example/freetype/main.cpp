#include <iostream>
#include <string>
#include <fstream>

// freetype
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/internal/ftobjs.h>

// mc low headers
#include <mc/engine.h>

// log
#include <mc/log/log.h>

namespace
{
    void print_req(FT_Face face)
    {
        FT_Size_RequestRec req;
        req.type = FT_SIZE_REQUEST_TYPE_NOMINAL;
        req.width = 16 * 64;
        req.height = 16 * 64;
        req.horiResolution = 72;
        req.vertResolution = 72;
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
        print_req(face);
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
                            "../others/resource/font/Batang.ttf",
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
                         16 * 64, /* char_height in 1/64th of points */
                         72,      /* horizontal device resolution    */
                         72);     /* vertical device resolution      */
        print_Face(face);

        return 0;
    }
}
