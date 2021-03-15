#include <stdio.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include "Utils.h"

using namespace std;

unsigned long millis() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    unsigned long rv = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
    return rv;
}

void delay(unsigned int millis) {
    usleep(millis * 1000);
}

void dump_data(uint8_t *data, int len) {
    for(int i = 0; i < len; i++) {
        if(i % 16 == 0)
            printf("\n");
        else if(i % 8 == 0)
            printf("   ");
        printf("%02x ", data[i]);
    }
    printf("\n");
}

bool verify_bytes(uint8_t *p1, uint8_t *p2, int len) {
    for(int i = 0; i < len; i++) {
        if(p1[i] != p2[i])
            return false;
    }
    return true;
}

bool startswith(std::string str, std::string key) {
    // A nice answer from here: https://stackoverflow.com/questions/1878001/how-do-i-check-if-a-c-stdstring-starts-with-a-certain-string-and-convert-a
    return str.rfind(key, 0) == 0;
}

bool contains(std::string str, std::string key) {
    return str.find(key) != string::npos;
}

const std::string WHITESPACE = " \n\r\t\f\v";
 
std::string ltrim(const std::string& s, const std::string chars_to_strip)
{
    size_t start = s.find_first_not_of(chars_to_strip);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string rtrim(const std::string& s, const std::string chars_to_strip)
{
    std::string to_strip = WHITESPACE + chars_to_strip;
    size_t end = s.find_last_not_of(to_strip);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string trim(const std::string& s, const std::string chars_to_strip)
{
    return rtrim(ltrim(s, chars_to_strip), chars_to_strip);
}

void split(const std::string& tosplit, const char delimiter, vector<string> &dest) {
    istringstream f(tosplit);
    string s;
    while (getline(f, s, delimiter)) {
        dest.push_back(s);
    }
}

std::string to_hexstring(uint8_t val) {
    char str[40];
    sprintf(str, "0x%02x", val);
    return std::string(str);
}

std::string to_hexstring(uint16_t val) {
    char str[40];
    sprintf(str, "0x%04x", val);
    return std::string(str);
}

std::string to_hexstring(uint32_t val) {
    char str[40];
    sprintf(str, "0x%08x", val);
    return std::string(str);
}

std::string to_hexstring(uint64_t val) {
    char str[40];
    sprintf(str, "0x%16lx", val);
    return std::string(str);
}
