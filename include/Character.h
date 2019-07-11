#pragma once

#define CHARACTER
#include "MorphingMenace_include.h"
#include "Engine_include.h"

class Character : public Component
{
public:
    Character(GameObject& associated, int maxHP, char_type type);
    void Accelerate(Vec2 acceleration = Vec2(0, 0));

    void Update(float dt);
    bool Is(std::string);
    void Render();
    void NotifyCollision(GameObject &other);

    void limitSpeeds();
    void collisionSide(Rect boxA, Rect boxB);
    bool applyNormal;
    bool applyWaterThrust;
    bool applyGravity;
    Vec2 GetLastPosition();
    Vec2 GetPosition();
    Vec2 GetSpeed();
    void SetSpeed(Vec2 speed);
    void SetSpeed(int speedX, int speedY);
    void SetSpeedX(int speedX);
    void SetSpeedY(int speedY);
    bool IsFlipped();
    void EnableFlip();
    void DisableFlip();
    void ApplyDamage(int damage);
    char_type Type();
    int GetCurrentHP();
    int GetMaxHP();
    bool IsAbsorbable();
    void Die();
    bool VerifyOcean();
    void EnableScenarioCollision();
    void DisableScenarioCollision();

    static Character* playerChar;
    Rect box;
private:
    bool scenarioCollision;
    Vec2 speed;
    Vec2 lastPosition;
    collision_side verticalCollision;
    collision_side horizontalCollision;
    bool flip;
    int maxHP;
    int currentHP;
    char_type charType;
};