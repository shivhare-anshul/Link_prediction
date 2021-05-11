#include <stdio.h>
#include <stdlib.h>

/************** Implementation of Adjacency list using Linkedlist of Linkedlist ******************/
struct jacards
{
    int index1;
    int index2;
    float val;
};


/***** Structure for node ******/
struct adjnode
{
    int vertex;
    struct adjnode* next;
};

/***** Structure for list ******/
struct Adjacencylist
{
    struct adjnode *head;
    struct Adjacencylist *next;
    int val;

};

/***** Structure for graph ******/

struct Adjacency_graph
{
    int v;
    struct Adjacencylist * link;
};


/******************** creating the adjacency list before inserting edges in graph  ************************/

struct Adjacency_graph* createAdjacency(int v)
{

   struct Adjacency_graph* graph =(struct Adjacency_graph*) malloc(sizeof(struct Adjacency_graph));
    graph->v = v;


    graph->link=NULL;

    struct Adjacencylist *temp;

    int c=0;
    for(int i=0;i<v;i++)
    {



        temp=(struct Adjacencylist*) malloc(sizeof(struct Adjacencylist));
        temp->head=NULL;
        if(i==0)
        {
            temp->next=NULL;

        }

        temp -> next = graph -> link;
        graph->link=temp;

    }

    //after inserting all nodes , now updating the value in nodes from 0 to 327, so that later it will be easy to insert or delete edges

    for(int i=0;i<v;i++)
    {

       if(temp->head==NULL)
       {
          temp->val=c;
          c++;
       }
       temp=temp->next;


    }



    return graph;


};





 /******************* addEdge function Adds an edge to an undirected graph  **************************/

void addEdge(struct Adjacency_graph* graph, int src, int dest)
{
     /*Add an edge from src to dest.  A new node is
     added to the adjacency list of src.  The node
     is added at the end*/

     /*****  This will link the destination vertex with source vertex in Adjacency list ******/

    struct adjnode* newnode;
    newnode=(struct adjnode*) malloc(sizeof(struct adjnode));
    newnode->vertex=dest;
    newnode->next=NULL;

    struct Adjacencylist *temp;
    temp= graph->link;


    while(temp->val !=src)
    {
        //printf("%d ",temp->val);
        temp=temp->next;
    }
    //printf("ab");
    if(temp->head==NULL)
    {
        temp->head=newnode;
    }
    else
    {
        struct adjnode* itr1;
        itr1=temp->head;
        while(itr1->next!=NULL)
        {
            itr1=itr1->next;
        }
        itr1->next=newnode;

    }

    /*Add an edge from dest to src.  A new node is
     added to the adjacency list of dest.  The node
     is added at the end*/

    /*****  This will link the source vertex with destination vertex in Adjacency list ******/

    struct Adjacencylist *temp1;
    temp1= graph->link;

    struct adjnode* newn;
    newn=(struct adjnode*) malloc(sizeof(struct adjnode));
    newn->vertex=src;
    newn->next=NULL;
    while(temp1->val !=dest)
    {
        temp1=temp1->next;
    }

    if(temp1->head==NULL)
    {
        temp1->head=newn;
    }
    else
    {
        struct adjnode* itr2;
        itr2=temp1->head;
        while(itr2->next!=NULL)
        {
            itr2=itr2->next;
        }
        itr2->next=newn;

    }

}



///**************** Print function to traverse every link with there respective nodes  ************************/

void printarray(struct Adjacency_graph *graph)
{

    struct Adjacencylist *temp;

    temp= graph->link;


    while(temp)
    {
        struct adjnode *temp22;

        temp22= temp->head;

        printf("\n%d   :",temp->val);
        while(temp22)
        {

           printf("%d  ",temp22->vertex);
           temp22=temp22->next;
        }

       temp=temp->next;
    }
    printf("\n");

}

/**************************************** Creating Adjacency matrix using the adjacency list   ************************************/

void Adjacency_matrix(struct Adjacency_graph *graph,int v,int **A_matrix)
{

/* Initializing the elements of matrix as 0 */
   for(int i=0;i<v-1;i++)
   {
       for(int j=0;j<v-1;j++)
       {
           A_matrix[i][j]=0;
       }
   }


   struct Adjacencylist *temp;

    temp= graph->link;


int g=0;
    while(temp)
    {
        struct adjnode *temp22;

        temp22= temp->head;

        while(temp22)                                           //Traversing the edges and for every edge updating the matrix with value 1
        {
            g++;
           A_matrix[temp->val-1][temp22->vertex-1]=1;
           temp22=temp22->next;
        }

       temp=temp->next;
    }

    /** Traversing the matrix **/

//    for(int i=0;i<v-1;i++)
//   {
//       for(int j=0;j<v-1;j++)
//       {
//           printf("%d   ",A_matrix[i][j]);
//       }
//       printf("\n");
//   }
//

}


