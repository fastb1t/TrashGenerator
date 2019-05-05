#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cstring>
#include <cstdlib>
#include <ctime>


static inline bool isNumber(const char *str)
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

static inline void showHelp()
{
    std::cout <<
        "Usage: TrashGenerator\n"
        "         -h | --help                     - Show help.\n"
        "         -f | --file   [file]            - Name of file. If you specified more than one file,\n"
        "                                           then specify [%] in the file name to indicate the\n"
        "                                           file number, otherwise only one file will be\n"
        "                                           created. For example: filename[%].dat\n"
        "         -n | --files  [n]               - n files.\n"
        "         -b | --bytes  [n]               - n bytes.\n"
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

    std::string filename;
    long nfiles = 1l;
    long nbytes = 0l;
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
                filename = argv[i + 1];
                i++;
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
                    if (nfiles <= 0l)
                    {
                        std::cerr << "Error! Wrong number of files.\n";
                        return 1;
                    }
                    i++;
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
                    if (nbytes < 0l)
                    {
                        std::cerr << "Error! Wrong number of bytes.\n";
                        return 1;
                    }
                    i++;
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
                    std::cerr << "Error! Wrong file size generation mode.\n";
                    return 1;
                }
                i++;
            }
            else
            {
                std::cerr << "Error! File size generation mode not specified.\n";
                return 1;
            }
        }
    }

    srand(static_cast<size_t>(time(NULL)));
    
    std::string part1;
    std::string part2;

    if (nfiles > 1l)
    {
        size_t pos = filename.find("[%]");
        if (pos != std::string::npos)
        {
            part1 = filename.substr(0, pos);
            part2 = filename.substr(pos + 3, filename.length() - pos - 3);
        }
        else
        {
            std::cerr << "Error! Wrong file name.\n";
            return 1;
        }
    }
    
    std::string tmp;
    for (long i = 0l; i < nfiles; i++)
    {
        if (nfiles > 1l)
        {
            tmp = part1 + std::to_string(i) + part2;
        }
        else
        {
            tmp = filename;
        }

        std::ofstream ofs;
        ofs.open(tmp, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);
        if (ofs.is_open())
        {
            long bytes = 0l;
            if (size_m == RANDOM_SIZE)
            {
                if (nbytes > 0l)
                {
                    bytes = rand() % nbytes;
                }
                else
                {
                    bytes = rand() % std::numeric_limits<long>::max();
                }
            }
            else
            {
                bytes = nbytes;
            }

            for (long j = 0l; j < bytes; j++)
            {
                char c = rand() % (sizeof(char) * 0xFF);
                ofs.write(reinterpret_cast<const char *>(&c), sizeof(char));
            }
            ofs.close();
        }
        else
        {
            std::cerr << "Error! File '" << tmp << "' not created.\n";
        }
    }

    std::cout << "Operation successful!\n";
    return 0;
}
