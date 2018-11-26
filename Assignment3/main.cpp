//
//  main.cpp
//  MovingBrick
//
//  Created by Tushar Chawla on 10/9/17.
//  Copyright © 2017 Tushar Chawla. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Node.cpp"
#include <map>
#include <random>
#include <iterator>
#include <queue>
#include <stack>
#include <time.h>
#include <limits>

using namespace std;

void traceAndPrintPath(Node* goal, int nodesVisited){
    vector<Move> movesMade;
    Node* current = goal;
    Puzzle lastState = current->getValue();
    while(current->hasParent()){
        movesMade.push_back(current->getMove());
        current = current->getParent();
    }
    for (int i=movesMade.size()-1; i>=0; i--){
        movesMade[i].print();
    }
    lastState.print();
    cout<<"Length of the solution: "<< movesMade.size()<<endl;
    cout<<"Number of nodes visited: "<< nodesVisited<<endl;
}

bool checkIfInClosed(vector<Node> closedNodes, Puzzle nextState){
    for (int i=0; i<closedNodes.size(); i++){
        Puzzle closedStates = closedNodes[i].getValue();
        if (nextState.checkSame(closedStates)){
            return true;
        }
        
    }
    return false;
}

bool DeapthSearch(int maxDepth, Node puzzleP, int nodesExplored){
    
    if (puzzleP.isGoal()){
        cout<<"IDS Search : "<<endl<<endl;
        traceAndPrintPath(&puzzleP, nodesExplored);
        return true;
    }
    if (maxDepth<=0){
        return false;
    }
    vector<Move> allMoves = puzzleP.getValue().getMovesList();
    for (int i=0; i<allMoves.size(); i++){
        Puzzle nextState = Puzzle::makeMoveCloning(allMoves[i]._piece, allMoves[i]._direction, puzzleP.getValue());
        
        Node childNode = Node(nextState, &puzzleP, allMoves[i]);
        if (DeapthSearch(maxDepth-1, childNode, nodesExplored+1)){
            return true;
        }
        
    }
    return false;
}

void iterativeDeapthSearch(Puzzle puzzleP){
    
    for (int d = 0  ; d <= 200 ; d++){
        bool result = DeapthSearch(d, Node(puzzleP), 0);
        if (result){
            break;
        }
    }
}

int getLowestCost(vector<Node> open){
    int cost = std::numeric_limits<int>::max();
    int position=-1;
    for (int i=0; i<open.size(); i++){
        if (open[i].getCost()<=cost){
            position = i;
            cost=open[i].getCost();
        }
    }
    return position;
}

void Astar(Puzzle puzzleP){
    int NodeNumber = 0;
    vector<Node> closedNodes;
    vector<Node> myQueue;
    Node root = Node(puzzleP, puzzleP.getHeuristic());

    myQueue.push_back(root);
    while(!myQueue.empty()){
        int lowestCostPos = getLowestCost(myQueue);
        Node* current = new Node(myQueue[lowestCostPos]);
        myQueue.erase(myQueue.begin()+lowestCostPos);
        // cout<<"parent hueristic is "<<current->getG()<<"+"<<current->getHeuristics()<<"="<<current->getCost()<<endl;
        // current->getValue().print();
        if(current->isGoal()){
            cout<<"A Star : "<<endl<<endl;
            traceAndPrintPath(current, NodeNumber);
            break;
        }
        NodeNumber++;
        closedNodes.push_back(*current);
        vector<Move> allMoves = current->getValue().getMovesList();
        // cout<<endl<<"Kids"<<endl<<endl;
        for (int i=0; i<allMoves.size(); i++){
            Puzzle nextState = Puzzle::makeMoveCloning(allMoves[i]._piece, allMoves[i]._direction, current->getValue());
            if (!checkIfInClosed(closedNodes, nextState)){
                // nextState.print();
                Node childNode = Node(nextState, current, allMoves[i], nextState.getHeuristic(), (current->getG())+1);
                // cout<<"The hueristic is "<<childNode.getG()<<"+"<<childNode.getHeuristics()<<"="<<childNode.getCost()<<endl;
                myQueue.push_back(childNode);
                closedNodes.push_back(childNode);
            }
        }
    }
}

