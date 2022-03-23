#include "Font.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"
#include "stb/stb_image.h"
#include <cstdio>
#include <cstdint>

Font::Font(const char *path, int size) {
    m_Path = path;
    m_FontSize = size;
    FILE* file = fopen(m_Path, "rb");
    if (file == nullptr) {
        return;
    }
    uint8_t fontBuffer[1 << 20];
    auto fontBitmap = new uint8_t[1024 * 1024];
    fread(fontBuffer, 1, 1 << 20, file);
    fclose(file);
    m_FontInfo = new stbtt_fontinfo;
    m_FontData = new stbtt_packedchar[96];
    stbtt_InitFont(m_FontInfo, fontBuffer, stbtt_GetFontOffsetForIndex(fontBuffer, 0));
    stbtt_pack_context packContext = {};
    stbtt_PackBegin(&packContext, fontBitmap, 1024, 1024, 0, 1, 0);
    stbtt_PackSetOversampling(&packContext, 2, 2);
    stbtt_pack_range ranges[1] = {};
    ranges[0].chardata_for_range = m_FontData;
    ranges[0].array_of_unicode_codepoints = 0;
    ranges[0].first_unicode_codepoint_in_range = 32;
    ranges[0].num_chars = 96;
    ranges[0].font_size = -STBTT_POINT_SIZE(m_FontSize);
    stbtt_PackFontRanges(&packContext, fontBuffer, 0, ranges, 1);
    stbtt_PackEnd(&packContext);
    glGenTextures(1, &m_FontTexture);
    glBindTexture(GL_TEXTURE_2D, m_FontTexture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 1024, 1024, 0, GL_ALPHA, GL_UNSIGNED_BYTE, fontBitmap);
    delete[] fontBitmap;
    m_IsCreated = true;

}

Font::~Font() {
    delete m_FontInfo;
    delete[] m_FontData;
    glDeleteTextures(1, &m_FontTexture);
}
