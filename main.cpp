#include<iostream>
#include<set>
#include<fstream>
#include<algorithm>
using namespace std;
struct element
{
    char ch;
    int weight;
    int parent;
    int lchild;
    int rchild;
    element()
    {
        weight = 0;
        parent = -1;
        lchild = -1;
        rchild = -1;
    }
};
element huff[1000];
int c = 0;
int find(char ch)
{
    for (int i = 0; i < c; i++)
    {
        if (ch == huff[i].ch) return i;
    }
    return -1;
}
bool cmp(element a, element b)
{
    return a.weight < b.weight;
}
void create_hufftree()
{
    for(int k=c;k<2*c-1;k++)
    {
        int min1,min2;
        min1=min2=huff[0].weight;
        int i1,i2;
        i1=i2=0;
        for(int j=1;j<k;j++)
        {
            if(huff[j].parent==-1)
            {
                if(huff[j].weight<min1)
                {
                    i2=i1;min2=min1;
                    i1=j;min1=huff[j].weight;
                }
                else if(huff[j].weight<min2)
                {
                    i2=j;min2=huff[j].weight;
                }
            }
        }
        huff[k].weight=huff[i1].weight+huff[i2].weight;
        huff[i1].parent=k;
        huff[i2].parent=k;
        huff[k].lchild=i1;
        huff[k].rchild=i2;
    }
}
int main()
{
    ifstream ifs;
    ifs.open("letters.txt", ios::in);
    char ch;
    while (ifs >> ch)
    {
        if (find(ch) == -1)
        {
            huff[c].ch = ch;
            c++;
        }
        else
        {
            huff[find(ch)].weight += 1;
        }
    }
    //sort(huff,huff+c,cmp);
    for(int i=0;i<c;i++)
    {
        cout<<huff[i].weight<<' '<<huff[i].ch<<endl;
    }
    create_hufftree();
    for(int i=0;i<2*c+1;i++)
    {
        cout<<huff[i].parent<<' '<<huff[i].ch<<' '<<huff[i].weight<<' '<<huff[i].lchild<<' '<<huff[i].rchild<<endl;
    }
}