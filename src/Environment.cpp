#include "../include/Environment.h"

Environment::Environment()
{
    /*
        TODO:
        Construir forças de início de jogo
            - Gravidade
            - Força normal
            - Empuxo
    */
}

Environment::~Environment()
{}

void Environment::ApplyForces(GameObject* go)
{
    for (int i = 0; i < (int)forcesArray.size(); i++)
    {
        if (forcesArray[i].Applicable(go))
        {
            forcesArray[i].Apply(go);
        }
    }
}