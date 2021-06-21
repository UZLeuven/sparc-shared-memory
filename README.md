# SPARC sharedmemory madv.so.1

Shared memory is created using
```
char *shmpointer_1 =shmat(shmid,NULL,00200 );

```

Intimate Shared memory using 
```
char *shmpointer_1 =shmat(shmid,NULL,SHM_SHARE_MMU);
```


## Building
````
make
````

## Testing
Shared memory is located in one locality groups
```
# ./test-shm
FFFFFFFE00000000  5070848K rwxs---     2 [ shmid=0x71000046 ]
FFFFFFFF35800000     1664K rwxs---     2 [ shmid=0x71000046 ]
FFFFFFFF359A0000       56K rwxs---     2 [ shmid=0x71000046 ]
````


Intimate shared memory is located in both locality groups
```
t# ./test-ishm
001FFFFD80000000  2097152K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFE00000000  2359296K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFE90000000   262144K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEA0000000   266240K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB0400000    12288K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB1000000    12288K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB1C00000    12288K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB2800000    28672K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB4400000     8192K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB4C00000     8192K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5400000     4096K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5800000      128K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5820000      128K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5840000      192K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5870000      128K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5890000       64K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB58A0000       64K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB58B0000       64K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB58C0000       64K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB58D0000      256K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5910000       64K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5920000      128K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5940000       64K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5950000      192K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB5980000       64K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB5990000       64K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB59A0000        8K rwxsR--     2 [ ism shmid=0x6a00006e ]
001FFFFEB59A2000        8K rwxsR--     1 [ ism shmid=0x6a00006e ]
001FFFFEB59A4000       40K rwxsR--     2 [ ism shmid=0x6a00006e ]
```