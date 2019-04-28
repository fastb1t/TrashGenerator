#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    std::cout << ">>> TrashGenerator v1.0 <<<\n\n";

    if (argc != 3)
    {
        std::cout << "Usage: TrashGenerator [file] [n bytes]\n";
        return 1;
    }

    for (int i = 0; i < strlen(argv[2]); i++)
    {
        if (!isdigit(argv[2][i]))
        {
            std::cerr << "Error! Wrong number.\n";
            return 1;
        }
    }
    
    srand(static_cast<size_t>(time(NULL)));

    std::ofstream ofs;
    ofs.open(argv[1], std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
    if (ofs.is_open())
    {
        for (int i = 0; i < atoi(argv[2]); i++)
        {
            char c = rand() % (sizeof(char) * 0xFF);
            ofs.write(reinterpret_cast<const char *>(&c), sizeof(char));
        }
        ofs.close();
        std::cout << "Operation successful!\n";
    }
    else
    {
        std::cerr << "Error! File '" << argv[1] << "' not created.\n";
        return 1;
    }
    return 0;
}
