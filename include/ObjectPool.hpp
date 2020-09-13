#pragma once

#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <cstddef>
#include <string_view>

union Vec2
{
    struct
    {
        float m_x;
        float m_y;
    };
    struct
    {
        float m_width;
        float m_height;
    };
};

struct Vec3
{
    float m_x;
    float m_y;
    float m_z;
};

class GameObject
{
public:
    explicit GameObject(const std::string_view name, const Vec3& kPos, const Vec2& kSize);

    GameObject(const GameObject&) = default;
    GameObject(GameObject&&) = default;
    GameObject& operator=(const GameObject&) = default;
    GameObject& operator=(GameObject&&) = default;

    void Draw() const;

private:
    std::string m_name;
    Vec3 m_pos;
    Vec2 m_size;
};

class ObjectPool
{
public:
    explicit ObjectPool(const size_t& kMaxObjCount);
    ~ObjectPool();

    void AddGameObject(const std::string_view kName, const Vec3& kPos, const Vec2& kSize);
    void DestroyGameObject(size_t index);

    GameObject& operator[](size_t index)
    {
        return GetGameObjects()[index];
    }

    void PrintGameObjects() const;

private:
    GameObject* GetGameObjects() const
    {
        return reinterpret_cast<GameObject*>(m_pGameObjects);
    }

private:
    const size_t m_kMaxObjCount;
    std::byte* m_pGameObjects;
    size_t m_numObjs;   // Current capacity

    std::queue<size_t> m_free;
    std::vector<size_t> m_inUsed;
};

