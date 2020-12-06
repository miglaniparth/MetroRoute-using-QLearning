#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#define RAN_LIM 500000

double qMatrix[11][11], rMatrix[11][11], gammaLR = 0.8; // defining all the required 1D and 2D arrays. Also gammaLR is learning rate
int max_index[11], available_acts[11];
int ran_top = 0, ran[RAN_LIM];



int returnRandom()   // returning random value as we know the more randomization we do,the more trained Q-matrix we will get
{
    return ran[ran_top++];
    return ran[ran_top++];
}

double update(int current_state, int action, double rMatrix[][11],double qMatrix[][11]) /* Here action is the value returned from sample next action function*/
{
    int i = 0, j = 0, k = 0, index_of_max;
    double temp_max = 0.0, max_value = 0.0, sumA = 0.0;

    //Collecting all the indexes where we have max in action row
    for (i = 0; i < 11; i++)
    {
        max_index[i] = 0;

        if (temp_max == qMatrix[action][i])
        {
            max_index[j] = i;
            j++;
        }
        else if (temp_max < qMatrix[action][i])
        {
            j = 0;
            temp_max = qMatrix[action][i];
            max_index[j] = i;
            j++;
        }
    }

    //Select a random out of all maximum
    int a = returnRandom() % j;
    index_of_max = max_index[a];

    max_value = qMatrix[action][index_of_max];


    //Main updation
    qMatrix[current_state][action] = rMatrix[current_state][action] + (gammaLR * max_value); // bellman equation
    temp_max = 0.0;
    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if (qMatrix[i][j] > temp_max)
            {
                temp_max = qMatrix[i][j];
            }
        }
    }

    //printf("\nQ Max: %d", temp_max);
    //printArray(qMatrix);
    if (temp_max > 0)
    {
        for (i = 0; i < 11; i++)
        {
            for (j = 0; j < 11; j++)
            {
                sumA = sumA + (qMatrix[i][j] / temp_max);
            }
        }

        sumA = sumA * 100;
        return sumA;
    }
    else
    {
        return 0.0;
    }
}

int available_actions(int state, int available_acts[],double rMatrix[][11])  //this function will return all the possible column values whose
                                                                            //R-Matrix value is greater than 0, for that specific row. State will
                                                                            // represent the current state and we will store all the column values
                                                                            //for these possible values in this available acts array
{
    int k = 0, j = 0;
    while (j < 11)
    {
        if (rMatrix[state][j] >= 0.0)
        {
            available_acts[k] = j;
            k++;
        }
        j++;
    }

    return k;
}


int sample_next_action(int size,int available_acts[])
/*This function will simply select a random index out of the previously returned array. Here
size is the value of k returned from the available_actions function*/
{
    int a = returnRandom();
    int next_action = available_acts[a % size];
    return next_action;
}

