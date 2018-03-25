#include "Node.hpp"
#include "Link.hpp"

Node::Node(std::string _name, int _id, Vector2f _iso_pos)
{
    name = _name;
    id = _id;
    iso_pos = _iso_pos;

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



void Node::dump(int indent)
{
    std::string ind = "";
    for(int n = 0; n < indent; n++) {
        ind += " ";
    }
    std::cout << "\n";
    if(up->to != nullptr) {
        std::cout << ind << "  " << up->to->getName() << "\n";
    } else {
        std::cout << ind <<"     NULL      \n";

    }


    std::cout << ind << "   +--------+\n";
    std::cout << ind << "   [ " << this->getName() << "  ]\n";
    std::cout << ind << "   +--------+\n";
    if(down->to != nullptr) {
        std::cout << ind << "  " << down->to->getName() << "\n";

    } else {
        std::cout << ind << "      NULL   \n";
    }

}



/// FIXME: Should be via Graph instead... you should call it from Graph::attachNewNode( and supply a BST *visitedNodes ) so you can
/// search for the _id and see if it's already in the tree and yeah warn at least?
///
/// Return nullptr on error, otherwise the new node we created
// (--)
Node *Node::attachNewNode(std::string _name, int _id, Vector2f _iso_pos, int weight1, int weight2, int debugLevel)
{

    if(_id < 0){
        std::cout << cn << " Warning!  attachNewNode got id < 0 !\n";
    }


    if(debugLevel >= 1) {

        std::cout << "\n\nattachNewNode()\n";
        std::cout << "this node before:\n";
        this->dump(0);
    }




    Node *newNode = new Node(_name, _id, _iso_pos);

    // Find out relative positioning (up, right, down or left) to the current node


    if(debugLevel >= 1) {
        std::cout << "curr.iso_pos (" << iso_pos.y << ", " << iso_pos.x << ")    newNode.iso_pos ( " << _iso_pos.y << ", " << _iso_pos.x << ")\n";
    }
    bool aboveOf = false;

    bool rightOf = false;

    bool downOf = false;

    bool leftOf = false;

    // are we above of current node?
    if(_iso_pos.y < iso_pos.y) {
        aboveOf = true;
    }
    // are we right of current node?
    if(_iso_pos.x > iso_pos.x) {
        rightOf = true;
    }

    if(_iso_pos.y > iso_pos.y) {
        downOf = true;
    }

    if(_iso_pos.x < iso_pos.x) {
        leftOf = true;
    }


    int relDir = -1;


    if(aboveOf) {
        relDir = dir_up;
    }

    if(rightOf) {
        relDir = dir_right;
    }

    if(downOf) {
        relDir = dir_down;
    }

    if(leftOf) {
        relDir = dir_left;
    }

    connectNodes(this, newNode, relDir, weight1, weight2, debugLevel);



    if(debugLevel >=1) {
        std::cout << "                          this node after:\n";
        this->dump(20);
    }

    return newNode;

}









void Node::resetForDijkstra()
{
    permanentLabel = INT_MAX;    // Set to INFINITY
    tempLabel = INT_MAX;
}



/*

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



*/





///
/// Simply attach
///


//test!
// (--)
void Node::attachNodeUp(Node *other)
{
    if(other == nullptr) {
        std::cout << "connecting nullptr!\n";
        return ;
    }

    this->up->to = other;
    this->up->from = this;

    other->down->to = this;
    other->down->from = other;

}


//test!
// (--)
void Node::attachNodeRight(Node *other)
{
    if(other == nullptr) {
        std::cout << "connecting nullptr!\n";
        return ;
    }


    this->right->to = other;
    this->right->from = this;

    other->left->to = this;
    other->left->from = other;

}


//test!
// (--)
void Node::attachNodeDown(Node *other)
{
    if(other == nullptr) {
        std::cout << "connecting nullptr!\n";
        return ;
    }
    this->down->to = other;
    this->down->from = this;

    other->up->to = this;
    other->up->from = other;

}


//test!
// (--)
void Node::attachNodeLeft(Node *other)
{
    if(other == nullptr) {
        std::cout << "connecting nullptr!\n";
        return ;
    }

    this->left->to = other;
    this->left->from = this;

    other->right->to = this;
    other->right->from = other;

}




int Node::getId()
{
    return id;
}

std::string Node::getName()
{
    return name;
}







/// Attaches secondnode to the firstnode.
/// reldir1 is link going from first to second
/// reldir2 is reverse, going from second to first
/// weight1 is for reldir1
/// weight2 is for reldir2
/// Return 0 on OK, -1 on FAIL
// TEST!
//(--)
int Node::connectNodes(Node *firstNode, Node *secondNode, int relDir, int weight1, int weight2, int debugLevel)
{

    if(secondNode == nullptr) {
        std::cout << cn << " ERROR connectNodes failed because of one of the nodes are nullptr. Programming error!\n";
        return -1;
    }


    if(debugLevel >= 1) {
        std::cout << "\nconnectNodes(" << firstNode->getName() << ", " << secondNode->getName() << ")\n";
    }

    ///  firstNode  UP  secondNode

    if(relDir == dir_up) {

        firstNode->up->from = firstNode;
        firstNode->up->weight = weight1;
        firstNode->up->to = secondNode;

        // also connect the new node upwards to our current node (doubly linked)
        secondNode->down->from = secondNode;
        firstNode->up->weight = weight2;
        secondNode->down->to = firstNode;
    }


     ///  firstNode  RIGHT    secondNode

    if(relDir == dir_right) {

        firstNode->right->from = firstNode;
        firstNode->right->weight = weight1;
        firstNode->right->to = secondNode;

        // also connect the new node upwards to our current node (doubly linked)
        secondNode->left->from = secondNode;
        firstNode->left->weight = weight2;
        secondNode->left->to = firstNode;
    }


     ///  firstNode  DOWN    secondNode

    if(relDir == dir_down) {

        firstNode->down->from = firstNode;
        firstNode->down->weight = weight1;
        firstNode->down->to = secondNode;

        // also connect the new node upwards to our current node (doubly linked)
        secondNode->up->from = secondNode;
        firstNode->up->weight = weight2;
        secondNode->up->to = firstNode;




    }



   ///  firstNode  LEFT    secondNode

    if(relDir == dir_left) {

        firstNode->left->from = firstNode;
        firstNode->left->weight = weight1;
        firstNode->left->to = secondNode;

        // also connect the new node upwards to our current node (doubly linked)
        secondNode->right->from = secondNode;
        firstNode->right->weight = weight2;
        secondNode->right->to = firstNode;
    }




    return 0;
}











