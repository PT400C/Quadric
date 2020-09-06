/* Proof Of Concept algorithm implementation for base-2 binary to base-4 DNA-coded conversion
 *
 *
 * Copyright 2020 Jomcraft Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissionsand
 * limitations under the License.
 */

#include <iostream>

inline std::string toBinary(int n)
{
    std::string r;
    while (n != 0) {

        const int value = n - (n / 4L) * 4L;

        switch (value) {
        case 0: {
            r = "A" + r;
            break;
        }
        case 1: {
            r = "T" + r;
            break;
        }
        case 2: {
            r = "G" + r;
            break;
        }
        case 3: {
            r = "C" + r;
            break;
        }
        }

        n /= 4L;
    }
    return r;
}

inline int fromBinary(std::string n)
{
    int r = 0;
    int index = 0;

    std::reverse(n.begin(), n.end());
    for (char& c : n) {
        const long factor = (long)powl(4L, (long)index);
        switch (c) {
        case 'A': {
            //  r += 0L * factor;
            break;
        }
        case 'T': {
            r += 1L * factor;
            break;
        }
        case 'G': {
            r += 2L * factor;
            break;
        }
        case 'C': {
            r += 3L * factor;
            break;
        }
        }
        index++;
    }
    return r;
}

inline std::string ToQuadFile(const std::string& s)
{
    std::string ret;

    for (std::string::size_type i = 0; i < s.length(); ++i)
    {
        const char at_i = s[i];
        std::string bin = toBinary((int)(unsigned char)at_i);

        while (bin.length() < 4) {
            bin = "A" + bin;
        }
        ret = ret + bin;
    }

    return ret;
}

/*
inline void FromQuadFile(const std::string name, const std::string& s)
{
    std::string output = "";
    const int length = (int) s.length();
    const int segments = length / 4;
    std::ofstream writeFile(name.substr(0, name.length() - 4), std::ios_base::binary);
    if (writeFile.is_open())
    {
        for (int i = 0; i < segments; i++) {
            const int begin = i * 4;
            int binVal = fromBinary(s.substr(begin, 4));
            writeFile << (unsigned char) binVal;
        }
        writeFile.close();
    }
}
*/

inline bool fileExists(const std::string& name) {
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}