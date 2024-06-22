#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>
#include <cstdlib>

// Function to extract Python imports
std::unordered_set<std::string> extractPythonImports(const std::string& filePath) {
    std::unordered_set<std::string> thirdPartyImports;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return thirdPartyImports;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("import ") == 0) {
            size_t start = 7; // length of "import "
            size_t end = line.find('#'); // Check for inline comments
            if (end == std::string::npos) {
                end = line.size();
            }
            std::string importStmt = line.substr(start, end - start);
            size_t commaPos = importStmt.find(',');
            while (commaPos != std::string::npos) {
                std::string moduleName = importStmt.substr(0, commaPos);
                thirdPartyImports.insert(moduleName);
                importStmt = importStmt.substr(commaPos + 1);
                commaPos = importStmt.find(',');
            }
            thirdPartyImports.insert(importStmt);
        } else if (line.find("from ") == 0) {
            size_t start = 5; // length of "from "
            size_t end = line.find(" import ");
            if (end == std::string::npos) {
                end = line.find('#');
            }
            if (end == std::string::npos) {
                end = line.size();
            }
            std::string fromStmt = line.substr(start, end - start);
            thirdPartyImports.insert(fromStmt);
        }
    }

    file.close();
    return thirdPartyImports;
}

// Function to generate requirements.txt for Python files
void generateRequirements(const std::string& filePath) {
    std::unordered_set<std::string> thirdPartyImports = extractPythonImports(filePath);
    if (thirdPartyImports.empty()) {
        std::cout << "No third-party imports found in " << filePath << ". Skipping requirements.txt generation." << std::endl;
        return;
    }

    std::ofstream reqFile("requirements.txt");
    if (!reqFile.is_open()) {
        std::cerr << "Error: Unable to create requirements.txt file." << std::endl;
        return;
    }

    for (const auto& module : thirdPartyImports) {
        reqFile << module << std::endl;
    }

    std::cout << "requirements.txt generated successfully." << std::endl;
    reqFile.close();
}

// Function to extract Ruby requires
std::vector<std::string> extractRubyRequires(const std::string& filePath) {
    std::vector<std::string> requires;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return requires;
    }

    std::string line;
    std::regex requireRegex("require ['\"]([^'\"]+)['\"]");

    while (std::getline(file, line)) {
        std::smatch match;
        if (std::regex_search(line, match, requireRegex)) {
            requires.push_back(match[1].str());
        }
    }

    file.close();
    return requires;
}

// Function to generate Gemfile for Ruby files
void generateGemfile(const std::string& filePath) {
    std::vector<std::string> requires = extractRubyRequires(filePath);
    if (requires.empty()) {
        std::cout << "No 'require' statements found in " << filePath << ". Skipping Gemfile generation." << std::endl;
        return;
    }

    std::ofstream gemFile("Gemfile");
    if (!gemFile.is_open()) {
        std::cerr << "Error: Unable to create Gemfile." << std::endl;
        return;
    }

    gemFile << "source 'https://rubygems.org'" << std::endl;
    for (const auto& gem : requires) {
        gemFile << "gem '" << gem << "'" << std::endl;
    }

    std::cout << "Gemfile generated successfully." << std::endl;
    gemFile.close();
}

// Function to generate dependencies based on file type
void generateDependencies(const std::string& filePath) {
    size_t dotPos = filePath.find_last_of('.');
    if (dotPos == std::string::npos) {
        std::cerr << "Error: Invalid file path." << std::endl;
        return;
    }

    std::string extension = filePath.substr(dotPos + 1);
    if (extension == "py") {
        generateRequirements(filePath);
    } else if (extension == "rb") {
        generateGemfile(filePath);
    } else {
        std::cerr << "Unsupported file type. Only .py (Python) and .rb (Ruby) files are supported." << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <file>" << std::endl;
        return 1;
    }

    std::string filePath = argv[1];
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filePath << std::endl;
        return 1;
    }

    generateDependencies(filePath);
    file.close();

    return 0;
}
