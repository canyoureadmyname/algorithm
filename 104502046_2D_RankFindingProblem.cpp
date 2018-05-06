#include <iostream>
//#include <windows.h>
using namespace std;

void mergeSort(int a[][4], int length, bool isSortingX);
void insertionSort(int a[][4], int length, bool isSortingX);
int t; //threshold

int main() {
    t=124;
	int n = 0;
	/*FILETIME startTime;
	FILETIME endTime;
	double timeCost;*/
	while (1) {
        /*cout<<"t=";
        cin>>t; //set threshold*/
		cin>>n;  // n points
		if (n == 0) return 0; //input 0 then ending
		int Points[n][4]; // [n][0] = x, [n][1] = y, [n][2] = rank, [n][3] = input sequence
		for (int i = 0; i<n; i++) { //input x,y
			cin >> Points[i][0];
			cin >> Points[i][1];
			Points[i][2] = 0; //init rank
			Points[i][3] = i; //input sequence
		}
		//GetSystemTimeAsFileTime(&startTime);
		mergeSort(Points, n, true);//sorting x
		mergeSort(Points, n, false);//sorting y and get rank
		//insertionSort(Points, n, false);
		/*GetSystemTimeAsFileTime(&endTime);
		timeCost = (endTime.dwLowDateTime - startTime.dwLowDateTime)*1E-7;*/
		int OriSeqRank[n]; //store rank with original sequence
		for (int i = 0; i<n; i++) { // get OriSeqRank
            int seq = Points[i][3];
            OriSeqRank[seq] = Points[i][2];
		}
		cout <<OriSeqRank[0];
		for (int i = 1; i<n; i++) { // cout rank,ending with no blank
			cout <<" "<<OriSeqRank[i];
		}
		cout<<endl;
		//cout<<"time cost:"<<timeCost<<endl;
	}
}

void mergeSort(int a[][4], int length, bool isSortingX) {
	if (length == 0 || length == 1)
		return;
	int LeftLength = length / 2, RightLength = (length - length / 2);
	int LeftSide[LeftLength][4];
	int RightSide[RightLength][4];
	for (int i = 0; i<LeftLength; i++) {//assign a
		LeftSide[i][0] = a[i][0];
		LeftSide[i][1] = a[i][1];
		LeftSide[i][2] = a[i][2];
		LeftSide[i][3] = a[i][3];
	}
	for (int i = 0; i<RightLength; i++) {
		RightSide[i][0] = a[LeftLength + i][0];
		RightSide[i][1] = a[LeftLength + i][1];
		RightSide[i][2] = a[LeftLength + i][2];
		RightSide[i][3] = a[LeftLength + i][3];
	}
	if(isSortingX){ //sorting x or y, using merge or insertion sort
        if(LeftLength <= t){
            insertionSort(LeftSide, LeftLength, true);
        }
        else{
            mergeSort(LeftSide, LeftLength, true);
        }
        if(RightLength <= t){
            insertionSort(RightSide, RightLength, true);
        }
        else{
            mergeSort(RightSide, RightLength, true);
        }
	}
	else{
        if(LeftLength <= t){
            insertionSort(LeftSide, LeftLength, false);
        }
        else{
            mergeSort(LeftSide, LeftLength, false);
        }
        if(RightLength <= t){
            insertionSort(RightSide, RightLength, false);
        }
        else{
            mergeSort(RightSide, RightLength, false);
        }
	}
	for (int k = 0, i = 0, j = 0,rankStack = 0; k<length; k++) {//attach left&right to a
        if(isSortingX){
            if (LeftSide[i][0]<RightSide[j][0]) {
                a[k][0] = LeftSide[i][0];
                a[k][1] = LeftSide[i][1];
                a[k][2] = LeftSide[i][2];
                a[k][3] = LeftSide[i][3];
                i++;
            }
            else {
                if((LeftSide[i][0]==RightSide[j][0]) && (LeftSide[i][1]<RightSide[j][1])) {//Lx=Rx, Ly<Ry
                    a[k][0] = LeftSide[i][0];
                    a[k][1] = LeftSide[i][1];
                    a[k][2] = LeftSide[i][2];
                    a[k][3] = LeftSide[i][3];
                    i++;
                }
                else{
                    a[k][0] = RightSide[j][0];
                    a[k][1] = RightSide[j][1];
                    a[k][2] = RightSide[j][2];
                    a[k][3] = RightSide[j][3];
                    j++;
                }
            }
        }
        else{//sorting y
            if (LeftSide[i][1]<=RightSide[j][1]) {//Ly=Ry,attach LeftSide first
                a[k][0] = LeftSide[i][0];
                a[k][1] = LeftSide[i][1];
                a[k][2] = LeftSide[i][2];
                a[k][3] = LeftSide[i][3];
                i++;
                rankStack++;
            }
            else {
                a[k][0] = RightSide[j][0];
                a[k][1] = RightSide[j][1];
                a[k][2] = RightSide[j][2] += rankStack; //get rank
                a[k][3] = RightSide[j][3];
                j++;
            }
        }
		if (i == LeftLength) {
			while (j<RightLength) {
                k++;
				a[k][0] = RightSide[j][0];
				a[k][1] = RightSide[j][1];
				a[k][3] = RightSide[j][3];
				if(isSortingX){
                    a[k][2] = RightSide[j][2];
				}
				else{
                    a[k][2] = RightSide[j][2] += rankStack;
				}
                j++;
			}
			break;
		}
		if (j == RightLength) {
			while (i<LeftLength) {
                k++;
				a[k][0] = LeftSide[i][0];
				a[k][1] = LeftSide[i][1];
				a[k][2] = LeftSide[i][2];
				a[k][3] = LeftSide[i][3];
                i++;
			}
			break;
		}
	}
	return;
}

void insertionSort(int a[][4], int length, bool isSortingX){
    if(isSortingX){//sorting x
        for(int i = 0; i<length; i++){
            int inValueX = a[i][0];
            int inValueY = a[i][1];
            int inRank = a[i][2];
            int inSeq = a[i][3];
            for(int j = 0; j<i; j++){
                if(inValueX<a[j][0] || (inValueX==a[j][0] && inValueY<a[j][1])){
                    swap(inValueX, a[j][0]);
                    swap(inValueY, a[j][1]);
                    swap(inRank, a[j][2]);
                    swap(inSeq, a[j][3]);
                }
            }
            a[i][0] = inValueX;
            a[i][1] = inValueY;
            a[i][2] = inRank;
            a[i][3] = inSeq;
        }
    }
    else{//sorting y
        for(int i = 0; i<length; i++){
            int inValueX = a[i][0];
            int inValueY = a[i][1];
            int inRank = a[i][2];
            int inSeq = a[i][3];
            bool isSwapped = false; //if it haven't swapped = false
            for(int j = 0; j<i; j++){
                if(inValueY<a[j][1]){
                    swap(inValueX, a[j][0]);
                    swap(inValueY, a[j][1]);
                    swap(inRank, a[j][2]);
                    swap(inSeq, a[j][3]);
                    if(!isSwapped){
                        a[j][2] = j; //get rank
                        isSwapped = true;
                    }
                }
            }
            a[i][0] = inValueX;
            a[i][1] = inValueY;
            a[i][2] = inRank;
            a[i][3] = inSeq;
            if(!isSwapped){//its y is the largest
                a[i][2] = i; //get rank
            }
        }
    }
    return;
}