void bredthFirstSearch(Puzzle puzzleP){
    //vector<Node> closedNodes;
    int NodeNumber = 0;
    vector<Node> closedNodes;
    queue<Node> myQueue;
    Node root = Node(puzzleP);
    myQueue.push(root);
    while(!myQueue.empty()){
        Node* current = new Node(myQueue.front());
        myQueue.pop();
        if(current->isGoal()){
            cout<<"BFS Search : "<<endl<<endl;
            traceAndPrintPath(current, NodeNumber);
            break;
        }
        NodeNumber++;
        closedNodes.push_back(*current);
        vector<Node> childrenNodes;
        vector<Move> allMoves = current->getValue().getMovesList();
        for (int i=0; i<allMoves.size(); i++){
            Puzzle nextState = Puzzle::makeMoveCloning(allMoves[i]._piece, allMoves[i]._direction, current->getValue());
            if (!checkIfInClosed(closedNodes, nextState)){
                Node childNode = Node(nextState, current, allMoves[i]);
                childrenNodes.push_back(childNode);
            }
        }
        for (int i=0; i<childrenNodes.size(); i++){
            myQueue.push(childrenNodes[i]);
        }
    }
}

void deapthFirstSearch(Puzzle puzzleP){
    int nodes=0;
    vector<Node> closedNodes;
    stack<Node> myQueue;
    Node root = Node(puzzleP);
    myQueue.push(root);
    while(!myQueue.empty()){
        Node* current = new Node(myQueue.top());
        myQueue.pop();
        if(current->isGoal()){
            cout<<"DFS Search : "<<endl<<endl;
            traceAndPrintPath(current, nodes);
            break;
        }
        nodes++;
        closedNodes.push_back(*current);
        vector<Node> childrenNodes;
        vector<Move> allMoves = current->getValue().getMovesList();
        for (int i=0; i<allMoves.size(); i++){
            Puzzle nextState = Puzzle::makeMoveCloning(allMoves[i]._piece, allMoves[i]._direction, current->getValue());
            if(!checkIfInClosed(closedNodes, nextState)){
                Node childNode = Node(nextState, current, allMoves[i]);
                childrenNodes.push_back(childNode);
            }
        }
        for (int i=0; i<childrenNodes.size(); i++){
            myQueue.push(childrenNodes[i]);
        }
    }
}



/*
 This function reads the file, gets all the data, converts the numbers into a vector<int> and returns it.
 */
vector<int> readFile(string filename){
    ifstream file;
    string line;
    string data="";
    file.open(filename);
    
    if(file.fail()){
        cout << "File failed to open." << endl;
    }
    else{
        while (file.good()) {
            getline(file, line);
            data.append(line);
            
        }
    }
    vector<int> numbers;
    stringstream ss(data);
    int i;
    while (ss >> i)
    {
        numbers.push_back(i);
        
        if (ss.peek() == ',')
            ss.ignore();
    }
    
    return numbers;
}

/*
 This function will pick a random move of all the available options.
 */
string pickRandomMove(Direction move){
    vector<string> moves;
    if (move.left){
        moves.push_back("left");
    }
    if (move.right){
        moves.push_back("right");
    }
    if (move.up){
        moves.push_back("up");
    }
    if (move.down){
        moves.push_back("down");
    }
    random_shuffle ( moves.begin(), moves.end() );
    return moves[0];
}

int main(int argc, char ** argv) {
    
    
    
    if (argc < 3)
        cout << "The 1st argument has to be filename and 2nd has to be search type."<<endl;
    else
    {
        
        vector<int> fileData = readFile(argv[1]); // getting the vector of ints from the given file.
        // int N=stoi(argv[2]); // number of moves given
        string searchType = argv[2];
        Puzzle puzzle1 = Puzzle(fileData); // making the puzzle board
        if (searchType=="bfs"){
            //clock_t tStart = clock();
            bredthFirstSearch(puzzle1);
            //printf("Time taken: %.9fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        }else if (searchType=="dfs"){
            // clock_t tStart = clock();
            deapthFirstSearch(puzzle1);
            // printf("Time taken: %.9fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        }else if (searchType=="id"){
            // clock_t tStart = clock();
            iterativeDeapthSearch(puzzle1);
           // printf("Time taken: %.9fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        }
        else if (searchType=="astar"){
            clock_t tStart = clock();
            Astar(puzzle1);
            printf("Time taken: %.9fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
        }
        else{
            cout<<"The second argument has to be dfs or bfs"<<endl;
        }
    }
    return 0;
}


