#include <stdbool.h>

typedef struct {
	int wings;
	int batteryPercent;
	int batteryCapacity;
	int weight;
	bool isFlying;
} Drone;

Drone* initialiseDrone(int wings, int batteryPercent, int batteryCapacity, int weight);