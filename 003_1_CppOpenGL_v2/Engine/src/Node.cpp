//
// Created by Андрей Марцинкевич on 22.11.21.
//

#include "Node.hpp"

void Node::addNode(std::shared_ptr<Node> node)
{
    if (node != nullptr)
    {
        _nodes.add(std::move(node));
    }
}

void Node::removeNode(std::shared_ptr<Node> node)
{
    _nodes.remove(node);
}

void Node::removeFromParent()
{
    _parent->removeNode(shared_from_this());
}

std::shared_ptr<Node> Node::getParent()
{
    return _parent;
}

void Node::visit()
{
    this->visitSelf();
    _nodes.forEach([](auto node)
    {
        node->visit();
    });
}
