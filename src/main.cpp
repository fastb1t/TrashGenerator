#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>


bool isNumber(const char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

void showHelp()
{
    std::cout <<
        "Usage: TrashGenerator\n"
        "         -h | --help                     - Show help\n"
        "         -f | --file   [file]            - Name of file. if you specified more than one file,\n"
        "                                           then specify [%] in the file name to indicate the\n"
        "                                           file number, otherwise only one file will be\n"
        "                                           created. For example: filename[%].dat\n"
        "         -n | --files  [n]               - n files\n"
        "         -b | --bytes  [n]               - n bytes\n"
        "         -s | --size   [fixed | random]  - Size of file. if --size == fixed, then the file will\n"
        "                                           be created with a fixed size, and if --size == random,\n"
        "                                           then the file will be created with a random size whose\n"
        "                                           maximum value will be what you specified in --bytes\n"
    ;
}

int main(int argc, char *argv[])
{
    std::cout << ">>> TrashGenerator v2.0 <<<\n\n";

    if (argc == 1)
    {
        showHelp();
        return 0;
    }

    enum SIZE_M {
        SIZE_ERROR,
        RANDOM_SIZE,
        FIXED_SIZE
    };

    std::string file;
    long nfiles = 1;
    long nbytes = 0;
    SIZE_M size_m = SIZE_ERROR;

    for (int i = 0; i < argc; i++)
    {
        if (!strcmp(argv[i], "-h") || !strcmp(argv[i], "--help"))
        {
            showHelp();
            return 0;
        }

        if (!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file"))
        {
            if (i + 1 < argc)
            {
                file = argv[i + 1];
            }
            else
            {
                std::cout << "Error! File name not specified.\n";
                return 1;
            }
        }

        if (!strcmp(argv[i], "-n") || !strcmp(argv[i], "--files"))
        {
            if (i + 1 < argc)
            {
                if (!isNumber(argv[i + 1]))
                {
                    std::cerr << "Error! Wrong number of files.\n";
                    return 1;
                }
                else
                {
                    nfiles = atol(argv[i + 1]);
                    if (nfiles <= 0)
                    {
                        std::cerr << "Error! Wrong number of files.\n";
                        return 1;
                    }
                }
            }
            else
            {
                std::cerr << "Error! Number of files not specified.\n";
                return 1;
            }
        }

        if (!strcmp(argv[i], "-b") || !strcmp(argv[i], "--bytes"))
        {
            if (i + 1 < argc)
            {
                if (!isNumber(argv[i + 1]))
                {
                    std::cerr << "Error! Wrong number of bytes.\n";
                    return 1;
                }
                else
                {
                    nbytes = atol(argv[i + 1]);
                    if (nbytes < 0)
                    {
                        std::cerr << "Error! Wrong number of bytes.\n";
                        return 1;
                    }
                }
            }
            else
            {
                std::cerr << "Error! Number of bytes not specified.\n";
                return 1;
            }
        }

        if (!strcmp(argv[i], "-s") || !strcmp(argv[i], "--size"))
        {
            if (i + 1 < argc)
            {
                if (!strcmp(argv[i + 1], "random"))
                {
                    size_m = RANDOM_SIZE;
                }
                else if (!strcmp(argv[i + 1], "fixed"))
                {
                    size_m = FIXED_SIZE;
                }
                else
                {
                    std::cerr << "Error! .\n";
                    return 1;
                }
            }
            else
            {
                std::cerr << "Error! .\n";
                return 1;
            }
        }
    }

    /*
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
    */
    return 0;
}
