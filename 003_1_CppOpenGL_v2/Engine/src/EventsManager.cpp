//
//  EventsManager.cpp
//  Engine
//
//  Created by Андрей Марцинкевич on 31.07.15.
//  Copyright (c) 2015 Андрей Марцинкевич. All rights reserved.
//

#include "EventsManager.hpp"
#include <algorithm>

void EventsManager::removeHandlersForTag(size_t tag) const
{
    for (auto&& [_, container] : _handlers)
    {
        container.removeIf([&](const EventHandlerWithTag& handler)
        {
            auto&& [handlerTag, _] = handler;
            return handlerTag == tag;
        });
    }

}

EventsAutoRegistarator::EventsAutoRegistarator(const EventsManager &mng, size_t entityId)
        : _eventsManager(mng)
        , _entityId(entityId)
{ }

EventsAutoRegistarator::EventsAutoRegistarator(EventsManager &mng, EventsAutoRegistarator::NoRemoveFlag)
        : _eventsManager(mng)
        , _entityId(-1)
{ }

EventsAutoRegistarator::~EventsAutoRegistarator()
{
    if (_entityId != -1)
    {
        _eventsManager.removeHandlersForTag(_entityId);
    }
}
