#ifndef NETWORK_TYPES_HPP
#define NETWORK_TYPES_HPP

#pragma once

#include <unordered_map>
#include "Utils/funcHelper.hpp"
#include "SFML/Config.hpp"

class NetworkObject;

// TODO name this something better (NetworkFactories?)
// TODO add a way for allowing only the server/client to make the object
class NetworkType
{
public:
    /// @param type the object type that is being added (derive from Object, NetworkObject, and have a constructor with no inputs)
    /// @param factoryFunc a function that creates the type defined
    /// @returns true if the type was added (only added if type does not already exists)
    static bool initType(sf::Uint64 type, const funcHelper::func<NetworkObject*>& factoryFunc);

    /// @param netID the network id of the new object
    /// @returns ptr to the created object (nullptr if not found)
    static NetworkObject* createObject(sf::Uint64 type, sf::Uint32 netID);

protected:

private:
    static std::unordered_map<sf::Uint64, funcHelper::func<NetworkObject*>> m_factories;
};

#endif