int main()
{
    int i, j,counter=0;
    char station[11][20]={
    "New Delhi",
    "Rajiv Chowk",
    "Mandi House",
    "Janpath",
    "Patel Chowk",
    "Central Secretariat",
    "Lok Kalyan Marg",
    "IMA",
    "South Extension",
    "Lajpat Nagar",
    "Khan Market"
    };
    printf("Station ID\tStation Name\n--------------------------------------------------------\n");
    for(int i=0;i<11;i++){
        printf("%d\t\t%s\n",i,station[i]);
    }
    int initial_state, final_state;
    int current_state, size_av_actions, action;
    double final_max = 0.0, scores[100000], rMatrix[11][11], score = 0.0;

    printf("Enter the initial station id: \n");
    scanf("%d",&initial_state);

    printf("Enter the final station id: ");
    scanf("%d",&final_state);

    for (int i = 0; i < RAN_LIM; i++)
    {
        ran[i] = rand() % 11;
    }


    for (i = 0; i < 11; i++)
    {
        for (j = 0; j < 11; j++)
        {
            rMatrix[i][j] = -1.0;
            qMatrix[i][j] = 0.0;

            if ((i == 0 && j == 1) || (i == 1 && j == 2) || (i == 2 && j == 3) || (i == 3 && j == 5) || (i == 1 && j == 4) || (i == 4 && j == 5) || (i == 5 && j == 6) || (i == 6 && j == 7) || (i == 7 && j == 8) || (i == 8 && j == 9) || (i == 9 && j == 10) || (i == 10 && j == 5))
            {
                rMatrix[i][j] = 0.0;
            }

            if ((j == 0 && i == 1) || (j == 1 && i == 2) || (j == 2 && i == 3) || (j == 3 && i == 5) || (j == 1 && i == 4) || (j == 4 && i == 5) || (j == 5 && i == 6) || (j == 6 && i == 7) || (j == 7 && i == 8) || (j == 8 && i == 9) || (j == 9 && i == 10) || (j == 10 && i == 5))
            {
                rMatrix[i][j] = 0.0;
            }

            switch(final_state)
            {
                case 0: if((i == 0 && j == 0) || (i == 1 && j == 0))
                        {
                            rMatrix[i][j]=100.0;
                        }
                        break;

                case 1:  if((i == 4 && j == 1) || (i == 0 && j == 1) || (i == 2 && j == 1) || (i == 1 && j == 1))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;

                case 2: if((i == 3 && j == 2) || (i == 1 && j == 2) || (i == 2 && j == 2))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;

                case 3: if((i == 2 && j == 3) || (i == 3 && j == 3)|| (i == 5 && j == 3))
                        {
                            rMatrix[i][j]=100.0;
                        }
                        break;

                case 4: if((i == 1 && j == 4) || (i == 5 && j == 4) || (i == 4 && j == 4))
                        {
                            rMatrix[i][j]=100.0;
                        }
                        break;

                case 5: if((i == 3 && j == 5) || (i == 10 && j == 5)|| (i == 4 && j == 5) || (i == 6 && j == 5) || (i == 5 && j == 5))
                        {
                            rMatrix[i][j]=100.0;
                        }
                        break;

                case 6: if((i == 5 && j == 6)|| (i == 7 && j == 6) || (i == 6 && j == 6))
                        {
                            rMatrix[i][j]=100.0;
                        }
                        break;

                case 7: if ((i == 6 && j == 7) || (i == 7 && j == 7) ||(i == 8 && j == 7))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;
                case 8: if ((i == 8 && j == 8) || (i == 7 && j == 8) ||(i == 9 && j == 8))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;
                case 9: if ((i == 8 && j == 9) || (i == 9 && j == 9) ||(i == 10 && j == 9))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;
                case 10: if ((i == 5 && j == 10) || (i == 10 && j == 10) ||(i == 9 && j == 10))
                        {
                            rMatrix[i][j] = 100.0;
                        }
                        break;
            }


        }
    }





    // Training the Q Matrix
    for (i = 0; i < 500; i++)
    {

        current_state = returnRandom();
        size_av_actions = available_actions(current_state,available_acts,rMatrix);
        action = sample_next_action(size_av_actions,available_acts);

        //printf("\nNext Step: %d\n", action);
        score = update(current_state, action,rMatrix,qMatrix);
        scores[i] = score;

    }


    //Finding the Max
    for (i = 0; i <11; i++)
    {
        for (j = 0; j < 11; j++)
        {
            if (final_max < qMatrix[i][j])
            {
                final_max = qMatrix[i][j];
            }
        }
    }



    int curr_state=initial_state;
    int visited[11]={0,0,0,0,0,0,0,0,0,0,0};
    int no_way=0;
    int row_max=0,max_ind=0;

    int gd = DETECT, gm;


	initgraph(&gd, &gm, "C:/TURBOC3/BGI");
    int big=initwindow(getmaxwidth(),getmaxheight(),"Optimal Path Graph");
    setcurrentwindow(big);

    int c_x=100,c_y=400;
    int c1_x=100,c1_y=400;
    int l_x1=190,l_y1=400,l_x2=250,l_y2=400;
    int p_x1=250,p_y1=390,p_x2=267,p_y2=400,p_x3=250,p_y3=410;
    int points[8];
    int txt_x=40,txt_y=394;

    printf("Path: \n");
    while (visited[final_state]!=1)
    {

        printf("%s-> ",station[curr_state]);
        counter++;
        row_max=0;
        max_ind=0;

        for(int i=0;i<11;i++)
        {
            if(visited[i]==0)
            {
                if(qMatrix[curr_state][i]>row_max)
                {
                    max_ind=i;
                    row_max=qMatrix[curr_state][i];
                }
            }
        }

        circle(c_x,c_y,80);
        circle(c1_x,c1_y,70);
        line(l_x1,l_y1,l_x2,l_y2);

        points[0]=p_x1;
        points[1]=p_y1;
        points[2]=p_x2;
        points[3]=p_y2;
        points[4]=p_x3;
        points[5]=p_y3;
        points[6]=p_x1;
        points[7]=p_y1;

        fillpoly(4,points);
        outtextxy(txt_x,txt_y,station[curr_state]);

        i++;

        c_x+=267;
        c1_x+=267;
        l_x1+=267;
        l_x2+=267;
        p_x1+=267;
        p_x2+=267;
        p_x3+=267;
        txt_x+=267;

        curr_state=max_ind;
        visited[max_ind]=1;



        if(row_max==0)
        {
            no_way=1;
            break;
        }

        if(curr_state==final_state)
        {
            break;
        }

    }

    circle(c_x,c_y,80);
    circle(c1_x,c1_y,70);
    outtextxy(txt_x,txt_y,station[curr_state]);

    if(no_way==1)
    {
        printf("%d | There's no way after this\n");
    }
    else
    {
        printf("%s is the shortest path\nYou will travel through %d stations and will take approximately %d minutes for your %dKm journey ",station[curr_state],counter,counter*5,counter*4);

    }
    int x;
    scanf("%d",&x);

}
