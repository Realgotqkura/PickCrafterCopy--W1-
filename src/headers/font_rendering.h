#pragma once
#include "ft2build.h"
#include FT_FREETYPE_H
#include <memory>
#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include "raw_object.h"

bool loadFont();

struct Character
{
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // Size of glyph
    glm::ivec2 Bearing;     // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Offset to advance to next glyph
};

extern std::map<char, Character> Characters;

namespace FontManager
{
    extern FT_Face currentFont;
};

class Text
{
public:
    Text(std::string text, glm::vec3 position, glm::vec3 scale, glm::vec3 color, std::string id);
    std::string m_text;
    std::string m_textID;
    unsigned int m_VAO = 0;
    unsigned int m_VBO = 0;
    glm::vec3 m_position;
    glm::vec3 m_scale;
    glm::vec3 m_color;
    unsigned int m_textureID;

    void renderText();
    void initTextVAO();
    unsigned int createTexture();
    glm::mat4 getModelMatrix();
};

namespace TextManager
{

    extern std::vector<std::unique_ptr<Text>> textComponents;
};

void createAllText();

Text *addText(std::unique_ptr<Text> textComponent);

Text* getText(std::string textID);