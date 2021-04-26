/**********************************************
Include header files
***********************************************/

#include "typewise-alert.h"
#include <stdio.h>

double LowerTempBoundary[]= {0,0,0};
double UpperTempBoundary[]= {35,45,40};

const char* Breach[] = { "normal", "low" , "high" } ;
AlertType AlertStatus= AlertFailed;

typedef AlertType (*SendtheAlertMessage) (BreachType breachType);
SendtheAlertMessage AlertDestination[] = 
    {
        sendToController, 
        sendToEmail, 
        sendToConsole
    };


/********************************************************************************
 * Function: inferBreach
 
 *it checks if the passed attribute value is exceeding the thresholds.
 
 * input: BMS attribute value here
 
 * returns: breach type as TOO LOW, HIGH OR NORMAL
 *********************************************************************************/
BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(
    CoolingType coolingType, double temperatureInC) {
  /*int lowerLimit = 0;
  int upperLimit = 0;
  switch(coolingType) {
    case PASSIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 35;
      break;
    case HI_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 45;
      break;
    case MED_ACTIVE_COOLING:
      lowerLimit = 0;
      upperLimit = 40;
      break;
  }*/
  return inferBreach(temperatureInC, LowerTempBoundary[coolingType], UowerTempBoundary[coolingType]);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  /*switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
    case TO_CONSOLE:
      sendToConsole(breachType);
      break;
  }*/
 return(AlertDestination[alertTarget](breachType));
}

AlertType  sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
 return DisplayMessage(breachType);
}

AlertType  sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
//   switch(breachType) {
//     case TOO_LOW:
//       printf("To: %s\n", recepient);
//       return DisplayMessage(breachType);
//       break;
//     case TOO_HIGH:
//       printf("To: %s\n", recepient);
//       return DisplayMessage(breachType);
//       break;
//     case NORMAL:
//       break;
//   }
  return DisplayMessage(breachType);
  }

  AlertType  sendToConsole(BreachType breachType)
  {
    return DisplayMessage(breachType);
  }

 AlertType DisplayMessage(BreachType breachType)
 {
   printf("Hi, the status is %x\n", breachType);
   return AlertPassed;
 }


