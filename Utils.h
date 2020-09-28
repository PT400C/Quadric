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
    r.reserve(4);
    while (n != 0) {

        const int value = n - (n / 4) * 4;

        switch (value) {
        case 0: {
            r.insert(0, 1, 'A');
            break;
        }
        case 1: {
            r.insert(0, 1, 'T');
            break;
        }
        case 2: {
            r.insert(0, 1, 'G');
            break;
        }
        case 3: {
            r.insert(0, 1, 'C');
            break;
        }
        }

        n /= 4;
    }
    return r;
}

inline int fromBinary(std::string n)
{
    int r = 0;
    int index = 0;

    std::reverse(n.begin(), n.end());
    for (const char c : n) {
        const long factor = powl(4, index);
        switch (c) {
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

inline std::string ToQuadFile(const unsigned char s)
{
    std::string ret;
    std::string bin = toBinary((const int)s);

    while (bin.length() < 4) {
        bin = "A" + bin;
    }
    ret = ret + bin;

    return ret;
}

inline bool fileExists(const std::string& name) {
#ifdef _WIN32
    struct _stat64 buffer;
    return (_stat64(name.c_str(), &buffer) == 0);
#else
    struct stat64 buffer;
    return (stat64(name.c_str(), &buffer) == 0);
#endif
}