#include <string>
#include <cmath>

using namespace std;


unsigned int binaryS_to_decimalInt(string s){
    unsigned int n =0;
    for(unsigned int i=0; i<s.size(); i++){
        if(s[s.size()-1-i]=='1')n+=pow(2,i);
    }
    return n;

}
string decimalInt_to_binaryS(unsigned int n,int size){
    string s(size,'0');
    while(n>0){
        unsigned int i=0,a=1;
        while(a<=n){
            a*=2;
            i++;
        }
        s[s.size()-1-(i-1)]='1';
        n-=(a/2);
    }
    return s;
    /*string s;
    for (int i = size - 1; i >= 0; --i) {
        s += ((n >> i) & 1) ? '1' : '0';
    }
    return s;*/

}
