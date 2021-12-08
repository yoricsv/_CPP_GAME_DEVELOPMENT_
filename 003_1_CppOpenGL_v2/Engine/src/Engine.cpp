//
// Created by Андрей Марцинкевич on 17.11.21.
//

#include "Engine.hpp"

#include <SDL/SdlWindow.hpp>
#include <SDL/SdlRenderer.hpp>

#include <EventsManager.hpp>
#include <Mesh.hpp>

Engine::Engine()
{
    _eventsManager = createUnique<EventsManager>();
}

void Engine::init(std::string_view windows_name, size_t width, size_t height)
{
    _window = createUnique<SdlWindow>("Game",
                                          1280, 720,
                                          SdlWindow::RenderMode::OpenGl);
    _renderer = _window->createRenderer();
    _scene = createShared<Node>();

    EventsAutoRegistarator reg(*_eventsManager, EventsAutoRegistarator::NoRemove);
    reg += [this](const SystemEvent& e)
    {
        if (e.type == SystemEvent::Type::Quit)
        {
            _isActive = false;
        }
    };

    _isActive = true;
}

bool Engine::isActive()
{
    return _isActive;
}

void Engine::update()
{
    _window->update();

    _scene->visit();
    _renderer->draw();

    _window->swap();
}

const EventsManager &Engine::eventsManager() const
{
    return *_eventsManager;
}

const Renderer &Engine::renderer() const
{
    return *_renderer;
}

std::shared_ptr<Node> Engine::scene()
{
    return _scene;
}

const Window &Engine::window() const
{
    return *_window;
}


Engine::~Engine() = default;
