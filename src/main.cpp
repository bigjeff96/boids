#include "vector2.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#define TOTAL_BIRDS 10
#define MAX_X 10.0f
#define MAX_Y 10.0f
#define TOTAL_STEPS 1000
#define COM_PARAM 0.5f
#define MAX_SPEED 3.0f

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
        center_of_mass = (1.0f / TOTAL_BIRDS) * center_of_mass;

        vec2 center_of_mass_relative = vec2();

        for (int i = 0; i < TOTAL_BIRDS; i++) {

            // TODO: always zero, why?
            center_of_mass_relative =
                (TOTAL_BIRDS / (TOTAL_BIRDS - 1)) * center_of_mass - (1.0f / (TOTAL_BIRDS - 1)) * birds[i].position;

            birds[i].velocity += COM_PARAM * (-1.0f) * birds[i].position + center_of_mass_relative;
        }


        //limit max speed
        float current_norm;
        for (int i = 0; i<TOTAL_BIRDS; i++) {
            if (birds[i].velocity.norm()>MAX_SPEED) {
                current_norm = birds[i].velocity.norm();
                birds[i].velocity = birds[i].velocity * (MAX_SPEED / current_norm);
            }
        }

        // update position based off velocity
        for (int i = 0; i < TOTAL_BIRDS; i++) {
            birds[i].position += birds[i].velocity;

            if (birds[i].position.x > MAX_X) {
                while (birds[i].position.x > MAX_X) {
                    birds[i].position.x -= MAX_X;
                }
            }

            if (birds[i].position.y > MAX_Y) {
                while (birds[i].position.y > MAX_Y) {
                    birds[i].position.y -= MAX_Y;
                }
            }
        }

        assert(birds[0].position.x <= MAX_X);

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
