#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Drone.h"

#define PERCENT_RANGE(x) ((x) >= 0 && (x) <= 100)
#define WINGS_RANGE(x) ((x) == 4 || (x) == 6 || (x) == 8)

void program(Drone* drone);

int main(int argc, char* argv[]) {
	int batteryCapacity = 0, weight = 0;
	short int wings = 0, batteryPercent = 0;

	if (argc != 9) {
		printf("Missing arguments");
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--batteryPercent") == 0) {
			batteryPercent = atoi(argv[++i]);
			if (!PERCENT_RANGE(batteryPercent)) {
				printf("Invalid battery percent (0-100)");
				return 1;
			}
		}
		else if (strcmp(argv[i], "--wings") == 0) {
			wings = atoi(argv[++i]);
			if (!WINGS_RANGE(wings)) {
				printf("Invalid number of wings (4, 6, 8)");
				return 1;
			}
		}
		else if (strcmp(argv[i], "--batteryCap") == 0) {
			batteryCapacity = atoi(argv[++i]);
		}
		else if (strcmp(argv[i], "--weight") == 0) {
			weight = atoi(argv[++i]);
		}
		else {
			printf("Unknown argument.\n");
			return 1;
		}
	}

	if (wings == 0 || batteryCapacity == 0 || weight == 0) {
		return 1;
	}

	Drone* drone = initialiseDrone(wings, batteryPercent, batteryCapacity, weight);

	if (drone != NULL) {
		program(drone);

		free(drone);
		drone = NULL;
	}

	return 0;
}