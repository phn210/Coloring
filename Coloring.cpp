#include <iostream>
#include <fstream>

using namespace std;

void tomau(int i, int **adj,int n2)
{
    int j;
    adj[i][0]=1;
    for(j=1;j<n2;j++)
    {
        if(adj[i][j]!=0&&adj[adj[i][j]-1][0]==adj[i][0])
        {
            adj[i][0]++;
            j=0;
        }
    }
    for(j=1;j<n2;j++)
    {
        if(adj[i][j]!=0)
            if (adj[adj[i][j]-1][0]==0) tomau(adj[i][j]-1,adj,n2);
    }
}

void print(int **adj, int **canh, int n1, int n2,ofstream &output)
{
    output << "graph dothi" <<endl;
    output << "{" <<endl;
    int i;
    for(i=0;i<n1;i++)
    {
        output << i+1 << " " << "[fillcolor=";
        switch (adj[i][0])
        {
            case 1:
            {
                output <<"SkyBlue";
                break;
            }
            case 2:
            {
                output <<"cyan";
                break;
            }
            case 3:
            {
                output <<"SeaGreen";
                break;
            }
            case 4:
            {
                output <<"OliveDrab";
                break;
            }
            case 5:
            {
                output <<"DarkSalmon";
                break;
            }
            case 6:
            {
                output <<"coral";
                break;
            }
            case 7:
            {
                output <<"red";
                break;
            }
            case 8:
            {
                output <<"HotPink";
                break;
            }
            case 9:
            {
                output <<"snow1";
                break;
            }
            case 10:
            {
                output <<"LightYellow";
                break;
            }
        }
        output << ", style=filled];" << endl;
    }
    for(i=0;i<n2;i++)
        output << canh[0][i] <<" -- " << canh[1][i] << endl;

    output << "}" << endl;
}

int main()
{
    int i=0,j=0;
    int n1,n2;//n1 la so dinh, n2 la so canh
    ifstream input;
    input.open("Dothi.txt");//file Dothi.txt giong nhu trong de bai
    input >> n1 >> n2;

    int **canh;
    canh = new int *[2];
    for(i=0;i<2; i++)
        canh[i] = new int[n2];

    int **adj; //luu tru do thi bang danh sach ke dang mang
    adj = new int *[n1];
    for(int i = 0; i <n1; i++)
        adj[i] = new int[n2];

    for(j=0;j<n2;j++)
        for(i=0;i<2;i++)
            input >> canh[i][j];
    input.close();

    for(i=0;i<n1;i++)
        for(j=0;j<n2;j++)
            adj[i][j]=0;

    for(i=0;i<n1;i++)
    {
        int count;
        count = 1;
        for(j=0;j<n2;j++)
        {
            if(canh[0][j]==i+1) adj[i][count++]=canh[1][j];
            else if(canh[1][j]==i+1) adj[i][count++]=canh[0][j];
        }
    }

    for(i=0;i<n1;i++)
    {
        if(adj[i][0]!=0) continue;
        tomau(i,adj,n2);
    }
    ofstream output;
    output.open("dothitomau.dot");
    print(adj,canh,n1,n2,output);
    output.close();
    return 0;
}
