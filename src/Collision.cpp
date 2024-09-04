#include"Collision.hpp"
#include"ECS/ColliderComponent.hpp"

bool Collision::AABB(const SDL_Rect & A, const SDL_Rect & B)
{
 if (SDL_HasIntersection(&A, &B))
    {
        return true;
    }
    return false;   
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{
    if (AABB(colA.collider, colB.collider))
    {
        std::cout << colA.tag << " hit " << colB.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
}

void Collision::ResolveCollision(ColliderComponent& colA, ColliderComponent& colB)
{
    SDL_Rect playerCol = colA.collider;
    SDL_Rect objectCol = colB.collider;

    // Tính toán các khoảng cách để xác định hướng va chạm
    int diffRight = (playerCol.x + playerCol.w) - objectCol.x;
    int diffLeft = (objectCol.x + objectCol.w) - playerCol.x;
    int diffDown = (playerCol.y + playerCol.h) - objectCol.y;
    int diffUp = (objectCol.y + objectCol.h) - playerCol.y;

    // Kiểm tra hướng va chạm bằng cách so sánh các khoảng cách
    if (diffRight < diffLeft && diffRight < diffDown && diffRight < diffUp) 
    {
        // Va chạm từ trái
        colA.transform->position.x = objectCol.x - playerCol.w;
    }
    else if (diffLeft < diffRight && diffLeft < diffDown && diffLeft < diffUp) 
    {
        // Va chạm từ phải
        colA.transform->position.x = objectCol.x + objectCol.w;
    }
    else if (diffDown < diffUp && diffDown < diffRight && diffDown < diffLeft) 
    {
        // Va chạm từ trên
        colA.transform->position.y = objectCol.y - playerCol.h;
    }
    else if (diffUp < diffDown && diffUp < diffRight && diffUp < diffLeft) 
    {
        // Va chạm từ dưới
        colA.transform->position.y = objectCol.y + objectCol.h;
    }
}