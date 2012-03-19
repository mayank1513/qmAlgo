# include <stdio.h>
# include <math.h>

#define N 16
int mergesort(int a[], int low, int high);

main()
{
    int K[N]={1,2,5,6,9,10,11,12,13,14,15},i,j,k,bit[16][4],stack[4],g[4][N][4]={0},tick[N]={-1};
    int x=0,y;

    for(i=0;i<N;i++)
        printf("\n%d",tick[i]);

    mergesort(K,0,N);//sort

    for(i=0;i<N;i++)
    {
        printf("\n%d\t",K[i]);
        for(j=0;j<4;j++)
        {
            bit[i][j]=K[i]%2;
            K[i]/=2;
            printf("%d",bit[i][j]);
        }

        for(k=0,j=0;k<4;k++,j++)
            stack[k]=bit[i][j];
        for(k=3,j=0;k>=0;k--,j++)
        {
            bit[i][j]=stack[k];
           // printf("\nk=%d,j=%d,bit[i][j]");
        }

        printf("\t");
        for(j=0;j<4;j++)
            printf("%d",bit[i][j]);
           // printf("\t%d",tick[i]);
    }//bits obtained
    for(k=0;k<4;k++)//grouping
    {
    for(i=0;i<N;i++)
    {
        x=0;
        for(j=0;j<4;j++)
        {
          x+=bit[i][j];
        }
        printf("\n%d,%d,%d",x,i,k);
        if(x==k){
        for(j=0;j<4;j++){
            g[k][i][j]=bit[i][j];
            printf("\t%d",g[k][i][j]);
        }
        }
    }
    }

    for(k=0;k<4;k++)
    {
        printf("\nGroup%d",k);
    for(i=0;i<N;i++)
    {
        printf("\t");
        for(j=0;j<4;j++)
        {
            printf("%d",g[k][i][j]);
        }
    }
    }

    for(k=0;k<4;k++)
    {
        for(i=0;i<N;i++)
        {
            for(y=0;y<16;y++){
                x=0;
            for(j=0;j<N;j++)
                x+=g[k][i][j]^g[k+1][y][j];
            if(x==1)
            {
                tick[i]=1;
                tick[y]=1;
            }
            }
        }
    }

}

//******************************************************************
int mergesort(int a[], int low, int high)
{
int mid;
if(low<high)
{
mid=(low+high)/2;
mergesort(a,low,mid);
mergesort(a,mid+1,high);
merge(a,low,high,mid);
}
return(0);
}

merge(int a[], int low, int high, int mid)
{
int i, j, k, c[10000];
i=low;
j=mid+1;
k=low;
while((i<=mid)&&(j<=high))
{
if(a[i]>a[j])
{
c[k]=a[i];
k++;
i++;
}
else
{
c[k]=a[j];
k++;
j++;
}
}
while(i<=mid)
{
c[k]=a[i];
k++;
i++;
}
while(j<=high)
{
c[k]=a[j];
k++;
j++;
}
for(i=low;i<k;i++)
{
a[i]=c[i];
}
}
