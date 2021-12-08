//
// Created by Андрей Марцинкевич on 17.11.21.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <string_view>

class Window;
class Renderer;
class EventsManager;
class Mesh;
class Node;

class Engine
{
public:
    explicit Engine();
    ~Engine();

    void init(std::string_view windows_name, size_t width, size_t height);

    bool isActive();
    void update();

    [[nodiscard]] const EventsManager& eventsManager() const;
    [[nodiscard]] const Renderer& renderer() const;
    [[nodiscard]] const Window& window() const;

    std::shared_ptr<Node> scene();

    template<typename T, typename... Args>
    std::shared_ptr<T> createShared(Args&&... args) const
    {
        if constexpr(std::is_constructible_v<T, const Engine&, Args&&...>)
        {
            return std::make_shared<T>(*this, std::forward<Args>(args)...);
        }
        else
        {
            return std::make_shared<T>(std::forward<Args>(args)...);
        }
    }

    template<typename T, typename... Args>
    std::unique_ptr<T> createUnique(Args&&... args) const
    {
        if constexpr(std::is_constructible_v<T, const Engine&, Args&&...>)
        {
            return std::make_unique<T>(*this, std::forward<Args>(args)...);
        }
        else
        {
            return std::make_unique<T>(std::forward<Args>(args)...);
        }
    }

private:
    std::unique_ptr<Window> _window;
    std::unique_ptr<Renderer> _renderer;
    std::unique_ptr<EventsManager> _eventsManager;
    bool _isActive = false;

    std::shared_ptr<Node> _scene;
};


#endif
