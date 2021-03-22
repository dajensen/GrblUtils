#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <math.h>

#include <string>
#include <vector>
#include <optional>
#include "log.h"
#include "Utils.h"
#include <libevdev/libevdev.h>

#include "input.h"
#include "gamepad.h"


void Gamepad::print_abs_bits(struct libevdev *dev, int axis)
{
	const struct input_absinfo *abs;

	if (!libevdev_has_event_code(dev, EV_ABS, axis))
		return;

	abs = libevdev_get_abs_info(dev, axis);

	log_printf(DEBUG, "    Value    %6d\n", abs->value);
	log_printf(DEBUG, "    Min	%6d\n", abs->minimum);
	log_printf(DEBUG, "    Max	%6d\n", abs->maximum);
	if (abs->fuzz)
		log_printf(DEBUG, "    Fuzz    %6d\n", abs->fuzz);
	if (abs->flat)
		log_printf(DEBUG, "    Flat    %6d\n", abs->flat);
	if (abs->resolution)
		log_printf(DEBUG, "    Resolution    %6d\n", abs->resolution);
}

void Gamepad::print_code_bits(struct libevdev *dev, unsigned int type, unsigned int max)
{
	unsigned int i;
	for (i = 0; i <= max; i++) {
		if (!libevdev_has_event_code(dev, type, i))
			continue;

		log_printf(DEBUG, "    Event code %i (%s)\n", i, libevdev_event_code_get_name(type, i));
		if (type == EV_ABS)
			print_abs_bits(dev, i);
	}
}

