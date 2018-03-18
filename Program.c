#include<stdio.h>
#include<pthread.h>
pthread_mutex_t pen,paper,question_paper;
void* teacher(void *c)
{
    sleep(1);
    while(1)
    {
        pthread_mutex_lock(&pen);
        pthread_mutex_lock(&paper);
        pthread_mutex_lock(&question_paper);

        int r = random()%3;
        switch(r)
        {
            case 0 :{pthread_mutex_unlock(&pen); pthread_mutex_unlock(&paper); break;}
            case 1 :{pthread_mutex_unlock(&paper); pthread_mutex_unlock(&question_paper); break;}
            case 2 :{pthread_mutex_unlock(&pen); pthread_mutex_unlock(&question_paper); break;}
        }
    }
}

void* stud(void *x)
{
    printf("Student is ready for Test ");
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