/***************************************** calculating the jaccards coef for the non- existing edges  ******************************************/
float jaccard_coef(int val1, int val2,struct Adjacency_graph *graph,int v)
{

   struct Adjacencylist *temp;
   temp= graph->link;

    while(temp->val !=val1)
    {
        temp=temp->next;
    }

    struct adjnode *temp22;
    temp22= temp->head;

    int a[v];

    for(int i=0;i<v;i++)                    //Initializing an array of size 328, to calculate the union and intersection of the both the vertices neigbours
    {
        a[i]=0;
    }

    while(temp22)
    {

      a[(temp22->vertex)-1]++;
      temp22=temp22->next;
    }



   struct Adjacencylist *temp1;
   temp1= graph->link;

   while(temp1->val !=val2)
    {
        temp1=temp1->next;
    }


    struct adjnode *temp23;
    temp23= temp1->head;

    while(temp23)
    {

      a[(temp23->vertex)-1]++;
      temp23=temp23->next;
    }

  float result=0;
  float u=0;
  float inter=0;
    for(int i=0;i<v;i++)
    {

        if(a[i]==1 ||a[i]==2)
        {
            u++;

        }
        if(a[i]==2)
        {
            inter++;

        }
    }
  if(u!=0)
    result=inter/u;
  return result;


}

/*************************************** Calling merge sort  *************************************************/
void merge_sort(struct jacards jacards_array[],int left,int mid,int right)
{

    int n1 = mid - left + 1;
    int n2 = right - mid;
    int k = left;

    /* create temp arrays */
    struct jacards arr1[n1], arr2[n2];

    /* Copy data to temp arrays */
    for (int j = 0; j < n2; j++)
        arr2[j] = jacards_array[mid + 1 + j];
    for (int i = 0; i < n1; i++)
        arr1[i] = jacards_array[left + i];


    // Merge the temp arrays back
    int i = 0;
    int j = 0;

    while (i < n1 && j < n2)
    {
        if (arr1[i].val < arr2[j].val) {
            jacards_array[k] = arr1[i];
            i++;
        }
        else if(arr1[i].val==arr2[j].val)
        {
            if(arr1[i].index1>arr2[j].index1)
            {
                jacards_array[k]=arr1[i];
                i++;
            }
            else if(arr1[i].index1<arr2[j].index1)
            {
                jacards_array[k]=arr2[j];
                j++;
            }
            else
            {
                if(arr1[i].index2>arr2[j].index2)
                {
                    jacards_array[k]=arr1[i];
                    i++;
                }
                else
                {
                    jacards_array[k]=arr2[j];
                    j++;
                }

            }

        }
        else {
            jacards_array[k] = arr2[j];
            j++;
        }

        k++;
    }


    // Copy the remaining elements
    while (j < n2) {
        jacards_array[k] = arr2[j];
        k++;
        j++;

    }

     // Copy the remaining elements
    while (i < n1) {
        jacards_array[k] = arr1[i];
        k++;
        i++;

    }

}

void sort_jaccards(struct jacards jacards_array[],int left,int right,int unvisited_edge)
{
  //mid=l+r/2;

  int mid= left+(right-left)/2;
      if(left<right)
      {
        sort_jaccards(jacards_array, left, mid,unvisited_edge);
        sort_jaccards(jacards_array, mid + 1, right,unvisited_edge);

        merge_sort(jacards_array,left,mid,right);


      }

}

/******************************* This "copy function" copies matrix of type int to matrix of type double ****************************/
void copy(double **B,int **A,int v)
{
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            B[i][j]=(double)A[i][j];
        }
    }


}


/******************************* This "copy1 function" copies matrix of type double to matrix of type double ****************************/
void copy1(double **B,double **A,int v)
{
    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            B[i][j]=A[i][j];
        }
    }

}

/******************** mul_matrix function to multiply the matrices *************************/

