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
        std::cout << colA.tag << " hit " << colB.tag << std::endl;
        return true;
    }else 
    {
        return false;
    }
    
}