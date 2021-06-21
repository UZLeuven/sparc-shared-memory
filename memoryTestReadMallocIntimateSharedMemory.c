#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/shm.h>

#include <unistd.h>

#define AANTAL_USEC_IN_SEC 1000000

char *createSharedMemory(int shmkey, size_t size, char *b)
{
  printf("create shared memory %d\n", shmkey);
  int shmid;
  if ((shmid = shmget(shmkey, size, 0644 | IPC_CREAT)) == -1)
  {
    perror("shmget");
    exit(1);
  }
  printf("shmid=%i\n", shmid);
  char *shmpointer_1 =shmat(shmid,NULL,SHM_SHARE_MMU    );
  strncpy(shmpointer_1, b, size);
  return shmpointer_1;
}

void doeLoop(char *b, size_t size)
{
  char *cp;
  char cp1;
  for (cp = b; cp < &b[size]; cp += 1024)
  {
    cp1 = *cp;
    *cp = 'a';
  }
}

main()
{
  size_t MAXIMUM;
  size_t MAXIMUM_SHMGET;
  char *cp;
  char cp1;
  struct timeval tp_start, tp_end;
  struct timezone tzp;
  long sec, usec;
  long msec;
  time_t result;
  int shmkey = 124; //u can choose it as your choice
  int shmid;
  int shmid_1;

  MAXIMUM = 64194304000; // 60 GB
  MAXIMUM = 5194304000;  // 15GB
  MAXIMUM_SHMGET = MAXIMUM;
  int aantalKeerStat = 0;
  long long usecTotStat = 0;
  char *b;
  printf("malloc b \n");
  b = (char *)malloc(MAXIMUM * sizeof(char));
  for (cp = b; cp < &b[MAXIMUM]; cp += 1024)
  {
    *cp = ' ';
  }
  //MAXIMUM=2048; // 60 GB
  // https://stackoverflow.com/questions/5656530/how-to-use-shared-memory-with-linux-in-c
  /*  create the segment: */
  char *shmpointer_1 = createSharedMemory(shmkey, MAXIMUM_SHMGET, b);
  //   char* shmpointer_2=createSharedMemory(121,MAXIMUM_SHMGET,b);
  free(b);

  //now attach a memory to this share memory
  // char *b = shmat(shmid,NULL,00200    );

  long long numberOfTimes = 64194304000 / MAXIMUM;
  long long numberMegabyte = numberOfTimes / (1024 * 1024);
  printf("number of time %d\n", numberOfTimes);
  struct tm *brokentime;

  int max = MAXIMUM / 1024;
  int i;

  long long numberMegabytesPerSecond;
  int aantalKeerTeDoen = 0;
  while (aantalKeerTeDoen <= 5)
  {
    // printf("aantal keer %d\n",aantalKeerTeDoen);
    aantalKeerTeDoen++;
    gettimeofday(&tp_start, &tzp);
    long long number = 0;
    long long index = 0;
    while (number <= numberOfTimes)
    {
      doeLoop(shmpointer_1, MAXIMUM);
      number++;
    }

    gettimeofday(&tp_end, &tzp);
    // hoe lang duurt het

    long long start_usec;
    long long end_usec;
    long long diff_usec;
    start_usec = tp_start.tv_sec * 1000000 + tp_start.tv_usec;
    end_usec = tp_end.tv_sec * 1000000 + tp_end.tv_usec;
    diff_usec = end_usec - start_usec;
    aantalKeerStat++;
    if (aantalKeerStat > 20)
    {
      aantalKeerStat = 1;
      usecTotStat = diff_usec;
    }
    else
    {
      usecTotStat += diff_usec;
    }
    long long gemUsecStat = usecTotStat / aantalKeerStat;
    result = time(NULL);
    brokentime = localtime(&result);
    time_t mytime = time(NULL);

    char *time_str = ctime(&mytime);
    time_str[strlen(time_str) - 1] = '\0';
    printf("%s\tusec\t%lld\tnumber:\t%d\tmaximum\t%lld\tstat aantalkeer\t%d\tgem\t%lld\n", time_str, diff_usec, number, MAXIMUM, aantalKeerStat, gemUsecStat);
  }

  //clear shared memory
  //shmdt(&shmpointer_1    );
  if ((shmid = shmget(shmkey, 1, 0644 | IPC_CREAT)) == -1)
  {
    perror("shmget");
    exit(1);
  }
  if (shmctl(shmid, IPC_RMID, NULL) < 0)
  {
    perror("shmctl");
  }
}


