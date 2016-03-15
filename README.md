b# Handy
An American sign language recognizer using the Leap Motion controller
- Recognizes the American sign language alphabet
- Presents a word to be signed to the Leap Motion
- Adaptively recognizes similar signs depending on context

# Theory
Several sign language letters are unique in number and type
of fingers extended, e.g. L is a thumb and index finger
while B is all four fingers. By recognizing which fingers
are extended we narrow the number of possible signs,
continuing until a single sign is reached or there are
multiple signs using the same fingers. These signs are
differentiated using unique key points on each sign,
such as the distance between the tip of the index and middle
finger to determine V or R/U, and the angle between the fingers
to separate R and U.

Some similar letters, such as T and N are difficult to tell apart.
There is a configurable list of similar letters that is used
to resolve this ambiguity, allowing letters to be used in
place of each other depending on context.

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