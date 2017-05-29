#include <iostream>
#include <cmath>
using namespace std;

//Global 2D Array for board
int board[8][8];
int blackCounter = 0, redCounter = 0;

void newGame();
void displayBoard(bool showID = false);   // set showID to true to represent pieces as numbers
bool checkWinner();
void checkKing(bool blacksTurn);
bool canCapture(bool blacksTurn);
bool doubleCapture(bool blacksTurn, int row, int col);
bool legalMove(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol);
bool legalMove2(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol);
void updateBoard(bool blacksTurn, int currentRow,int currentCol, int toRow, int toCol,int jumpRow, int jumpCol);
void anotherCapture(bool &blacksTurn, int currentRow, int currentCol);
void makeMove(bool blacksTurn);
int boardEvaluation();
int[10] AIMove;

int main() {
    bool blacksTurn = true;

    newGame();
    displayBoard();

    while(!checkWinner()){
      makeMove(blacksTurn);
      cout << endl;
      displayBoard();
      cout << endl << "Boardvalue: " << boardEvaluation();
      blacksTurn = !blacksTurn;
    }

    return 0;
}

void generateMove(int[10] &AIMove) {
  int place = 0
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[i][j] != 0) {
        if (legalMove(i, i, i+1, j+1)) {
          AIMove[++place] == i * 1000 + j * 100 (i) + (i+1) * 10 + (j+1);
        }
        if (legalMove(i, j, i+1, j-1)) {
          AIMove[++place] == i * 1000 + j * 100 (i) + (i+1) * 10 + (j-1);
        }
        if (canCapture(i, j, i+1, j+1)) {
          AIMove[++place] == i * 1000 + j * 100 (i) + (i+2) * 10 + (j+2);
          //moves[place - 1] *= -1;
        }
        if (canCapture(i, j, i+1, j-1)) {
          AIMove[++place] == i * 1000 + j * 100 (i) + (i+2) * 10 + (j-2);
          //moves[place - 1] *= -1;
        }
      }
    }
  }
}

int boardEvaluation(){
  //Kings are worth 3, pieces are worth 1
  int blackWorth = 0;
  int redWorth = 0;
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      if (board[i][j] == 1)
        blackWorth++;
      if (board[i][j] == 2)
        redWorth++;
      if (board[i][j] == 3)
        blackWorth +=3;
      if (board[i][j] == 4)
        redWorth +=3;
    }
  }
  return (blackWorth - redWorth);
}



void displayBoard(bool showID) {
  if (showID) {
    for (int i = 7; i >= 0; i--) {
      for (int j = 0; j < 8; j++){
        if (board[i][j] != 0) cout << "[" << board[i][j] << "]";
        else cout << "[ ]";
      }
      cout << " " << i+1 << endl;
    }
  }
  else {
    for (int i = 7; i >= 0; i--) {
      for (int j = 0; j < 8; j++){
        switch (board[i][j]) {
          case 1: cout << "[b]"; break;
          case 2: cout << "[r]"; break;
          case 3: cout << "[B]"; break;
          case 4: cout << "[R]"; break;
          default: cout << "[ ]"; break;
        }
      }
      cout << " " << i+1 << endl;
    }
  }
    cout << endl;
    cout << " a  b  c  d  e  f  g  h";
}

void newGame(){
  //I is row, J is col

  for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8; j++){
        //Setting default pieces

        // //Black pieces 1
        if (i < 3){
          if (i%2 == 0){
            if (j%2 == 0){
              board[i][j] = 1;
            }
          }
          else if (i%2 == 1){
            if (j%2 == 1){
              board[i][j] = 1;
            }
          }
        }
        else if (i > 4){
          if (i%2 == 0){
            if (j%2 == 0){
              board[i][j] = 2;
            }
          }
          else if (i%2 == 1){
            if (j%2 == 1){
              board[i][j] = 2;
            }
          }
        }
      }
    }

}
//Checks for winner using a counter
bool checkWinner(){
  if(redCounter == 12 || blackCounter == 12){
    return true;
  }
  else{
  return false;
  }
}
//Turns a checker piece into a king
void checkKing(bool blacksTurn){
  if(blacksTurn){
    for(int j = 1; j<8; j += 2){
      if(board[7][j] == 1){
        board[7][j] = 3;
      }
    }
  }
  else{
    for(int j = 0; j<8; j += 2){
      if(board[0][j] == 2){
        board[0][j] = 4;
      }
    }
  }
}

