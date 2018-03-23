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

    // TEST!
    // (--)
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

class Graph
{

public:
    Graph(std::string _name);

    HurkaMatrixV1 *clockwiseTraverseUpFirst(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, int debugLevel);
    Node *         clockwiseTraverseUpFirstFindNode(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, int searchId, int debugLevel);
    void dump(int debugLevel);

    void test();
    Node *getFirstNode();



    void addFirstNode(std::string _name, int _id);
    Node *findNode(int searchId, int debugLevel);

    ResultSet *runDijkstra(Node *startNode, Node *endNode, int debugLevel);

private:

    Node *head;
    int nrNodes = 0;

    std::string name;
    std::string cn = "Graph.cpp";


};

#endif

