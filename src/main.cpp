#include <iostream>
#include <sstream>

#include <queue>
#include <vector>


#include "BinarySearchTree.hpp"

#include "Graph.hpp"

#include "Vector2f.hpp"



void testPrioQueue()
{
    std::priority_queue<Node *, std::vector<Node *>, graphNodeCompare> my_min_heap;

    Node *road1 = new Node("A", 1);
    road1->tempLabel = 6;
    Node *road2 = new Node("B", 2);
    road2->tempLabel = 21;
    Node *road3 = new Node("C", 3);
    road3->tempLabel = 26;
    Node *road4 = new Node("C", 4);
    road4->tempLabel = 1;
    Node *road5 = new Node("C", 5);
    road5->tempLabel = 5;
    Node *road6 = new Node("C", 6);
    road6->tempLabel = 3;
    Node *road7 = new Node("C", 7);
    road7->tempLabel = 7;

    my_min_heap.push(road1);
    my_min_heap.push(road2);
    my_min_heap.push(road3);
    my_min_heap.push(road4);
    my_min_heap.push(road5);
    my_min_heap.push(road6);
    my_min_heap.push(road7);

    for(int n = 0; n < 7; n++) {
        Node *workNode = nullptr;

        workNode = my_min_heap.top();
        my_min_heap.pop();
        std::cout << "id=" << workNode->getId()  << "\n";


    }




}

// (--)
std::string iso_to_str(Vector2f iso_pos)
{
    std::stringstream sstm;

    sstm << "(" << iso_pos.y << "," << iso_pos.x << ")";

    return sstm.str();
}

// (-+)
int generateID(Vector2f iso_pos)
{
    if(iso_pos.y < 0) {
        std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
        return -1;
    }

    if(iso_pos.x < 0) {
        std::cout << "ERROR Cannot generateID from negative nrs in iso_pos!\n";
        return -1;
    }

    return iso_pos.y * 10000 + iso_pos.x;

}








int main(int argc, char *argv[])
{




    //testPrioQueue();


    int searchId;
    Vector2f iso_pos ;


    // make your own salads


    // Todo: bedöma vilken av Right Left Up Down den ska använda baserat på jämföra mellan NOD1 och NOD2 i iso_pos.
    // en funktion som jämför två iso_pos och kommer fram till en av de fyra




    Graph *roads = new Graph("road_network_1");


    /// 0,1     SPECIAL FIRST

    // create the first road
    iso_pos = Vector2f();  iso_pos.y = 0; iso_pos.x = 1; searchId = generateID(iso_pos);
    roads->addFirstNode(iso_to_str(iso_pos), searchId);





    // Now add a lot of roads to this road
    Node *road1 =     roads->findNode(searchId,0);

    if(road1 == nullptr) {
        std::cout << "error\n";
        return -1;
    }


    /// 1,1
    iso_pos = Vector2f(); iso_pos.y = 1; iso_pos.x = 1; searchId = generateID(iso_pos);
    Node *road2 = road1->attachNewNodeDown(iso_to_str(iso_pos), searchId);


    /// 1,0
    iso_pos = Vector2f(); iso_pos.y = 1; iso_pos.x = 0; searchId = generateID(iso_pos);
    Node *road3 = road2->attachNewNodeLeft(iso_to_str(iso_pos), searchId);



    /// 2,1
    iso_pos = Vector2f();    iso_pos.y = 2;    iso_pos.x = 1;  searchId = generateID(iso_pos);
    Node *road4 = road2->attachNewNodeDown(iso_to_str(iso_pos), searchId);



    /// 3,1
    iso_pos = Vector2f();    iso_pos.y = 3;    iso_pos.x = 1;  searchId = generateID(iso_pos);
    Node *road5 = road4->attachNewNodeDown(iso_to_str(iso_pos), searchId);


    /// 3,2
    iso_pos = Vector2f();    iso_pos.y = 3;    iso_pos.x = 2;  searchId = generateID(iso_pos);
    Node *road6 = road5->attachNewNodeRight(iso_to_str(iso_pos), searchId);

    /// 3,3
    iso_pos = Vector2f();    iso_pos.y = 3;    iso_pos.x = 3;  searchId = generateID(iso_pos);
    Node *road7 = road6->attachNewNodeRight(iso_to_str(iso_pos), searchId);

    /// 3,4
    iso_pos = Vector2f();    iso_pos.y = 3;    iso_pos.x = 4;  searchId = generateID(iso_pos);
    Node *road8 = road7->attachNewNodeRight(iso_to_str(iso_pos), searchId);

    /// 2,4
    iso_pos = Vector2f();    iso_pos.y = 2;    iso_pos.x = 4;  searchId = generateID(iso_pos);
    Node *road9 = road8->attachNewNodeUp(iso_to_str(iso_pos), searchId);


    /// 1,4
    iso_pos = Vector2f();    iso_pos.y = 1;    iso_pos.x = 4;  searchId = generateID(iso_pos);
    Node *road10 = road9->attachNewNodeUp(iso_to_str(iso_pos), searchId);

    /// 1,3
    iso_pos = Vector2f();    iso_pos.y = 1;    iso_pos.x = 3;  searchId = generateID(iso_pos);
    Node *road11 = road10->attachNewNodeLeft(iso_to_str(iso_pos), searchId);

    /// 1,2
    iso_pos = Vector2f();    iso_pos.y = 1;    iso_pos.x = 2;  searchId = generateID(iso_pos);
    Node *road12 = road11->attachNewNodeLeft(iso_to_str(iso_pos), searchId);

    /// 0,4
    iso_pos = Vector2f();    iso_pos.y = 0;    iso_pos.x = 4;  searchId = generateID(iso_pos);
    Node *road13 = road10->attachNewNodeUp(iso_to_str(iso_pos), searchId);

    /// 1,5
    iso_pos = Vector2f();    iso_pos.y = 1;    iso_pos.x = 5;  searchId = generateID(iso_pos);
    Node *road14 = road10->attachNewNodeRight(iso_to_str(iso_pos), searchId);


    // Bind the gap!
    road2->attachNodeRight(road12);
    std::cout << "\n\n ** graph created!\n";


    // Setup a high weight on a link
    road12->right->weight = 5;





    // dump entire graph
    //roads->dump(0);



    std::cout << "\n\n Running Dijkstra:\n";



    // Setup start and end positions for Dijkstra

    iso_pos.y = 3;
    iso_pos.x = 1;
    Node *startNode = roads->findNode( generateID(iso_pos), 0);

    iso_pos.y = 1;
    iso_pos.x = 2;
    Node *endNode   = roads->findNode ( generateID(iso_pos) , 0);

    if(startNode == nullptr || endNode == nullptr) {
        std::cout << "ERROR! Could not find the start or end node for Dijkstra\n";
        return 0;
    }

    std::cout << " startNode.id=" << startNode->getId() << "\n";
    std::cout << " endNode.id= " << endNode->getId() << "\n";



    /// CRASHES WHEN debugLevel = 0 !! some code is within debuglevel>=1{} blocks
    ResultSet *dijkstraResult = roads->runDijkstra(startNode, endNode,0);

    if(dijkstraResult->shortestPath.empty()) {
        return 0;
    }

    std::cout << "The shortest distance is=" << dijkstraResult->resultInt << "\n";
    std::cout << "The path is: \n    ";

    // Look at the result
    while( ! (dijkstraResult->shortestPath.empty()) )
    {
        std::cout << dijkstraResult->shortestPath.top()->getName() << " ===>  " ;
        dijkstraResult->shortestPath.pop();

    }
    std::cout << "\n";




    return 0;

}


















