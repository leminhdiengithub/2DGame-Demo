#include"Collision.hpp"
#include"ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect & A, const SDL_Rect & B)
{
 return SDL_HasIntersection(&A, &B);
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if(AABB(colA.collider, colB.collider))
    {
        //A_Right-B_Left
        if (colA.collider.x + colA.collider.w >= colB.collider.x)
        {
            
            return true;
        }
        //A_Left B_Right
        if (colB.collider.x + colB.collider.w >= colA.collider.x)
        {
            return true;
        }
        //A_Bottom B_Top
        if (colA.collider.y + colA.collider.h >= colB.collider.y)
        {
            return true;
        }
        //A_Top B_Bottom
        if (colB.collider.y + colB.collider.h >= colA.collider.y)
        {
            return true;
        }
        return true;
    }else 
    {
        return false;
    }
}