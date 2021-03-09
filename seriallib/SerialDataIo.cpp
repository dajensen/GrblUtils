#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <stdint.h>
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <string>

#include "log.h"
#include "SerialDataIo.h"

SerialDataIoImpl::SerialDataIoImpl() {

}

SerialDataIoImpl::~SerialDataIoImpl(){

}

bool SerialDataIoImpl::begin(std::string portname) {
    bool rv = false;

    fd = open(portname.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if(fd == -1){
        perror((std::string("open_port: Unable to open %s\n") + portname.c_str()).c_str());
    }
    else {
        fcntl(fd, F_SETFL, FNDELAY);    // Set nonblocking mode
        SetOptions(fd);
        rv = true;
    }
    log(DEBUG, "Serial fd: " + std::to_string(fd));
    return rv;
}

void SerialDataIoImpl::SetOptions(int fd){
        struct termios options;

    // Get the current options for the port
    tcgetattr(fd, &options);

    // Set the baud rates to 115200
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    // Enable the receiver and set local mode
    options.c_cflag |= (CLOCAL | CREAD);

   // Set the character size to 8
    options.c_cflag &= ~CSIZE; /* Mask the character size bits */
    options.c_cflag |= CS8;    /* Select 8 data bits */

    // Set no parity
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;

    // No hardware flow control
    options.c_cflag &= ~CRTSCTS;

    // No software flow control (XON/XOFF)
    options.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Settings to NOT change carriage return to line feed from here: https://stackoverflow.com/questions/42209980/serial-port-binary-transfer-changes-carriage-return
    options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IUCLC | IMAXBEL | IUTF8);

    // Raw input (not canonical)
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG | ECHOK | ECHONL | NOFLSH | TOSTOP);

    // Raw output
    options.c_oflag = ~OPOST;

    tcsetattr(fd, TCSANOW, &options);
}

int SerialDataIoImpl::Read(uint8_t *dest, int len) {
    return read(fd, dest, len);
}

int SerialDataIoImpl::Write(uint8_t *data, int len) {
    return write(fd, data, len);
}
