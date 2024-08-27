#include "ControlEventMap.h"

namespace maps
{

EventMap* EventMaps::GetEventMap(uint16_t mapid)
{
    auto it = map.find(mapid);
    if (it != map.end())
    {
        return &(it->second);
    }
    return nullptr;
}

void EventMaps::addMap(EventMap eventMap)
{
    map.emplace(eventMap.MAP_ID, std::move(eventMap));
}

void EventMaps::RemoveMap(uint16_t mapid)
{
    map.erase(mapid);
}

} // namespace maps