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
#include <algorithm> 
#include <cmath> 
#include <vector>
#include <fstream>
#include "Utils.h"

void encodeFile(const char* fileName) {
    std::ifstream file(fileName, std::ifstream::binary);

    const std::string fileName_s = fileName;

    if (!fileExists(fileName))
    {
        std::cout << "No valid file provided" << "\n";
        return;
    }

#ifdef _WIN32

    struct _stat64 filestat;
    _stat64(fileName, &filestat);

#else

    struct stat64 filestat;
    stat64(fileName, &filestat);

#endif

    const size_t totalSize = filestat.st_size;
    size_t chunkSize = 0;

    chunkSize = 16 * 1024;

    size_t chunks = totalSize / chunkSize;
    size_t sizeLastChunk = totalSize % chunkSize;

    if (sizeLastChunk != 0)
    {
        ++chunks;
    }
    else
    {
        sizeLastChunk = chunkSize;
    }

    std::ofstream ofs;
    ofs.open(fileName_s + ".qdc", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    std::ofstream readFile(fileName_s + ".qdc", std::fstream::in | std::fstream::out | std::fstream::app);
    if (readFile.is_open())
    {
    for (size_t chunk = 0; chunk < chunks; ++chunk)
    {
        const size_t currentChunkSize =
            chunk == chunks - 1
            ? sizeLastChunk
            : chunkSize;

        std::vector<char> chunkData(currentChunkSize);
        file.read(&chunkData[0],
            currentChunkSize);

        for (const char c : chunkData)
        {
            const std::string s(1, c);
          
            readFile << ToQuadFile(s);
        }
    }
    readFile.close();
    }
}

void decodeFile(const char* fileName) {
    std::ifstream file(fileName, std::ifstream::binary);

    const std::string fileName_s = fileName;

    if (!fileExists(fileName))
    {
        std::cout << "No valid file provided" << "\n";
        return;
    }

#ifdef _WIN32

    struct _stat64 filestat;
    _stat64(fileName, &filestat);

#else

    struct stat64 filestat;
    stat64(fileName, &filestat);

#endif

    const size_t totalSize = filestat.st_size;
    size_t chunkSize = 0;

    chunkSize = 16 * 1024;

    size_t chunks = totalSize / chunkSize;

    size_t sizeLastChunk = totalSize % chunkSize;

    if (sizeLastChunk != 0)
    {
        ++chunks;
    }
    else
    {
        sizeLastChunk = chunkSize;
    }

    std::ofstream ofs;
    ofs.open(fileName_s.substr(0, fileName_s.length() - 4), std::ofstream::out | std::ofstream::trunc);
    ofs.close();
    std::ofstream readFile(fileName_s.substr(0, fileName_s.length() - 4), std::ios_base::binary | std::fstream::app);
    if (readFile.is_open())
    {   
        for (size_t chunk = 0; chunk < chunks; ++chunk)
        {
            const size_t currentChunkSize =
                chunk == chunks - 1
                ? sizeLastChunk
                : chunkSize;

            std::vector<char> chunkData(currentChunkSize);
            file.read(&chunkData[0],
                currentChunkSize);
        
            std::string str(chunkData.begin(), chunkData.end());
            std::string output = "";
            const int length = (int) str.length();
            const int segments = length / 4;

            for (int i = 0; i < segments; i++) {
                const int begin = i * 4;
                const int binVal = fromBinary(str.substr(begin, 4));
                readFile << (unsigned char) binVal;
            }
        }
        readFile.close();
    }
}

int main(int argc, const char* argv[])
{
    setlocale(LC_ALL, "en-US");

    const std::string help = "--help";

    const std::string enc = "-e";

    const std::string dec = "-d";

    if (argc < 2) {
        std::cout << "Please use `quadric --help` for the usage guide" << "\n";
    }
    else if(argc < 3 && help.compare(argv[1]) == 0){
        #ifdef _WIN32
        std::cout << "      -- THIS DEMO HAS BEEN COMPILED FOR WINDOWS x86-64--" << "\n\n";
        #else
        std::cout << "      -- THIS DEMO HAS BEEN COMPILED FOR LINUX / MAC--" << "\n\n";
        #endif
        std::cout << "      -- Quadric v3 Demo Help --" << "\n\n";
        std::cout << "  -e <TEXT>       |   encode a specific file" << "\n";
        std::cout << "  -d <QUADv3>     |   decode a .qdc file" << "\n\n";
        std::cout << "      Copyright 2020 Jomcraft Network" << "\n";
    }
    else if (argc < 4) {
        if (enc.compare(argv[1]) == 0) {
            encodeFile(argv[2]);
            std::cout << "File successfully wrapped!" << "\n";
        } else if (dec.compare(argv[1]) == 0) {
            decodeFile(argv[2]);
            std::cout << "File successfully unwrapped!" << "\n";
        }
        else {
            std::cout << "Please use `quadric --help` for the usage guide" << "\n";
        }
    }
}