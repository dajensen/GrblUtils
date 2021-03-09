class LineReader {
  std::ifstream gcfile;
public:
    LineReader(std::string filename) : gcfile(filename) {}
    bool IsOpen() {return gcfile.is_open();}
    bool ReadLine(std::string &out);
};