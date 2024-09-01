#pragma once
#include "esp_log.h"
#include <stdint.h>
#include <string>
#include <unordered_map>

namespace maps
{
    class EventMap
    {
    public:
        const uint16_t MAP_ID;
        const std::string NAME;
        const uint16_t ACTION_ID;
        bool ACTIVE;

        EventMap(const uint16_t mapid, std::string name, uint16_t actionid, bool active)
            : MAP_ID(mapid), NAME(name), ACTION_ID(actionid), ACTIVE(active) {};


                    // For moving
        EventMap(EventMap&&) noexcept = default;
        EventMap& operator=(EventMap&&) noexcept = default;
        
        // Deleting copy operations
        EventMap(const EventMap&) = delete;
        EventMap& operator=(const EventMap&) = delete;
    };

    class EventMaps
    {
    public:
        EventMap *GetEventMap(uint16_t mapid);
        void addMap(EventMap map);
        void RemoveMap(uint16_t mapid);
     private:
        std::unordered_map<uint16_t, EventMap> map;
    };
} // namespace maps