#include <iostream>
#include <fstream>
#include <string>
#include <stack>

int main() {
    std::ifstream infile("code.by");
    std::ofstream outfile("code.py");

    if (!infile.is_open() || !outfile.is_open()) {
        std::cerr << "Error opening files!" << std::endl;
        return 1;
    }

    std::string line;
    int indentLevel = 0;
    const std::string indent = "    "; // 4 spaces

    while (std::getline(infile, line)) {
        std::string trimmed;
        // Trim leading/trailing whitespace
        size_t start = line.find_first_not_of(" \t");
        size_t end = line.find_last_not_of(" \t");
        if (start != std::string::npos)
            trimmed = line.substr(start, end - start + 1);

        if (trimmed.empty()) {
            outfile << "\n";
            continue;
        }

        if (trimmed == "}") {
            indentLevel--;
            continue;
        }

        // Handle opening brace
        size_t bracePos = trimmed.find('{');
        if (bracePos != std::string::npos) {
            trimmed.replace(bracePos, 1, ":");
            outfile << std::string(indentLevel * indent.size(), ' ') << trimmed << "\n";
            indentLevel++;
        } else {
            outfile << std::string(indentLevel * indent.size(), ' ') << trimmed << "\n";
        }
    }

    infile.close();
    outfile.close();

    std::cout << "Conversion complete. Output written to code.py" << std::endl;
    return 0;
}
