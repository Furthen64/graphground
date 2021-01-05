#include <iostream>
#include <sstream>

#include <queue>
#include <vector>


#include "BinarySearchTree.hpp"
#include "CityCreator.hpp"

#include "Graph.hpp"



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



std::stack <Vector2f> *reverseStack(std::stack <Vector2f> *stacker)
{

    std::stack <Vector2f> *newStacker  = new std::stack <Vector2f>();

    while(!stacker->empty()) {

        newStacker->push( stacker->top() );

        stacker->pop();
    }

    return newStacker;


}






int main(int argc, char *argv[])
{


    Vector2f city_pos;
    city_pos.y = 5;
    city_pos.x = 5;
    int createSteps = 4;

    CityCreator *cityCreator = new CityCreator();

//    HurkaMatrixV1 *city =  cityCreator->createCity(city_pos, createSteps);






    int searchId = -1;
    Vector2f iso_pos ;
    iso_pos.y = -1;
    iso_pos.x = -1;
    Node *workNode = nullptr;
    Node *workNode2 = nullptr;

    DijkstraResult *dijkstraResult = nullptr;


    std::cout << "\nTesting the Graph by creating a complex road network \n";
    std::cout << "and running Dijkstra from A to B \n-------------------------------------------------------\n";

    Graph *roads = new Graph("road_network_1");


    /// 0,1     SPECIAL FIRST

    // create the first road
    iso_pos = Vector2f();  iso_pos.y = 0; iso_pos.x = 0; searchId = generateID(iso_pos);
    roads->addFirstNode(iso_to_str(iso_pos), searchId, iso_pos);


    // Now add a lot of roads to this road
    Node *road1 = roads->findNode(searchId,0);
    if(road1 == nullptr) { std::cout << "error\n";  return -1;  }


    // Push lots of positions to a stack
    std::stack<Vector2f > possies;


    // All of the positions in order of attachment!
    iso_pos.y = 1; iso_pos.x = 0;    possies.push(iso_pos);
    iso_pos.y = 1; iso_pos.x = 1;    possies.push(iso_pos);
    iso_pos.y = 1; iso_pos.x = 2;    possies.push(iso_pos);
    iso_pos.y = 2; iso_pos.x = 2;    possies.push(iso_pos);
    iso_pos.y = 2; iso_pos.x = 1;    possies.push(iso_pos);
    iso_pos.y = 2; iso_pos.x = 0;    possies.push(iso_pos);
    iso_pos.y = 3; iso_pos.x = 0;    possies.push(iso_pos);
    iso_pos.y = 3; iso_pos.x = 1;    possies.push(iso_pos);
    iso_pos.y = 3; iso_pos.x = 2;    possies.push(iso_pos);

    iso_pos.y = 4; iso_pos.x = 2;    possies.push(iso_pos);

    iso_pos.y = 5; iso_pos.x = 2;    possies.push(iso_pos);
    iso_pos.y = 5; iso_pos.x = 3;    possies.push(iso_pos);
    iso_pos.y = 5; iso_pos.x = 4;    possies.push(iso_pos);
    iso_pos.y = 6; iso_pos.x = 4;    possies.push(iso_pos);
    iso_pos.y = 6; iso_pos.x = 3;    possies.push(iso_pos);
    iso_pos.y = 6; iso_pos.x = 2;    possies.push(iso_pos);
    iso_pos.y = 7; iso_pos.x = 2;    possies.push(iso_pos);
    iso_pos.y = 7; iso_pos.x = 3;    possies.push(iso_pos);
    iso_pos.y = 7; iso_pos.x = 4;    possies.push(iso_pos);

    iso_pos.y = 8; iso_pos.x = 4;    possies.push(iso_pos);

    std::stack<Vector2f> *finalPossies = reverseStack(&possies);



    /// Pop the stack and bind them all together, like a snake moving through the road network

    workNode = road1;   // start at the first road node
    while(!finalPossies->empty()) {
        iso_pos = finalPossies->top();
        finalPossies->pop();
        searchId = generateID(iso_pos);

        workNode = workNode->attachNewNode(iso_to_str(iso_pos), searchId, iso_pos, 1,1, 0);

    }


    /// Bind the things that weren't connected automatically
    iso_pos.y = 1; iso_pos.x = 0; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 2; iso_pos.x = 0; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);


    iso_pos.y = 1; iso_pos.x = 1; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 2; iso_pos.x = 1; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 2; iso_pos.x = 1; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 3; iso_pos.x = 1; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 2; iso_pos.x = 2; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 3; iso_pos.x = 2; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 5; iso_pos.x = 2; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 6; iso_pos.x = 2; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 5; iso_pos.x = 3; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 6; iso_pos.x = 3; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 6; iso_pos.x = 3; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 7; iso_pos.x = 3; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);

    iso_pos.y = 6; iso_pos.x = 4; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    iso_pos.y = 7; iso_pos.x = 4; searchId = generateID(iso_pos);    workNode2 = roads->findNode(searchId, 0);
    workNode->attachNodeDown(workNode2);


    std::cout << "\n\nGraph created:\n---------------------------------\n";


    std::cout << "\n\nRunning Dijkstra 1st time:\n------------------------------\n";


    // Setup start and end positions for Dijkstra

    iso_pos.y = 0;
    iso_pos.x = 0;
    Node *startNode = roads->findNode( generateID(iso_pos), 0);


    iso_pos.y = 8;
    iso_pos.x = 4;
    Node *endNode   = roads->findNode ( generateID(iso_pos) , 0);

    if(startNode == nullptr || endNode == nullptr) {
        std::cout << "ERROR! Could not find the start or end node for Dijkstra\n";
        return 0;
    }

    std::cout << "  * startNode.id=" << startNode->getId() << "\n";
    std::cout << "  * endNode.id= " << endNode->getId() << "\n";


    dijkstraResult = roads->runDijkstra(startNode, endNode, 2);

    if(dijkstraResult->shortestPath.empty()) {
        return 0;
    }

    std::cout << "\n";
    std::cout << "The shortest distance is=" << dijkstraResult->resultInt << "\n";







    std::cout << "\n\nTesting dijkstraResult->getShortestPathStack()\n";

    std::stack<Node *> *myStack = dijkstraResult->getShortestPathStack();

    Node *myRef = nullptr;

    while(!myStack->empty()) {
        myRef = myStack->top();
        std::cout << myRef->getName() << "---";
        myStack->pop();
    }

    std::cout << "\n\n\n";






    std::cout << "The path is: \n    ";
    roads->printPathFromDijkstra(dijkstraResult);

    std::cout << "\n";





    std::cout << "\n\nReset all nodes\n-------------------------------\n";
    roads->dump(0, 1);

    roads->resetAllNodes();
    std::cout << "\n\n\n ***** Should be reseted ****\n\n\n";

    roads->dump(0, 1 );





    std::cout << "\n\nTry Dijkstra again, reverse path\n--------------------------\n";

     // Setup start and end positions for Dijkstra

    iso_pos.y = 8;
    iso_pos.x = 4;
    startNode = roads->findNode( generateID(iso_pos), 0);


    iso_pos.y = 0;
    iso_pos.x = 0;
    endNode   = roads->findNode ( generateID(iso_pos) , 0);

    if(startNode == nullptr || endNode == nullptr) {
        std::cout << "ERROR! Could not find the start or end node for Dijkstra\n";
        return 0;
    }

    std::cout << "  * startNode.id=" << startNode->getId() << "\n";
    std::cout << "  * endNode.id= " << endNode->getId() << "\n";



    dijkstraResult = roads->runDijkstra(startNode, endNode, 0);


    if(dijkstraResult->shortestPath.empty()) {
        return 0;
    }

    std::cout << "\n";
    std::cout << "The shortest distance is=" << dijkstraResult->resultInt << "\n";
    std::cout << "The path is: \n    ";

    roads->printPathFromDijkstra(dijkstraResult);

    std::cout << "\n";









    std::cout << "\n\nReset all nodes\n-------------------------------\n";

    roads->resetAllNodes();
    std::cout << "\n\n\n ***** Should be reseted ****\n\n\n";







    //
    std::cout << "\n\n Add HIGH WEIGHT on 3,0->3,1  ***************\n";
    iso_pos.y = 3; iso_pos.x = 0; searchId = generateID(iso_pos);    workNode = roads->findNode(searchId, 0);
    workNode->right->weight = 50;
    workNode->right->to->left->weight = 50;     // Both direction















    std::cout << "\n\nRun Dijkstra 3rd time ***********************\n";


     // Setup start and end positions for Dijkstra

    iso_pos.y = 8;
    iso_pos.x = 4;
    startNode = roads->findNode( generateID(iso_pos), 0);


    iso_pos.y = 0;
    iso_pos.x = 0;
    endNode   = roads->findNode ( generateID(iso_pos) , 0);

    if(startNode == nullptr || endNode == nullptr) {
        std::cout << "ERROR! Could not find the start or end node for Dijkstra\n";
        return 0;
    }

    std::cout << "  * startNode.id=" << startNode->getId() << "\n";
    std::cout << "  * endNode.id= " << endNode->getId() << "\n";



    dijkstraResult = roads->runDijkstra(startNode, endNode, 0);


    if(dijkstraResult->shortestPath.empty()) {
        return 0;
    }

    std::cout << "\n";
    std::cout << "The shortest distance is=" << dijkstraResult->resultInt << "\n";
    std::cout << "The path is: \n    ";

    roads->printPathFromDijkstra(dijkstraResult);

    std::cout << "\n";



    return 0;

}
















