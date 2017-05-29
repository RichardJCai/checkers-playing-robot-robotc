const int ONE_SQUARE = 148; // 2.25 inches * 25.4 mm/inch * 2pi*radius /180 = 148, where radius = 22.1mm
const int POW = 50; //Power Constant
const int correctionFactor = 0.5;


void getInPosition(int currentRow, int currentCol, int toRow, int toCol);	// Karam
void moveForward();															// Karam
void moveBackward();														// Karam
void moveRight();															// Karam
void moveLeft();															// Karam
void moveDiagonal(int deltaX, int deltaY);									// Jin
void moveZ(bool up);														// Jin
void jump(int currentRow, int currentCol, int toRow, int toCol);			// Karam
void step(int currentRow, int currentCol, int toRow, int toCol);			// Jin
void removePiece(int jumpRow, int jumpCol);									// Karam
void calibrate();															// Jin


/* Get in Position
 * Moves the magnet from the current row and column to the desired row and column
 * Void function, int currentRow, currentCol, toRow and toCol and required parameters
 */
void getInPosition(int currentRow, int currentCol, int toRow, int toCol) {
	nMotorEncoder[motorA] = 0;		// x-axis motor
	nMotorEncoder[motorB] = 0;		// y-axis motor
	int deltaX = (toCol - currentCol) * ONE_SQUARE; //Distance required to move in x-axis
	int deltaY = (toRow - currentCol) * ONE_SQUARE; //Distance required to move in y-axis
	if(deltaX > 0){
	  motor[motorA] = POW;
	}
	else{
	  motor[motorA] = -POW;
	}
	if(deltaY > 0){
	  motor[motorB] = POW;
	}
  	else{
    	motor[motorB] = -POW;
  	}
	if (currentRow == -1){
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    deltaX -= ONE_SQUARE;
	    deltaY -= ONE_SQUARE;
	    if(nMotorEncoder[motorA] == deltaX + correctionFactor){
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == deltaY + correctionFactor){
	      motor[motorB] = 0;
	    }
	  }
	}
	else{
	  while(motor[motorA] != 0 || motor[motorB] != 0){
	    if(nMotorEncoder[motorA] == deltaX){
	      motor[motorA] = 0;
	    }
	    if(nMotorEncoder[motorB] == deltaY){
	      motor[motorB] = 0;
	    }
	  }
	}
}

