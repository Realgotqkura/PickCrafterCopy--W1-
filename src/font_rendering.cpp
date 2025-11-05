#include "font_rendering.h"
#include <iostream>
#include <glad/glad.h>
#include "shader.h"

std::map<char, Character> Characters;

bool loadFont()
{

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return false;
    }

    FT_Face font;
    if (FT_New_Face(ft, "fonts/minecraft.ttf", 0, &font))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return false;
    }

    FT_Set_Pixel_Sizes(font, 0, 48);

    if (FT_Load_Char(font, 'X', FT_LOAD_RENDER))
    {
        std::cout << "ERROR::FREETYPE: Could not load character!" << std::endl;
        return false;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(font, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            font->glyph->bitmap.width,
            font->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            font->glyph->bitmap.buffer);
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(font->glyph->bitmap.width, font->glyph->bitmap.rows),
            glm::ivec2(font->glyph->bitmap_left, font->glyph->bitmap_top),
            font->glyph->advance.x};
        Characters.insert(std::pair<char, Character>(c, character));
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    FontManager::currentFont = font;
    return true;
}

Text::Text(std::string text, glm::vec3 position, glm::vec3 scale, glm::vec3 color, std::string id) : m_textID(id), m_text(text), m_position(position), m_scale(scale), m_color(color)
{

    initTextVAO();
    createTexture();
}

void Text::initTextVAO()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);



    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    // Reserve enough space for 6 vertices * 5 floats (x, y, z, u, v)
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, nullptr, GL_DYNAMIC_DRAW);

    // Vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

glm::mat4 Text::getModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, m_position);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));
    model = glm::scale(model, m_scale);

    return model;
}

void Text::renderText()
{
    // activate corresponding render state
    glm::vec3 colorNormalized = m_color / 255.0f;
    glUniform3f(glGetUniformLocation(t_ShaderProgram, "textColor"), colorNormalized.x, colorNormalized.y, colorNormalized.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    // iterate through all characters
    std::string::const_iterator c;
    float xAdd = 0;
    for (c = m_text.begin(); c != m_text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = (m_position.x + ch.Bearing.x * m_scale.x) + xAdd;
        float ypos = m_position.y + (ch.Bearing.y - ch.Size.y) * m_scale.y;

        float w = ch.Size.x * m_scale.x;
        float h = ch.Size.y * m_scale.y;
        // update VBO for each character
        float vertices[6][5] = {
            {xpos, ypos + h, 0.0f, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 0.0f, 1.0f},
            {xpos + w, ypos, 0.0f, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f, 0.0f},
            {xpos + w, ypos, 0.0f, 1.0f, 1.0f},
            {xpos + w, ypos + h, 0.0f, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        xAdd += (ch.Advance >> 6) * m_scale.x; // advance local cursor only
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Text::createTexture()
{
    FT_Face &face = FontManager::currentFont;
    // First, figure out texture size
    int width = 0;
    int height = 0;
    for (char c : m_text)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            continue;
        width += face->glyph->bitmap.width;
        height = std::max(height, (int)face->glyph->bitmap.rows);
    }

    // Allocate buffer
    std::vector<unsigned char> pixels(width * height, 0);

    // Render text into that buffer
    int x = 0;
    for (char c : m_text)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
            continue;

        FT_Bitmap &bmp = face->glyph->bitmap;
        for (int row = 0; row < bmp.rows; ++row)
        {
            for (int col = 0; col < bmp.width; ++col)
            {
                int dstIndex = (row * width) + (x + col);
                pixels[dstIndex] = bmp.buffer[row * bmp.pitch + col];
            }
        }
        x += bmp.width;
    }

    // Upload to OpenGL texture
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}

void createAllText()
{
    addText(std::make_unique<Text>("0 XP", glm::vec3(120.0f, 420.0f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 255.0f, 0.0f), "xp"));
}

Text *addText(std::unique_ptr<Text> textComponent)
{
    TextManager::textComponents.emplace_back(std::move(textComponent));
    return TextManager::textComponents.back().get();
}

Text* getText(std::string textID){
    for(size_t i = 0; i < TextManager::textComponents.size(); i++){
        if(textID.compare(TextManager::textComponents[i].get()->m_textID) == 0){
            return TextManager::textComponents[i].get();
        }
    }

    return nullptr;
}

namespace FontManager
{
    FT_Face currentFont = nullptr;
}

namespace TextManager
{

    std::vector<std::unique_ptr<Text>> textComponents;
};
