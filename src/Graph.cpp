#include "Graph.hpp"

Graph::Graph(std::string _name)
{

    name = _name;


}



// Ojsan vad den h�r kommer beh�va TESTANDE
// Skulle vara fantastiskt om den kunde plottas.... med en matris som populeras och returneras
// (-+)
HurkaMatrixV1 *Graph::clockwiseTraverseUpFirst(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, int debugLevel)
{

    // Go clockwise from Top
    // TOP
    //      RIGHT
    //              DOWN
    //                          LEFT



    // Have we already visited this node?
    int result = visited->findVal(curr->getId(), 0 );



    if(result == -1) {

        // Never seen this node before, output its value
        int m = 0;
        int n = 0;

        curr->idTo_iso_pos(curr->getId(), &m, &n);
        matrix->matrix[m][n] = 1;


        std::cout << "curr id = " << curr->getId() << ", name = \"" << curr->getName() << "\"\n";

        // add to visited
        visited->add(curr->getId(), debugLevel);

        /// Up
        if(curr->up->to != nullptr) {

            clockwiseTraverseUpFirst(curr->up->to, visited, matrix, debugLevel);
        }

        /// Right
        if(curr->right->to != nullptr) {

            clockwiseTraverseUpFirst(curr->right->to, visited, matrix, debugLevel);

        }

        /// Down
        if(curr->down->to != nullptr) {

            clockwiseTraverseUpFirst(curr->down->to, visited, matrix, debugLevel);

        }

        /// Left
        if(curr->left->to != nullptr) {

            clockwiseTraverseUpFirst(curr->left->to, visited, matrix, debugLevel);

        }



    } else {

        // already been here
        if(debugLevel >= 1) {
            std::cout << "already been here\n";
        }
    }

    return matrix;
}



// Wishlist: Remove the Matrix after you're done with this. Remove all unecesseary outputs
// TEST
// (--)
Node *Graph::clockwiseTraverseUpFirstFindNode(Node *curr, BinarySearchTree *visited, HurkaMatrixV1 *matrix, int searchId, int debugLevel)
{


    Node *resultNode = nullptr;   /// THINK ABOUT THIS and life cycle through recursion! should it be passed along?


    // Go clockwise from Top
    // TOP
    //      RIGHT
    //              DOWN
    //                          LEFT



    // Have we already visited this node?
    int result = visited->findVal(curr->getId(), 0 );



    if(result == -1) {

        // Never seen this node before, check its value against searchId
        int m = 0;
        int n = 0;

        if(curr->getId() == searchId) {

            if(debugLevel >= 1) { std::cout << " ! Found it \n"; }

            // Mark it in the matrix
            curr->idTo_iso_pos(curr->getId(), &m, &n);
            matrix->matrix[m][n] = 2;

            return curr;
        } else {
            if(debugLevel >= 1) {  std::cout << "    no match on " << curr->getId() << "\n"; }
        }



        curr->idTo_iso_pos(curr->getId(), &m, &n);
        matrix->matrix[m][n] = 1;


        if(debugLevel >= 1) {  std::cout << "    curr id = " << curr->getId() << ", name = \"" << curr->getName() << "\"\n"; }

        // add to visited
        visited->add(curr->getId(), debugLevel);

        /// Up
        if(curr->up->to != nullptr) {

            resultNode = clockwiseTraverseUpFirstFindNode(curr->up->to, visited, matrix, searchId, debugLevel);
        }

        if(resultNode != nullptr) {
            return resultNode;
        }

        /// Right
        if(curr->right->to != nullptr) {

            resultNode = clockwiseTraverseUpFirstFindNode(curr->right->to, visited, matrix, searchId, debugLevel);

        }

        if(resultNode != nullptr) {
            return resultNode;
        }

        /// Down
        if(curr->down->to != nullptr) {

            resultNode = clockwiseTraverseUpFirstFindNode(curr->down->to, visited, matrix, searchId, debugLevel);

        }

        if(resultNode != nullptr) {
            return resultNode;
        }

        /// Left
        if(curr->left->to != nullptr) {

            resultNode = clockwiseTraverseUpFirstFindNode(curr->left->to, visited, matrix, searchId, debugLevel);

        }

        if(resultNode != nullptr) {
            return resultNode;
        }



    } else {

        // already been here
        if(debugLevel >= 1) {
            std::cout << "already been here\n";
        }
    }


    return resultNode;




}




