#include "ObjectManager.hpp"

ObjectManager::_objectCompClass ObjectManager::m_compClass(0);
std::unordered_set<Object*> ObjectManager::m_objects;

std::list<Object::Ptr<>> ObjectManager::m_destroyQueue0;
std::list<Object::Ptr<>> ObjectManager::m_destroyQueue1;
bool ObjectManager::m_nextQueue = false;


//* Comparison classes

ObjectManager::_objectCompClass::_objectCompClass(size_t id) : Object(id) {}
void ObjectManager::_objectCompClass::setID(size_t id) { Object::setID(id); }

// -------------------

Object::Ptr<> ObjectManager::getObject(size_t id)
{
    m_compClass.setID(id);
    std::unordered_set<Object*>::iterator obj = m_objects.find((Object*)&m_compClass);
    m_compClass.setID(0);

    return Object::Ptr(obj == m_objects.end() ? nullptr : *obj);
}

size_t ObjectManager::getNumberOfObjects()
{
    return m_objects.size();
}

void ObjectManager::ClearDestroyQueue()
{
    std::list<Object::Ptr<>>& list = m_nextQueue ? m_destroyQueue1 : m_destroyQueue0;
    for (std::list<Object::Ptr<>>::iterator obj = list.begin(); obj != list.end(); obj++)
    {
        if (*obj)
        {
            (*obj)->m_destroy();
        }
    }
    list.clear();

    m_nextQueue = !m_nextQueue;
}

Object::Ptr<> ObjectManager::addObject(Object* object)
{
    m_objects.insert({object});
    return object->getPtr();
}

void ObjectManager::removeObject(Object* object)
{
    m_objects.erase(object);
}

void ObjectManager::addToDestroyQueue(Object* object)
{
    std::list<Object::Ptr<>>& list = m_nextQueue ? m_destroyQueue0 : m_destroyQueue1;
    list.emplace_back(object);
}

void ObjectManager::destroyAllObjects()
{
    auto i = m_objects.begin();
    while (i != m_objects.end())
    {
        auto temp = i;
        i++;
        (*temp)->m_destroy();
    }
    Object::m_lastID = 1;
}
