// ObjectSystem.cpp
#include "ObjectPool.hpp"
#include <iostream>

//--------------------------------------------
// Game Objects
//--------------------------------------------
GameObject::GameObject(const std::string_view name, const Vec3& kPos, const Vec2& kSize)
    : m_name(name)
    , m_pos(kPos)
    , m_size(kSize)

{
}

void GameObject::Draw() const
{
    std::cout << "[" << m_name << "]" << std::endl;
    std::cout << "\tx: " << m_pos.m_x << std::endl;
    std::cout << "\ty: " << m_pos.m_y << std::endl;
    std::cout << "\tz: " << m_pos.m_z << std::endl;
    std::cout << "\twidth: " << m_size.m_width<< std::endl;
    std::cout << "\theight: " << m_size.m_height << std::endl << std::endl;
}


//--------------------------------------------
// Object System
//--------------------------------------------
ObjectPool::ObjectPool(const size_t& kMaxObjectCount)
    : m_kMaxObjCount(kMaxObjectCount)
    , m_pGameObjects(new std::byte[m_kMaxObjCount * sizeof(GameObject)]) 
    , m_numObjs(0)
{
}

ObjectPool::~ObjectPool()
{
    GameObject* pObj = GetGameObjects();

    for (size_t i = 0; i < m_inUsed.size(); ++i)
    {
        pObj[m_inUsed.at(i)].~GameObject();
    }

    delete[] m_pGameObjects;
}

void ObjectPool::AddGameObject(const std::string_view kName, const Vec3& kPos, const Vec2& kSize)
{
    if (m_numObjs >= m_kMaxObjCount)
    {
        std::cout << "Not enough space." << std::endl;
        return;
    }

    // Add GameObject
    {
        GameObject* pObj = GetGameObjects();
        size_t index = m_numObjs++;

        if (m_free.size() > 0)
        {
            index = m_free.front();
            m_free.pop();
        }

        new(pObj + index) GameObject(kName, kPos, kSize);
        m_inUsed.push_back(index);
    }
}

void ObjectPool::DestroyGameObject(size_t index)
{
    if (m_kMaxObjCount <= index)
        return;

    // Call destructor and push index to queue
    {
        GameObject* pObjs = GetGameObjects();
        pObjs[index].~GameObject();
        m_free.push(index);
        --m_numObjs;
    }

    // Remove it from currently used.
    {
        std::vector<size_t>::iterator it = std::find(m_inUsed.begin(), m_inUsed.end(), index);
        if (it != m_inUsed.end())
        {
            m_inUsed.erase(it);
        }
    }
}

void ObjectPool::PrintGameObjects() const
{
    GameObject* pObj = GetGameObjects();
    for (size_t i = 0; i < m_inUsed.size(); ++i)
    {
        pObj[m_inUsed.at(i)].Draw();
    }
    std::cout << std::endl;
}