void mul_matrix(double **B,int **A,double **mat,int v)
{


    for (int i = 0; i <v; i++)
    {
        for (int j = 0; j <v; j++)

        {
            mat[i][j] = 0;
            for (int k = 0; k <v; k++)
            {

                mat[i][j] +=(double)A[i][k] * B[k][j];

            }

        }
    }

}
void mul_matrix_1(double **B,double **A,double **mat,int v)
{


    for (int i = 0; i <v; i++)
    {
        for (int j = 0; j <v; j++)

        {
            mat[i][j] = 0;
            for (int k = 0; k <v; k++)
            {

                mat[i][j] +=A[i][k] * B[k][j];

            }

        }
    }



}


/*************************************** katz function returns the "katz matrix" which include kartz score of every 2 nodes  ***********************************************/


double **katz(int **A_matrix,float beta_1,float beta,int v)
{

    double **updated_mat = (double **)calloc(v,sizeof(double *));
    for (int i=0; i<v; i++)
         updated_mat[i] = (double *)calloc(v,sizeof(double));



    double **B_matrix=(double **)calloc(v,sizeof(double*));       //Dynamically allocating the matrix.
     for (int i=0; i<v; i++)
         B_matrix[i] = (double *)calloc(v,sizeof(double));



     double **mat=(double **)calloc(v,sizeof(double*));
     for (int i=0; i<v; i++)
         mat[i] = (double *)calloc(v, sizeof(double));



     copy(B_matrix,A_matrix,v);

//     for(int i=0;i<v;i++)
//     {
//         for(int j=0;j<v;j++)
//         {
//             printf("%lf ",B_matrix[i][j]);
//         }
//         printf("\n");
//     }

     for(int i=2;i<=6;i++)
     {

         mul_matrix(B_matrix,A_matrix,mat,v);
         copy1(B_matrix,mat,v);

         for(int j=0;j<v;j++)
         {
             for(int k=0;k<v;k++)
             {
                 updated_mat[j][k]=updated_mat[j][k]+beta_1 * mat[j][k];


             }
         }

        beta_1=beta_1* beta;
     }

//     for(int i=0;i<v;i++)
//     {
//         for(int j=0;j<v;j++)
//         {
//             printf("%lf ",updated_mat[i][j]);
//         }
//         printf("\n");
//     }

     for(int i=0;i<v;i++)
   {
     free(B_matrix[i]);
   }
   free(B_matrix);

   for(int i=0;i<v;i++)
   {
     free(mat[i]);
   }
   free(mat);


     return updated_mat;

}

/***********************************  commute_time function returns the commute_time matrix ***************************************/

double **commute_time(int **A_matrix,int v,int k)
{

      //dynamically allocating space to matrices
     double **prob_mat=(double **)calloc(v,sizeof(double*));
     for (int i=0; i<v; i++)
         prob_mat[i] = (double *)calloc(v,sizeof(double));

     double **B_matrix=(double **)calloc(v,sizeof(double*));
     for (int i=0; i<v; i++)
         B_matrix[i] = (double *)calloc(v,sizeof(double));

     double **mat=(double **)calloc(v,sizeof(double*));
     for (int i=0; i<v; i++)
          mat[i] = (double *)calloc(v,sizeof(double));

     double **updated_mat=(double **)calloc(v,sizeof(double*));
     for (int i=0; i<v; i++)
          updated_mat[i] = (double *)calloc(v,sizeof(double));

    int a[v];
    for(int i=0;i<v;i++)
    {
        int sum=0;
        for(int j=0;j<v;j++)
        {
            sum=sum+A_matrix[i][j];

        }
        a[i]=sum;
    }


    for(int i=0;i<v;i++)
    {
        for(int j=0;j<v;j++)
        {
            if(a[i]==0)
            {
                a[i]=1;
            }
            prob_mat[i][j]=(double)A_matrix[i][j]/(double)a[i];
        }
    }

//     for(int i=0;i<v;i++)
//    {
//        for(int j=0;j<v;j++)
//        {
//            printf("%lf ",prob_mat[i][j]);
//        }
//        printf("\n");
//    }



 if(k==1)
 {
    copy1(B_matrix,prob_mat,v);

    for(int i=2;i<=6;i++)
     {
         int p=i;
         //printf("%d  ",p);
         mul_matrix_1(B_matrix,prob_mat,mat,v);

         copy1(B_matrix,mat,v);

         for(int j=0;j<v;j++)
         {
             for(int k=0;k<v;k++)
             {
                 updated_mat[j][k]=updated_mat[j][k]+p* mat[j][k];


             }
         }


     }
     for(int i=0;i<v;i++)
     {
         for(int j=i;j<v;j++)
         {
            updated_mat[i][j]=updated_mat[i][j]+updated_mat[j][i];
         }
     }

 }


 else
 {
     if(k==2)
     {
        copy1(B_matrix,prob_mat,v);
        int x;


            for(int i=2;i<=20;i++)
             {
                 int p=i;
                 //printf("%d  ",p);
                 mul_matrix_1(B_matrix,prob_mat,mat,v);

                 copy1(B_matrix,mat,v);

                 for(int j=0;j<v;j++)
                 {
                     for(int k=0;k<v;k++)
                     {
                         updated_mat[j][k]=updated_mat[j][k]+p* mat[j][k];


                     }
                 }


             }
             for(int i=0;i<v;i++)
             {
                 for(int j=i;j<v;j++)
                 {
                    updated_mat[i][j]=updated_mat[i][j]+updated_mat[j][i];
                 }
             }



     }

 }
//    for(int i=0;i<v;i++)
//    {
//        for(int j=0;j<v;j++)
//        {
//            printf("%lf ",updated_mat[i][j]);
//        }
//        printf("\n");
//    }


   for(int i=0;i<v;i++)
   {
     free(B_matrix[i]);
   }
   free(B_matrix);

   for(int i=0;i<v;i++)
   {
     free(mat[i]);
   }
   free(mat);


   for(int i=0;i<v;i++)
   {
     free(prob_mat[i]);
   }
   free(prob_mat);



    return updated_mat;
}

