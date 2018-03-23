#include "Node.hpp"
#include "Link.hpp"
Node::Node(std::string _name, int _id)
{
    name = _name;
    id = _id;

    up = new Link();
    up->weight = 1;
    right = new Link();
    right->weight = 1;
    down = new Link();
    down->weight = 1;
    left = new Link();
    left->weight = 1;


    resetForDijkstra();
}




Node *Node::attachNewNodeUp(std::string _name, int _id)
{
    Node *newNode = new Node(_name, _id);

    // attach it downwards to current node (this)
    this->up->from = this;
    this->up->to = newNode;

    newNode->down->from = newNode;        // also connect the new node upwards to our current node (doubly linked)
    newNode->down->to = this;

    return newNode;

}

void Node::resetForDijkstra()
{
    permanentLabel = INT_MAX;    // Set to INFINITY
    tempLabel = INT_MAX;
}

Node *Node::attachNewNodeRight(std::string _name, int _id)
{
    Node *newNode = new Node(_name, _id);

    // attach it downwards to current node (this)
    this->right->from = this;
    this->right->to = newNode;

    newNode->left->from = newNode;
    newNode->left->to = this;

    return newNode;

}




// Test more!

/// Returns the new Node
// (--)
Node *Node::attachNewNodeDown(std::string _name, int _id)
{
    Node *newNode = new Node(_name, _id);

    // attach it downwards to current node (this)
    this->down->from = this;
    this->down->to = newNode;

    newNode->up->from = newNode;
    newNode->up->to = this;

    return newNode;

}






///
/// Simply attach
///


//test!
// (--)
void Node::attachNodeUp(Node *other)
{
    this->up->to = other;
    this->up->from = this;

    other->down->to = this;
    other->down->from = other;

}


//test!
// (--)
void Node::attachNodeRight(Node *other)
{
    this->right->to = other;
    this->right->from = this;

    other->left->to = this;
    other->left->from = other;

}


//test!
// (--)
void Node::attachNodeDown(Node *other)
{
    this->down->to = other;
    this->down->from = this;

    other->up->to = this;
    other->up->from = other;

}


//test!
// (--)
void Node::attachNodeLeft(Node *other)
{
    this->left->to = other;
    this->left->from = this;

    other->right->to = this;
    other->right->from = other;

}

///
/// Create while you attach!
///

// Test more!

/// Returns the new Node
// (--)
Node *Node::attachNewNodeLeft(std::string _name, int _id)
{
    Node *newNode = new Node(_name, _id);

    // attach it downwards to current node (this)
    this->left->from = this;
    this->left->to = newNode;

    newNode->right->from = newNode;
    newNode->right->to = this;

    return newNode;

}







int Node::getId()
{
    return id;
}

std::string Node::getName()
{
    return name;
}















