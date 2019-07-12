#include "../include/Minimap.h"
#include "../include/Camera.h"
#include "../include/Character.h"

Minimap::Minimap(GameObject &associated) : Component::Component(associated),
                                           map(new Sprite(associated, MINIMAP_SPRITE_PATH)),
                                           dot(new Sprite(associated, MINIMAP_DOT_PATH)),
                                           border(new Sprite(associated, MINIMAP_BORDER_PATH))
{
    map->SetScale(MINIMAP_SCALE, MINIMAP_SCALE);
    map->SetBlendMode(SDL_BLENDMODE_MOD);
    dot->SetScale(MINIMAP_DOT_SCALE, MINIMAP_DOT_SCALE);
    dot->SetBlendMode(SDL_BLENDMODE_BLEND);
    border->SetScale(MINIMAP_SCALE, MINIMAP_SCALE);
}

void Minimap::Update(float dt)
{
    float clipInitX = -Camera::pos.x + MINIMAP_OFFSET_X;
    float clipInitY = -Camera::pos.y + MINIMAP_OFFSET_Y;
    if (clipInitX < MINIMAP_MIN_X)
    {
        clipInitX = MINIMAP_MIN_X;
    }
    if (clipInitX + MINIMAP_WIDTH > MINIMAP_MAX_X)
    {
        clipInitX = MINIMAP_MAX_X;
    }
    if (clipInitY + MINIMAP_HEIGHT > MINIMAP_MAX_Y)
    {
        clipInitY = MINIMAP_MAX_Y;
    }
    if (clipInitY < MINIMAP_MIN_Y)
    {
        clipInitY = MINIMAP_MIN_Y;
    }
    map->SetClip(clipInitX, clipInitY,
                    MINIMAP_WIDTH, MINIMAP_HEIGHT);
    associated.box.x += MINIMAP_INIT_POS_X;
    associated.box.y += MINIMAP_INIT_POS_Y;
}

void Minimap::Render()
{
    map->Render();
    dot->Render((Character::playerChar->GetPosition().x + Camera::pos.x) * MINIMAP_SCALE + DOT_OFFSET_X,
                (Character::playerChar->GetPosition().y + Camera::pos.y) * MINIMAP_SCALE + DOT_OFFSET_Y);
    border->Render();
}

bool Minimap::Is(std::string type)
{
    return (type == "Minimap");
}