#include <algorithm.c>
#include <motion.c>

//Global variables
//Board is a global variable to avoid returning
//and taking a 2D array as variables

task main() {
	SensorType[S1] = sensorTouch;
	SensorType[S2] = sensorSONAR;
	displayString(0, "GROUP 100");
	displayString(1, "AUTOCHECKERS");
	wait1Msec(750);

	// MENU
	eraseDisplay();
	displayString(0, "USE GATE TO START");
	displayString(1, "WHEN PIECES ARE");
	displayString(2, "SET");
	while (SensorValue[S2] > 10) {} //this value needs to be tested
	eraseDisplay();

	// GAME LOOP
	bool blacksTurn = true;
	newGame();
	while(!checkWinner()){
		makeMove(blacksTurn);				// NOTE: Need to confirm this is an actual function
		blacksTurn = !blacksTurn;
	}
}
