#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE  2000
#define INT_SIZE    9

struct Number
{
    int cells_number;
    int number_elements;
    int* wsk;
    char sign;
    int index;
};

void load_line(struct Number* wskaznik, char* char_tab);

void divide_totabint (struct Number* wskaznik, char* char_tab);

void tab_output (char * tablica);

void adding (struct Number* number1, struct Number* number2, struct Number* number3);

void operations (struct Number* number1, struct Number* number2, struct Number* number3, char sign);

void number_10digits (struct Number* number1);

void subtract (struct Number* number1, struct Number* number2, struct Number* number3);

void subtraction (struct Number* number1, struct Number* number2, struct Number* number3);

void subtraction1 (struct Number* number1, struct Number* number2, struct Number* number3);

void subtraction2 (struct Number* number1, struct Number* number2, struct Number* number3);

void subtraction3 (struct Number* number1, struct Number* number2, struct Number* number3);

int minimum (struct Number* wskaznik,struct Number* minimum);

int maximum (struct Number* wskaznik,struct Number* maximum);

int load_line2(char* tab);

void print(struct Number* wskaznik);


int main()
{
    int numbers=0, i=0;
    int j=0;
    int index1, index2, index3;
    char tab[10];
    char inputtab[29];
    char sign;
    int index_max=0, index_min=0;

    load_line2(inputtab);
    if (inputtab[0]>='0' && inputtab[0]<='9')
    {
        j=0; i=0;
        while (inputtab[i]>='0' && inputtab[i]<='9')
        {
            tab[j]=inputtab[i];
            i++; j++;
        }
    tab[j]='\0';
    sscanf(tab, "%d", &numbers);

    struct Number* wskaznik = (struct Number *)malloc(numbers*sizeof(struct Number));

    index_max=0; index_min=0;

    for (i=0; i<numbers; i++)
    {

        wskaznik[i].number_elements=0;
        wskaznik[i].cells_number=0;
        wskaznik[i].sign='+';
        wskaznik[i].index=i;

        char* char_tab = (char *)malloc(ARRAY_SIZE*sizeof(char));

        load_line(&wskaznik[i], char_tab);

        wskaznik[i].wsk=(int *)malloc(wskaznik[i].cells_number*sizeof(int));

        divide_totabint(&wskaznik[i], char_tab);

        if (i>0)
        {
        index_min=minimum(&wskaznik[i], &wskaznik[index_min]);

        index_max=maximum(&wskaznik[i], &wskaznik[index_max]);
        }

        free(char_tab);
    }
        while(1)
        {
            load_line2(inputtab);
            if (inputtab[0]=='q') exit(0);

            else if (inputtab[0]=='?')
            {
                for (i=0; i<numbers; i++)
                {
                    print(&wskaznik[i]);
                }
            }
            else if (inputtab[0]=='m' && inputtab[1]=='i' && inputtab[2]=='n')
            {
                print(&wskaznik[index_min]);
            }
            else if (inputtab[0]=='m' && inputtab[1]=='a' && inputtab[2]=='x')
            {
                print(&wskaznik[index_max]);
            }
            else if (inputtab[0]>='0' && inputtab[0]<='9')
            {
                j=0; i=0;
                while (inputtab[i]>='0' && inputtab[i]<='9')
                {
                    tab[j]=inputtab[i];
                    i++; j++;
                }
                tab[j]='\0';
                sscanf(tab, "%d", &index1);
                i=i+3;
                j=0;
                while (inputtab[i]>='0' && inputtab[i]<='9')
                {
                    tab[j]=inputtab[i];
                    i++; j++;
                }
                tab[j]='\0';
                sscanf(tab, "%d", &index2);
                sign=inputtab[i+1];
                i=i+3;
                j=0;
                while (inputtab[i]>='0' && inputtab[i]<='9')
                {
                    tab[j]=inputtab[i];
                    i++; j++;
                }
                tab[j]='\0';
                sscanf(tab, "%d", &index3);

                operations(&wskaznik[index1],&wskaznik[index2],&wskaznik[index3],sign);
                index_max=0;
                index_min=0;
                for (i=1; i<numbers; i++)
                {
                    index_min=minimum(&wskaznik[i], &wskaznik[index_min]);
                    index_max=maximum(&wskaznik[i], &wskaznik[index_max]);
                }
            }
        }

    return 0;
}
}




