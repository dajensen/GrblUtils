#ifndef __SERIALDATAIO_H
#define __SERIALDATAIO_H

class SerialDataIoImpl {

public:
    SerialDataIoImpl();
    ~SerialDataIoImpl();

    bool begin(std::string portname);        // portname is unused in Arduino and may be any value
    int Read(uint8_t *dest, int len);
    int Write(uint8_t *data, int len);

private:
    int fd;
    void SetOptions(int fd);
};



#endif  // __SERIALDATAIO_H 