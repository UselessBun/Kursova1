#include <iostream>;
using namespace std;
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
int find(int dtofind[2], domino_half riddle[6][10]){
    
}
int main() {
    domino_half riddle[6][10]={
        {0,0,1,1,2,3,3,5,4,0},
        {3,3,2,5,6,6,3,4,2,0},
        {6,3,0,6,1,1,6,4,2,0},
        {2,2,4,3,6,6,1,3,2,2},
        {2,4,4,0,0,5,4,5,5,5},
        {1,1,4,6,0,5,1,3,5,3}
    };
    cout<<"The riddle: "<<endl;
    for(int i=0;i<6;i++){
        for(int j=0;j<10;j++){
            cout<<riddle[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"Found dominos: "<<endl;
    cout<<"0-0, at adresses: "<<endl;
    cout<<"0-1, at adresses: "<<endl;
    cout<<"0-2, at adresses: "<<endl;
    cout<<"0-3, at adresses: "<<endl;
    cout<<"0-4, at adresses: "<<endl;
    cout<<"0-5, at adresses: "<<endl;
    cout<<"0-6, at adresses: "<<endl;
    cout<<"1-1, at adresses: "<<endl;
    cout<<"1-2, at adresses: "<<endl;
    cout<<"1-3, at adresses: "<<endl;
    cout<<"1-4, at adresses: "<<endl;
    cout<<"1-5, at adresses: "<<endl;
    cout<<"1-6, at adresses: "<<endl;
    cout<<"2-2, at adresses: "<<endl;
    cout<<"2-3, at adresses: "<<endl;
    cout<<"2-4, at adresses: "<<endl;
    cout<<"2-5, at adresses: "<<endl;
    cout<<"2-6, at adresses: "<<endl;
    cout<<"3-3, at adresses: "<<endl;
    cout<<"3-4, at adresses: "<<endl;
    cout<<"3-5, at adresses: "<<endl;
    cout<<"3-6, at adresses: "<<endl;
    cout<<"4-4, at adresses: "<<endl;
    cout<<"4-5, at adresses: "<<endl;
    cout<<"4-6, at adresses: "<<endl;
    cout<<"5-5, at adresses: "<<endl;
    cout<<"5-6, at adresses: "<<endl;
    cout<<"6-6, at adresses: "<<endl;
    return 0;
}