#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

void displayBoard(vector<vector<int>> board){
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

vector<vector<int>> newGame(){
  //I is row, J is col
  vector<vector<int>> board;
  board.resize(8);
  for (int i = 0; i < 8; i++){
    board[i].resize(8);
  }

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
          if ((j+1)%2 == 1){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 7
        else if ((i+1) == 7){
          if ((j+1)%2 == 0){
            board[i][j] = 2;
          }
          else{
            board[i][j] = 0;
          }
        }

        //Row 8
        else if ((i+1) == 8){
          if ((j+1)%2 == 1){
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
    return board;
}

bool whosTurn(){
  return true; //keep true for now
  //later make true if it's black turn and false if red turn
}

bool checkWinner(vector<vector<int>> board){
  return false;
}

//Turns a checker piece into a king
void makeKing(){

}

//Checks if a piece is a king
void checkKing(){

}

//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(vector<vector<int>> board, int currentX, int currentY, int toX, int toY, bool king){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

  //Check if a piece moves single piece diagonally

  cout << endl << currentX << currentY << toX << toY << endl;
  //For nonking black pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (whosTurn()){
    if (( (abs(toX - currentX)) == 1) && (toY - currentY == 1) && (board[currentY][currentX] == 1) && (board[toY][toX] == 0) ){
      cout << true;
      return true;
    }
  }

  //For nonking red pieces - single diagonal move, can only move forward, left/right, piece must be there and destination should be empty
  if (!whosTurn()){
    if (( (abs(toX - currentX)) == 1) && (toY - currentY == -1) && (board[currentY][currentX] == 2) && (board[toY][toX] == 0) ){
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

vector<vector<int>> updateBoard(vector<vector<int>> board,int currentX,int currentY, int toX, int toY){
  if (whosTurn()){
    board[currentX][currentY] = 0;
    board[toX][toY] = 1;
  }
  else{
    board[currentX][currentY] = 0;
    board[toX][toY] = 2;
  }


  return board;
}

void makeMove(vector<vector<int>> board){
  int currentX = 0, currentY = 0, toX = 0, toY = 0;
  string curr = "x", to = "x";

  do{
    cout << endl << "Which piece would you like to move? ";
    cin >> curr;
    cout << "To where? ";
    cin >> to;
    int currentX = curr.at(0) - 97; //Converts letter input to an integer number, COLUMN INPUT
    int currentY = curr.at(1) - '0' - 1; //Converts char number to integer number, ROW INPUT

    int toX = to.at(0) - 97;
    int toY = to.at(1) - '0' - 1;
    cout << currentX << currentY <<toX << toY;

  } while (!legalMove(board,currentX,currentY,toX,toY,false));

    updateBoard(board,currentX,currentY,toX,toY);
  //whosTurn = !whosTurn
}

int main() {
    int counter = 0;
    vector<vector<int>> board;

    board = newGame();
    displayBoard(board);

    while(!checkWinner(board)){
      makeMove(board);
      cout << endl;
      displayBoard(board);

    }

    return 0;
}
