#pragma once

#define INCLUDE_SDL
#define INCLUDE_SDL_TTF

#include "SDL_include.h"

#include <iostream>

#include "Component.h"
#include "Timer.h"

class Text: public Component{//implementar update, is e render da classe mãe (component)

  public:

    enum TextStyle {SOLID, SHADED, BLENDED};

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, float screenTime = 0, SDL_Color bgcolor = {0, 0, 0, 255});
    ~Text();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetBGColor(SDL_Color bgcolor);
    void SetStyle(TextStyle style);
    void SetFontFile(std::string fontFile);
    void SetFontSize(int fontSize);
    void SetScreenTime(float screenTime);
    void RemakeTexture();


private:

    std::shared_ptr<TTF_Font> font;
    SDL_Texture* texture;
    std::string text;
    TextStyle style;
    std::string fontFile;
    int fontSize;
    SDL_Color color;
    SDL_Color bgcolor;

    Timer OnOff;
    float screenTime;
    int onScreen = 0;
};
