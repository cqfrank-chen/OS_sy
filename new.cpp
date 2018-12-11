#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mem = 1024;
const int N = 10, M = 10;
ll currentTime;
struct node {
    ll address;
    ll length;
    ll flag;
} usedTable[N], freeTable[M];
struct node1{
    ll workId;
    ll startTime;
    ll runningTime;
} workList[N];
bool done(int pos){
    for (int i = 0; i < N; i++){
        if (usedTable[i].flag){
            int t = usedTable[i].flag;
            if (workList[t].startTime + workList[t].runningTime <= currentTime){
                usedTable[i].flag = 0;
                bool f = 0;
                for (int j = 0; j < M; j++){
                    if (!freeTable[j].flag){
                        freeTable[j].flag = 1;
                        freeTable[j].address = usedTable[i].address;
                        freeTable[j].length = usedTable[i].length;
                        f = 1;
                        break;
                    }
                }
                if (!f)
                    merge();
                for (int j = 0; j < M; j++){
                    if (!freeTable[j].flag){
                        freeTable[j].flag = 1;
                        freeTable[j].address = usedTable[i].address;
                        freeTable[j].length = usedTable[i].length;
                        f = 1;
                        break;
                    }
                } 
                if (!f)
                    return false;
            }
        }
    }
    return true;
}
bool getSpace(int pos){
    currentTime = workList[pos].startTime = max(currentTime, workList[pos].startTime);
    if (!done(pos))
        return false;
    int aim = -1;
    for (int i = 0; i < M; i++){
        if (freeTable[i].flag && freeTable[i].length >= workList[pos].length){
            if (aim == -1 || freeTable[i].length < freeTable[aim].length)
                aim = i;
        }
    }
    for (int i = 0; i < N; i++){
        if (!usedTable[i].flag){
            freeTable[aim].length -= workList[pos].length;
            usedTable[i].flag = pos;
            usedTable[i].address = freeTable[aim].address + freeTable[aim].length;
            usedTable[i].length = workList[pos].length;


        }
    }
}
int main(){
    currentTime = 0;
    int index = 0;
    freeTable[0].address = 0;
    freeTable[0].length = mem;
    freeTable[0].flag = 1;
    
    int T;
    scanf("%d", &T);
    while (T--){
        index++;
        scanf("%lld%lld", &workList[index].startTime, &workList[index].runningTime);
        workList[index].workId = index;
        bool gs = getSpace(index);
    }
    
}