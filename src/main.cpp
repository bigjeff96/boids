#include "vector2.h"
#include <cstdio>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>

#define TOTAL_BIRDS 10
#define MAX_X 5
#define MAX_Y 5
#define TOTAL_STEPS 100

struct boid {
    vec2 position = vec2();
    vec2 velocity = vec2();
};

// void velocity_alignment(boid *birds);
// void avoid_contact(boid *birds);
// void goto_center_mass(boid *birds);

int main() {
    boid *birds = (boid *)malloc(TOTAL_BIRDS * sizeof(boid));
    float x, y;
    for (int i = 0; i < TOTAL_BIRDS; i++) {
        x = MAX_X * (float)(rand()) / RAND_MAX;
        y = MAX_Y * (float)(rand()) / RAND_MAX;
        birds[i].position = vec2(x, y);
    }

    int current_steps = 0;

    while (current_steps < TOTAL_STEPS) {

        // converge to center of mass
        vec2 center_of_mass = vec2();

        for (int i = 0; i < TOTAL_BIRDS; i++) {
            center_of_mass += birds[i].position;
        }

        center_of_mass = (float)(1 / TOTAL_BIRDS) * center_of_mass;

        vec2 center_of_mass_relative = vec2();

        for (int i = 0; i < TOTAL_BIRDS; i++) {
            center_of_mass_relative =
                (TOTAL_BIRDS / (TOTAL_BIRDS - 1)) * center_of_mass - (1 / (TOTAL_BIRDS - 1)) * birds[i].position;
            birds[i].velocity += center_of_mass_relative;
        }

        // update position based off velocity
        for (int i = 0; i<TOTAL_BIRDS; i++) {
            birds[i].position+=birds[i].velocity;
        }

        // apply rules for bird-obstacle interaction
        // TODO implement obstacle avoidance for the Boids
    }
    free(birds);
}
