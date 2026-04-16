#include <iostream>
#include <chrono>
using namespace std;
using namespace std ::chrono;
struct domino{
    int a,b;
    int x1,y1,x2,y2;
    domino(){
        a=-1;
        b=-1;
        x1=-1;
        y1=-1;
        x2=-1;
        y2=-1;
    }
    domino(int a,int b,int x1,int y1,int x2,int y2){
        this->a=a;
        this->b=b;
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
    }
};
class domino_half{
    int a;
    bool taken;
public:
    domino_half(int a){
        this->a=a;
        taken=false;
    }
    friend ostream &operator<<(ostream &out, const domino_half &d);
};
ostream &operator<<(ostream &out, const domino_half &d){
        out<<d.a;
        return out;
}
void find(const domino_half riddle[6][10],domino answer[28]){
    for(int i=0;i<6;i++){
        for(int j=0;j<10;j++){
            if(i==0){
                if(j==0){

                } else {

                }
            }
            if(j==0){

            }
            if(i!=0 && j!=0){

            }
        }
    }
}
int main() {
    auto start = high_resolution_clock::now();
    const domino_half riddle[6][10]={
        {0,0,1,1,2,3,3,5,4,0},
        {3,3,2,5,6,6,3,4,2,0},
        {6,3,0,6,1,1,6,4,2,0},
        {2,2,4,3,6,6,1,3,2,2},
        {2,4,4,0,0,5,4,5,5,5},
        {1,1,4,6,0,5,1,3,5,3}
    };
    domino answer[28];
    cout<<"The riddle: "<<endl;
    for(int i=0;i<6;i++){
        for(int j=0;j<10;j++){
            cout<<riddle[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Found dominos: "<<endl;
    for(int i=0;i<7;i++){
        for(int j=0;j<7-i;j++){
            cout<<i<<'-'<<6-j<<" at adress: "<<endl;
        }
        cout<<endl;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout <<"Program took: "<< duration.count() << " milliseconds" << endl;
    return 0;
}