bool captureCan(int currentRow, int currentCol, int toRow, int toCol) {
  if (
    board[currentRow][currentCol] != 0 &&
    board[toRow][toCol] != 0 &&
    board[currentRow][currentCol] != board[toRow][toCol] &&
    board[toRow*2 - currentRow][toCol*2 - currentCol] == 0
  )

  {return true;} else {return false;}
}

/*
bool canCapture(bool blacksTurn){
  for (int i = 0; i < 8; i++){ //iterating through rows
    for (int j = 0; j < 8; j++){ //iterating through columns

      if (blacksTurn){
        //Black Piece Cases
        if ( (board[i][j] == 1 || board[i][j] == 3) && j < 6 && i < 6 && ((board[i+1][j+1] == 2 || board[i+1][j+1] == 4) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if ( (board[i][j] == 1 || board[i][j] == 3) && j > 1 && i < 6 && ((board[i+1][j-1] == 2 || board[i+1][j-1] == 4) && (board[i-2][j-2] == 0))){
          return true;
        }

        //Extra King Checks
        else if (board[i][j] == 3 && j < 6 && i > 1 && ( ((board[i-1][j+1] == 2) || (board[i-1][j+1] == 4)) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 3 && j > 1 && i > 1 && ( ((board[i-1][j-1] == 2 || board[i-1][j-1] == 4 )) && (board[i-2][j-2] == 0))){
          return true;
        }
      }
      else{
        //Red Piece Cases
        if ((board[i][j] == 2 || board[i][j] == 4) && j < 6 && i > 1 && ((board[i-1][j+1] == 1 || board[i-1][j+1] == 3) && (board[i-2][j+2] == 0))){
          return true;
        }
        else if  ((board[i][j] == 2 || board[i][j] == 4) && j > 1 && i > 1 && ((board[i-1][j-1] == 1 || board[i-1][j-1] == 3) && (board[i-2][j-2] == 0))){
          return true;
        }
        //Extra King Checks
        else if (board[i][j] == 4 && j < 6 && i < 6 && ( ((board[i+1][j+1] == 1 || board[i+1][j+1] == 3)) && (board[i+2][j+2] == 0))){
          return true;
        }
        else if  (board[i][j] == 4 && j > 1 && i < 6 && (((board[i+1][j-1] == 1 || board[i+1][j-1] == 3)) && (board[i+2][j-2] == 0))){
          return true;
        }
      }
    }
  }
  return false;
}
*/
bool doubleCapture(bool blacksTurn, int row, int col){
  if (blacksTurn){
    //Black Piece Cases
    if ( (board[row][col] == 1 || board[row][col] == 3) && col < 6 && row < 6 &&  ((board[row+1][col+1] == 2 || board[row+1][col+1] == 4) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if ( (board[row][col] == 1 || board[row][col] == 3) && col > 1 && row < 6 &&  ((board[row+1][col-1] == 2 || board[row+1][col-1] == 4) && (board[row+2][col-2] == 0))){
      return true;
    }

    //Extra King Checks
    else if (board[row][col] == 3 && col < 6 && row > 1 && ( ((board[row-1][col+1] == 2) || (board[row-1][col+1] == 4)) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 3 && col > 1 && row > 1 && ( ((board[row-1][col-1] == 2 || board[row-1][col-1] == 4 )) && (board[row-2][col-2] == 0))){
      return true;
    }
  }
  else{
    //Red Piece Cases
    if ((board[row][col] == 2 || board[row][col] == 4) && col < 6 && row > 1 && ((board[row-1][col+1] == 1 || board[row-1][col+1] == 3) && (board[row-2][col+2] == 0))){
      return true;
    }
    else if  ((board[row][col] == 2 || board[row][col] == 4) && col > 1 && row > 1 && ((board[row-1][col-1] == 1 || board[row-1][col-1] == 3) && (board[row-2][col-2] == 0))){
      return true;
    }
    //Extra King Checks
    else if (board[row][col] == 4 && col < 6 && row < 6 &&  ( ((board[row+1][col+1] == 1 || board[row+1][col+1] == 3)) && (board[row+2][col+2] == 0))){
      return true;
    }
    else if  (board[row][col] == 4 && col > 1 && row < 6 &&  (((board[row+1][col-1] == 1 || board[row+1][col-1] == 3)) && (board[row+2][col-2] == 0))){
      return true;
    }
  }
  return false;
}

void updateBoard(bool blacksTurn, int currentRow,int currentCol, int toRow, int toCol,int jumpRow, int jumpCol){
  board[toRow][toCol] = board[currentRow][currentCol];
  board[currentRow][currentCol] = 0;
  checkKing(blacksTurn);
  if (jumpRow != -1){
    board[jumpRow][jumpCol] = 0;
    //run move function
    //run remove captured piece function
    if(blacksTurn){
      redCounter += 1;
    }
    else{
      blackCounter +=1;
    }
    if(doubleCapture(blacksTurn, toRow, toCol)){
      displayBoard();
      anotherCapture(blacksTurn, toRow, toCol);
    }
  }
  else{
    //run diagonal moving function
  }
}


//Checks if a move is legal, returns a boolean, called by the makeMove
bool legalMove(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol){
  //Legal move conditions, 1 diagonal, jump over piece, jump over multiple pieces - will be hard to implement

  int jumpRow = -1, jumpCol = -1;
  bool legal = false;
  //Check if a piece moves single piece diagonally

  //cout << endl << currentRow << currentCol << toRow << toCol << endl;

  //Black moves
  if (blacksTurn){
    if (( (toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 1) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    else if ( (abs(toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 3) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    //Jumps
    else if ( (toRow - currentRow == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 1) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 3) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  //Red moves
  else{
    if (( (toRow - currentRow) == -1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 2) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    else if ( (abs(toRow - currentRow) == 1) && (abs(toCol - currentCol) == 1) && (board[currentRow][currentCol] == 4) && (board[toRow][toCol] == 0) ){
      legal = true;
    }
    //Jumps
    else if ( (toRow - currentRow == -2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 2) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 4) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  if (legal){
    updateBoard(blacksTurn, currentRow,currentCol,toRow,toCol,jumpRow,jumpCol);
  }
  return legal;
}

bool legalMove2(bool blacksTurn, int currentRow, int currentCol, int toRow, int toCol){
//Legal move conditions for second capture, jumps only

  int jumpRow = -1, jumpCol = -1;
  bool legal = false;

  cout << endl << currentRow << currentCol << toRow << toCol << endl;

  //Black moves
  if (blacksTurn){
    //Jumps
    if ( (toRow - currentRow == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 1) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 3) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 2 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 4)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  //Red moves
  else{
    //Jumps
    if ( (toRow - currentRow == -2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 2) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
    else if( (abs(toRow - currentRow) == 2) && (abs(toCol - currentCol) == 2) && (board[currentRow][currentCol] == 4) && board[toRow][toCol] == 0 && (board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 1 || board[(toRow+currentRow)/2][(toCol+currentCol)/2] == 3)){
      jumpRow = (toRow+currentRow)/2;
      jumpCol = (toCol+currentCol)/2;
      legal = true;
    }
  }

  if (legal){
    updateBoard(blacksTurn, currentRow,currentCol,toRow,toCol,jumpRow,jumpCol);
  }
  return legal;
}

void anotherCapture(bool &blacksTurn, int currentRow, int currentCol){
  int toRow = -1, toCol = -1;
  string to = "x";
  do{
    cout<<endl<<"Second capture, to where?"<<endl;
    cin>>to;
    toCol = to.at(0) - 97;
    toRow = to.at(1) - '0' - 1;
    cout << currentRow << currentCol <<endl<<toRow << toCol;
  }while(abs(toRow-currentRow) == 1 || abs(toCol-currentCol) == 1
  || !legalMove2(blacksTurn,currentRow,currentCol,toRow,toCol));
}

void makeMove(bool blacksTurn){
  int currentRow = -1, currentCol = -1, toRow = -1, toCol = -1;
  string curr = "X", to = "X";

  cout << endl << "Force? " << canCapture(blacksTurn); // DEBUGGINGPURPOSE
  do {
    cout << endl << "Which piece would you like to move? ";
    cin >> curr;
    cout << "To where? ";
    cin >> to;

    cout << endl;

    currentCol = curr.at(0) - 97; //Converts letter input to an integer number, COLUMN INPUT
    currentRow = curr.at(1) - '0' - 1; //Converts char number to integer number, ROW INPUT

    toCol = to.at(0) - 97;
    toRow = to.at(1) - '0' - 1;
  } while (!legalMove(blacksTurn,currentRow,currentCol,toRow,toCol));
}
