# include <stdio.h>
# include <math.h>

main()
{
    int t,k,i,i1,ifd,if1,j,x,x1,y,z,a,b,b1,c='-';
    int *fd,*f,*f1,*fd1,n,N;
    int ****G,**gc,**B,**B1,***tick;
    int **T,**T1,**Tf;

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

    fp=fopen("Bullionexp.txt","r");//###################################################opening input file

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

    fclose(fp);

    fp=fopen("BullionOut.txt","w");

    mergesort(fd,0,i+j-1);

    printf("\n%d,%d",i,i+j);

   fprintf(fp,"\n Hari Bol!! n=%d,N=%d\ni\tf[i]\tfd[i]",n,N);
    for(k=0;k<N;k++)
        fprintf(fp,"\n\n%d\t%d\t%d",k,f[k],fd[k]);//varifying inputs

    f=(int *)realloc(f,(i+1)*sizeof(int));
    if(f==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    fd=(int *)realloc(fd,(i+j+1)*sizeof(int));
    if(fd==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    ifd=i+j;
    if1=i;

    fprintf(fp,"\n Hari Bol!! n=%d,N=%d\ni\tf[i]\tfd[i]",n,N);
    for(k=0;k<N;k++)
        fprintf(fp,"\n\n%d\t%d\t%d",k,f[k],fd[k]);//varifying inputs********************

//**************************Allocating memory to G**********************************************************
//    Alloc(G,n,N,N*N);


    G=(int****)malloc(n*sizeof(int *));
    if(G==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    tick=(int***)malloc(n*sizeof(int *));
    if(tick==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

        fprintf(fp,"\n!!Hari Bol!!__Memory allocation done for G\n");//**********************************Remove
    for(t=0;t<n;t++)
    {
        G[t]=(int ***)malloc(n*sizeof(int *));
        if(G[t]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

        tick[t]=(int **)malloc(n*sizeof(int *));
        if(tick[t]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

        for(k=0;k<n;k++)
    {
        G[t][k]=(int **)malloc(N*N*sizeof(int *));
        if(G[t][k]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

        tick[t][k]=(int *)malloc(N*N*sizeof(int));
        if(tick[t][k]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

        for(i=0;i<N*N;i++)
        {
            G[t][k][i]=(int *)calloc(n,sizeof(int));
            if(G[t][k][i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
        }
    }
    }

//*****************************************initializing G************************************************************************************
    fprintf(fp,"!!Hari Bol!!__Memory allocation done for G");//**********************************Remove
    for(t=0;t<n;t++){
        //fprintf(fp,"\nG[t]=%d",G[t]);
        for(k=0;k<n;k++){
            //fprintf(fp,"\nG[t][k]=%d",G[t][k]);
            for(i=0;i<N*N;i++){
                tick[t][k][i]=0;
                //fprintf(fp,"\nG[t][k][i]=%d,%d",G[t][k][i],i);
                for(j=0;j<n;j++){
                    G[t][k][i][j]=0;
                    //fprintf(fp,"\nG[t][k][i][j]=%d",G[t][k][i][j]);
                    }}}}
        fprintf(fp,"\n!!Hari Bol!!__Initialization done for G\n");//**********************************Remove


    B=(int **)malloc(ifd*sizeof(int *));
    if(B==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(i=0;i<ifd;i++)
    {
        B[i]=(int *)calloc(n,sizeof(int));
        if(B[i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }

    B1=(int **)malloc(N*N*sizeof(int *));
    if(B1==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(i=0;i<N*N;i++)
    {
        B1[i]=(int *)calloc(n,sizeof(int));
        if(B1[i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }

    gc=(int **)malloc(n*sizeof(int *));
    if(gc==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(t=0;t<n;t++)
    {
        gc[t]=(int *)malloc(n*sizeof(int));
        if(gc[t]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }



    fprintf(fp,"!!Hari Bol!!__Memory allocation done");
//****************************************Getting binary and Grouping*******************************************

    for(i=0;i<ifd;i++)
    {
       // fprintf(fp,"\n%d\t",fd[i]);//**********************************************Remove
        for(j=0;j<n;j++)
        {
            B[i][j]=fd[i]%2;
            fd[i]/=2;
           // fprintf(fp,"%d",B[i][j]);//**********************************************Remove
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
        //fprintf(fp,"\n%d,%d,%d\tG[0][k][i][j]",x,i,k);//***********************************************************Remove
            if(x==k)
            {
                for(j=n-1,y=0;j>=0;j--,y++)
                {
                    G[0][k][b][j]=B[i][j];
                    //fprintf(fp,"\t%d",G[0][k][i][j]);
                }
                b++;
            }
        }
    gc[0][k]=b;
    }
for(k=0;k<n;k++)
    fprintf(fp,"\nHari Bol!!%d",gc[0][k]);


        /*for(k=0;k<n;k++)
            for(i=gc[0][k];i<N*N;i++)
                free(G[0][k][i]);*/

    for(t=0;t<n;t++)
    {
        fprintf(fp,"\n******************************************************");
        for(k=0;k<n-t-1;k++)
        {
            b=0;
            for(i=0;i<gc[t][k];i++)
            {
                b1=0;
                for(i1=0;i1<gc[t][k+1];i1++)
                {
                    /*for(y=0;y<b1-1;y++)
                            {
                                if(i1==0)
                                break;
                                x1=0;
                                for(z=0;z<n;z++)
                                {
                                    if(B1[b1-1][z]!=G[t+1][k][y][z])
                                    x1++;
                                }
                                if(x1==0)
                                b1--;
                            }*/

                    x=0;
                    for(j=0;j<n;j++)
                        x+=G[t][k][i][j]^G[t][k+1][i1][j];

                   // fprintf(fp,"\nHari Hari!!%d,%d,%d,%d,%d,%d",x,j,i1,i,k,t);//*************************************************

                    if(x==1)
                    {
                        tick[t][k][i]=tick[t][k][i1]=1;
                        //fprintf(fp,"\nHari!!%d,%d,%d,%d,%d,%d",x,j,i1,i,k,t);//*************************************************
                        for(j=0;j<n;j++)
                        {
                            if(G[t][k][i][j]!=G[t][k+1][i1][j])
                                B1[b1][j]='-';
                            else
                                B1[b1][j]=G[t][k][i][j];
                                fprintf(fp,"%d",B1[b1][j]);
                        }
                    b1++;fprintf(fp,"\t!!%d!!\n",b1);
                    }

                }
                if(t==n-1) break;
                x=0;

            i1=0;
        for(i1=0;i1<b1;i1++)
        {
            x=0;
            fprintf(fp,"\n********%d*********",i1);
            for(j=0;j<n;j++)
            {
                x+=B1[i1][j];
            }
       // fprintf(fp,"\n%d,%d,%d\tG[t+1][k][i][j]",x,i,k+(t+1)*c);//***********************************************************Remove
            if(x==k+(t+1)*c)
            {
                fprintf(fp,"\nG[%d][%d][%d]=",t+1,k,b);
                for(j=0;j<n;j++)
                {
                    G[t+1][k][b][j]=B1[i1][j];
                    fprintf(fp,"%d",G[t+1][k][b][j]);
                }
                b++;
            }
            //i1++;
        }
            }
        gc[t+1][k]=b;
        }
    }

    T=(int **)malloc(N*N*sizeof(int *));
    if(T==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(i=0;i<N*N;i++)
    {
        T[i]=(int *)calloc(n,sizeof(int));
        if(T[i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }

    for(i=0;i<N*N;i++)
        for(j=0;j<n;j++)
        T[i][j]=0;

    y=0;

    for(t=0;t<n;t++)
        for(k=0;k<n-t;k++)
            for(i=0;i<gc[t][k];i++)
            {
                if(tick[t][k][i]==0)
                {
                    x=0;
                    //for(j=0;j<n;j++)
                      //  x+=G[t][k][i][j];

                    for(j=0;j<n;j++)
                        T[i][j]=G[t][k][i][j];
                    //if(i==0) continue;
                    //if(x==0) y++;
                }
            }

    //***********************printing Groups**************************

for(t=0;t<n;t++)
{
     fprintf(fp,"\n\t*************************************");
    for(k=0;k<n;k++)
    {
        for(i=0;i<gc[t][k];i++)
        {
            fprintf(fp,"\n");
                for(j=0;j<n;j++)
                fprintf(fp,"%d",G[t][k][i][j]);
            }
        }
    }
//********************************Freeing Memory********************
        for(t=0;t<n;t++)
        {
            for(k=0;k<n;k++)
            {
                for(i=0;i<N*N;i++)
                    free(G[t][k][i]);
            }
            for(k=0;k<n;k++)
                free(G[t][k]);
        }

        for(t=0;t<n;t++)
            free(G[t]);

        free(G);

    T1=(int **)malloc(N*N*sizeof(int *));
        if(T1==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(i=0;i<N*N;i++)
    {
        T1[i]=(int *)calloc(n,sizeof(int));
        if(T1[i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }

    if(tick[0][0][0]==0)
        z=1;
    else
        z=0;

        for(i=0;i<N*N;i++)
        {
            x=0;
            for(j=0;j<n;j++)
                x+=T[i][j];
            for(j=0;j<n;j++)
                T1[i-y+z][j]=T[i][j];
            if(x==0) y++;
        }

            T1[i-y+z][n-1]=-1;
    z=i-y+z;
    for(i=0;i<N*N;i++)
    {
        fprintf(fp,"\nT[%d]=",i);
        for(j=0;j<n;j++)
            fprintf(fp,"%d",T[i][j]);
    }

    for(i=0;i<z;i++)
    {
        fprintf(fp,"\nT1[%d]=",i);
        for(j=0;j<n;j++)
            fprintf(fp,"%d",T1[i][j]);
    }

    Tf=(int **)malloc(if1*sizeof(int *));
    if(Tf==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

    for(i=0;i<if1;i++)
    {
        Tf[i]=(int *)calloc(z,sizeof(int));
        if(Tf[i]==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");
    }

    for(i=0;i<if1;i++)
        for(j=0;j<z;j++)
        Tf[i][j]=0;

/*    for(i=0;i<if1;i++)
    for(j=0;j<z;j++)
        fprintf(fp,"%d",Tf[i][j]);

    for(i=0;i<z;i++)
    {
    /*    fprintf(fp,"\nTf[%d]=",i);
        fd[0]=0;
        k=0;
        for(j=0;j<n;j++)
        {
            if(T1[i][j]=='-')
            {
                fd[k]+=0;
                fd[k+1]+=1;
                k+=2;
            }
            else
            {
                fd[k]+=pow(2,j)*T1[i][j];
                fd[k+1]+=pow(2,j)*T1[i][j];
            }
        }*/

  /*      for(j=0;j<n;j++)
        if(T1[i][j]=='-')
        {
            fd[k]=j;
            k++;
        }
        else
            x+=T1[i][j]*pow(2,n-j-1);

        y=pow(2,k)-1;

        for(a=0;y>=0;a++)
        {
            t=0;
            b=y;
            for(j=0;j<k;j++)
            {
                T[a][fd[j]]=b%2;
                b/=2;
                t+=T[a][fd[j]]*pow(2,n-fd[j]-1);
           // fprintf(fp,"%d",B[i][j]);//**********************************************Remove
            }
            for(i1=0;i1<if1;i1++)
                if((x+t)==f[i1])
                    Tf[i1][i]=1;
            y--;
        }
        for(i1=0;i1<if1;i1++)
            fprintf(fp,"\t%d",Tf[i1][i]);
    }
*/
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
//    if(G==NULL) fprintf(fp,"\nsufficient memory not avilable!!\n");

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
