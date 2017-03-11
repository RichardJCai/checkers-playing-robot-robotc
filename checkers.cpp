#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//Global 2D Array for board
int board[8][8];

void displayBoard(){
  for (int i = 7; i >= 0;i--){
      for (int j = 0; j < 8; j++){
        cout << "[" << board[i][j] << "]";
      }
      cout << " " << i+1 << endl;
    }
    cout << endl;
    cout << " "<< "a" << "  " <<  "b" << "  "  << "c" << "  "
    << "d" << "  " << "e" << "  " << "f" << "  " << "g"  << "  "<< "h";
}

void newGame(){
  //I is row, J is col

  for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8; j++){
        //Setting default pieces

        //Black pieces 1

        //Row 1
        if ((i+1) == 1){
          if ((j+1)%2 == 1){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 2
        else if ((i+1) == 2){
          if ((j+1)%2 == 0){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 3
         else if ((i+1) == 3){
          if ((j+1)%2 == 1){
            board[i][j] = 1;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 6
        else if ((i+1) == 6){
          if ((j+1)%2 == 0){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 7
        else if ((i+1) == 7){
          if ((j+1)%2 == 1){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 8
        else if ((i+1) == 8){
          if ((j+1)%2 == 0){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Set blank spaces to 0
        else{
        board[i][j] = 0;
        }
      }
    }
}
bool checkWinner(){
  return false;
}

//Turns a checker piece into a king
void makeKing(){

}

//Checks if a piece is a king
void checkKing(){

}

bool canCapture(){
  //Must capture pieces if available
  
  //Can Capture for Regular Pieces
    for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8; j++){
        if (i < 6 && i > 1 && board[i][j] == 1){
          if ((board[i+1][j+1] == 2) && (board[i+2][j+2])){
            return true;
          }
        }
        else if (board[i][j] == 2){
          //Check if it can jump over backwards diagonals
        }
        else if (board[i][j] == 3){
          //black king check
        }
        else if (board[i][j] == 4){
          //red king check
        }
  
    return false;
    }
  }
}

//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(bool blacksTurn, int currentX, int currentY, int toX, int toY, bool king){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

  //Check if a piece moves single piece diagonally

  cout << endl << currentX << currentY << toX << toY << endl;
  //For nonking black pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (blacksTurn){
    if (( (toX - currentX) == 1) && (abs(toY - currentY) == 1) && (board[currentX][currentY] == 1) && (board[toX][toY] == 0) ){
      cout << true;
      return true;
    }
  }

  //For nonking red pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (!blacksTurn){
    if ( (toX - currentX == -1) && (abs(toY - currentY) == 1) && (board[currentX][currentY] == 2) && (board[toX][toY] == 0) ){
      cout << true;
      return true;
    }
  }
  
  //For king black pieces
  if (blacksTurn){
    if (( abs(toX - currentX) == 1) && (abs(toY - currentY) == 1) && (board[currentX][currentY] == 1) && (board[toX][toY] == 0) ){
      cout << true;
      return true;
    }
  }
  
  if (!blacksTurn){
    if (( abs(toX - currentX) == 1) && (abs(toY - currentY) == 1) && (board[currentX][currentY] == 2) && (board[toX][toY] == 0) ){
      cout << true;
      return true;
    }
  }

  //Check jumping over pieces for nonking black
  // if (whosTurn()){
  //   //Check if current space contains black nonking and final square is blank
  //   //Then check if intermediate spaces hold correct
  // }

  cout << false;
  return false;
}

void updateBoard(bool blacksTurn, int currentX,int currentY, int toX, int toY){
  if (blacksTurn){
    board[currentX][currentY] = 0;
    board[toX][toY] = 1;
  }
  else{
    board[currentX][currentY] = 0;
    board[toX][toY] = 2;
  }
}

void makeMove(bool blacksTurn){
  int currentX = 0, currentY = 0, toX = 0, toY = 0;
  string curr = "x", to = "x";

  cout << endl << "Can? " << canCapture();
  do{
    cout << endl << "Which piece would you like to move? ";
    cin >> curr;
    cout << "To where? ";
    cin >> to;
    currentY = curr.at(0) - 97; //Converts letter input to an integer number, COLUMN INPUT
    currentX = curr.at(1) - '0' - 1; //Converts char number to integer number, ROW INPUT

    toY = to.at(0) - 97;
    toX = to.at(1) - '0' - 1;
    cout << currentX << currentY <<toX << toY;

  } while (!legalMove(blacksTurn,currentX,currentY,toX,toY,true));

  updateBoard(blacksTurn, currentX,currentY,toX,toY);
}

int main() {
    int counter = 0;
    int blacksTurn = true;
    
    newGame();
    displayBoard();

    while(!checkWinner()){
      makeMove(blacksTurn);
      cout << endl;
      displayBoard();
      blacksTurn = !blacksTurn;

    }

    return 0;
}