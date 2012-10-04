#include <stdio.h>
#include <stdlib.h>
#include <math.h>

main()
{
    int n;
    scanf("%d",&n);
    input(n);
}
void input(int n)
{
    int *s,*f,*d,N;
    int i,j,k=0,x,a,b,h, jf, jd;
    FILE *fp;
    char s1[15];

    printf("\nOutput file(less than 15 char including'.txt':\t");
    scanf("%s",s1);

    N=pow(2,n);

    s=(int*)malloc(N*sizeof(int));
    if(s==NULL) printf("\nsufficient memory not avilable!!\n");

    f=(int*)malloc(N*sizeof(int));
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    d=(int*)malloc(N*sizeof(int));
    if(d==NULL) printf("\nsufficient memory not avilable!!\n");

    printf("\n n=%d,N=%d\n",n,N);//****************************************************************************Keep

    fp=fopen(s1,"w");

    for(i=0;i<N;i++)
        s[i]=f[i]=d[i]=0;
printf("\n Enter a random number.");
scanf("%d",&h);
    for(i=0;i<N;i++)//generating random no.s
        s[i]=(rand()*h+2*i/rand()+i*i*rand()+rand())%N;

    for(i=0,k=0;i<N;i++)
    {
        x=*(s+i);
        for(j=i+1;j<N;j++)
        {
            if(x>s[j])
            {
                x=s[j];
                a=j;
            }
        }
        s[a]=s[i];

        if(i==0){f[i]=x;printf("\t%d,%d,%d",f[i],i,k); continue;}
        if(f[i-k-1]==x)
            k++;

        f[i-k]=x;
    }
    f[i-k]=-1;

    for(j=0;f[j]>-1;j++)
        fprintf(fp,"\n%d",f[j]);

    jf=j;

    fprintf(fp,"\n%d",-1);

printf("\n Enter a random number.");
scanf("%d",&h);
for(i=0;i<N;i++)//generating random values
        s[i]=(rand()*i+2*i/rand()+rand()*2)%N;

 for(i=0,k=0;i<N;i++)//extracting values for d
    {
        x=*(s+i);
        for(j=i+1;j<N;j++)
        {
            if(x>s[j])
            {
                x=s[j];
                a=j;
            }
        }

        s[a]=s[i];

        if(i==0){d[i]=x; continue;}
        if(d[i-k-1]==x)
            k++;
        for(j=0;f[j]>-1;j++)
        {
            if(d[i-k-1]==f[j])
            {
                if(d[i-k-1]!=x)
                    k++;
                    break;
            }
        }
        d[i-k]=x;
        }
    d[i-k]=-1;

    for(j=0;d[j]>-1;j++)//Printing d into file
        fprintf(fp,"\n%d",d[j]);

    jd=j;

    fprintf(fp,"\n%d",-1);

    fclose(fp);

    //fp=fopen(s1,"r");
    //if(fp==NULL){printf("\nError opening file %s",s1);  return;}

    printf("\nOutput file for main(less than 15 char including'.txt':\t");
    scanf("%s",s1);

    fp=fopen(s1,"w");

        for(j=jf-1;j>=0;j--)
        fprintf(fp,"\n%d",f[j]);

        for(j=jd-1;j>=0;j--)
        {
            fprintf(fp,"\n%c",'x');
            fprintf(fp,"%d",d[j]);
        }
}

