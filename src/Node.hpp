#include <string>
#include <iostream>
#include <climits>
#include <sstream>

#include "Vector2f.hpp"

class Link; // Forward declaration


enum NODE_DIR {
    dir_up,
    dir_right,
    dir_down,
    dir_left
};

// A very HEAVY class
// Its use with the Dijkstra algorithm makes it so that we need to overload the "<" operator
// in order to put it in a prio queue

// It also has some member labels for the algorithm to work (labels)
class Node
{
public:
    Node(std::string _name, int _id, Vector2f _iso_pos);
    void createLink();
    void dump(int indent);

    void attachNodeUp(Node *other);
    void attachNodeRight(Node *other);
    void attachNodeDown(Node *other);
    void attachNodeLeft(Node *other);



    Node *attachNewNode(std::string _name, int _id, Vector2f _iso_pos, int weight1, int weight2, int debugLevel);

    int getId();
    std::string getName();
    void resetForDijkstra();
    int connectNodes(Node *firstNode, Node *secondNode, int relDir, int weight1, int weight2, int debugLevel);




    /// Variables
    Link *up;
    int upLabel = INT_MAX;
    Link *right;
    int rightLabel = INT_MAX;
    Link *down;
    int downLabel = INT_MAX;
    Link *left;
    int leftLabel = INT_MAX;

    // Dijkstra stuff on top of the graph
    Node *fastestPrevNode = nullptr;
    int permanentLabel = INT_MAX;
    int tempLabel = INT_MAX;



    // Hur ska den hantera tal under 10000 ? såna där M=0
    // (--)
    static void idTo_iso_pos(int _id, int *y, int *x)
    {
        //if(_id > 10000) {
            (*y) = _id/10000;
            (*x) = _id-(10000* (*y));
        //}

    }





private:
    std::string name;
    int id;
    Vector2f iso_pos;
    std::string cn = "Node.cpp";
};
