//
// Created by Андрей Марцинкевич on 18.11.21.
//

#include "SdlWindow.hpp"
#include <Engine.hpp>

#include <SDL/SdlRenderer.hpp>
#include <GL/GlRenderer.hpp>

#include <EventsManager.hpp>

SdlWindow::SdlWindow(const Engine& engine,
                     std::string_view name,
                     size_t width,
                     size_t height,
                     RenderMode renderMode)
 : Window(width, height)
 , _engine(engine)
 , _renderMode(renderMode)
{
    SDL_version version   = { 0, 0, 0 };

    SDL_GetVersion(&version);

    printf("SDL Version: %d.%d.%d", version.major, version.minor, version.patch);

    SDL_Init(SDL_INIT_EVERYTHING);

    Uint32 windowFlags = SDL_WINDOW_SHOWN;

    if (_renderMode == RenderMode::OpenGl)
    {
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

        windowFlags |=  SDL_WINDOW_OPENGL;
    }

    _window = {SDL_CreateWindow(name.data(),
                             SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                             width,
                             height,
                             windowFlags), SDL_DestroyWindow};
}

void SdlWindow::update()
{
    SDL_Event e;

    const auto& event_manager = _engine.eventsManager();

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
            case SDL_QUIT:
            {
                event_manager.invokeEvent(SystemEvent{SystemEvent::Type::Quit});

                break;
            }

            case SDL_MOUSEBUTTONDOWN :
            {
                event_manager.invokeEvent(MouseEvent{MouseEvent::Type::LButtonDown, e.button.x, e.button.y});

                break;
            }

            case SDL_MOUSEBUTTONUP :
            {
                event_manager.invokeEvent(MouseEvent{MouseEvent::Type::LButtonUp, e.button.x, e.button.y});

                break;
            }

            case SDL_MOUSEMOTION:
            {
                event_manager.invokeEvent(MouseEvent{MouseEvent::Type::Move, e.button.x, e.button.y});

                break;
            }
        }
    }
}

std::unique_ptr<Renderer> SdlWindow::createRenderer()
{
    if (_renderMode == RenderMode::OpenGl)
    {
        return _engine.createUnique<GlRenderer>(_window.get());
    }
    else
    {
        return _engine.createUnique<SdlRenderer>(_window);
    }
}

void SdlWindow::swap()
{
    if (_renderMode == RenderMode::OpenGl)
    {
        SDL_GL_SwapWindow(_window.get());
    }
}