/**********  GENERIC MOVEMENT FUNCTIONS **********/
void moveForward() {		// move one space forward
	nMotorEncoder[motorB] = 0;
	motor[motorB] = POW;
	while (nMotorEncoder[motorB] < ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveBackward() {			// move one space backward
	nMotorEncoder[motorB] = 0;
	motor[motorB] = -POW;
	while (nMotorEncoder[motorB] > ONE_SQUARE) {}
	motor[motorB] = 0;
}

void moveRight() {		// move ones space right
	nMotorEncoder[motorA] = 0;
	motor[motorA] = POW;
	while (nMotorEncoder[motorA] < ONE_SQUARE) {}
	motor[motorA] = 0;
}

void moveLeft() {			// move one space left
	nMotorEncoder[motorA] = 0;
	motor[motorA] = -POW;
	while (nMotorEncoder[motorA] > ONE_SQUARE) {}
	motor[motorA] = 0;
}

void moveDiagonal(int deltaX, int deltaY) {
  nMotorEncoder[motorA] = 0;
  nMotorEncoder[motorB] = 0;
  deltaX *= ONE_SQUARE;
  deltaY *= ONE_SQUARE;
  motor[motorA] = POW * sgn(deltaX);
  motor[motorB] = POW * sgn(deltaY);
  while (abs(nMotorEncoder[motorA]) < deltaX ||
         abs(nMotorEncoder[motorB]) < deltaY) {}
  motor[motorA] = 0;
  motor[motorB] = 0;
}

/**********  MOVING PIECES  **********/

/* Moves the z-axis arm upward or downwards
 * until it encounters resistance.
 */
void moveZ(bool up) {
	nMotorEncoder[motorC] = 0;
	int prev = -10;
	if (up) {
		motor[motorC] = -10;
	}
	else {
		motor[motorC] = 10;
	}
	while (!(abs(nMotorEncoder[motorC] - prev) < 0.1)) {
		prev = nMotorEncoder[motorC];
		wait1Msec(50);
	}
	motor[motorC] = 0;
}

/* Jump function
 * Moves the current piece diagonally to desired coordinates
 * Void function, int currentRow, currentCol, toRow, toCol required as parameters
 */
void jump(int currentRow, int currentCol, int toRow, int toCol){

  int deltaY = toRow - currentRow;
  int deltaX = toCol - currentCol;

  moveZ(true);//magnet up

  if (deltaY > 0){
    moveForward();
    if (deltaX > 0){
      moveDiagonal(1, 1);
      moveRight();
    }
    else{ //deltaX < 0
      moveDiagonal(-1, 1);
      moveLeft();
    }
  }

  else{ //deltaY < 0
    moveBackward();
    if (deltaX > 0){
      moveDiagonal(1, -1);
      moveRight();
    }
    else{ //deltaX < 0
      moveDiagonal(-1, -1);
      moveLeft();
    }
  }
  moveZ(false);//magnet down
}

/* Step function
 * Moves pieces by one space diagonally
 * Void int currentRow, currentCol, toRow, toCol required as parameters
 */
void step(int currentRow, int currentCol, int toRow, int toCol) {
	// steps one space in stated direction in separate dx and dy steps
	int deltaY = toRow - currentRow;
  	int deltaX = toCol - currentCol;
	moveZ(true);			// magnet up
	if (deltaY > 0) {
		moveForward();
	}
	else {
		moveBackward();
	}
	if (deltaX > 0) {
		moveRight();
	}
	else {
		moveLeft();
	}
}

/* Remove Piece
 * Removes pieces by first moving across the diagonals into
 * the garbage collection area
 * if the piece reaches the end of the board before moving into the garbage collection area
 * the y direction changes while x stays the same. -Moves in a diagonal bouncing motion
 * Void, int jumpRow,jumpCol required as parameters
 */
void removePiece(int jumpRow, int jumpCol){
  moveZ(true);			// magnet up
	if(jumpCol<4){
		moveLeft();
		if(jumpCol != 0){
			if ((7 - jumpRow) > jumpCol){
				moveDiagonal(-jumpCol, jumpCol);
				jumpCol = 0;
			}
			else{
				moveDiagonal(jumpRow-7, 7-jumpRow);
				jumpCol += jumpRow - 7;
				moveDiagonal(-jumpCol, -jumpCol);
			}
		}
	}
	else{
		moveRight();
		jumpCol = 7 - jumpCol;
		if(jumpCol != 0){
			if ((7 - jumpRow) > jumpCol){
				moveDiagonal(jumpCol, jumpCol);
				jumpCol = 0;
			}
			else{
				moveDiagonal(jumpRow-7, 7-jumpRow);
				jumpCol += jumpRow - 7;
				moveDiagonal(jumpCol, -jumpCol);
			}
		}

	}
}

/* calibrate
 * Calibrates the magnet by moving it to the origin of the board
 * The y-axis motor is moved for 10 seconds - the maximum required time to cross the board
 * The y-axis motor moves until the touch sensor is pressed
 */
void calibrate() {
	// motorA is stopped when motorB is stopped by the button
	motor[motorA] = -POW;
	motor[motorB] = -POW;
	time1[T2] = 0;

	while (time1[T2] < 10000) {		// should not take longer than 10 sec
		if (SensorValue[S1] == 1) {
			wait1Msec(100);
			break;
		}
	}
	motor[motorA] = 0;
	motor[motorB] = 0;
}
