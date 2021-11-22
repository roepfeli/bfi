#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEM_SIZE (512)

size_t read_in_file(char* filename, char** buffer_ptr)
{
    // open file
    FILE* file = fopen(filename, "r");

    // get length of file
    fseek(file , 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file , 0, SEEK_SET);

    *buffer_ptr = malloc(length+1);

    fread(*buffer_ptr, 1, length, file);

    (*buffer_ptr)[length] = '\0';

    return length;
}

size_t get_pos_of_matching_bracket(char bracket, char* instructions, size_t length, size_t crnt_pos)
{
    if (bracket == '[')
    {
        size_t pos = crnt_pos + 1;
        size_t opening_brackets = 1;

        for (; opening_brackets != 0 && pos < length; ++pos)
        {
            if (*(instructions + pos) == '[')
            {
                opening_brackets++;
            }

            else if (*(instructions + pos) == ']')
            {
                opening_brackets--;
            }
        }

        return pos-1;
    }

    else 
    {
        size_t pos = crnt_pos - 1;
        size_t closing_brackets = 1;

        for (; closing_brackets != 0 && pos >= 0; --pos)
        {
            if (*(instructions + pos) == ']')
            {
                closing_brackets++;
            }

            else if (*(instructions + pos) == '[')
            {
                closing_brackets--;
            }
        }

        return pos+1;
    }
}

int main (int argc, char** argv)
{
    if (argc != 2)
    {
        printf("ERROR: Wrong number of arguments.\n");
        printf("Usage: %s <main.bf> \n", argv[0]);
        return 1;
    }

    char* instructions = NULL;

    size_t length = read_in_file(argv[1], &instructions) - 1;

    char memory[MEM_SIZE] = { 0 };

    char* data_ptr = memory;

    for (size_t i = 0; i < length; ++i)
    {
        switch (instructions[i])
        {
            case '<':
                ++data_ptr;
            break;
            case '>':
                --data_ptr;
            break;
            case '+':
                ++*data_ptr;
            break;
            case '-':
                --*data_ptr;
            break;
            case '.':
                printf("%c", *data_ptr);
            break;
            case ',':
                *data_ptr = getchar();
            break;
            case '[':
                if (*data_ptr == 0)
                {
                    i = get_pos_of_matching_bracket('[', instructions, length, i) + 1;
                    
                }
            break;
            case ']':
                if (*data_ptr)
                {
                    i = get_pos_of_matching_bracket(']', instructions, length, i) + 1;
                    
                }
            break;
        }
    }

    free(instructions);

    return 0;
}
