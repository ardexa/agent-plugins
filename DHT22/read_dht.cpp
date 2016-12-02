// (c) Ardexa Pty Ltd 2016

#include <string>
#include <cstring>
#include <iostream>
#include <sys/statvfs.h>
#include "pi_2_dht_read.h"

using namespace std;

int main(int argc, char * argv[]) 
{
	int pin = 4;
	int sensor_type = DHT22;
	float humidity = -9999.9;
	float temperature = -9999.9;	

    if (argc > 2 || (argc == 2 && strcmp(argv[1], "hum") && strcmp(argv[1], "temp"))) {
        cout << "Usage: " << argv[0] << " [temp|hum]" << endl;
        return 1;
    }
	
    int attempt = 0;
    while (true) {
        int ret = pi_2_dht_read(sensor_type, pin, &humidity, &temperature);		
        if (ret == DHT_ERROR_GPIO) {
            cerr << "ERROR: Failed to initialise GPIO. Try running with sudo." << endl;
            return 1;
        } else if (ret == DHT_SUCCESS) {
            if (argc == 2) {
                if (strcmp(argv[1], "temp") == 0) {
                    cout << temperature;
                } else if (strcmp(argv[1], "hum") == 0) {
                    cout << humidity;
                }
            } else {
                cout << "Temperature: " << temperature << " and humidty: " << humidity << endl;
            }
            return 0;
        }
        attempt++;
        if (attempt > 10) {
            cerr << "ERROR: Failed to find results after 10 tries" << endl;
            return 1;
        }
    }
}