// (--)
void clockwiseSearchUpFirst(Node *curr, int searchVal)
{
    std::cout << "\n\nNOT DONE!!! :(\n\n";

}


// (--)
void Graph::dump(int debugLevel)
{
    std::cout << "\n\nDumping Graph:\n";

    BinarySearchTree *visited = new BinarySearchTree();

    HurkaMatrixV1 *matrix = new HurkaMatrixV1(16,16);

    matrix = clockwiseTraverseUpFirst(head, visited, matrix, debugLevel);


    matrix->dump();
}


// (--)
void Graph::addFirstNode(std::string _name, int _id)
{
    head =  new Node(_name, _id);
}


// (--)
Node *Graph::getFirstNode()
{
    return head;
}



/// Walks the graph in one thread and return the node, return nullptr if not found
// (-+)     Seems to work with head and most of the nodes I tried
Node *Graph::findNode(int searchId, int debugLevel)
{

    if(searchId < 0) {
        std::cout << cn << " ERROR! Trying findNode with a negative searchId=" << searchId << "\n";
    }

    if(debugLevel >=1) {std::cout << "\n\n *** Searching the Graph for searchId= " << searchId << "\n ------------------------\n";}


    /// Is it the head?

    if(head != nullptr) {
        if(head->getId() == searchId) {
            if(debugLevel >=1) {std::cout << "  Found it!\n";}
            return head;
        }
    }



   /// Find the Node* and return it


    BinarySearchTree *visited = new BinarySearchTree();

    HurkaMatrixV1 *matrix = new HurkaMatrixV1(16,16);  // For output!

    Node *foundNode = clockwiseTraverseUpFirstFindNode(head, visited, matrix, searchId, debugLevel);

    if(foundNode == nullptr) {
        std::cout << cn << " ERROR! Could not find a node with id=" << searchId << " in the graph \n";
    }

    if(debugLevel >= 2) {
        matrix->dump();
    }

    return foundNode;

}



/// Testa med 10001 och testa med 00001 de tv� f�rsta som headers. se om det fortfarande fungerar!!


    /// Vore bra hitta p� ngt scenario d�r man m�ste r�kna om templabels p� n�gon interesection i v�gn�tet!

    /// Vore bra om Dijkstra slutade N�R den har .permanentLabel= p� EndNode ? matcha mot endnode vid permanent och g�r en exit d�r


    /// Detta m�ste g�ras i setup-steget ocks�! G�rs det?
 //Now work with the node you just made Permanent "workNode".
 //Put temporary labels on each node you can reach from this node.


