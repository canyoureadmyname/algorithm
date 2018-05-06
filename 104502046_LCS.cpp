#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
void ArrayCalculate(int m, int n, string X, string Y, int* out);
string LCS(int m, int n, string X, string Y);

int main(){
    int t = 0;
    cin>>t;
    string Output[t];
    for(int i = 0; i<t; i++){
        string seqX;
        string seqY;
        cin>>seqX;
        cin>>seqY;
        int lenX = seqX.length();
        int lenY = seqY.length();
        if(lenX < lenY){//guarantee n<=m
            swap(seqX, seqY);
            swap(lenX, lenY);
        }
        Output[i] = LCS(lenX, lenY, seqX, seqY);
    }
    //cout result
    cout<<Output[0];
    for(int i = 1; i<t; i++){
        cout<<endl<<Output[i];
    }
}

void ArrayCalculate(int m, int n, string X, string Y, int* out){
    int cur[n+1];
    int prv[n+1];
    for(int i=0; i<=n; i++){cur[i] = 0;}//init
    for(int i=0; i<m; i++){
        for(int  k=0; k<=n; k++){prv[k] = cur[k];}//sync
        for(int j=0; j<n; j++){//calculate cur[]
            if(X.at(i) == Y.at(j)){
                cur[j+1] = prv[j] + 1;
            }
            else{
                cur[j+1] = max(prv[j+1], cur[j]);
            }
        }
    }
    for(int i=0; i<=n; i++){out[i] = cur[i];}//result store
}

string LCS(int m, int n, string X, string Y) {
    if(n==0){return "";}//trivial
    else if(m==1){
        string result = "";
        for(int i=0; i<n; i++){
            if(X.at(0)==Y.at(i)){
                result += X.at(0);
                break;
            }
        }
        return result;
    }
    //split to 2
    int div_m = m/2;
    int L1[n+1];//store sub LCS value
    int L2[n+1];
    string subX = X.substr(0, div_m);
    //get reverse substring
    string rev_subX = X.substr(div_m, m-div_m);
    string rev_Y = Y;
    reverse(rev_subX.begin(), rev_subX.end());
    reverse(rev_Y.begin(), rev_Y.end());
    //calculate sub LCS value
    ArrayCalculate(div_m, n, subX, Y, L1);
    ArrayCalculate(m-div_m, n, rev_subX, rev_Y, L2);
    int max_value = -1;
    int k;//link point
    for(int i=n ; i>=0; i--){//find k
        if(max_value < L1[i] + L2[n-i]){
            max_value = L1[i] + L2[n-i];
            k = i;
        }
    }
    //deal with the little problem
    string shortX_1 = X.substr(0, div_m);
    string shortX_2 = X.substr(div_m, m-div_m);
    string shortY_1 = Y.substr(0, k);
    string shortY_2 = Y.substr(k, n-k);
    string subLCS_1 = LCS(div_m, k, shortX_1, shortY_1);
    string subLCS_2 = LCS(m-div_m, n-k, shortX_2, shortY_2);

    return subLCS_1 + subLCS_2;
}
