# SignLanguageTutor
An American sign language recognizer using the Leap Motion controller
- Recognizes the American sign language alphabet
- Presents a word to be signed to the Leap Motion
- Adaptively recognizes similar signs depending on context

# Compilation
Compiles using cmake and make on Linux
- Requires Leap SDK (Set environment variable `LEAP_SDK` to the sdk directory)
- Requires Qt5

        mkdir build
        cd build
        cmake ..
        make

# Usage
Navigate to build directory

        ./signLanguage

