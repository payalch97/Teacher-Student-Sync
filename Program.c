#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mut1;
int i,resource;
int active[5];
char* fun1(int x)
{
    switch(x)
    {
        case 1 : return "Pen";
        case 2 : return "Paper";
        case 3 : return"Question Paper";
    }
}
void* teacher(void *c)
{
    sleep(1);
    while(1)
    {
        pthread_mutex_lock(&mut1);
        resource = (random() % 1029)%3;
        resource += 1;
        if(active[1]==0 && active[2]==0 && active[3]==0)
            {
                printf("All the student completed the Test\n");
                break;
            }
        switch(resource)
        {
            case 1 :{
                        printf("Teacher put Paper and Question Paper on Desk \n");
                        break;
                    }
            case 2 :{
                        printf("Teacher put Pen and Question Paper on Desk \n");
                        break;
                    }
            case 3 :{
                        printf("Teacher put Pen and Paper on Desk \n");
                        break;
                    }
        }
        pthread_mutex_unlock(&mut1);
        sleep(1);
    }
}

void* stud(void *x)
{
    int studentID = *(int *)x;
    printf("Student %d is ready for Test having %s\n",studentID,fun1(studentID));
    while(1)
    {
        pthread_mutex_lock(&mut1);
        if(studentID == resource)
        {
            printf("Student %d already have %s\n",studentID,fun1(studentID));
            printf("Student %d has acquired the resource available on desk \n",studentID);
            active[studentID]=0;
            printf("Student %d completed the Test \n",studentID);
            pthread_mutex_unlock(&mut1);
            break;
        }
        pthread_mutex_unlock(&mut1);
    }

}

void main()
{
    pthread_t t1;
    pthread_t *t = malloc(sizeof(pthread_t)*3);
    int *x = malloc(sizeof(int)*3);
    pthread_mutex_init(&mut1,NULL);
    pthread_create(&t1,NULL,teacher,NULL);
    for(i=0;i<3;i++)
    {
        *(x+i) = i+1;
        active[i+1]=1;
        pthread_create((t+i),NULL,stud,(void*)(x+i));

    }
    pthread_join(t1,NULL);
    for(i=0;i<3;i++)
        pthread_join(*(t+i),NULL);
}