void load_line(struct Number* wskaznik, char* char_tab)
{
    do
        {
            if (wskaznik->number_elements%ARRAY_SIZE==0 && wskaznik->number_elements>0)
            {
                char_tab = (char *)realloc((void*)char_tab, ((wskaznik->number_elements/ARRAY_SIZE)+1)*ARRAY_SIZE*sizeof(char));
            }
            *(char_tab+wskaznik->number_elements)=getc(stdin);
            if (wskaznik->number_elements==0 && *(char_tab)=='-')
            {
                wskaznik->sign='-';
                wskaznik->number_elements--;
            }
            wskaznik->number_elements++;
        }
        while (wskaznik->number_elements==0 || *(char_tab+wskaznik->number_elements-1)!='\n');

        *(char_tab+wskaznik->number_elements-1)='\0'; wskaznik->number_elements--;

        wskaznik->cells_number=(wskaznik->number_elements/INT_SIZE)+(wskaznik->number_elements%INT_SIZE>0 ? 1 : 0);

}

void divide_totabint (struct Number* wskaznik, char* char_tab)
{
    int k=0, j=0, l=0, x=0;
    char tablica[10];

    for (k=0, j=0; k<wskaznik->number_elements, j<wskaznik->cells_number; k++)
            {
                x=0;
                if (j==0 && k==wskaznik->number_elements%INT_SIZE-1)
                {
                    tablica[l]=*(char_tab+k);
                    tablica[l+1]='\0';
                    sscanf(tablica, "%d", &x);
                    (wskaznik->wsk[j])=x;
                    l=0; j++;
                }
                else if (((k+1-wskaznik->number_elements%INT_SIZE)%INT_SIZE)==0)
                {
                    tablica[l]=*(char_tab+k);
                    tablica[l+1]='\0';
                    sscanf(tablica, "%d", &x);
                    (wskaznik->wsk[j])=x;
                    l=0; j++;
                }
                else
                {
                    tablica[l]=*(char_tab+k);
                    l++;
                }
            }
}


void adding (struct Number* number1, struct Number* number2, struct Number* number3)
{
    int i=0;

    if (number3->cells_number>number2->cells_number)
    {
        adding(number1, number3, number3);
    }
    else
    {
        number1->cells_number=number2->cells_number;
        number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));

        for (i=0; i<number3->cells_number; i++)
        {
            number1->wsk[number1->cells_number-i-1]=number2->wsk[number2->cells_number-i-1]+number3->wsk[number3->cells_number-i-1];
        }
        for (i=number3->cells_number; i<number2->cells_number; i++)
        {
            number1->wsk[number1->cells_number-i-1]=number2->wsk[number2->cells_number-i-1];
        }
        for (i=0; i<number1->cells_number-1; i++)
        {
            if (number1->wsk[number1->cells_number-1-i]>=1000000000)
            {
                number1->wsk[number1->cells_number-1-i]-=1000000000;
                number1->wsk[number1->cells_number-2-i]+=1;
            }
        }

            if (number1->wsk[0]>=1000000000)
            {
                number1->cells_number +=1;
                number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));

                for (i=0; i<number1->cells_number-1; i++)
                {
                    number1->wsk[number1->cells_number-i-1]=number1->wsk[number1->cells_number-i-2];
                }
                number1->wsk[0]=1;
            }
    }
}


