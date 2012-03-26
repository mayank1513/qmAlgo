
# include <stdio.h>
# include <math.h>

main()
{
    int t,k,k1,i,i1,ifd,if1,j,x,x1,y,z,a,b,b1,c;
    int *fd,*f;
    unsigned *F,*F1,n,N;
    unsigned ****G,**gc,**B,**B1,***tick;
    unsigned **T,**T1,**Tf;

    FILE *fp,*fp1;

    printf("\nEnter number of variables");
    scanf("%d",&n);//**********************************************************************************n=No. of variables

    N=pow(2,n);

    printf("\n No. of Variables, n=%d,N=2^n=%d\n",n,N);
//**************************************************************************Allocating Memory to
    f=(int *)malloc(N*sizeof(int));
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    fd=(int *)malloc(N*sizeof(int));
    if(fd==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<N;i++)//*********************************************************************************initializing arrayas to 0
        f[i]=fd[i]=0;

    fp=fopen("Bullionexp1.txt","r");//###################################################opening input file

    for(i=0;;i++)//**********************************************************************************Reading from input file Bullionexp1.txt
    {
        fscanf(fp,"%d",&fd[i]);
        f[i]=fd[i];
        if(fd[i]==-1)
        break;
    }

    if1=i;//if1-->max count of f[] should not be varied durinng program execution

    fd[i]=0;
    for(j=0;;j++)//***************************expression for f(...)is kept separate in f[], whereas exp. for d(...) is merged with that of f(...) in fd[].
    {
        fscanf(fp,"%d",&fd[i+j]);
        if(fd[i+j]==-1)
        break;
    }

    ifd=i+j;//******************************************ifd-->max count for fd[]

    fclose(fp);

    mergesort(fd,0,ifd-1);//sorting expression
    //mergesort(f,0,if1-1);

    f=(int *)realloc(f,(i+1)*sizeof(int));//***************************************freeing extra memory
    if(f==NULL) printf("\nsufficient memory not avilable!!\n");

    fd=(int *)realloc(fd,(i+j+1)*sizeof(int));
    if(fd==NULL) printf("\nsufficient memory not avilable!!\n");

    fp=fopen("BullionOut.txt","w");//****************************************Opening output file

    printf("\n n=%d,N=%d",n,N);
//**************************Allocating memory to 4 dimentional Grouping Array,G and other needful arrays**********************************************************
        printf("\nAllocating memory...");
    G=(int****)malloc((n+1)*sizeof(int *));
    if(G==NULL) printf("\nsufficient memory not avilable!!\n");

    tick=(int***)malloc((n+1)*sizeof(int *));
    if(tick==NULL) printf("\nsufficient memory not avilable!!\n");

       // printf("\nHari!!__Memory allocation done for G\n");//**********************************Remove
    for(t=0;t<n+1;t++)
    {
        G[t]=(int ***)malloc((n+1)*sizeof(int *));
        if(G[t]==NULL) printf("\nsufficient memory not avilable!!\n");

        tick[t]=(int **)malloc((n+1)*sizeof(int *));
        if(tick[t]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(k=0;k<n+1;k++)
    {
        G[t][k]=(int **)malloc(pow(3,n)*sizeof(int *));
        if(G[t][k]==NULL) printf("\nsufficient memory not avilable!!\n");

        tick[t][k]=(int *)malloc(pow(3,n)*sizeof(int));
        if(tick[t][k]==NULL) printf("\nsufficient memory not avilable!!\n");

        for(i=0;i<pow(3,n);i++)
        {
            G[t][k][i]=(int *)calloc(n,sizeof(int));
            if(G[t][k][i]==NULL) printf("\nsufficient memory not avilable!!\n");
        }
    }
    }

//*****************************************initializing G and tick************************************************************************************
    for(t=0;t<n+1;t++){
       // printf("\nG[%d]=%d",t,G[t]);
        for(k=0;k<(n+1);k++){
         //   printf("\nG[t][k]=%d",G[t][k]);
            for(i=0;i<pow(3,n);i++){
                tick[t][k][i]=0;
           //     printf("\nG[t][k][i]=%d,%d",G[t][k][i],i);
                for(j=0;j<n;j++){
                    G[t][k][i][j]=0;
             //       printf("\nG[t][k][i][j]=%d",G[t][k][i][j]);
                    }}}}
       // printf("\nHari!!__Initialization done for G\n");//**********************************Remove


    B=(int **)malloc(ifd*sizeof(int *));
    if(B==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<ifd;i++)
    {
        B[i]=(int *)calloc(n,sizeof(int));
        if(B[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    B1=(int **)malloc(pow(3,n)*sizeof(int *));
    if(B1==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<pow(3,n);i++)//01-3digit no.-==2
    {
        B1[i]=(int *)calloc(n,sizeof(int));
        if(B1[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    gc=(int **)malloc((n+1)*sizeof(int *));
    if(gc==NULL) printf("\nsufficient memory not avilable!!\n");

    for(t=0;t<n+1;t++)
    {
        gc[t]=(int *)calloc((n+1),sizeof(int));
        if(gc[t]==NULL) printf("\nsufficient memory not avilable!!\n");
    }



    printf("\n\t\t_Memory allocation done!!\n\n");
//****************************************Getting binary and Grouping*******************************************

    for(i=0;i<ifd;i++)
    {
        for(j=0;j<n;j++)
        {
            B[i][j]=fd[i]%2;
            fd[i]/=2;
        }
    }//Bs obtained

    for(k=0;k<(n+1);k++)//grouping
    {
        b=0;
        for(i=0;i<ifd;i++)
        {
            x=0;
            for(j=0;j<n;j++)
            {
                x+=B[i][j];
            }
           if(x==k)
            {
                for(j=0;j<n;j++)
                    G[0][k][b][j]=B[i][j];
            b++;
            }
        }
    gc[0][k]=b;
    }
for(k=0;k<(n+1);k++)
    printf("\nHari Bol!!%d",gc[0][k]);

    //*********************T[0]Grouping done*******************


    for(t=0;t<n+1;t++)
    {
        b=0;
        b1=0;
        //printf("\n**%d**",t);
        //printf("\nHari Bol_k=%d\n",k);
        for(k=0;k<(n+1)-1;k++)
        {
            //b=0;
            //printf("\nHari Bol_k=%d\n",k);
            for(i=0;i<gc[t][k];i++)
            {
                //printf("\nHari Bol_i=%d\n",i);
                //b1=0;
                for(i1=0;i1<gc[t][k+1];i1++)
                {
                   // printf("\nHari Bol_i1=%d\n",i1);
                    x=0;
                    for(j=0;j<n;j++)
                        x+=G[t][k][i][j]^G[t][k+1][i1][j];

                   // printf("\nHari Hari!!%d,%d,%d,%d,%d,%d",x,j,i1,i,k,t);//*************************************************

                    if(x==1)
                    {
                        tick[t][k][i]=1;
                        tick[t][k+1][i1]=1;
                        //printf("\n**tick[%d][%d][%d]=%d",t,k,i,tick[t][k][i]);
                      //  printf("\n**tick[%d][%d][%d]=%d",t,k,i1,tick[t][k][i1]);
                        //printf("\nHari!!%d,%d,%d,%d,%d,%d",x,j,i1,i,k,t);//*************************************************
                        for(j=0;j<n;j++)
                        {
                            if(G[t][k][i][j]!=G[t][k+1][i1][j])
                                B1[b1][j]=2;
                            else{
                                B1[b1][j]=G[t][k][i][j];}
                            //printf("%d",B1[b1][j]);
                        }
                    b1++;//printf("\t!!%d!!\n",b1);
                    }

                }//for(i1)end
            }//i end
            for(i1=i;i1<pow(3,n);i1++)
                tick[t][k][i1]=1;

        }//k end

        for(k1=k;k1<n+1;k1++)
            for(i=0;i<pow(3,n);i++)
                tick[t][k1][i]=1;

        F=(int *)calloc(pow(3,n),sizeof(int));
            if(F==NULL) printf("\nsufficient memory not avilable!!\n");

        F1=(int *)calloc(pow(3,n),sizeof(int));
            if(F1==NULL) printf("\nsufficient memory not avilable!!\n");

        for(i=0;i<b1;i++){
            F[i]=0;
            F1[i]=0;}

        for(i=0;i<b1;i++)
            for(j=0;j<n;j++)
                F[i]+=B1[i][j]*pow(3,j);

        mergesort(F,0,b1-1);

        F1[0]=F[0];
        y=0;
        for(i=1;i<b1;i++)
        {
           // for(j=0;j<i;j++)
                if(F[i]==F[i-1])
                    y++;
                    F1[i-y]=F[i];
                    }


        for(i=0;i<b1;i++)
            printf("\n%d,%d,%d",F[i],F1[i],i);

        for(i=0;i<b1;i++)
        {
//            printf("\nHari!%d\t",F1[i]);//**********************************************Remove
            for(j=0;j<n;j++)
            {
                B1[i][j]=F1[i]%3;
                F1[i]/=3;
           // printf("%d",B1[i][j]);//**********************************************Remove
            }
        }
    //free(F1);

for(k=0;k<(n+1)-(t+1);k++)//grouping
    {
 //printf("\nHari!%d%d\t",k,t);//**********************************************Remove

        b=0;
        for(i=0;i<b1;i++)
        {
            x=0;
            for(j=0;j<n;j++)
                x+=B1[i][j];
   //     printf("\n%d,%d,%d\tG[0][k][i][j]",x,i,k);//***********************************************************Remove
            if(x==k+(t+1)*2)
            {
                for(j=0;j<n;j++)
                {
                    G[t+1][k][b][j]=B1[i][j];
                    //printf("\t%d",G[0][k][i][j]);
                }
                b++;
            }
     //       printf("\nHari %d,%d,%d\tG[0][k][i][j]",x,i,k);//***********************************************************Remove
        }
        gc[t+1][k]=b;
       //  printf("\nHari!%d,%d\t",k,t);//**********************************************Remove

    }//2nd k end
    }//t end

    //fprintf(fp,"tend=%d",t);
    //x1=t;
    /*for(t=0;t<n+1;t++)
    {
     printf("\n\t*****************t=%d********************",t);
    for(k=0;k<(n+1);k++)
    {
        for(i=0;i<gc[t][k];i++)
        {
            printf("\n");
                for(j=0;j<n;j++)
                printf("%d",G[t][k][i][j]);
            }
        }
    }*/

    T=(int **)malloc(pow(3,n)*sizeof(int *));
    if(T==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<pow(3,n);i++)
    {
        T[i]=(int *)calloc(n,sizeof(int));
        if(T[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    for(i=0;i<pow(3,n);i++)
        for(j=0;j<n;j++)
        T[i][j]=0;

    y=0;

    for(t=0;t<n+1;t++)
        for(k=0;k<(n+1);k++)
            for(i=0;i<pow(3,n);i++)
            {
                if(tick[t][k][i]==0)
                {
                   // printf("\n**tick[%d][%d][%d]=%d",t,k,i,tick[t][k][i]);
                    //x=0;
                    //for(j=0;j<n;j++)
                      //  x+=G[t][k][i][j];

                    for(j=0;j<n;j++)
                        T[y][j]=G[t][k][i][j];
                        y++;
                    //if(i==0) continue;
                    //if(x==0)
                }
            }

    /* for(k=0;k<(n+1);k++)
    {
        printf("\n\t****************%d*********************",k);
        for(i=0;i<pow(3,n);i++)
        {
            printf("\n");
            for(t=0;t<n+1;t++)
            {
                printf("  tick[%d][%d][%d]=%d",t,k,i,tick[t][k][i]);
            }
        }
    }*/

    //***********************printing Groups**************************

    for(k=0;k<(n+1);k++)
    {
        fprintf(fp,"\n\t****************%d*********************",k);
        for(i=0;i<pow(3,n);i++)
        {
            fprintf(fp,"\n");
            for(t=0;t<n+1;t++)
            {
                fprintf(fp,"\t");
                for(j=0;j<n;j++)
                fprintf(fp,"%d",G[t][k][i][j]);
            }
        }
    }
//********************************Freeing Memory********************
        for(t=0;t<n+1;t++)
        {
            for(k=0;k<(n+1);k++)
            {
                for(i=0;i<pow(3,n);i++)
                    free(G[t][k][i]);
            }
            for(k=0;k<(n+1);k++)
                free(G[t][k]);
        }

        for(t=0;t<n;t++)
            free(G[t]);

        free(G);
//**************************************Memory freed**********
    T1=(int **)malloc(pow(3,n)*sizeof(int *));
        if(T1==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<pow(3,n);i++)
    {
        T1[i]=(int *)calloc(n,sizeof(int));
        if(T1[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    if(tick[0][0][0]==0)
        z=1;
    else
        z=0;

        for(i=0,y=0;i<pow(3,n);i++)
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

   // for(i=0;i<pow(3,n);i++)
    //{
      //  printf("\nT[%d]=",i);
        //for(j=0;j<n;j++)
          //  printf("%d",T[i][j]);
  //  }

   // for(i=0;i<z;i++)
    //{
      //  printf("\nT1[%d]=",i);
        //for(j=0;j<n;j++)
          //  printf("%d",T1[i][j]);
    //}

    Tf=(int **)malloc(if1*sizeof(int *));
    if(Tf==NULL) printf("\nsufficient memory not avilable!!\n");

    for(i=0;i<if1;i++)
    {
        Tf[i]=(int *)calloc(z,sizeof(int));
        if(Tf[i]==NULL) printf("\nsufficient memory not avilable!!\n");
    }

    for(i=0;i<if1;i++)
        for(j=0;j<z;j++)
        Tf[i][j]=0;

   // for(i=0;i<if1;i++)
    //for(j=0;j<z;j++)
       // printf("%d",Tf[i][j]);

  //  printf("\nz=%d\n",z);
    for(i=0;i<z;i++)
    {
        x=0;
        printf("\nTf[%d]=",i);
        fd[0]=0;
        k=0;

        for(j=0;j<n;j++)
        {
        if(T1[i][j]==2)
        {
            fd[k]=j;
            k++;
        }
        else
            x+=T1[i][j]*pow(2,j);
        }
    //    printf("\nx=%d",x);

        y=pow(2,k)-1;

        for(a=0;y>=0;a++)
        {
            t=0;
            b=y;
            for(j=0;j<k;j++)
            {
                T[a][fd[j]]=b%2;
                b/=2;
                t+=T[a][fd[j]]*pow(2,fd[j]);
           // printf("%d",B[i][j]);//**********************************************Remove
            }

     //       printf(",t=%d,t+x=%d",t,t+x);
            for(i1=0;i1<if1;i1++)
                if((x+t)==f[i1])
                    Tf[i1][i]=1;
            y--;
        }
        for(i1=0;i1<if1;i1++)
            printf("%d",Tf[i1][i]);
    }

    x1=2;
    a=0;
    b=0;
    c=0;

   // for(i=0;i<pow(3,n);i++)
     //   printf("\n%d,%d,%d",F1[i],i,F[i]);

printf("if1=%d",if1);
   for(j=0;j<if1;j++)//i,i1,y->;j,k|^__Elemination
    {
       // printf("\nj=%d",j);
        //for(i1=0;i1<b;i1++)
          //  if(i==fd[i1]) break;
        x=0;
        for(i1=0;i1<z;i1++)//Searching for column having only one 1
        {
            //printf("\n Hari%d",j);
            x+=Tf[j][i1];
            if(x>1) break;
        }
        if(x==0) //F1[c]=j;c++;
        if(x==1)//Searching horizontally for 1
        {

        //    printf("x=%d",x);
            for(y=0;y<z;y++)//searching for value of i corresponding to unique 1
                if(Tf[j][y]==1)
                {
                    if(F[b-1]!=y){
                    F[b]=y;
                    b++;}
                    break;}

          //  printf("y=%d",y);
            //F1[c]=j;c++;//******************************************************************Remove

            for(k=0;k<if1;k++)//Eliminating
            {
            if(Tf[k][y]==1)
            {
                //*************************Remove
                //fd[b]=i1;b++;
                for(a=0;a<z;a++)
                    Tf[k][a]=0;//making zero
            //    printf("\n Hari,k=%d,y=%d",k,y);
            }
            }
        }
    }

    for(i=z-1;i>=0;i--)
    {
        for(j=0;j<if1;j++)
        {
            x=0;
            if(Tf[j][i]==1)
            {
                x++;
                if(x<=1);
                F[b]=i;b++;

                //*************************Remove
                //fd[b]=i1;b++;
                for(a=0;a<z;a++)
                    Tf[k][a]=0;//making zero
            //    printf("\n Hari,k=%d,y=%d",k,y);
            }
            }
    }

    F1[0]=F[0];
        y=0;
        for(i=1;i<b;i++)
        {
           // for(j=0;j<i;j++)
                if(F[i]==F[i-1])
                    y++;
                    F1[i-y]=F[i];
                    }

    fp1=fopen("Minimized.txt","w");

    for(a=0;a<i-y;a++)
    {
        fprintf(fp1,"\n%d\t",a);
        for(j=0;j<n;j++)
        {
           // printf("%d",T1[F1[a]][j]);
            if(T1[F1[a]][j]==0)
                fprintf(fp1,"%c'",'a'+j);
            else if(T1[F1[a]][j]==1)
                fprintf(fp1,"%c",'a'+j);
        }
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
