#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t mut1;
int i,resource;
int active[5];
void* teacher(void *c)
{
    sleep(1);
    while(1)
    {
        pthread_mutex_lock(&mut1);
        resource = random() % 3;
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

    printf("Student is ready for Test having %s\n");
    while(1)
    {
        pthread_mutex_lock(&mut1);
        if(studentID == resource)
        {
            active[studentID]=0;
            printf("Student completed the Test \n");
            pthread_mutex_unlock(&mut1);
            break;
        }
        pthread_mutex_unlock(&mut1);
    }

}

void main()
{
    pthread_t t1,s1,s2,s3;

    pthread_create(t1,NULL,teacher,NULL);

    pthread_create(s1,NULL,stud,NULL);
    pthread_create(s2,NULL,stud,NULL);
    pthread_create(s3,NULL,stud,NULL);
    pthread_join(t1,NULL);
    pthread_join(s1,NULL);
    pthread_join(s2,NULL);
    pthread_join(s3,NULL);
}
