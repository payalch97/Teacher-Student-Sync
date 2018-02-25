#include<stdio.h>
#include<pthread.h>
void* teacher(void *c)
{
    sleep(1);
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
