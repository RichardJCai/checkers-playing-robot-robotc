int main(){
  //Main loop
  //Tracking distance, 24 inches by 24 inches
  //Using 8 by 8 nested array, 3 inches represents 1 square
  //For example, moving to square D6 from the origin (0,0), D6 is 4,6
  //The robot must move right 4 squres, so x motor moves 12 inches,
  //Then the robot must move up 6 squres, so y motor moves 18 inches
}

//Moves the x-direction motor, A is X direction motor, B is Y direction motor, C is Z direction motor
float moveDirection(float distance,char motor){
  motor[char] = 75;
  while(distTravelled < distance){
    //Code to move the motor, stops when distance travelled reaches distance
  }
  distTravelled = //Calculations for distance;

  //PID code?
}

void resetToOrigin(){
  //Move X,Y,Z all to 0
  //Possibly use color/touch sensor to set to origin
}

void inputMove(){
  //Use buttons to input a move
}
