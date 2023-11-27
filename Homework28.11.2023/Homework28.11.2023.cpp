#include <iostream>
#include <fstream>
#include <ctime>

int main()
{
    srand(time(0));
    std::fstream first;
    first.open("first.txt", std::ios_base::out | std::ios_base::binary);
    if (!first)
    {
        std::cout << "Can't open first.txt" << std::endl;
        return 1;
    }
    char input[1024];
    char tmp;
    for (size_t i = 0; i < 16777216 / 1024; ++i)
    {
        for (size_t j = 0; j < 1024; ++j)
        {
            do
            {
                tmp = static_cast<unsigned char>(rand());
            } while (tmp == EOF);
            input[j] = tmp;
        }
        first.write(input, 1024);
    }
    first.close();
    //!!!!!!!!!!!!!!!!
    std::fstream first2;
    first2.open("first.txt", std::ios_base::in | std::ios_base::binary);
    if (!first2)
    {
        std::cout << "Can't open first.txt" << std::endl;
        return 2;
    }
    std::fstream second;
    second.open("second.txt", std::ios_base::out);
    if (!second)
    {
        first2.close();
        std::cout << "Can't open second.txt" << std::endl;
        return 3;
    }
    double value = 0.0;
    int count1 = 0;
    while (first2.peek()!=EOF)
    {
        first2.read((char*)(&value), 8);
        if (static_cast<char>(value) != EOF)
        {
            second << " " << value;
        }
        else
        {
            value = 1.0;
            second << " " << value;
        }
        ++count1;
    }
    first2.close();
    second.close();
    std::cout << "count1 = " << count1 << std::endl;
    //!!!!!!!!!!!!!!
    std::fstream second2;
    second2.open("second.txt", std::ios_base::in);
    if (!second2)
    {
        std::cout << "Can't open second.txt" << std::endl;
        return 4;
    }
    std::fstream third;
    third.open("third.txt", std::ios_base::out | std::ios_base::binary);
    if (!third)
    {
        second2.close();
        std::cout << "Can't open third.txt" << std::endl;
        return 5;
    }
    double value2 = 0.0;
    int count2 = 0;
    while (second2.peek() != EOF)
    {
        second2 >> value2;
        if (static_cast<char>(value2) == EOF)
        {
            third.write("notmypro", 8);
        }
        else
        {
            third.write((char*)(&value2), 8);
        }
        ++count2;
    }
    second2.close();
    third.close();
    std::cout << "count2 = " << count2 << std::endl << "it's all" << std::endl;
    return 0;
}