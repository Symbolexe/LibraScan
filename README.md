# LibraScan: Dependency Scanner & Requirement Extractor
LibraScan is a tool designed to simplify the management of dependencies in Python and Ruby projects by automatically generating requirements.txt and Gemfile files based on your project's import statements.
# Features
- Python Support: Automatically detects and extracts third-party Python libraries used in your project, excluding standard library modules.
- Ruby Support: Parses require statements in Ruby files (*.rb) to generate a Gemfile listing required gems.
- Accurate Detection: Uses stdlib_list to ensure standard Python library modules are not included in requirements.txt.
- Error Handling: Provides basic error handling for file parsing and generation processes.
# Installation
- Clone the Repository:
```git clone https://github.com/Symbolexe/LibraScan.git```
- Navigate to the Directory:
```cd LibraScan```
## CMAKE
### MacOS
```bash
brew install cmake
```
### Linux
```bash
sudo apt-get install cmake
sudo yum install cmake
```
## Build
### MacOS & Linux
```bash
mkdir build
cd build
cmake ..
make
sudo make install
```
### Windows
```bash
mkdir build
cd build
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
```
# Usage
- Generating ```requirements.txt``` for Python Projects
```bash
./LibraScan file.py
```
- Generating ```Gemfile``` for Ruby Projects
```bash
python ./LibraScan file.rb
```
