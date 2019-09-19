#include <stdio.h>
int r0, r1, r2, r3, r4, r5, r6, r7,
	r8, r9, r10, r11, r12, r13, r14, r15,
	r16, r17, r18, r19, r20, r21, r22, r23,
	r24, r25, r26, r27, r28, r29, r30, r31;
int *iptr1;
char *cptr1;
char *fp, *sp;
char global_array_0[24000];
char global_array_1[24000];
char global_array_2[24000];
char global_array_3[24000];
main ()
{
    printf("The solution for 4 disks is:\n");
    hanoi(1,3,2,4);
}

hanoi(r1 ,r2 ,r3 ,r4 )
{
    *(global_array_0 + 12) = r4;
    *(global_array_0 + 8) = r3;
    *(global_array_0 + 4) = r2;
    *(global_array_0 + 0) = r1;
    r7 = 0;
    r5 = *(global_array_0 + 12);
    r6 = 1;
    if (r5==r6) goto assign0;
    goto AssignEnd0;
    assign0:
    r7 = 1;
    AssignEnd0:
    r8 = 1;
    if (r7 == r8 ) goto execuate0;
    goto end0;
    execuate0:
    printf("     Move disk from ");
    r9 = *(global_array_0 + 0);
    printf("%d",r9);
    printf(" to ");
    r10 = *(global_array_0 + 4);
    printf("%d\n",r10);
    end0:
    r11 = 0;
    if (r7 == r11 ) goto execuate1;
    goto end1;
    execuate1:
    r12 = *(global_array_0 + 12);
    r13=r12-1;
    r14 = *(global_array_0 + 0);
    r15 = *(global_array_0 + 8);
    r16 = *(global_array_0 + 4);
    hanoi(r14,r15,r16,r13);
    printf("     Move disk from ");
    r17 = *(global_array_0 + 0);
    printf("%d", r17);
    printf(" to ");
    r18 = *(global_array_0 + 8);
    printf("%d\n",r18);
    r19 = *(global_array_0 + 12);
    r20=r19-1;
    r21 = *(global_array_0 + 8);
    r22 = *(global_array_0 + 4);
    r23 = *(global_array_0 + 0);
    hanoi(r21,r22,r23,r20);
    end1:
	return 0;
}

