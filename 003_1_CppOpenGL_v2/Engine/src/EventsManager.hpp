//
//  EventsManager.h
//  Engine
//
//  Created by Андрей Марцинкевич on 31.07.15.
//  Copyright (c) 2015 Андрей Марцинкевич. All rights reserved.
//

#pragma once

#include <vector>

#include <Utils/KeyCodes.hpp>

#include <functional>
#include <unordered_map>
#include <string>

#include <Utils/CppExt.hpp>
#include <Utils/ProtectedVector.hpp>



    struct BaseEvent {};

    struct FileDropEvent : public BaseEvent
    {
        std::string filename;

        explicit FileDropEvent(std::string filename)
            : filename(std::move(filename))
            { }
    };

    struct MouseWheelEvent : public BaseEvent
    {
        int value;

        explicit MouseWheelEvent(int value) : value(value) { }
    };


    struct MouseEvent : public BaseEvent
    {
        enum class Type
        {
            Move,
            LButtonDown,
            LButtonUp,
        } type;

        int x, y;

        explicit MouseEvent(Type type, int x, int y) : type(type), x(x), y(y) { }
    };

    struct TextInputEvent : public BaseEvent
    {
        std::string string;
        bool isBackspace {false};


        explicit TextInputEvent(std::string string)
            : string(std::move(string))
        {}


        TextInputEvent() :
            isBackspace(true)
        {}
    };

    struct KeyEvent : public BaseEvent
    {
        KeyCode key = KeyCode::UNKNOWN;

        enum class Type
        {
            KeyDown,
            KeyUp,
        } type;

        KeyEvent(Type type, KeyCode key) : type(type), key(key) { }
    };

    struct TouchEvent : public BaseEvent
    {
        size_t idx;
        float x, y;

        enum class Type
        {
            TouchBegin,
            TouchMove,
            TouchEnd,
        } type;

        TouchEvent(Type type, size_t idx, float x, float y)
            : type(type), idx(idx), x(x), y(y)
        {}
    };

    struct ResizeEvent : public BaseEvent
    {
        int width;
        int height;

        ResizeEvent(int width, int height) : width(width), height(height) { }
    };

    struct SystemEvent : public BaseEvent
    {
        enum class Type
        {
            Pause,
            Resume,
            Quit,
        } type;

        explicit SystemEvent(Type type) : type(type)
        {}
    };


    class EventsManager final
    {
    public:
        template <typename Handler>
        void addHandler(Handler handler, size_t id) const
        {
            using traits = ext::function_traits<std::decay_t<Handler>>;

            static_assert(traits::arity == 1, "Need only one argument for handler");
            static_assert(std::is_same_v<typename traits::result_type, void>, "Return type must be void");

            using arg_type_raw = typename traits:: template arg<0>::type;

            static_assert(std::is_reference_v<arg_type_raw>, "Argument must be reference");

            using arg_type = std::decay_t<arg_type_raw>;

            static_assert(!std::is_same_v<BaseEvent, arg_type>, "Argument must be not BaseEvent");
            static_assert(std::is_base_of_v<BaseEvent, arg_type>, "Argument must be derived of BaseEvent");

            const auto entityId = ext::classId<arg_type>();
            printf("Add handler for %ld\n", entityId);
            _handlers[entityId].add({id, [handler](const BaseEvent& e)
            {
                handler(static_cast<arg_type_raw>(e));
            }});
        }

        void removeHandlersForTag(size_t tag) const;

        using EventHandler = std::function<void(const BaseEvent& e)>;
        using EventHandlerWithTag = std::pair<size_t, EventHandler>;

        template <typename Event>
        void invokeEvent(const Event& event) const
        {
            static_assert(!std::is_same_v<BaseEvent, void>, "Argument must be not BaseEvent");
            static_assert(std::is_base_of_v<BaseEvent, Event>, "Argument must be derived of BaseEvent");

            const auto entId = ext::classId<std::decay_t<Event>>();
            auto it = _handlers.find(entId);
            if (it != _handlers.end())
            {
                it->second.forEach([&](const EventHandlerWithTag& value)
                {
                    auto&& [_, handler] = value;
                    handler(event);
                });
            }
        }

    private:
        mutable std::unordered_map<size_t, ProtectedVector<EventHandlerWithTag>> _handlers;
    };


    class EventsAutoRegistarator
    {
    public:

        struct NoRemoveFlag {};
        static constexpr NoRemoveFlag NoRemove{};

        EventsAutoRegistarator(const EventsManager& mng, size_t entityId);;

        EventsAutoRegistarator(EventsManager& mng, NoRemoveFlag);;

        template<typename Handler>
        void operator+=(Handler handler) const
        {
            _eventsManager.addHandler(handler, _entityId);
        }


        ~EventsAutoRegistarator();

    private:
        const size_t _entityId;
        const EventsManager& _eventsManager;
    };
