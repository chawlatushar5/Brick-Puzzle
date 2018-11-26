//
//  Puzzle.cpp
//  MovingBrick
//
//  Created by Tushar Chawla on 10/12/17.
//  Copyright © 2017 Tushar Chawla. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
using namespace std;

struct Direction{
    bool up;
    bool down;
    bool left;
    bool right;
};

struct Coordinates{
    int x;
    int y;
};

struct Move{
    string _direction;
    int _piece;
    void print(){
        cout<<"("<<_piece<<", "<<_direction<<")"<<endl;
    }
};

class Puzzle{
private:
    
    int _height;
    int _width;
    vector<vector<int>> _board;
    
public:
    Puzzle(){
        _height=0;
        _width=0;
    }
    bool isValid(){
        if (_height>0 && _width>0){
            return true;
        }else{
            return false;
        }
        
    }
    Puzzle(vector<int> data)
    {
        _height=data[1];
        _width=data[0];
        
        
        int counter=1;
        vector<int> row(_width);
        // setting the board
        for (int i=2; i<data.size(); i++){
            row[counter-1]=data[i];
            
            if (counter==_width){
                counter=0;
                _board.push_back(row);
            }
            counter++;
        }
        
        
    }
    // iterating through 2D vector and prinitng the values.
    void print(){
        for (int i=0; i<_board.size(); i++){
            for (int m=0; m<_board[i].size(); m++){
                cout<<_board[i][m]<<"  ";
            }
            cout<<endl;
        }
    }
    
    // iterating through 2D vector and checking if any value is -1.
    bool isFinished(){
        
        for (int i=0; i<_board.size(); i++){
            for (int m=0; m<_board[i].size(); m++){
                if (_board[i][m]==-1){
                    return false;
                }
            }
        }
        return true;
    }
    
    

   // find the piece, check the available options using its coordinates and its corresponding positions.
    Direction checkAvailableMoves(int piece){
        Direction move;
        move.left=true;
        move.right=true;
        move.up=true;
        move.down=true;
        vector<Coordinates> coords = findCoordinates(piece); // for 2 pieces, it checks for both coordinates.
        for (int i=0; i<coords.size(); i++){
            if (piece==2){
            if ((coords[i].x-1)>=0 && coords[i].x-1<_width){
                if ((_board[coords[i].y][coords[i].x-1]!=0 && _board[coords[i].y][coords[i].x-1]!=-1) && _board[coords[i].y][coords[i].x-1]!=piece){
                    move.left=false;
                }
            }else{
                move.left=false;
            }
            if ((coords[i].x+1)>=0 && coords[i].x+1<_width){
                if ((_board[coords[i].y][coords[i].x+1]!=0 && _board[coords[i].y][coords[i].x+1]!=-1) && _board[coords[i].y][coords[i].x+1]!=piece){
                    move.right=false;
                }
            }else{
                move.right=false;
            }
            if ((coords[i].y-1)>=0 && coords[i].y-1<_height){
                if ((_board[coords[i].y-1][coords[i].x]!=0 && _board[coords[i].y-1][coords[i].x]!=-1) && _board[coords[i].y-1][coords[i].x]!=piece){
                    move.up=false;
                }
            }else{
                move.up=false;
            }
            if ((coords[i].y+1)>=0 && coords[i].y+1<_height){
                if ((_board[coords[i].y+1][coords[i].x]!=0 && _board[coords[i].y+1][coords[i].x]!=-1) && _board[coords[i].y+1][coords[i].x]!=piece){
                    move.down=false;
                }
            }else{
                move.down=false;
            }
            }else{
                if ((coords[i].x-1)>=0 && coords[i].x-1<_width){
                    if (_board[coords[i].y][coords[i].x-1]!=0 && _board[coords[i].y][coords[i].x-1]!=piece){
                        move.left=false;
                    }
                }else{
                    move.left=false;
                }
                if ((coords[i].x+1)>=0 && coords[i].x+1<_width){
                    if (_board[coords[i].y][coords[i].x+1]!=0 && _board[coords[i].y][coords[i].x+1]!=piece){
                        move.right=false;
                    }
                }else{
                    move.right=false;
                }
                if ((coords[i].y-1)>=0 && coords[i].y-1<_height){
                    if (_board[coords[i].y-1][coords[i].x]!=0 && _board[coords[i].y-1][coords[i].x]!=piece){
                        move.up=false;
                    }
                }else{
                    move.up=false;
                }
                if ((coords[i].y+1)>=0 && coords[i].y+1<_height){
                    if (_board[coords[i].y+1][coords[i].x]!=0 && _board[coords[i].y+1][coords[i].x]!=piece){
                        move.down=false;
                    }
                }else{
                    move.down=false;
                }
            }
        }
        // check here
        return move;
    }
    
