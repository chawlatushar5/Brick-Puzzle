//
//  Node.cpp
//  MovingBrick
//
//  Created by Tushar Chawla on 10/28/17.
//  Copyright © 2017 Tushar Chawla. All rights reserved.
//

#include <stdio.h>
#include "Puzzle.cpp"
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Node{

private:
    Move _move;
    Node* _parent;
    Puzzle _value;
    int _g;
    int _h;
public:
    Node(Node* node){
        _move = node->_move;
        _parent = node->_parent;
        _value = node->_value;
        _g = node->_g;
        _h = node->_h;
    }
    


    
    Node(Puzzle value){
        _value = value;
        _parent=NULL;
        _g=0;
        _h=0;
    }
    Node(Puzzle value, int h){
        _value = value;
        _parent=NULL;
        _g=0;
        _h=h;
    }
    Node(Puzzle value, Node* parent, Move move){
        _value = value;
        _parent = parent;
        _move = move;
    }
    Node(Puzzle value, Node* parent, Move move, int h, int g){
        _value = value;
        _parent = parent;
        _move = move;
        _g=g;
        _h=h;
    }
    
    bool isGoal(){
        return _value.isFinished();
    }
    
    vector<Node> getChildrenNodes(Node *parent){
        vector<Node> childrenNodes;
        vector<Move> allMoves = _value.getMovesList();
        for (int i=0; i<allMoves.size(); i++){
            Puzzle nextState = Puzzle::makeMoveCloning(allMoves[i]._piece, allMoves[i]._direction, _value);
            Node childNode = Node(nextState, parent, allMoves[i]);
            childrenNodes.push_back(childNode);
            //Node n = Node()
        }
        return childrenNodes;
    }
    
    bool hasParent(){
        return (_parent!=NULL);
    }
    
    Move getMove(){
        return _move;
    }
    Node* getParent(){
        return _parent;
    }
    Puzzle getValue(){
        return _value;
    }
    
    int getHeuristics(){
        return _h;
    }

    int getCost(){
        return _h+_g;
    }

    int getG(){
        return _g;
    }

    
};
    
        
