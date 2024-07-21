#include <stdio.h>
#include <windows.h>

#include "Drone.h"

typedef struct {
	Drone* drone;
	char* console;
} Data;

void reduceBattery(Data* data);
DWORD WINAPI decrementBattery(LPVOID lpParam);
void updateBatteryInConsole(Drone* drone, char* console);

Drone* initialiseDrone(int wings, int batteryPercent, int batteryCapacity, int weight) {
	Drone* drone = malloc(sizeof(Drone));
	if (drone != NULL) {
		drone->wings = wings;
		drone->batteryPercent = batteryPercent;
		drone->batteryCapacity = batteryCapacity;
		drone->weight = weight;
		drone->isFlying = false;
	}
	return drone;
}

void startDrone(Drone* drone, char* console) {
	drone->isFlying = true;

	Data* data = malloc(sizeof(Data));
	if (data == NULL) {
		perror("unable to allocate memory");
		return;
	}

	data->drone = drone;
	data->console = console;

	reduceBattery(data);
}

void reduceBattery(Data* data) {
	HANDLE threadHandle;
	DWORD threadId;

	threadHandle = CreateThread(NULL, 0, decrementBattery, data, 0, &threadId);
	if (threadHandle == NULL) {
		perror("Error creating thread\n");
	}
}

DWORD WINAPI decrementBattery(LPVOID lpParam) {
	Data* data = (Data*)lpParam;
	Drone* drone = data->drone;

	int reductionInterval;

	int capacityToWeightRatio = drone->batteryCapacity / drone->weight;
	if (capacityToWeightRatio > 10) {
		reductionInterval = 3;
	}
	else if (capacityToWeightRatio >= 1) {
		reductionInterval = 2;
	}
	else {
		reductionInterval = 1;
	}

	while (drone->isFlying) {
		Sleep(reductionInterval * 1000);
		--drone->batteryPercent;

		if (drone->batteryPercent == 0) {
			updateBatteryInConsole(drone, data->console);
			drone->isFlying = false;
			break;
		}
		updateBatteryInConsole(drone, data->console);
	}
	updateBatteryInConsole(drone, data->console);

	free(data);
	data = NULL;
	ExitThread(0);

	return 0;
}

void stopDrone(Drone* drone) {

	drone->isFlying = false;
}

void updateBatteryInConsole(Drone* drone, char* console) {
	system("cls");

	if (drone->batteryPercent == 0) {
		printf("Drone battery died.\n\n");
	} 
	else if (!drone->isFlying) {
		printf("Drone has stopped.\n\n");
	}
	else {
		printf("Drone battery percent: %d\n\n", drone->batteryPercent);
	}

	printf(console);
}