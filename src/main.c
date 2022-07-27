#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <malloc.h>
#include <ctype.h>

char** in(int* p_count_sentence, int capacity, int capacity_two, char** text){
    int count_word = 0;
    char c;
    int start = 1;
    text[0] = (char*)malloc(capacity_two * sizeof(char));
    while ((c = getchar()) != '\n'){
        
        if (count_word == capacity_two)
        {
            capacity_two += 100;
            char* ArrTemp = (char*)realloc(text[*p_count_sentence], capacity_two*sizeof(char));
            if (ArrTemp != NULL)
            {
                text[*p_count_sentence] = ArrTemp;
            }
        }
        if (*p_count_sentence == capacity)
        {
            capacity += 100;
            char** ArrTemp_two = (char**)realloc(text, capacity*sizeof(char*));
            if (ArrTemp_two != NULL)
            {
                text = ArrTemp_two;
            }
        }
        
        
        if(c == '.'){
            text[*p_count_sentence][count_word++] = c;
            text[*p_count_sentence][count_word++] = '\0';
            *p_count_sentence += 1;
            text[*p_count_sentence] = malloc(capacity_two*sizeof(char));
            count_word = 0;
            start = 1;
        }
        else if(c == ' ' && start){ ; }
        else{
            start = 0;
            text[*p_count_sentence][count_word] = c;
            count_word++;
        }
    }
    return text;
}

void out(char** array, int size){
    printf("\n");
    for (int i = 0; i < size; i++)
    {
        printf("%s ", array[i]);
    }
    printf("\n");
}

int delete_repeating_sentence(char** array, int size){
    int i, j, k;
    for (i = 0; i < size - 1; i++)
    {
        for (j = i + 1; j < size; j++)
        {
            if (!(strcasecmp(array[j], array[i]))) // работает только на Линукс
            {   
                for (k = j; k < size - 1; k++)
                {
                    array[k] = array[k + 1];
                }
                i = 0;
                j = 0;
                size--;
            }
        }
    }
    char** ArrT = (char**)realloc(array, size*sizeof(char*));
    if (ArrT != NULL)
    {
        array = ArrT;
    }
    return size;
}

void capital_letter(char** array, int size){
    for (int i = 0; i < size; i++)
    {
        if (array[i][0] >= 'a' && array[i][0] <= 'z')
        {
            array[i][0] = (char)(toupper(array[i][0]));
        }
        for (int j = 1; array[i][j] != '.'; j++)
        {                             // Если сделать остальные символы прописными см в комментарии (была отпечатка в задании)
            if (array[i][j] >= 'A' && array[i][j] <= 'Z') // (array[i][j] >= 'a' && array[i][j] <= 'z')
            {
                array[i][j] = (char)(tolower(array[i][j])); // array[i][j] = (char)(toupper(array[i][j])); 
            }
        }
    }
}

int delete2018(char** array, int size){
    int i, j, k;
    for (i = 0; i < size; i++)
    {
        if (strlen(array[i]) > 4){
            for (j = 0; array[i][j+3] != '.'; j++)
            {
                if (array[i][j] == '2' && array[i][j+1] == '0' && array[i][j+2] == '1' && array[i][j+3] == '8')
                {
                    for (k = i; k < size - 1; k++)
                    {
                        array[k] = array[k+1];
                    }
                    i = 0;
                    j = -1;
                    size = size - 1;
                }   
            }
        }
    }
    char** ArrTe = (char**)realloc(array, size*sizeof(char*));
    if (ArrTe != NULL)
    {
        array = ArrTe;
    }
    return size;
}

void digits(char** array, int size){
    char symbol;
    char** sentence;
    int was_digit = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; array[i][j] != '.'; j++){
            symbol = array[i][j];
            if (isdigit(symbol))
            {
                sentence = &array[i];
                was_digit = 1;
                break;
            }
        }
        if (was_digit == 1){
            printf("%s ", *sentence);
            was_digit = 0;
        }
    }
}

int cmp(const void *a, const void *b){
    char** first_sentence = (char**) a;
    char** second_sentence = (char**) b;
    long long int sum_first = 0;
    long long int sum_second = 0;
    int only_str_one = 1;
    int only_str_two = 1;
    for (int i = 0; (*first_sentence)[i] != '.'; i++)
    {
        if (isdigit((*first_sentence)[i]))
        {
            sum_first += (*first_sentence)[i] - '0';
            only_str_one = 0;
        }
    }
    for (int i = 0; (*second_sentence)[i] != '.'; i++)
    {
        if (isdigit((*second_sentence)[i]))
        {
            sum_second += (*second_sentence)[i] - '0';
            only_str_two = 0;
        }
    }
    if (sum_first > sum_second)
    {
        if (only_str_two)
        {
            return -1;
        }
        else
        {
            return 1;
        }
    }
    else if (sum_first < sum_second)
    {
        if (only_str_one)
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return 0;
    }
}

int main(){
    int command;
    int count_sentence = 0;
    int capacity = 1;
    int capacity_two = 1;
    char** text = (char**)malloc(capacity*sizeof(char*));
    printf("Enter text:\n");
    text = in(&count_sentence, capacity, capacity_two, text);
    count_sentence = delete_repeating_sentence(text, count_sentence);
    int stop = 1;
    while (stop){
        printf("\nHere is a list of commands.\n");
        printf("0) Exit the program.\n");
        printf("1) Make the first letter of a string uppercase ");
        printf("and others letters lowercase.\n");
        printf("2) Remove all sentences containing 2018.\n");
        printf("3) Sort sentences in increase the amount of digits found in the sentences. ");
        printf("If there are no digits in the sentence,");
        printf(" then the sum of the numbers in this sentence is equal to infinity.\n");
        printf("4) Display all sentences in which all digits occur at least once.\n");
        printf("Enter command: ");
        scanf("%d", &command);
        switch (command)
        {
        case 0:
            stop = 0;
            break;
        case 1:
            capital_letter(text, count_sentence);
            out(text, count_sentence);
            break;
        case 2:
            count_sentence = delete2018(text, count_sentence);
            out(text, count_sentence);
            break;
        case 3:
            qsort(text, count_sentence, sizeof(char*), cmp);
            out(text, count_sentence);
            break;
        case 4:
            printf("\n");
            digits(text, count_sentence);
            printf("\n");
            break;
        default:
            printf("Something went wrong.\n");;
        }
    }
    for (int i = 0; i < count_sentence; i++)
    {
        free(text[i]);
    }
    free(text);
    return 0;
}