    // iterating through 2D vector and checking if any value is number. Returns a vector, in case piece is of size 2.
    vector<Coordinates> findCoordinates(int number){
        vector<Coordinates> coordinates;
        for (int i=0; i<_board.size(); i++){
            for (int m=0; m<_board[i].size(); m++){
                if (_board[i][m]==number){
                    Coordinates coord;
                    coord.y = i;
                    coord.x=m;
                    coordinates.push_back(coord);
                }
            }
        }
        return coordinates;
        
    }
    // Loops throgh all the pieces, get all the moves and put the pieces that has available Directioninto a map and return it.
    map<int, Direction> getAllMoves(){
        map<int, Direction> allMoves;
        for (int i=2; i<=getMaximum(); i++){
            Direction availableMove= checkAvailableMoves(i);
            if (availableMove.left || availableMove.right || availableMove.up || availableMove.down){
                allMoves[i] = checkAvailableMoves(i);
            }
        }
        return allMoves;
    }

    
    vector<Move> getMovesList(){
        vector<Move> moves;
        for (int i=2; i<=getMaximum(); i++){
            Direction availableMove= checkAvailableMoves(i);
            if (availableMove.left){
                Move mv = {"left", i};
                moves.push_back(mv);
            }
            if (availableMove.right){
                Move mv = {"right", i};
                moves.push_back(mv);
            }
            if (availableMove.up){
                Move mv = {"up", i};
                moves.push_back(mv);
            }
            if (availableMove.down){
                Move mv = {"down", i};
                moves.push_back(mv);
            }
        }
        return moves;
        
    }
    
    // gets the number of pieces on board.
    int getMaximum(){
        int max=0;
        for (int i=0; i<_board.size(); i++){
            for (int m=0; m<_board[i].size(); m++){
                if (_board[i][m]>max){
                    max=_board[i][m];
                }
            }
        }
        return max;
    }
    
    // changes the position of the pieces by replacing the corresponding direction piece.
    void makeMove(int piece, string move){
        vector<Coordinates> coords = findCoordinates(piece);
        if (move=="right" || move=="down"){
            reverse(coords.begin(), coords.end());
        }
        for (int i=0; i<coords.size(); i++){
            if (move=="left"){
                _board[coords[i].y][coords[i].x-1]=_board[coords[i].y][coords[i].x];
            }else if (move=="right"){
                _board[coords[i].y][coords[i].x+1]=_board[coords[i].y][coords[i].x];
            }else if (move=="down"){
                _board[coords[i].y+1][coords[i].x]=_board[coords[i].y][coords[i].x];
            }else if (move=="up"){
                _board[coords[i].y-1][coords[i].x]=_board[coords[i].y][coords[i].x];
            }
            _board[coords[i].y][coords[i].x]=0;
        }
    }
    
    // getting a duplicate object at the same stage.
    static Puzzle makeMoveCloning(int piece, string move, Puzzle puzzle1){
        Puzzle puzzleClone = puzzle1;
        puzzleClone.makeMove(piece, move);
        return puzzleClone;
    }
    
    Puzzle clone(){
        Puzzle puzzleClone = *(this);
        return puzzleClone;
    }
    
    // gets the numbers organized, which makes it easier if the state is same.
    void normalize(){
        int nextIdx = 3;
        for(int i = 0;i < _height;i++) {
            for(int j = 0;j < _width;j++) {
                if (_board[i][j]==nextIdx) {
                    nextIdx++;
                } else if (_board[i][j] > nextIdx) {
                    swapIdx(nextIdx,_board[i][j]);
                    nextIdx++;
                }
            }
        }
    }
    
    // helper function for normalizing. 
    void swapIdx(int idx1,int idx2) {
        for(int i = 0;i < _height;i++) {
            for(int j = 0;j < _width;j++) {
                if (_board[i][j]==idx1) {
                    _board[i][j]=idx2;
                } else if (_board[i][j]==idx2) {
                    _board[i][j]=idx1;
                }
            }
        }
    }
    
    bool checkSame(Puzzle p2){
        (*this).normalize();
        p2.normalize();
        if (p2._height==_height && p2._width==_width){
            for (int h=0; h<_height; h++){
                for (int w=0; w<_width; w++){
                    if (_board[h][w]!=p2._board[h][w]){
                        return false;
                    }
                }
            }
            return true;
        }else{
            return false;
        }
    }
    
    int getHeuristic(){
        if (isFinished()){
            return 0;
        }
        vector<Coordinates> goalCoords = findCoordinates(-1);
        vector<Coordinates> brick2Coords = findCoordinates(2);
        int x_minimum=_width+_height+1;
        int y_minimum=_width+_height+1;
        for (Coordinates goal: goalCoords){
            for (Coordinates brick2: brick2Coords){
                if ((abs(goal.x-brick2.x))<x_minimum){
                    x_minimum=abs(goal.x-brick2.x);
                }
                if ((abs(goal.y-brick2.y))<y_minimum){
                    y_minimum=abs(goal.y-brick2.y);
                }
            }
        }
        return x_minimum+y_minimum;
    }

    
    
    
    
};
