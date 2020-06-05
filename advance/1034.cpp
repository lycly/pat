#include <iostream>
#include <string>
#include <map>
using namespace std;

const int maxn = 2010; //总人数
const int INF = 1000000000; //无穷大

map<int, string> intToString; //编号->姓名
map<string, int> stringToInt; //姓名->编号
map<string, int> Gang; //head->人数

int G[maxn][maxn] = {0}, weight[maxn] = {0}; //邻接矩阵G，点权weight
int n, k, numPerson = 0; //边数n、下限k、总人数numPerson
bool visited[maxn] = {false}; //标记是否被访问

//head为头目，numMember为成员编号，totalValue为连通块的总边权
void DFS(int nowVisit, int &head, int &numMember, int &totalValue) {
    numMember++; //成员人数加1
    visited[head] = true; //标记nowVisit已访问
    if(weight[nowVisit] > weight[head]) {
        head = nowVisit; //当前访问结点的权值大于头目的点权，则更新头目
    }
    for(int i = 0; i < numPerson; i++) { //枚举所有人
        if(G[nowVisit][i] > 0) {
            totalValue += G[nowVisit][i]; //连通块的总边权增加该边权
            G[nowVisit][i] = G[i][nowVisit] = 0; //删除这条边，防止回头
            if(visited[i] == false)
                DFS(i, head, numMember, totalValue);
        }
    }
}

//DFSTrave函数遍历整个图，获取每个连通块的信息
void DFSTrave() {
    for(int i = 0; i < numPerson; i++) {
        if(!visited[i]) { //如果i未被访问
            int head = i,numMember = 0, totalValue = 0; //头目、成员数、总边权
            DFS(i, head, numMember, totalValue); //遍历i所在的连通块
            if(numMember > 2 && totalValue > k) { //成员数大于2且总边权大于k
                Gang[intToString[head]] = numMember;
            }
        }
    }
}

//change函数返回姓名str对应的编号
int change(string str) {
    if(stringToInt.find(str) != stringToInt.end()) {
        return stringToInt[str];
    }
    else{
        stringToInt[str] = numPerson; //str的编号为numPerson
        intToString[numPerson] = str; //numPerson对应str
        return numPerson++; //总人数加1
    }
}

int main()
{
    int w;
    string str1,str2;
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> str1 >> str2 >> w; //输入两个端点和点权
        int id1 = change(str1); //将str1转换为编号id1
        int id2 = change(str2); //将str2转换为编号id2
        weight[id1] += w; //id1的点权增加w
        weight[id2] += w; //id2的点权增加w
        G[id1][id2] += w; //边id1->id2的边权增加w
        G[id2][id1] += w; //边id2->id1的边权增加w
    }
    DFSTrave(); //遍历整个图的所有连通表，获取Gang的信息
    cout << Gang.size() << endl; //Gang的个数
    map<string, int>::iterator it;
    for(it = Gang.begin(); it != Gang.end(); it++)
        cout <<it->first << " " << it->second << endl; //输出信息
    return 0;
}