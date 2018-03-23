#include <string>
#include <iostream>
#include <climits>


class Link; // Forward declaration




// A very HEAVY class
// Its use with the Dijkstra algorithm makes it so that we need to overload the "<" operator
// in order to put it in a prio queue

// It also has some member labels for the algorithm to work (labels)
class Node
{
public:
    Node(std::string _name, int _id);
    void createLink();

    void attachNodeUp(Node *other);
    void attachNodeRight(Node *other);
    void attachNodeDown(Node *other);
    void attachNodeLeft(Node *other);

    Node *attachNewNodeUp(std::string _name, int _id);
    Node *attachNewNodeRight(std::string _name, int _id);
    Node *attachNewNodeDown(std::string _name, int _id);
    Node *attachNewNodeLeft(std::string _name, int _id);



    int getId();
    std::string getName();
    void resetForDijkstra();





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
};
