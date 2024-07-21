#include <stdio.h>
#include <stdlib.h>
#include "Drone.h"

void startDrone(Drone* drone, char* console);
void stopDrone(Drone* drone);

void program(Drone* drone) {
	char input[10];
	char *console = malloc(1024);
	int command;

	if (console == NULL) {
		perror("Failed to allocate memory");
		exit(1);
	}

	while (1) {
		console = "Enter command: 1 - Start drone, 2 - stop drone, 3 - create obstacle, Any key - Exit\n> ";
		printf(console);

		if (fgets(input, sizeof(input), stdin) == NULL) {
			break;
		}

		command = atoi(input);

		switch (command) {
		case 1:
			if (drone->isFlying) {
				printf("Drone is already flying");
				break;
			}
			startDrone(drone, console);
			break;
		case 2:
			if (!drone->isFlying) {
				printf("Drone is already stopped");
				break;
			}
			stopDrone(drone);
			break;
		case 3:
			console = "obstactle location : 1 - left, 2 - front, 3 - right, 4 - rear.\n >";
			printf(console);
			if (fgets(input, sizeof(input), stdin) == NULL) {
				break;
			}
			// short int location = atoi(input);
			//TODO - handle obstacles

			break;
		default:
			stopDrone(drone);
			printf("Exiting program...\n");
			free(console);
			console = NULL;
			return;
		}
	}
	console = NULL;
	free(console);
}