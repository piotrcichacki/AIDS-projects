#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Rotor{
    int* step_forward;
    int* step_backward;
    int  number_turnover_letters;
    int* turnover_letters;
    int start_position;
    bool moved;
};

struct Reflector{
    int* step;
};

int reszta(int number, int number_of_letters)
{
    if(number>number_of_letters)    return number%number_of_letters;
    else if (number<1)              return number+number_of_letters;
    else                            return number;
}

void load_rotor(struct Rotor* rotor, int number_of_letters)
{
    int number=0, j=0;
    rotor->step_forward = (int *)malloc(number_of_letters*sizeof(int));
    rotor->step_backward = (int *)malloc(number_of_letters*sizeof(int));
    rotor->start_position = 0;
    rotor->moved=false;

    for (j=0; j<number_of_letters; j++)
    {
        scanf("%d", &number);
        rotor->step_forward[j]=number-1-j;
        rotor->step_backward[number-1]=1+j-number;
    }

    scanf("%d", &number);
    rotor->number_turnover_letters = number;
    rotor->turnover_letters = (int *)malloc(rotor->number_turnover_letters*sizeof(int));

    for (j=0; j<rotor->number_turnover_letters; j++)
    {
            scanf("%d", &number);
            rotor->turnover_letters[j]=number;
    }

}

void load_reflector(struct Reflector* reflector, int number_of_letters)
{
    int number=0, j=0;

    reflector->step = (int *)malloc(number_of_letters*sizeof(int));
    for (j=0; j<number_of_letters; j++)
    {
        scanf("%d", &number);
        reflector->step[j]=number-1-j;
    }
}

void copy_rotor(struct Rotor* copy, struct Rotor* rotor, int number_of_letters)
{
    int j=0;

    copy->step_forward = (int *)malloc(number_of_letters*sizeof(int));
    copy->step_backward = (int *)malloc(number_of_letters*sizeof(int));
    copy->start_position=0;
    copy->moved=false;

    for (j=0; j<number_of_letters; j++)
    {
        copy->step_forward[j]=rotor->step_forward[j];
        copy->step_backward[j]=rotor->step_backward[j];
    }
    copy->number_turnover_letters=rotor->number_turnover_letters;
    copy->turnover_letters = (int *)malloc(copy->number_turnover_letters*sizeof(int));

    for (j=0; j<copy->number_turnover_letters; j++)
    {
        copy->turnover_letters[j]=rotor->turnover_letters[j];
    }
}

bool notch_position (struct Rotor* rotor, int number_of_letters)
{
    int k=0;
    for (k=0; k<rotor->number_turnover_letters; k++)
    {
        if ((rotor->start_position%number_of_letters)+1 == rotor->turnover_letters[k])
        {
            return true;
        }
    }
    return false;
}


int main()
{
    int number_of_letters=0, number_of_rotors=0, number_of_reflectors=0;
    int tests_number=0, index_reflector=0;
    int i=0, j=0;
    int letter=0;


    scanf("%d", &number_of_letters);

    scanf("%d", &number_of_rotors);
    struct Rotor* rotor = (struct Rotor *)malloc(number_of_rotors*sizeof(struct Rotor));
    for (i=0; i<number_of_rotors; i++)
    {
        load_rotor(&rotor[i], number_of_letters);
    }

    scanf("%d", &number_of_reflectors);
    struct Reflector* reflector = (struct Reflector *)malloc(number_of_reflectors*sizeof(struct Reflector));
    for (i=0; i<number_of_reflectors; i++)
    {
        load_reflector(&reflector[i], number_of_letters);
    }


    scanf("%d", &tests_number);

    for (i=0; i<tests_number; i++)
    {
        scanf("%d", &number_of_rotors);

        int* rotors_indexes = (int *)malloc(number_of_rotors*sizeof(int));

        struct Rotor* rotor_copy = (struct Rotor *)malloc(number_of_rotors*sizeof(struct Rotor));

        for (j=0; j<number_of_rotors; j++)
        {
            scanf("%d", &rotors_indexes[j]);
            copy_rotor(&rotor_copy[j], &rotor[rotors_indexes[j]], number_of_letters);
            scanf("%d", &rotor_copy[j].start_position);
        }
        scanf("%d", &index_reflector);


        scanf("%d", &letter);

        while(letter!=0)
        {

            if (number_of_rotors>=3 && notch_position(&rotor_copy[1], number_of_letters) && rotor_copy[1].moved)
            {
                rotor_copy[2].start_position = (rotor_copy[2].start_position)%number_of_letters+1;
                rotor_copy[1].start_position = (rotor_copy[1].start_position)%number_of_letters+1;
                rotor_copy[2].moved = true;
            }
            else if (number_of_rotors>=2 && notch_position(&rotor_copy[0], number_of_letters) && rotor_copy[0].moved)
            {
                rotor_copy[1].start_position = (rotor_copy[1].start_position)%number_of_letters+1;
                rotor_copy[1].moved = true;
            }
            rotor_copy[0].start_position = (rotor_copy[0].start_position)%number_of_letters+1;
            rotor_copy[0].moved = true;



            for (j=0; j<number_of_rotors; j++)
            {
                letter += rotor_copy[j].step_forward[reszta(letter+rotor_copy[j].start_position-1, number_of_letters)-1];
                letter = reszta(letter, number_of_letters);
            }

            letter += reflector[index_reflector].step[letter-1];
            letter = reszta(letter, number_of_letters);

            for (j=number_of_rotors-1; j>=0; j--)
            {
                letter += rotor_copy[j].step_backward[reszta(letter+rotor_copy[j].start_position-1,number_of_letters)-1];
                letter = reszta(letter, number_of_letters);
            }

            printf("%d ", letter);
            scanf("%d", &letter);
        }

        free(rotors_indexes);
        free(rotor_copy);
    }

    return 0;
}
