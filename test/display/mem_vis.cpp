#include <bits/stdc++.h>

int main(int argc, char* argv[]) {
    std::string filepath = "./memory.txt";
    std::ifstream file(filepath);

    std::string outfile = "./memory_out.txt";

    freopen(outfile.c_str(), "w+", stdout);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filepath << std::endl;
        return 1;
    }

    int c = 0;

    while (!file.eof()) {
        std::string line;
        std::getline(file, line);
        int n = line.length();
        if(n > 1){
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '0') {
                    line[i] = ' ';
                }
                else {
                    line[i] = '*';
                }
            }
            std::cout << line;
            c++;
        }
        if (c == 80) {
            std::cout << "\n";
            c = 0;
        }
    }

    file.close();
    fclose(stdout);
}