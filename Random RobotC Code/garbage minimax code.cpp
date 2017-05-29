
/*
int minimax(int depth){
  bool AIblacksTurn = true;
  if (depth == 0){
    int parentAIMove[20];
    for (int i = 0; i < 20; i++){
      parentAIMove[i] = AIMove[i];
    }
    for (int i = 0; i < 8;i++){
      for (int j = 0; j < 8; j++){
        TopAIboard[i][j] = board[i][j];
      }
    }
  }

  int i = 0;
  if (depth == 0){
    int minMove = 1000;
    int index = 0; //index of best move
    while (AIMove[i] != 0){
        cout << endl << AIMove[i];
        legalMove(AIblacksTurn,AIMove[i]/1000,AIMove[i]%1000/100,AIMove[i]%100/10,AIMove[i]%10,false,true);
        cout << " " << boardEvaluation();
        i++;

        if (boardEvaluation() < minMove){
          minMove = boardEvaluation();
        }

        //Revert move
        for (int i = 0; i < 8;i++){
          for (int j = 0; j < 8; j++){
            AIboard[i][j] = board[i][j];
          }
        }
      }
      return minMove;
  }
  else{
       while (AIMove[i] != 0){
        legalMove(AIblacksTurn,AIMove[i]/1000,AIMove[i]%1000/100,AIMove[i]%100/10,AIMove[i]%10,false,true);
        i++;
        AIblacksTurn = !AIblacksTurn;
        minimax(depth-1);
        cout << endl << AIMove[i];
        allAILegalMoves(AIblacksTurn);
      }
  }
}
*/
