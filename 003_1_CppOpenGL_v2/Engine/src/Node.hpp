//
// Created by Андрей Марцинкевич on 22.11.21.
//

#ifndef GAME_NODE_HPP
#define GAME_NODE_HPP

#include <memory>
#include <Utils/ProtectedVector.hpp>

class Node : public std::enable_shared_from_this<Node>
{
public:
    virtual ~Node() = default;

    void visit();
    void addNode(std::shared_ptr<Node> node);
    void removeNode(std::shared_ptr<Node> node);
    void removeFromParent();

    std::shared_ptr<Node> getParent();

protected:
    virtual void visitSelf() {};

    std::shared_ptr<Node> _parent;
    ProtectedVector<std::shared_ptr<Node>> _nodes;
};


#endif //GAME_NODE_HPP
