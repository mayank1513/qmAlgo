#ifndef QMA_H_
#define QMA_H_




#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input(int n)
{
    int *s,*f,*d,N;
    int i,j,k=0,x,a,b;
    FILE *fp;

    N=pow(2,n);

    s=(int*)malloc(N*sizeof(int));
    if(s==NULL) printf("\nsufficient memory not avilable!!\n");

    f=(int*)malloc(N*sizeof(int));
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    d=(int*)malloc(N*sizeof(int));
    if(d==NULL) printf("\nsufficient memory not avilable!!\n");

    printf("\n n=%d,N=%d\n",n,N);//****************************************************************************Keep

    fp=fopen("Bullionexp1.txt","w");

    for(i=0;i<N;i++)
        s[i]=f[i]=d[i]=0;

    for(i=0;i<N;i++)//generating random no.s
        s[i]=(rand()*i+2*i/rand()+i*i*rand()+rand())%N;

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

    fprintf(fp,"\n%d",-1);

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

    fprintf(fp,"\n%d",-1);

}
#endif // QMA_H_INCLUDED
