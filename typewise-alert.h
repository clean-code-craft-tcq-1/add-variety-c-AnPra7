#pragma once

typedef enum {
  PASSIVE_COOLING,
  HI_ACTIVE_COOLING,
  MED_ACTIVE_COOLING
} CoolingType;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef enum {
  AlertFailed,
  AlertPassed
}AlertType;

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL,
  TO_CONSOLE
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

AlertType sendToController(BreachType breachType);
AlertType sendToEmail(BreachType breachType);
AlertType sendToConsole(BreachType breachType);
AlertType DisplayMessage(BreachType breachType);

