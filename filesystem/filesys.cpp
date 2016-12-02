// (c) Ardexa Pty Ltd 2016

#include <unistd.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <sys/statvfs.h>

using namespace std;

float check_filesystem_space(string directory, bool bytes, bool used, bool privileged, bool percent) {
	struct statvfs file_stats;
	float value = 0.0;

	if (statvfs(directory.c_str(), &file_stats) == 0) {
        if (percent) {
            if (bytes) {
                // bavail?
                value = (float) (privileged ? file_stats.f_bfree : file_stats.f_bavail) / (float) file_stats.f_blocks;
            } else {
                value = (float) (privileged ? file_stats.f_ffree : file_stats.f_favail) / (float) file_stats.f_files;
            }
            value *= 100.0;
            if (used) {
                value = 100.0 - value;
            }
        } else {
            if (bytes) {
                value = (float) (privileged ? file_stats.f_bfree : file_stats.f_bavail) * (float) file_stats.f_bsize;
                if (used) {
                    value = ((float) file_stats.f_blocks * (float) file_stats.f_bsize) - value;
                }
            } else {
                value = (float) (privileged ? file_stats.f_ffree : file_stats.f_favail);
                if (used) {
                    value = (float) file_stats.f_files - value;
                }
            }
        }
	} else {
		value = -1.0;
	}
	return value;
}

void usage(const char *app_name) {
    cout << "Calculate the used/free bytes/inodes on the partition hosting a particular folder" << endl;
    cout << endl;
    cout << "Usage: " << app_name << " [-d <folder_name>] [-f] [-h] [-i] [-p] [-s]" << endl;
    cout << endl;
    cout << "   -d  The directory you wish to query. Default: /" << endl;
    cout << "   -f  Output free instead of used" << endl;
    cout << "   -h  Output this help message" << endl;
    cout << "   -i  Examine inodes instead of bytes" << endl;
    cout << "   -p  Output used/free values for privileged users" << endl;
    cout << "   -s  Output the actual used/free instead of percent" << endl;
}

int main(int argc, char** argv) {
	float value;
    bool used = true;
    bool percent = true;
    bool bytes = true;
    bool privileged = false;
	string directory = "/";
    int opt;
    while ((opt = getopt(argc, argv, "d:fhips")) != -1) {
        switch (opt) {
            case 'd': {
                directory = optarg;
                break;
            }
            case 'f': {
                used = false;
                break;
            }
			case 'h': {
                usage(argv[0]);
                exit(0);
			}
			case 'i': {
                bytes = false;
                break;
			}
			case 'p': {
                privileged = true;
                break;
			}
			case 's': {
                percent = false;
                break;
			}
			default: {
                usage(argv[0]);
                exit(1);
            }
        }
    }

	value = check_filesystem_space(directory, bytes, used, privileged, percent);
	if (value >= 0) 
		cout << setprecision(2) << value << endl;
	else
		cerr << "Could not get the free space for the filesystem" << endl;

	return 0;
}



