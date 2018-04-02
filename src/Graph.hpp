#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
#include <stack>
#include <queue>


#include "Node.hpp"     // Important that Node is first! Only include Node here!
#include "Link.hpp"

#include "BinarySearchTree.hpp"
#include "HurkaMatrixV1.hpp"




struct graphNodeCompare
 {
   bool operator()(Node* l, Node* r)
   {
       //std::cout <<    "                            l->templabel=" << l->tempLabel << ",   r->templabel= " << r->tempLabel << "\n";
       if( (l->tempLabel) < (r->tempLabel) ) {
            return 0;
       }
       return 1;
   }
 };


class ResultSet
{
public:

    int resultInt;
    std::string resultStr;
    std::stack<Node *> shortestPath;
    std::stack<Node *> shortestPath_memcpy;



    /// Dumps the shortest path as an array with all the id's of the nodes
    // (-+)
    void dumpShortestPath()
    {
        // Copy the shortestpath to shortestpath_memcpy
        int i = 0;

        Node *node;
        while(!shortestPath.empty()) {

            node = shortestPath.top();
            shortestPath.pop();

            std::cout << "[" << i << "] " << node->getId() << "\n";

            shortestPath_memcpy.push(node);

            i++;
        }



        // Copy back to the shortestpath
        while(!shortestPath_memcpy.empty()) {

            //shortestPath_memcpy.pop();
            node = shortestPath_memcpy.top();
            shortestPath_memcpy.pop();
            shortestPath.push(node);
        }

    }



private:

};




/*

Graph now works
2018-03-26


You can put nodes in there and build a network,
Run the Dijkstra algorithm, get results of the fastest path from A to B

You can also reset the algorithm and run it again on the same graph
with new result

For examples see:

    dijkstra_examples.cpp




*/
class Graph
{

public:
    Graph(std::string _name);

    HurkaMatrixV1 *clockwiseTraverseUpFirst(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, bool dumpNodes, int debugLevel);
    Node *         clockwiseTraverseUpFirstFindNode(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, int searchId, int debugLevel);
    void dump(int debugLevel, int dumpNodes);
    void test();
    Node *getFirstNode();
    void addFirstNode(std::string _name, int _id, Vector2f _iso_pos);
    Node *findNode(int searchId, int debugLevel);
    ResultSet *runDijkstra(Node *startNode, Node *endNode, int debugLevel);
    void printPathFromDijkstra(ResultSet *dijkstraResult);
    void traverseAndReset(Node *curr, BinarySearchTree *visited);
    void resetAllNodes();




private:

    Node *head;
    int nrNodes = 0;

    std::string name;
    std::string cn = "Graph.cpp";


};

#endif

