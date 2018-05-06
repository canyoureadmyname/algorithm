#include <iostream>
#include <climits>
using namespace std;
void mergeSort(int a[][2],int length);

class max_heap
{
private:
    int n = 0;
    int *heap;

public:
    max_heap(int index)
    {
        heap = new int[index+1];
    }

    ~max_heap()
    {
        delete [] heap;
    }

    int get_size()
    {
        return this->n;
    }

    int heap_remove()  //remove and get the heap root
    {
        int v = heap[1];
        heap[1] = heap[(this->n)--];
        down_heap(1);
        return v;
    }

    void down_heap(int k)
    {
        int j;
        int v;
        v = heap[k];
        while(k <= (this->n)/2)
        {
            j = k + k;
            if((j < this->n)&&(heap[j] < heap[j+1]))
                j++;
            if(v >= heap[j])
                break;
            heap[k] = heap[j];
            k = j;
        }
        heap[k] = v;
        return;
    }

    void up_heap(int k)
    {
        int v;
        v = heap[k];
        heap[0] = INT_MAX;
        while(heap[k/2] < v)
        {
            heap[k] = heap[k/2];
            k = k/2;
        }
        heap[k] = v;
        return;
    }

    void insert_heap(int v)  //insert new value into the heap
    {
        heap[++(this->n)] = v;
        up_heap(this->n);
        return;
    }

    int total_value()
    {
        int total = 0;
        for(int i = 1; i <= this->n; i++)
        {
            total += heap[i];
        }
        return total;
    }
};

int main()
{
    int k;
    cin>>k;
    int ans[k];
    for(int i = 0; i < k; i++)
    {
        int n;
        cin>>n;
        int works[n][2];// [0]=t, [1]=d
        for(int l = 0; l < n; l++)
        {
            cin>>works[l][0];
            cin>>works[l][1];
        }
        mergeSort(works, n);//sort with deadline
        max_heap h(n);
        for(int l = 0; l < n; l++)
        {
            h.insert_heap(works[l][0]);
            if(works[l][1] < h.total_value())
            {
                h.heap_remove();
            }
        }
        ans[i] = h.get_size();
    }
    for(int i = 0; i < k-1; i++)
    {
        cout<<ans[i]<<endl;
    }
    cout<<ans[k-1];
    return 0;
}

void mergeSort(int a[][2],int length)
{
    if(length == 0 || length == 1)
        return;
    int l = length/2,r = (length-length/2);
    int left[l][2];
    int right[r][2];
    for(int i=0; i<l; i++) //assign a
    {
        left[i][0] = a[i][0];
        left[i][1] = a[i][1];
    }
    for(int i=0; i<r; i++)
    {
        right[i][0] = a[l+i][0];
        right[i][1] = a[l+i][1];
    }
    mergeSort(left,l);
    mergeSort(right,r);
    for(int k=0,i=0,j=0; k<length; k++) //attach left&right to a
    {
        if(left[i][1] <= right[j][1])
        {
            a[k][0] = left[i][0];
            a[k][1] = left[i][1];
            i++;
        }
        else
        {
            a[k][0] = right[j][0];
            a[k][1] = right[j][1];
            j++;
        }
        if(i == l)
        {
            while(j < r)
            {
                k++;
                a[k][0] = right[j][0];
                a[k][1] = right[j][1];
                j++;
            }
            break;
        }
        if(j == r)
        {
            while(i < l)
            {
                k++;
                a[k][0] = left[i][0];
                a[k][1] = left[i][1];
                i++;
            }
            break;
        }
    }
    return;
}