void operations (struct Number* number1, struct Number* number2, struct Number* number3, char sign)
{
    if (sign=='+')
    {
        if ((number2->sign=='+' && number3->sign=='+')||(number2->sign=='-' && number3->sign=='-'))
        {
            number1->sign=number2->sign;
            if(number2->cells_number>=number3->cells_number)
                adding(number1, number2, number3);
            else adding(number1, number3, number2);
        }
        else if (number2->sign=='-' && number3->sign=='+')
        {
            subtract(number1, number2, number3);
            if (number2->cells_number>number3->cells_number) number1->sign='-';
            else if (number2->cells_number<number3->cells_number) number1->sign='+';
        }
        else if (number2->sign=='+' && number3->sign=='-')
        {
            subtract(number1, number2, number3);
            if (number2->cells_number>number3->cells_number) number1->sign='+';
            else if (number2->cells_number<number3->cells_number) number1->sign='-';
        }
    }
    else if (sign=='-')
    {
        if ((number2->sign=='-' && number3->sign=='+')||(number2->sign=='+' && number3->sign=='-'))
        {
            number1->sign=number2->sign;
            if(number2->cells_number>=number3->cells_number)
                adding(number1, number2, number3);
            else adding(number1, number3, number2);
        }
        else if (number2->sign=='-' && number3->sign=='-')
        {
            subtract(number1, number2, number3);
            if (number2->cells_number>number3->cells_number) number1->sign='-';
            else if (number2->cells_number<number3->cells_number) number1->sign='+';
        }
        else if (number2->sign=='+' && number3->sign=='+')
        {
            subtract(number1, number2, number3);
            if (number2->cells_number>number3->cells_number) number1->sign='+';
            else if (number2->cells_number<number3->cells_number) number1->sign='-';
        }
    }
}


int minimum (struct Number* wskaznik, struct Number* minimum)
{
    int i=0;
    if (minimum->sign=='+' && wskaznik->sign=='+')
    {
        if(wskaznik->cells_number < minimum->cells_number)
        {
            return wskaznik->index;
        }
        else if (wskaznik->cells_number == minimum->cells_number)
        {
            for(i=0; i<wskaznik->cells_number; i++)
            {
                if (wskaznik->wsk[i]>minimum->wsk[i])
                    return minimum->index;
                else if (wskaznik->wsk[i]<minimum->wsk[i])
                {
                    return wskaznik->index;
                }
            }
        }
        else return minimum->index;
    }
    else if (minimum->sign=='+' && wskaznik->sign=='-')
    {
        return wskaznik->index;
    }
    else if (minimum->sign=='-' && wskaznik->sign=='-')
    {
         if(wskaznik->cells_number > minimum->cells_number)
        {
            return wskaznik->index;
        }
        else if (wskaznik->cells_number == minimum->cells_number)
        {
            for(i=0; i<wskaznik->cells_number; i++)
            {
                if (wskaznik->wsk[i]<minimum->wsk[i])
                    return minimum->index;
                else if (wskaznik->wsk[i]>minimum->wsk[i])
                {
                    return wskaznik->index;
                }
            }
        }
        else return minimum->index;
    }
    return minimum->index;
}

int maximum (struct Number* wskaznik,struct Number* maximum)
{
    int i=0;
    if (maximum->sign=='+' && wskaznik->sign=='+')
    {
        if(wskaznik->cells_number > maximum->cells_number)
        {
            return wskaznik->index;
        }
        else if (wskaznik->cells_number == maximum->cells_number)
        {
            for(i=0; i<wskaznik->cells_number; i++)
            {
                if (wskaznik->wsk[i] < maximum->wsk[i])
                    return maximum->index;
                else if (wskaznik->wsk[i]>maximum->wsk[i])
                {
                    return wskaznik->index;
                }
            }
        }
        else return maximum->index;
    }
    else if (maximum->sign=='-' && wskaznik->sign=='+')
    {
        return wskaznik->index;
    }
    else if (maximum->sign=='-' && wskaznik->sign=='-')
    {
        if(wskaznik->cells_number < maximum->cells_number)
        {
            return wskaznik->index;
        }
        else if (wskaznik->cells_number == maximum->cells_number)
        {
            for(i=0; i<wskaznik->cells_number; i++)
            {
                if (wskaznik->wsk[i] > maximum->wsk[i])
                     return maximum->index;
                else if (wskaznik->wsk[i]<maximum->wsk[i])
                {
                    return wskaznik->index;
                }
            }
        }
        else return maximum->index;
    }
    return maximum->index;
}

