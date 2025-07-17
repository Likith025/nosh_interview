#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_BUFFER_SIZE 1024
unsigned char sensor_buffer[MAX_BUFFER_SIZE];
int buffer_len = 0;

void simulate_sensor_tick(int current_second) {
    int num_bytes = rand() % 6;
    for (int i = 0; i < num_bytes && buffer_len < MAX_BUFFER_SIZE; ++i) {
        sensor_buffer[buffer_len++] = rand() % 256;
    }
    printf("Second: %d, Buffer length: %d\n", current_second, buffer_len);
}

void print_and_remove_50_bytes() {
    if (buffer_len >= 50) {
        printf("Printing latest 50 bytes: ");
        for (int i = buffer_len - 1; i >= buffer_len - 50; --i) {
            printf("%X ", sensor_buffer[i]);
        }
        printf("\n");
        buffer_len -= 50;   
    }
}

void simulate_delay(int seconds) {
    volatile unsigned long long count;
    for (int s = 0; s < seconds; ++s) {
        count = 0;
        for (unsigned long long i = 0; i < 400000000ULL; ++i) {
            count += i;
        }
    }
}

int main() {
    srand(time(NULL));
    int total_seconds = 100;
    for (int second = 1; second <= total_seconds; ++second) {
        simulate_sensor_tick(second);
        if (second % 10 == 0) {
            print_and_remove_50_bytes();
            simulate_delay(10);
        }
        simulate_delay(1);
    }
    printf("Simulation complete. Remaining bytes in buffer: %d\n", buffer_len);
    return 0;
}


