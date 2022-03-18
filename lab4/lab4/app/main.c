#include "lib.h"
#include "types.h"

#define N 5                // 哲学家个数
sem_t sem[5];
void philosopher(int i){   // 哲学家编号：0-4
  //if(i == -1) return;
  while(1){
    printf("Philosopher %d: think\n", i);              // 哲学家在思考
	sleep(128);
    if(i%2==0){
      sem_wait(&sem[i]);          // 去拿左边的叉子
      sem_wait(&sem[(i+1)%N]);    // 去拿右边的叉子
    } else {
      sem_wait(&sem[(i+1)%N]);    // 去拿右边的叉子
      sem_wait(&sem[i]);          // 去拿左边的叉子
    }
    printf("Philosopher %d: eat\n", i);               // 吃面条
	sleep(128);
    sem_post(&sem[i]);            // 放下左边的叉子
    sem_post(&sem[(i+1)%N]);      // 放下右边的叉子
	//printf("Philosopher %d: eatend\n", i);
	sleep(128);
  }
}

int uEntry(void) {
	// For lab4.1
	// Test 'scanf' 
	/*int dec = 0;
	int hex = 0;
	char str[6];
	char cha = 0;
	int ret = 0;
	while(1){
		printf("Input:\" Test %%c Test %%6s %%d %%x\"\n");
		ret = scanf(" Test %c Test %6s %d %x", &cha, str, &dec, &hex);
		printf("Ret: %d; %c, %s, %d, %x.\n", ret, cha, str, dec, hex);
		if (ret == 4)
			break;
	}*/
	
	// For lab4.2
	// Test 'Semaphore'
	/*int i = 4;
	int ret = 0;
	sem_t sem;
	printf("Father Process: Semaphore Initializing.\n");
	ret = sem_init(&sem, 2);
	if (ret == -1) {
		printf("Father Process: Semaphore Initializing Failed.\n");
		exit();
	}

	ret = fork();
	if (ret == 0) {
		while( i != 0) {
			i --;
			printf("Child Process: Semaphore Waiting.\n");
			sem_wait(&sem);
			printf("Child Process: In Critical Area.\n");
		}
		printf("Child Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}
	else if (ret != -1) {
		while( i != 0) {
			i --;
			printf("Father Process: Sleeping.\n");
			sleep(128);
			printf("Father Process: Semaphore Posting.\n");
			sem_post(&sem);
		}
		printf("Father Process: Semaphore Destroying.\n");
		sem_destroy(&sem);
		exit();
	}*/

	// For lab4.3
	// TODO: You need to design and test the philosopher problem.
	// Note that you can create your own functions.
	// Requirements are demonstrated in the guide.
	int ret;
	for(int i = 0; i < 5; i++)
	{
		ret = sem_init(&sem[i], 1);
		if(ret == -1)
			exit();
	}
	int no = 0;
	for(int i = 1; i < 5; i++)
	{
		ret  = fork();
		if(ret == -1)
			exit();
		if(ret == 0)//the son process
		{
			no = i;//the num of the philisopher
			break;
		}
	}
	philosopher(no);

	return 0;
}
