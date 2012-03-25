# include <stdio.h>
# include <math.h>

main()
{
    int t,k,i,i1,ifd,j,x,y,z,a,b,c;
    int *fd,*f,*f1,*fd1,n,N;
    int ****G,**gc,**B,**B1,***tick;

    FILE *fp;

    printf("\nEnter number of variables");
    scanf("%d",&n);

    N=pow(2,n);

    printf("\n n=%d,N=%d\n",n,N);

    f=(int *)malloc(N*sizeof(int));
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    fd=(int *)malloc(N*sizeof(int));
    if(fd==NULL) printf("\nsufficient memory not avilable!!\n");

    //printf("\n n=%d,N=%d\n",n,N);

    for(i=0;i<N;i++)//initializing arrayas to 0
        f[i]=fd[i]=0;

    fp=fopen("Bullionexp1.txt","r");//###################################################opening input file

    //for(i=0;i<N;i++)
      //  printf("\n%d\t%d\t%d",i,f[i],fd[i]);//**************************************************************

    for(i=0;;i++)
    {
        fscanf(fp,"%d",&fd[i]);
        f[i]=fd[i];

        //printf("\n%d\t%d\t%d",i,f[i],fd[i]);//**************************************************************

        if(fd[i]==-1)
        break;

    }         //   printf("\tHari!!%d,%d\n",f[j],j);//*****************************************
//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    //printf("\n Hari! n=%d,N=%d\n",n,N);

    //for(k=0;k<N;k++)
      //  printf("\n%d\t%d\t%d",k,f[k],fd[k]);//*************************************

    fd[i]=0;
    for(j=0;fd[j+i]>-1;j++)//i should not be varied o
    {
        fscanf(fp,"%d",&fd[i+j]);
        if(fd[i+j]==-1)
        break;

       // printf("\tHari!!%d,%d\n",f[j-1],j-1);//*************************************
    }

    mergesort(fd,0,i+j-1);

    printf("\n%d,%d",i,i+j);

   printf("\n Hari Bol!! n=%d,N=%d\ni\tf[i]\tfd[i]",n,N);
    for(k=0;k<N;k++)
        printf("\n\n%d\t%d\t%d",k,f[k],fd[k]);//varifying inputs

    f=(int *)realloc(f,(i+1)*sizeof(int));
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    fd=(int *)realloc(fd,(i+j)*sizeof(int));
    if(fd==NULL) printf("\nsufficient memory not avilable!!\n");

    ifd=i+j;

    printf("\n Hari Bol!! n=%d,N=%d\ni\tf[i]\tfd[i]",n,N);
    for(k=0;k<N;k++)
        printf("\n\n%d\t%d\t%d",k,f[k],fd[k]);//varifying inputs********************

//**************************Allocating memory to G**********************************************************
//    Alloc(G,n,N,ifd);


    G=(int****)malloc(n*sizeof(int *));
    if(G==NULL) printf("\nsufficient memory not avilable!!\n");

        printf("\n!!Hari Bol!!__Memory allocation done for G\n");//**********************************Remove
    for(t=0;t<n;t++)
    {
        G[t]=(int ***)malloc(n*sizeof(int *));
        if(G[t]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(k=0;k<n;k++)
    {
        G[t][k]=(int **)malloc(ifd*sizeof(int *));
        if(G[t][k]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(i=0;i<ifd;i++)
        {
            G[t][k][i]=(int *)calloc(n,sizeof(int));
            if(G[t][k][i]==NULL) printf("\nsufficient memory not avilable!!\n");
        }
    }
    }

//*****************************************initializing G************************************************************************************
    printf("!!Hari Bol!!__Memory allocation done for G");//**********************************Remove
    for(t=0;t<n;t++){
        printf("\nG[t]=%d",G[t]);
        for(k=0;k<n;k++){
            printf("\nG[t][k]=%d",G[t][k]);
            for(i=0;i<ifd;i++){
                printf("\nG[t][k][i]=%d,%d",G[t][k][i],i);
                for(j=0;j<n;j++){
                    G[t][k][i][j]=0;
                    printf("\nG[t][k][i][j]=%d",G[t][k][i][j]);}}}}
        printf("\n!!Hari Bol!!__Initialization done for G\n");//**********************************Remove


    B=(int **)malloc(ifd*sizeof(int *));
    if(B==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<ifd;i++)
    {
        B[i]=(int *)calloc(n,sizeof(int));
        if(B[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    //B1=(int **)malloc(n*sizeof(int *));
    //if(B1==NULL) printf("\nsufficient memory not avilable!!\n");

    gc=(int **)malloc(n*sizeof(int *));
    if(gc==NULL) printf("\nsufficient memory not avilable!!\n");

    for(t=0;t<n;t++)
    {
        gc[t]=(int *)malloc(n*sizeof(int));
        if(gc[t]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    printf("!!Hari Bol!!__Memory allocation done");
//****************************************Getting binary and Grouping*******************************************

    for(i=0;i<ifd;i++)
    {
        printf("\n%d\t",fd[i]);//**********************************************Remove
        for(j=0;j<n;j++)
        {
            B[i][j]=fd[i]%2;
            fd[i]/=2;
            printf("%d",B[i][j]);//**********************************************Remove
        }
    }//Bs obtained
    for(k=0;k<n;k++)//grouping
    {
        b=0;
        for(i=0;i<ifd;i++)
        {
            x=0;
            for(j=0;j<n;j++)
            {
                x+=B[i][j];
            }
        printf("\n%d,%d,%d\nG[0][k][i][j]",x,i,k);//***********************************************************Remove
            if(x==k)
            {
                for(j=0;j<n;j++)
                {
                    G[0][k][i][j]=B[i][j];
                    printf("\t%d",G[0][k][i][j]);
                }
                b++;
            }
    }
    gc[0][k]=b;
    }


}




mergesort(int a[], int low, int high)
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
if(a[i]<a[j])
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

void Alloc(int ****G, int n, int N, int ifd)
{
    int t, k, i, j;
    G=(int****)malloc(n*sizeof(int *));
    if(G==NULL) printf("\nsufficient memory not avilable!!\n");

        printf("\n!!Hari Bol!!__Memory allocation done for G\n");//**********************************Remove
    for(t=0;t<n;t++)
    {
        G[t]=(int ***)malloc(n*sizeof(int *));
        if(G[t]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(k=0;k<n;k++)
    {
        G[t][k]=(int **)malloc(ifd*sizeof(int *));
        if(G[t][k]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(i=0;i<ifd;i++)
        {
            G[t][k][i]=(int *)calloc(n,sizeof(int));
            if(G[t][k][i]==NULL) printf("\nsufficient memory not avilable!!\n");
        }
    }
    }

//*****************************************initializing G************************************************************************************
    printf("!!Hari Bol!!__Memory allocation done for G");//**********************************Remove
    for(t=0;t<n;t++){
        printf("\nG[t]=%d",G[t]);
        for(k=0;k<n;k++){
            printf("\nG[t][k]=%d",G[t][k]);
            for(i=0;i<ifd;i++){
                printf("\nG[t][k][i]=%d,%d",G[t][k][i],i);
                for(j=0;j<n;j++){
                    G[t][k][i][j]=0;
                    printf("\nG[t][k][i][j]=%d",G[t][k][i][j]);}}}}
        printf("\n!!Hari Bol!!__Initialization done for G\n");//**********************************Remove

}
