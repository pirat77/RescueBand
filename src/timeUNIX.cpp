#include <timeUNIX.h>

// TODO: implement UNIX time handling and separate logs for every day

int transformScoreIntoDelay(int warningScore){
  switch (warningScore)
  {
  case 0:
    return 21600000;    
  case 1:
    return 10800000;
  case 2: 
    return 3600000;
  case 3:
    return 600000;
  case 4:
    return 300000;
  case 5: 
    return 60000;
  case 6: 
    return 30000;
  case 7:
    return 15000;
  case 8:
    return 5000;
  case 9:
    return 1000;
  case 10:
    return 500;
  case 11:
    return 100;
  case 12:
    return 10;   
  default:
    return 0;
  }
}
