#include "Node.hpp"
#include "Link.hpp"

// (-+)
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




// if  INT_MAX , return "INF"
// (-+)
std::string normInt(int val)
{
    std::string resultStr = std::string();

    if(val == INT_MAX) {
        resultStr.append("INF");
    } else {
        resultStr = std::to_string(val);
    }

    return resultStr;

}


// Displays the neighbor nodes of this node, the weights and the dijkstra labels
//
// (--)
void Node::dump(int indent)
{


    std::string ind = "";
    for(int n = 0; n < indent; n++) {
        ind += " ";
    }

    // Find out what neighbors to Node exists
    bool hasUp = false;
    bool hasRight = false;
    bool hasDown = false;
    bool hasLeft = false;
    if(up->to != nullptr) { hasUp = true; }
    if(right->to != nullptr) { hasRight= true; }
    if(down->to != nullptr) { hasDown= true; }
    if(left->to != nullptr) { hasLeft= true; }



    std::cout << "\n";


    std::stringstream up1; std::stringstream up2; std::stringstream up3;
    std::stringstream mid1; std::stringstream mid2; std::stringstream mid3;


    if(hasUp) {
        up1 << "\ttemp=" << normInt(up->to->tempLabel);
        up2 << "\t" << up->to->getName() << "\t\t";
        up3 << "\tperm=" << normInt(up->to->permanentLabel);
    } else {
        up1.clear();
        up2 << "\tNULL";
        up3.clear();
    }

    mid1 << "+--------+";
    mid2 << "| " << this->getName() << " |";
    mid3 << "+--------+";




/*
                       temp=INF
                       (1,0)
                       perm=INF
                       +--------+              temp=F
       NULL            | (2,0)  |              (2,1)
                       +--------+              perm=F
                       temp=F
                       (3,0)
                       perm=F

*/





    std::cout << ind << up1.str() << "\n";
    std::cout << ind << up2.str() << "\n";
    std::cout << ind << up3.str() << "\n";
    std::cout << ind << "" << mid1.str() << "" << "\n";
    std::cout << ind << "" << mid2.str() << "" << "\n";
    std::cout << ind << "" << mid3.str() << "" << "\n";
    /*
    std::cout << ind << downStr1 << "\n";
    std::cout << ind << downStr2<< "\n";
    std::cout << ind << downStr3<< "\n";*/















/*



    if(hasUp) {
         upStr1 = "\t\t\ttemp=" + normInt(up->to->tempLabel);
         upStr2 = "\t\t\t" + up->to->getName();
         upStr3 = "\t\t\tperm=" + normInt(up->to->permanentLabel);
    } else {
        upStr1 = "";
        upStr2 = "\t\t\tNULL";
        upStr3 = "";
    }

    if(hasRight) {
            rightStr1 = "\t\ttemp=" + normInt(right->to->tempLabel);
            rightStr2 = "\t\t" + right->to->getName();
            rightStr3 = "\t\tperm=" + normInt(right->to->permanentLabel);
    } else {
        rightStr1 = "";
        rightStr2 = "\t\t\tNULL";
        rightStr3 = "";
    }

    if(hasDown) {
        downStr1 = "\t\t\ttemp=" + normInt(down->to->tempLabel);
        downStr2 = "\t\t\t" + down->to->getName();
        downStr3 = "\t\t\tperm=" + normInt(down->to->permanentLabel);
    } else {
        downStr1 = "";
        downStr2 = "\t\t\tNULL";
        downStr3 = "";
    }

    if(hasLeft) {
        leftStr1    = "temp=" + normInt(left->to->tempLabel) + "\t\t" ;
        leftStr2    = "" + left->to->getName();
        leftStr2    += " -- " + left->weight;
        leftStr2    += " --- \t";
        leftStr3    = "perm=" + normInt(left->to->permanentLabel) + "\t\t";
    } else {
        leftStr1 = "\t\t\t";
        leftStr2 = "\tNULL\t\t";
        leftStr3 = "\t\t\t";
    }

    middleStr1  = "+--------+";
    middleStr2  = "| " + this->getName() + "  |";
    middleStr3  = "+--------+";




    std::cout << ind << upStr1 << "\n";
    std::cout << ind << upStr2 << "\n";
    std::cout << ind << upStr3 << "\n";
    std::cout << ind << leftStr1 << middleStr1 << rightStr1 << "\n";
    std::cout << ind << leftStr2 << middleStr2 << rightStr2 << "\n";
    std::cout << ind << leftStr3 << middleStr3 << rightStr3 << "\n";
    std::cout << ind << downStr1 << "\n";
    std::cout << ind << downStr2<< "\n";
    std::cout << ind << downStr3<< "\n";
*/




    std::cout << "\n\n";


}



/// FIXME: Should be via Graph instead... you should call it from Graph::attachNewNode( and supply a BST *visitedNodes ) so you can
/// search for the _id and see if it's already in the tree and yeah warn at least?
///
/// Return nullptr on error, otherwise the new node we created
// (--)
Node *Node::attachNewNode(std::string _name, int _id, Vector2f _iso_pos, int weight1, int weight2, int debugLevel)
{
    int result = 0;

    if(_id < 0){
        std::cout << cn << " Warning!  attachNewNode got id < 0 !\n";
        return nullptr;
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

    result = connectNodes(this, newNode, relDir, weight1, weight2, debugLevel);


    if(result == -1) {
        std::cout << cn << " ERROR! Could not connect nodes.\n";
        return nullptr;
    }



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
    fastestPrevNode = nullptr;
}





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
/// reldir is link going from first to second
/// weight1 is for weight from first to second
/// weight2 is for weight from second to first
/// Return 0 on OK, -1 on FAIL
//(-+)
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