void print(struct Number* wskaznik)
{
    int j;
    if (wskaznik->sign=='-') printf("%c",wskaznik->sign);

        for (j=0; j<wskaznik->cells_number; j++)
        {
            if (j>0)
            {
                printf("%09d", wskaznik->wsk[j]);
            }
            else
            printf("%d", wskaznik->wsk[j]);
        }
    printf("\n");
}

int load_line2(char* tab)
{
    int k=0;
    do
    {
        *(tab+k)=getc(stdin);
        k++;
    }while (*(tab+k-1)!='\n');
    *(tab+k-1)='\0';
    return k-1;
}


void subtract (struct Number* number1, struct Number* number2, struct Number* number3)
{
    int i=0, j=0;

    if (number2->cells_number>number3->cells_number)
    {
        number1->cells_number=number2->cells_number;

        number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));

        for (i=0; i<number3->cells_number; i++)
        {
            number1->wsk[number1->cells_number-1-i]=number2->wsk[number2->cells_number-1-i]-number3->wsk[number3->cells_number-1-i];
        }
        for (i=number3->cells_number; i<number2->cells_number; i++)
        {
            number1->wsk[number1->cells_number-1-i]=number2->wsk[number2->cells_number-1-i];
        }
        for (i=0; i<number1->cells_number-1; i++)
        {
            if (number1->wsk[number1->cells_number-1-i]<0)
            {
                number1->wsk[number1->cells_number-1-i]+=1000000000;
                number1->wsk[number1->cells_number-2-i]-=1;
            }
        }
            if (number1->wsk[0]==0)
            {
                for (i=0; i<number1->cells_number-1; i++)
                {
                    number1->wsk[i]=number1->wsk[i+1];
                }
                number1->cells_number -=1;
                number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));
            }

    }
    else if (number2->cells_number<number3->cells_number)
    {

        subtract(number1, number3, number2);
    }


    else if (number2->cells_number==number3->cells_number)
    {
        number1->cells_number=number2->cells_number;
        number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));

        for(i=0; i<number2->cells_number; i++)
            {
                if (number3->wsk[i] > number2->wsk[i])
                {
                    subtract(number1, number3, number2);
                    if (number2->sign=='+')
                    {
                        number1->sign='-';
                    }
                    else if (number2->sign=='-')
                    {
                        number1->sign='+';
                    }
                    return;sz
                }
                else if (number2->wsk[i] > number3->wsk[i])
                {
                    if (number2->sign=='+')
                    {
                        number1->sign='+';
                    }
                    else if (number2->sign=='-')
                    {
                        number1->sign='-';
                    }
                    break;
                }
            }
        for (i=0; i<number2->cells_number; i++)
        {
            number1->wsk[number1->cells_number-1-i]=number2->wsk[number2->cells_number-1-i]-number3->wsk[number3->cells_number-1-i];
        }
        for (i=0; i<number1->cells_number-1; i++)
        {
            if (number1->wsk[number1->cells_number-1-i]<0)
            {
                number1->wsk[number1->cells_number-1-i]+=1000000000;
                number1->wsk[number1->cells_number-2-i]-=1;
            }
        }
        for (i=0; i<number1->cells_number; i++)
            {
            if (number1->wsk[0]==0)
            {
                for (j=0; j<number1->cells_number-1; j++)
                {
                    number1->wsk[j]=number1->wsk[j+1];
                }
                number1->cells_number -=1;
                number1->wsk = (int*) realloc((void*)number1->wsk, (number1->cells_number)*sizeof(int));
            }
            else break;
            }
    }
}

