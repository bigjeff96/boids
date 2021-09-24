#include "vector2.h"
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string>

#define TOTAL_BIRDS 10
#define MAX_X 5
#define MAX_Y 5
#define TOTAL_STEPS 100

using std::string;

const string data_dir = "Data";

struct boid {
    vec2 position = vec2();
    vec2 velocity = vec2();
};

// void velocity_alignment(boid *birds);
// void avoid_contact(boid *birds);
// void goto_center_mass(boid *birds);
void write_data(boid *birds, int current_steps);

int main() {

    system(("rm -f " + data_dir + "/*").c_str());
    system(("mkdir -p " + data_dir).c_str());
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

        // TODO: com always zero, casting error from me
        center_of_mass = (float)(1 / TOTAL_BIRDS) * center_of_mass;

        vec2 center_of_mass_relative = vec2();

        for (int i = 0; i < TOTAL_BIRDS; i++) {

            // TODO: always zero, why?
            center_of_mass_relative =
                (TOTAL_BIRDS / (TOTAL_BIRDS - 1)) * center_of_mass - (1 / (TOTAL_BIRDS - 1)) * birds[i].position;

            birds[i].velocity += (-1) * birds[i].position + center_of_mass_relative;
        }

        // update position based off velocity
        for (int i = 0; i < TOTAL_BIRDS; i++) {
            birds[i].position += birds[i].velocity;
        }

        // printf stuff
        write_data(birds, current_steps);

        // apply rules for bird-obstacle interaction
        // TODO implement obstacle avoidance for the Boids
        current_steps++;
    }
    free(birds);
    printf("done\n");
}

void write_data(boid birds[], int current_steps) {
    char *file_name;
    asprintf(&file_name, (data_dir + "/birds%d").c_str(), current_steps);
    std::ofstream birds_file(file_name);

    for (int i = 0; i < TOTAL_BIRDS; i++) {

        birds_file << (float)birds[i].position.x << "\t" << (float)birds[i].position.y << "\n";
    }
    birds_file.close();
    free(file_name);
}