/**************************** display output function is displaying the output in the text file ********************************/

void display_output(char *f_name,FILE *f_obj,struct jacards jacards_array[],int p,int m)
{
  f_obj= fopen(f_name,"w");
//  int k;
//  printf("\n enter the number of elements to be displayed:\n");
//  scanf("%d",&k);

  for(int i=0;i<m;i++)
      {
         printf("%f   \n",jacards_array[p-1].val);
         fprintf(f_obj,"%d ", jacards_array[p-1].index1);
         fprintf(f_obj,"%d ", jacards_array[p-1].index2);
         fprintf(f_obj,"%f \n", jacards_array[p-1].val);

         p--;
      }
      printf("\n\n");

  fclose(f_obj);

}

//void display_output_1(char *f_name,FILE *f_obj,struct jacards jacards_array[],int p)
//{
//    f_obj= fopen(f_name,"w");
//  int k;
//  printf("\nenter the number of elements to be displayed:\n");
//  scanf("%d",&k);
//
//  for(int i=0;i<k;i++)
//      {
//         printf("%f   \n",jacards_array[i].val);
//         fprintf(f_obj,"%d ", jacards_array[i].index1);
//         fprintf(f_obj,"%d ", jacards_array[i].index2);
//         fprintf(f_obj,"%f \n", jacards_array[i].val);
//
//      }
//}




/***************************************************** Main function **************************************************************/

