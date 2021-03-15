#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <poll.h>

#include <string>
#include <vector>
#include "Utils.h"
#include <libevdev/libevdev.h>


void print_abs_bits(struct libevdev *dev, int axis)
{
	const struct input_absinfo *abs;

	if (!libevdev_has_event_code(dev, EV_ABS, axis))
		return;

	abs = libevdev_get_abs_info(dev, axis);

	printf("	Value	%6d\n", abs->value);
	printf("	Min	%6d\n", abs->minimum);
	printf("	Max	%6d\n", abs->maximum);
	if (abs->fuzz)
		printf("	Fuzz	%6d\n", abs->fuzz);
	if (abs->flat)
		printf("	Flat	%6d\n", abs->flat);
	if (abs->resolution)
		printf("	Resolution	%6d\n", abs->resolution);
}

void print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max)
{
	unsigned int i;
	for (i = 0; i <= max; i++) {
		if (!libevdev_has_event_code(dev, type, i))
			continue;

		printf("    Event code %i (%s)\n", i, libevdev_event_code_get_name(type, i));
		if (type == EV_ABS)
			print_abs_bits(dev, i);
	}
}

void print_bits(struct libevdev *dev)
{
	unsigned int i;
	printf("Supported events:\n");

	for (i = 0; i <= EV_MAX; i++) {
		if (libevdev_has_event_type(dev, i))
			printf("  Event type %d (%s)\n", i, libevdev_event_type_get_name(i));
		switch(i) {
			case EV_KEY:
				print_code_bits(dev, EV_KEY, KEY_MAX);
				break;
			case EV_REL:
				print_code_bits(dev, EV_REL, REL_MAX);
				break;
			case EV_ABS:
				print_code_bits(dev, EV_ABS, ABS_MAX);
				break;
			case EV_LED:
				print_code_bits(dev, EV_LED, LED_MAX);
				break;
		}
	}
}


void print_props(struct libevdev *dev)
{
	unsigned int i;
	printf("Properties:\n");

	for (i = 0; i <= INPUT_PROP_MAX; i++) {
		if (libevdev_has_property(dev, i))
			printf("  Property type %d (%s)\n", i, libevdev_property_get_name(i));
	}
}

int get_xbox_fd(const std::string &inputdir, std::vector<std::string> &detects, std::string &devname, struct libevdev * &evd){
    const std::string prefix("event");
    int rv = -1;
    DIR *dir = opendir(inputdir.c_str());

    if(dir) {
        struct dirent *pDE = readdir(dir);

        while(pDE != NULL) {
            std::string filename = std::string(pDE->d_name);
            if(startswith(filename, prefix)){
                std::string fullpath = inputdir + "/" + filename;
                printf("Dir: %s\n", fullpath.c_str());

                int fd = open(fullpath.c_str(), O_RDONLY|O_NONBLOCK);
                if(fd > -1) {
                    fcntl(fd, F_SETFD, O_NONBLOCK);
                    struct libevdev *evdev = NULL;    
                    int ret = libevdev_new_from_fd(fd, &evdev);
                    if(ret > -1) {
                        std::string devname(libevdev_get_name(evdev));
                        printf("Input device name: \"%s\"\n", devname.c_str());
                        for(auto detectstr : detects) {
                            if(contains(devname, detectstr)) {
                                printf("FOUND IT ******************!\n");
                                print_bits(evdev);
                                printf("\n\n");
                                print_props(evdev);
                                printf("\n\n");
                                evd = evdev;
                                devname = fullpath;
                                return fd;
                            }
                        }
                        libevdev_free(evdev);
                    }
                    close(fd);
                }
            }
            pDE = readdir(dir);
        }
    }
    return rv;
}

bool WaitForReadable(int fd, int timeout) {
    
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;

    int rv = poll(&pfd, 1, timeout);
    return rv > 0;
}


int main () {
    const std::string inputdir("/dev/input");
    std::vector<std::string> detectstrings = {
        "Xbox One",
        "X-Box"
    };
    std::string devicename;

    struct libevdev * evdev = NULL;
    int fd = get_xbox_fd(inputdir, detectstrings, devicename, evdev);
    if(fd < 0) {
        printf("Couldn't find a device\n");
        exit(-1);
    }

    int sl_x = 0;
    int sl_y = 0;
    int sl_z = 0;
    int sr_x = 0;
    int sr_y = 0;
    int sr_z = 0;
    int hat0x = 0;
    int hat0y = 0;
    int btn_a = 0;
    int btn_b = 0;
    int btn_x = 0;
    int btn_y = 0;
    int btn_l = 0;
    int btn_r = 0;
    int btn_thumbl = 0;
    int btn_thumbr = 0;
    int btn_select = 0;
    int btn_start = 0;
    int btn_mode = 0;

    bool must_sync = false;
    while (true) {
        if(WaitForReadable(fd, 5000)){
            int rv = -EAGAIN;
            while(rv == -EAGAIN) {
                struct input_event ev; 
                int rv = libevdev_next_event(evdev, must_sync ? LIBEVDEV_READ_FLAG_SYNC : LIBEVDEV_READ_FLAG_NORMAL, &ev);
                if(rv == LIBEVDEV_READ_STATUS_SUCCESS) {
                    switch (ev.type) {
                        case EV_ABS:
                            switch (ev.code) {
                                case ABS_X: { sl_x = ev.value; } break;
                                case ABS_Y: { sl_y = ev.value; } break;
                                case ABS_Z: { sl_z = ev.value; } break;
                                case ABS_RX: { sr_x = ev.value; } break;
                                case ABS_RY: { sr_y = ev.value; } break;
                                case ABS_RZ: { sr_z = ev.value; } break;
                                case ABS_HAT0X: { hat0x = ev.value; } break;
                                case ABS_HAT0Y: { hat0y = ev.value; } break;
                            }
                            break;
                        case EV_KEY:
                            switch (ev.code) {
                                case BTN_A: { btn_a = ev.value; } break;
                                case BTN_B: { btn_b = ev.value; } break;
                                case BTN_X: { btn_x = ev.value; } break;
                                case BTN_Y: { btn_y = ev.value; } break;
                                case BTN_TL: { btn_l = ev.value; } break;
                                case BTN_TR: { btn_r = ev.value; } break;
                                case BTN_THUMBL: { btn_thumbl = ev.value; } break;
                                case BTN_THUMBR: { btn_thumbr = ev.value; } break;
                                case BTN_SELECT: { btn_select = ev.value; } break;
                                case BTN_START: { btn_start = ev.value; } break;
                                case BTN_MODE: { btn_mode = ev.value; } break;
                            } 
                            break;
                    }
                    if(ev.type != EV_SYN) {
                        printf("Left:%d,%d,%d  Right:%d,%d,%d  Hat:%d,%d A:%d B:%d X:%d Y:%d L:%d R:%d TL:%d TR:%d SEL:%d START:%d MODE:%d\n", 
                            sl_x,
                            sl_y,
                            sl_z,
                            sr_x,
                            sr_y,
                            sr_z,
                            hat0x,
                            hat0y,
                            btn_a,
                            btn_b,
                            btn_x,
                            btn_y,
                            btn_l,
                            btn_r,
                            btn_thumbl,
                            btn_thumbr,
                            btn_select,
                            btn_start,
                            btn_mode
                        );
                    }
                }
                if(rv == LIBEVDEV_READ_STATUS_SYNC) {
                    printf("SYNC\n");
                    must_sync = true;
                }
            }
            must_sync = false;
        }
    }
}