// TEST and TEST and Test some more!
// (--)
ResultSet *Graph::runDijkstra(Node *startNode, Node *endNode)
{

    int debugLevel = 1;
    std::string ind1 = "   ";
    std::string ind2 = "       ";
    std::string ind3 = "           ";
    std::string ind4 = "              ";



    int minWorkLabel = INT_MAX;

    Node *workNode = nullptr;

    ResultSet *result = new ResultSet();

    BinarySearchTree *visitedNodes = new BinarySearchTree();

    std::priority_queue<Node *, std::vector<Node *>, graphNodeCompare> workList;         // we need to have a prio queue to see which has the SHORTEST DISTANCE node (top prio!)







    // FIXME, TODO: resetDijkstra for all Nodes()


    /// setup the first node
    startNode->permanentLabel = 0;
    startNode->fastestPrevNode = nullptr;


    std::cout << "\n";
    std::cout << ind1 << "Setup startNode\n" << ind1 << "------------------\n";
    std::cout << ind2 << startNode->getName() << ", " << startNode->getId() << "\n";
    std::cout << ind2 << "startNode.permanent=0\n";


    /// Which vertices can we reach from the start?


    if(startNode->up->to != nullptr) {

        // assign temporary label to this node          put the distance (weight) in that box!
        startNode->up->to->tempLabel = startNode->up->weight;
        startNode->up->to->fastestPrevNode = startNode;

        if(debugLevel >= 2) { std::cout << ind2 << "startNode ----(" << startNode->up->weight << ")----> up\n";  }

        // Now that we have a temporaryLabel value, put it on the worklist
        if(debugLevel >=1) {
            std::cout << ind3 << "--> push up ( " << startNode->up->to->getName() << ", " << startNode->up->to->getId() << ")  tempLabel= " << startNode->up->to->tempLabel
            << ", fastestPrevNode= " << startNode->up->to->fastestPrevNode->getId() << "\n\n";
        }
        workList.push(startNode->up->to);
        visitedNodes->add(startNode->up->to->getId(),0);

    }
    if(startNode->right->to != nullptr) {
        // assign temporary label to this node
        startNode->right->to->tempLabel = startNode->right->weight;
        startNode->right->to->fastestPrevNode = startNode;

        if(debugLevel >= 2) { std::cout << ind2 << "startNode ----(" << startNode->right->weight << ")----> right\n";  }

        if(debugLevel >=1) {
            std::cout << ind3 << "--> push right ( " << startNode->right->to->getName() << ", " << startNode->right->to->getId() << ")  tempLabel= " << startNode->right->to->tempLabel
            << ", fastestPrevNode= " << startNode->right->to->fastestPrevNode->getId() << "\n\n";
        }
        workList.push(startNode->right->to);
        visitedNodes->add(startNode->right->to->getId(),0);



    }
    if(startNode->down->to != nullptr) {
        // assign temporary label to this node
        startNode->down->to->tempLabel = startNode->down->weight;
        startNode->down->to->fastestPrevNode = startNode;

        if(debugLevel >= 2) { std::cout << ind2 << "startNode ----(" << startNode->down->weight << ")----> down\n";  }

        if(debugLevel >=1) {
            std::cout << ind3 << "--> push down ( " << startNode->down->to->getName() << ", " << startNode->down->to->getId() << ")  tempLabel= " << startNode->down->to->tempLabel
            << ", fastestPrevNode= " << startNode->down->to->fastestPrevNode->getId() << "\n\n";
        }
        workList.push(startNode->down->to);
        visitedNodes->add(startNode->down->to->getId(),0);

    }
    if(startNode->left->to != nullptr) {
        // assign temporary label to this node
        startNode->left->to->tempLabel = startNode->left->weight;
        startNode->left->to->fastestPrevNode = startNode;

        if(debugLevel >= 2) { std::cout << ind2 << "startNode ----(" << startNode->left->weight << ")----> left\n";  }

        if(debugLevel >=1) {
            std::cout << ind3 << "--> push left ( " << startNode->left->to->getName() << ", " << startNode->left->to->getId() << ")  tempLabel= " << startNode->left->to->tempLabel
            << ", fastestPrevNode= " << startNode->left->to->fastestPrevNode->getId() << "\n\n";
        }
        workList.push(startNode->left->to);
        visitedNodes->add(startNode->left->to->getId(),0);
    }

    // startNode is now permanent
    visitedNodes->add(startNode->getId(), 0);




/*
    /// select the vertex with the smallest  temporary label and make its label permanent ...
    std::cout << "\n\n";
    std::cout << ind1 << "Find the node around the startNode with the smallest temporary label \n" << ind1 << "--------------------------\n"<< ind1<<"\n";

    // First find the smallest temporary label
    // (j�rgen adds: And dont go to already visited nodes)


    workNode = workList.top();
    workList.pop();
*/
/*
    minWorkLabel = INT_MAX;

    if(startNode->up->to != nullptr) {

        if(startNode->up->weight < minWorkLabel) {
            minWorkLabel = startNode->up->weight;
            workNode = startNode->up->to;
            if(debugLevel >=1) { std::cout << ind2 << "workNode is now   startNode->up\n"; }
            if(debugLevel >= 2) { std::cout << ind2 << "startNode->up has smallest weight. Updated minWorkLabel = " << minWorkLabel << "\n";}
        }

    }
    if(startNode->right->to != nullptr) {


        if(startNode->right->weight < minWorkLabel) {
            minWorkLabel = startNode->right->weight;
            workNode = startNode->right->to;
            if(debugLevel >=1) { std::cout << ind2 << "workNode is now   startNode->right\n"; }
            if(debugLevel >= 2) { std::cout << ind2 << "startNode->right has smallest weight. Updated minWorkLabel = " << minWorkLabel << "\n";}
        }


    }
    if(startNode->down->to != nullptr) {

        if(startNode->down->weight < minWorkLabel) {
            minWorkLabel = startNode->down->weight;
            workNode = startNode->down->to;
            if(debugLevel >=1) { std::cout << ind2 << "workNode is now   startNode->down\n"; }
            if(debugLevel >= 2) { std::cout << ind2 << "startNode->down has smallest weight. Updated minWorkLabel = " << minWorkLabel << "\n";}
        }


    }
    if(startNode->left->to != nullptr) {

        if(startNode->left->weight < minWorkLabel) {
            minWorkLabel = startNode->left->weight;
            workNode = startNode->left->to;
            if(debugLevel >=1) { std::cout << ind2 << "workNode is now   startNode->left\n"; }
            if(debugLevel >= 2) { std::cout << ind2 << "startNode->left) has smallest weight. Updated minWorkLabel = " << minWorkLabel << "\n"; }
        }
    }

    */


/*

    /// ... make its label permanent

    std::cout << ind2 << "workNode = (" << workNode->getName() << ", " << workNode->getId() << ")\n";


    workNode->permanentLabel = workNode->tempLabel;
    visitedNodes->add(workNode->getId(),0);   // Add to visited because this one is now permanent
    std::cout << ind2 << "workNode.permanent=" << workNode->permanentLabel <<  "(" << workNode->getName() << ", " << workNode->getId() << ")\n";
*/

    int steps = 0;
    int maxSteps = 400;
    int done = false;
    int lastOne = false;
    minWorkLabel = INT_MAX;






    if(debugLevel >=1 ) {
        std::cout << "\n";
        std::cout << ind1 << "Loop begins {\n" << ind1 << "--------------------\n" << ind1 << "\n";
    }

    while(!done) {



        ///
        /// Select the vertex with the smallest temporary label and
        /// make its label permanent (change worknode to this)
        ///

        if(workList.empty()){
            std::cout << ind2 << "Worklist is empty, exiting loop\n" << ind1 << "}\n";
            done = true;
            break;
        }

        if(debugLevel >= 2) {

            std::cout << "\n\n";
            std::cout << ind2<<"Get worknode from Prio Queue with the smallest temporary label and \n";
            std::cout << ind2<<"make its label permanent, change worknode to this\n";
            std::cout << ind2<<"-----------------------------------------------------------------------------\n";
        }


        // Ist�llet f�r att s�ka fr�n workNode och runtomkring
        // s�tt worknode till vad du poppar fr�n workList (prio k�n)
        workNode = workList.top();
        workList.pop();

        if(debugLevel >=1){
            std::cout << ind2 << "workNode = worklist.pop()  (" << workNode->getName() << ", " << workNode->getId() << ")\n";
        }


        /// ... make its label permanent
        workNode->permanentLabel = workNode->tempLabel;
        visitedNodes->add(workNode->getId(),0);

        if(debugLevel >=1) {
            std::cout << ind2 << "workNode.permanent = " << workNode->tempLabel << " (" << workNode->getName() << ", " << workNode->getId() << ")\n";
            std::cout << ind2 << "workNode.fastestPrevNode = " << workNode->fastestPrevNode->getId() << "\n";
        }



        std::cout << "\n";












        ///
        /// Now work with the node you just made Permanent."workNode"
        /// Put temporary labels on each node you can reach from this node
        ///

        if(debugLevel >=2) {
            std::cout << ind2 << "\n\n";
            std::cout << ind2 << "Now work with the node you just made Permanent \"workNode\". \n";
            std::cout << ind2 << "Put temporary labels on each node you can reach from this node.\n";
            std::cout << ind2 << "--------------------------------------------------------------------\n";
        } else if(debugLevel >=1) {
            std::cout << ind2 << "Look around current node, update temp labels\n";
        }


        if(workNode->up->to != nullptr) {

        ///
        /// UP
        ///

            // Is it already Permanent?

            if(workNode->up->to->permanentLabel == INT_MAX) {


                // Store sum of "permanent and direct distance from it"
                if(workNode->up->to->tempLabel > (workNode->permanentLabel + workNode->up->weight)) {

                    if(debugLevel >= 1) {
                        std::cout << ind3 << "new minimum! workNode --> up (value before=" << workNode->up->to->tempLabel << ", after=" <<
                        (workNode->permanentLabel + workNode->up->weight) << ")\n";
                    }

                    // New minimum, update tempLabel and also the fastest Prev Node
                    workNode->up->to->tempLabel = workNode->permanentLabel + workNode->up->weight;
                    workNode->up->to->fastestPrevNode = workNode;



                }


                // Now that we have a temporaryLabel value, put it on the worklist

                if(visitedNodes->findVal(workNode->up->to->getId(),0) == -1)  {

                    // did not find it , push it to work list!
                    if(debugLevel >=1) {
                        std::cout << ind3 << "--> push up ( " << workNode->up->to->getName() << ", " << workNode->up->to->getId() << ")  tempLabel= " << workNode->up->to->tempLabel
                            << ", fastestPrevNode= " << workNode->up->to->fastestPrevNode->getId() << "\n\n";
                    }

                    workList.push(workNode->up->to);
                    visitedNodes->add(workNode->up->to->getId(),0);
                }



            } else {
                if(debugLevel >=2) { std::cout << ind3 << "Already permanented: workNode->up->to\n"; }
            }
        }





        ///
        /// RIGHT
        ///



        if(workNode->right->to != nullptr) {


            if(workNode->right->to->permanentLabel == INT_MAX) {



                if(workNode->right->to->tempLabel > (workNode->permanentLabel + workNode->right->weight)) {

                    if(debugLevel >= 1) {
                        std::cout << ind3 << "new minimum! workNode --> right (value before=" << workNode->right->to->tempLabel << ", after=" <<
                        (workNode->permanentLabel + workNode->right->weight) << ")\n";
                    }

                    // New minimum, update tempLabel and also the fastest Prev Node
                    workNode->right->to->tempLabel = workNode->permanentLabel + workNode->right->weight;
                    workNode->right->to->fastestPrevNode = workNode;

                }

                // Now that we have a temporaryLabel value, put it on the worklist

                if(visitedNodes->findVal(workNode->right->to->getId(),0) == -1)  {

                    // did not find it , push it to work list!

                    std::cout << ind3 << "--> push right ( " << workNode->right->to->getName() << ", " << workNode->right->to->getId() << ")  tempLabel= " << workNode->right->to->tempLabel
                            << ", fastestPrevNode= " << workNode->right->to->fastestPrevNode->getId() << "\n\n";



                    workList.push(workNode->right->to);
                    visitedNodes->add(workNode->right->to->getId(),0);
                }




            } else {
                if(debugLevel >=2) { std::cout << ind3 << "Already permanented: workNode->right->to\n"; }
            }

        }





        ///
        /// DOWN
        ///


        if(workNode->down->to != nullptr) {

            if(workNode->down->to->permanentLabel == INT_MAX) {


                if(workNode->down->to->tempLabel > (workNode->permanentLabel + workNode->down->weight)) {


                    if(debugLevel >= 1) {
                        std::cout << ind3 << "new minimum! workNode --> down (value before=" << workNode->down->to->tempLabel << ", after=" <<
                        (workNode->permanentLabel + workNode->down->weight) << ")\n";


                    }

                    // New minimum, update tempLabel and also the fastest Prev Node
                    workNode->down->to->tempLabel = workNode->permanentLabel + workNode->down->weight;
                    workNode->down->to->fastestPrevNode = workNode;

                }



                if(visitedNodes->findVal(workNode->down->to->getId(),0) == -1)  {

                    // did not find it , push it to work list!

                   std::cout << ind3 << "--> push down ( " << workNode->down->to->getName() << ", " << workNode->down->to->getId() << ")  tempLabel= " << workNode->down->to->tempLabel
                            << ", fastestPrevNode= " << workNode->down->to->fastestPrevNode->getId() << "\n\n";

                    workList.push(workNode->down->to);
                    visitedNodes->add(workNode->down->to->getId(),0);
                }

            } else {
                if(debugLevel >=2) { std::cout << ind3 << "Already permanented: workNode->down->to\n"; }
            }


        }





        ///
        /// LEFT
        ///


        if(workNode->left->to != nullptr) {


            if(workNode->left->to->permanentLabel == INT_MAX) {


                if(workNode->left->to->tempLabel > (workNode->permanentLabel +  workNode->left->weight)) {

                    if(debugLevel >= 1) {
                        std::cout << ind3 << "new minimum! workNode --> left (value before=" << workNode->left->to->tempLabel << ", after=" <<
                        (workNode->permanentLabel + workNode->left->weight) << ")\n";
                    }

                    // New minimum, update tempLabel and also the fastest Prev Node
                    workNode->left->to->tempLabel = workNode->permanentLabel +  workNode->left->weight;
                    workNode->left->to->fastestPrevNode = workNode;
                }



                if(visitedNodes->findVal(workNode->left->to->getId(),0) == -1)  {

                    // did not find it , push it to work list!
                   std::cout << ind3 << "--> push left ( " << workNode->left->to->getName() << ", " << workNode->left->to->getId() << ")  tempLabel= " << workNode->left->to->tempLabel
                            << ", fastestPrevNode= " << workNode->left->to->fastestPrevNode->getId() << "\n\n";


                    workList.push(workNode->left->to);
                    visitedNodes->add(workNode->left->to->getId(),0);
                }


            } else {
               if(debugLevel >=2) { std::cout << ind3 << "Already permanented: workNode->left->to\n"; }

            }


        }


        ///
        /// Exiting ?
        ///

        steps++;

        if(steps > maxSteps) {
            done = true;
        }



        // Step 2 in exiting
        if(lastOne && workList.empty() ) {
            done = true;
        }

        // Step 1  in exiting
        if(workList.empty() == true) {
            lastOne = true;
        }



    }



    ///
    /// Return the result
    ///

    workNode = endNode;
    std::cout << ind1 << "Result output\n";
    std::cout << ind1 << "--------------------------\n";


    std::stack <int> outputs;
    int weightTotal = 0;
    std::cout << "\n\nGet the right weight!\n\n\n";


    while(workNode != nullptr) {

            std::cout << workNode->getId() << " has fastestPrevNode= " << workNode->fastestPrevNode << "!\n";

            outputs.push(workNode->getId());

            // weightTotal += // FIXME TODO find out the link between these two nodes and get the weight in the link between them, also the direction matters

            workNode = workNode->fastestPrevNode;

            if(workNode->getId() == startNode->getId()) {
                // add the last one
                outputs.push(workNode->getId());
                workNode = nullptr; // End search
            }

    }



    while(!outputs.empty()) {
        std::cout << outputs.top() << " => " ;
        outputs.pop();
    }

    std::cout << "\n";

    return result;

}