int main()
{
    int v=0;
     FILE *file1;
     char* filename="contact-high-school-proj-graph.txt";


    //opening file in read mode

    file1= fopen(filename,"r");


    if(file1==NULL)
    {
        printf("empty");
        return 0;
    }

        int a[3];
        int s=0;
        while(1)
        {


            for(int i=0;i<3;i++)
            {
                if(feof(file1))
                {
                 s++;
                 break;
                }

                fscanf(file1,"%d",&a[i]);           //Here i am calculating the total number of vertices in the graph,
                if(a[0]>v) v=a[i];                  //This can be done by taking out the maximum value in the first 2 columns in the
                if(a[1]>v) v=a[i];                  //txt file.


            }
            if(s)
                break;
        }

    //printf("%d ",v);
    int total_edges= v*(v-1) *0.5;                  //calculating the total number of edges
    //printf("%d ",total_edges);

    int **A_matrix=(int **)calloc(v , sizeof(int*)); //Dynamically allocating memory to matrix using calloc.
     for (int i=0; i<v; i++)
         A_matrix[i] = (int *)calloc(v, sizeof(int));


    struct Adjacency_graph* Ag= createAdjacency(v+1);  //creating graph for v+1 nodes, as my adjacency list starts from 0

    FILE *file;

    //opening file in read mode

    file= fopen(filename,"r");


    if(file==NULL)
    {
        printf("empty");
        return 0;
    }

        int b[3];
        int edge=0;
        int y=0;
        while(1)
        {


            for(int i=0;i<3;i++)
            {
                if(feof(file))
                {
                 y++;
                 break;
                }

                fscanf(file,"%d",&b[i]);


            }
            if(y)
                break;

            addEdge(Ag,b[0],b[1]);          //adding edge to graph (adjacency list)
            edge++;
        }
        //printarray(Ag);                   //uncomment printarray to print the adjacency list .

        int unvisited_edge= total_edges-edge; //calculating the non existing edges in graph
        Adjacency_matrix(Ag,v+1,A_matrix);

        struct jacards jacards_array[unvisited_edge];  //A array of structures is maintained so that it stores the 3 values in it
                                                       //first 2 values includes the vertices and the last entry include the jaccards coeeffiets of those to vertex




     int count=0;

      for(int i=0;i<v;i++)                         //calling jaccards for every 0th entry in adjacency matrix
      {
          for(int j=i;j<v;j++)
          {
              if(i!=j && A_matrix[i][j]==0)          //checking it should not be diagonal entry and entry with value 1
              {
                 float k=jaccard_coef(i+1,j+1,Ag,v);

                 jacards_array[count].index1=i+1;     //storing the values in array
                 jacards_array[count].index2=j+1;
                 jacards_array[count].val=k;
               count++;

              }

          }
      }

      int left=0;                    //initializing left and right ,to sort the jaccards array using merge sort.
      int right=unvisited_edge-1;


      sort_jaccards(jacards_array,left,right,unvisited_edge); //function to sort the array of structures using there jaccards coefficient



     double beta=0.1;
     double beta_1=beta * beta;

    double **k=katz(A_matrix,beta_1,beta,v);   //calling katz function,and this function return a pointer to a matrix

    struct jacards katzs_array[unvisited_edge]; //same as jaccards, a array of structures are maintained


     int count1=0;

      for(int i=0;i<v;i++)                         //calling kartz for every 0th entry in adjacency matrix
      {
          for(int j=i;j<v;j++)
          {
              if(i!=j && A_matrix[i][j]==0)          //checking it should not be diagonal entry and entry with value 1
              {

                 katzs_array[count1].index1=i+1;     //storing the values in array
                 katzs_array[count1].index2=j+1;
                 katzs_array[count1].val=k[i][j];
                 count1++;

              }
          }
      }

      sort_jaccards(katzs_array,left,right,unvisited_edge);  //sorting the katzs array in decreasing order w.r.t katz value


      double **ct=commute_time(A_matrix,v,1);   //calling COMMUTE function ,this will return the respective matrix
      double **convergence =commute_time(A_matrix,v,2);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      struct jacards *hitting_array = (struct jacards*)calloc(unvisited_edge,sizeof(struct jacards));

      int count3=0;

      for(int i=0;i<v;i++)
      {
          for(int j=i;j<v;j++)
          {
              if(i!=j && A_matrix[i][j]==0)          //checking it should not be diagonal entry and entry with value 1
              {


                 hitting_array[count3].index1=i+1;     //storing the values in array
                 hitting_array[count3].index2=j+1;
                 hitting_array[count3].val=ct[i][j] * -1;

                 count3++;

              }
          }
      }


      sort_jaccards(hitting_array,left,right,unvisited_edge);  //sorting the katzs array in decreasing order w.r.t katz value



      ////////////////////////////////////////////////////////////////////
      struct jacards *converge_array = (struct jacards*)calloc(unvisited_edge,sizeof(struct jacards));

      int count4=0;

      for(int i=0;i<v;i++)
      {
          for(int j=i;j<v;j++)
          {
              if(i!=j && A_matrix[i][j]==0)          //checking it should not be diagonal entry and entry with value 1
              {


                 converge_array[count4].index1=i+1;     //storing the values in array
                 converge_array[count4].index2=j+1;
                 converge_array[count4].val=convergence[i][j] * -1;

                 count4++;

              }
          }
      }


      sort_jaccards(converge_array,left,right,unvisited_edge);  //sorting the katzs array in decreasing order w.r.t katz value





/**************************** Writing on file *******************************/

      int m;
      printf("\n enter the number of elements to be displayed ,for all 4 methods:\n");
      scanf("%d",&m);


     char *f_name1="Jaccard.txt";
     FILE *f_obj1;
     display_output(f_name1,f_obj1,jacards_array,unvisited_edge,m );

     char *f_name2="Katz.txt";
     FILE *f_obj2;
     display_output(f_name2,f_obj2,katzs_array, unvisited_edge,m);

     char *f_name3="HittingTime.txt";
     FILE *f_obj3;
     display_output(f_name3,f_obj3,hitting_array, unvisited_edge,m);

     char *f_name4="HittingTimeAccurate.txt";
     FILE *f_obj4;
     display_output(f_name4,f_obj4,converge_array, unvisited_edge,m);




}