void Gamepad::print_bits(struct libevdev *dev)
{
	unsigned int i;
	log_printf(DEBUG, "Supported events:\n");

	for (i = 0; i <= EV_MAX; i++) {
		if (libevdev_has_event_type(dev, i))
			log_printf(DEBUG, "    Event type %d (%s)\n", i, libevdev_event_type_get_name(i));
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


void Gamepad::print_props(struct libevdev *dev)
{
	unsigned int i;
	log_printf(DEBUG, "Properties:\n");

	for (i = 0; i <= INPUT_PROP_MAX; i++) {
		if (libevdev_has_property(dev, i))
			log_printf(DEBUG, "    Property type %d (%s)\n", i, libevdev_property_get_name(i));
	}
}

std::optional<Gamepad::DevInfo> Gamepad::IsDesiredDevice(const std::string fullpath, std::vector<std::string> detectstrings) {
    int fd = open(fullpath.c_str(), O_RDONLY|O_NONBLOCK);
    if(fd > -1) {
        fcntl(fd, F_SETFD, O_NONBLOCK);
        struct libevdev *evdev = NULL;    
        int ret = libevdev_new_from_fd(fd, &evdev);
        if(ret > -1) {
            std::string devname(libevdev_get_name(evdev));
            log(DEBUG, "Input device name: " +  devname);
            for(auto detectstr : detectstrings) {
                if(contains(devname, detectstr)) {
                    log(DEBUG, "FOUND the GAMEPAD\n");
                    print_bits(evdev);
                    log(DEBUG, "\n\n");
                    print_props(evdev);
                    log(DEBUG, "\n\n");
                    return std::optional<DevInfo>(DevInfo(fd, evdev));
                }
            }
            libevdev_free(evdev);
        }
        close(fd);
    }
    return std::nullopt;
}

std::optional<Gamepad::DevInfo> Gamepad::get_xbox_fd(const std::string &inputdir, std::vector<std::string> &detectstrings){
    std::vector<std::string> dirlist = list_directory(inputdir);
    const std::string prefix("event");
    
     for(auto filename : dirlist) {
        if(startswith(filename, prefix)){
            std::string fullpath = path_join(inputdir, filename);
            log(DEBUG, "Dir: " + fullpath);
            auto devinfo = IsDesiredDevice(fullpath, detectstrings);
            if(devinfo)
                return devinfo;
        }
    }
    return std::nullopt;
}

void Gamepad::print_status() {
    log_printf(DEBUG, "Left:%d,%d,%d  Right:%d,%d,%d  Hat:%d,%d A:%d B:%d X:%d Y:%d L:%d R:%d TL:%d TR:%d SEL:%d START:%d MODE:%d\n", 
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

// ***************************************************************************************
// Constructor
// ***************************************************************************************
Gamepad::Gamepad() {
    const std::string inputdir("/dev/input");
    std::vector<std::string> detectstrings = {
        "Xbox One",
        "X-Box"
    };

    device_info = get_xbox_fd(inputdir, detectstrings);
    if(!device_info) {
        log(DEBUG, "Couldn't find a gamepad device\n");
    }
}

int Gamepad::calc_speed(int joystick_val) {
    if(joystick_val < 5000)
        return false;
    return (int)(4000.0 * pow(joystick_val - 5000.0, 2.0) / 771006289.0);    
}

double Gamepad::scale_value(int val) {
    if(val > JOYSTICK_THRESHOLD) {
        return 1;                       // Calculate how far you could have traveled since last poll at max speed, and go that far.
    }
    else if(val < -JOYSTICK_THRESHOLD) {
        return -1;
    }
    return 0;
}

int Gamepad::find_greatest(std::vector<int> vals) {
    int rv = 0;
    for( auto val : vals){
        if(val > rv)
            rv = val;
    }
    return rv;
}

uint32_t Gamepad::update_event_mask(uint16_t event, uint16_t value) {
    bool modified = btn_l || btn_r;
    uint32_t rv = 0;

    if(value) {
        switch(event) {
        case BTN_A: 
            rv |= modified ? INPUT_A_ZERO : INPUT_A_GOTO; 
            break;
        case BTN_B:
            rv |= modified ? INPUT_Z_ZERO : INPUT_Z_GOTO; 
            break;
        case BTN_X:
            rv |= modified ? INPUT_X_ZERO : INPUT_X_GOTO; 
            break;
        case BTN_Y:
            rv |= modified ? INPUT_Y_ZERO : INPUT_Y_GOTO; 
            break;
        }        
    }
    return rv;
}


Input::Changes Gamepad::Check() {
    Input::Changes changes;
    int ret = 0;
    static unsigned long prevtime = 0;
    unsigned long newtime = millis();

//    if(prevtime > 0)
//        log(DEBUG, "Betwen polling: " + std::to_string(newtime - prevtime));

    while(ret >= 0) {
        struct input_event ev; 
        ret = libevdev_next_event(device_info.value().evdev, must_sync ? LIBEVDEV_READ_FLAG_SYNC : LIBEVDEV_READ_FLAG_NORMAL, &ev);
        if(ret == LIBEVDEV_READ_STATUS_SUCCESS) {
            switch (ev.type) {
                case EV_ABS:
                    switch (ev.code) {
                        case ABS_X: { sl_x = ev.value;} break;
                        case ABS_Y: { sl_y = ev.value;} break;
                        case ABS_Z: { sl_z = ev.value; } break;
                        case ABS_RX: { sr_x = ev.value;} break;
                        case ABS_RY: { sr_y = ev.value;} break;
                        case ABS_RZ: { sr_z = ev.value; } break;
                        case ABS_HAT0X: { hat0x = ev.value; } break;
                        case ABS_HAT0Y: { hat0y = ev.value; } break;
                    }
                    break;
                case EV_KEY:
                    switch (ev.code) {
                        case BTN_A: { btn_a = ev.value; changes.events |= update_event_mask(ev.code, ev.value);} break;
                        case BTN_B: { btn_b = ev.value; changes.events |= update_event_mask(ev.code, ev.value);} break;
                        case BTN_X: { btn_x = ev.value; changes.events |= update_event_mask(ev.code, ev.value);} break;
                        case BTN_Y: { btn_y = ev.value; changes.events |= update_event_mask(ev.code, ev.value);} break;
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
                print_status();
            }
        }
        else if(ret == LIBEVDEV_READ_STATUS_SYNC) {
            log(DEBUG, "SYNC\n");
            must_sync = true;
        }
    }

    changes.feedrate = calc_speed(find_greatest(std::vector<int>{sr_x, sr_y, sl_x, sl_y}));
    log(DEBUG, std::to_string(changes.feedrate));
    changes.x = scale_value(sr_x);
    changes.y = -scale_value(sr_y);  // Y axis is inverted on the gamepad
    changes.z = -scale_value(sl_y);  // Y axis is inverted on the gamepad
    changes.a = scale_value(sl_x);

    must_sync = false;
    prevtime = newtime;
    return changes;
}
