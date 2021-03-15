
unsigned long millis();
void delay(unsigned int millis);
void dump_data(uint8_t *data, int len);
bool verify_bytes(uint8_t *p1, uint8_t *p2, int len);
bool startswith(std::string str, std::string key);      // Search the beginning of str for key
bool contains(std::string str, std::string key);      // Search the beginning of str for key

extern const std::string WHITESPACE;
std::string ltrim(const std::string& s, const std::string chars_to_strip);
std::string rtrim(const std::string& s, const std::string chars_to_strip);
std::string trim(const std::string& s, const std::string chars_to_strip);
void split(const std::string& s, const char delimiter, std::vector<std::string> &dest);
std::string to_hexstring(uint8_t val);
std::string to_hexstring(uint16_t val);
std::string to_hexstring(uint32_t val);
std::string to_hexstring(uint64_t val);