#include<iostream>
#include<vector>
#include<set>

class Edge{
public:
    int node_1;
    int node_2;
    int w;
    Edge(int x, int y, int w){
        this->node_1 = x;
        this->node_2 = y;
        this->w = w;
    }
};

int main(){
     int out[20]; //output ans
     int n;//vertex
     int m;//edge
     int times = -1;//record input data sequence
     while(1){
        times++;
        out[times] = 0;//init
        std::cin>>n>>m;
        if(n==0 && m==0)
            break;

        std::vector<Edge> e;
        for(int i = 0; i < m; i++){//add edge
            int x, y, w;
            std::cin>>x>>y>>w;
            Edge ee(x, y, w);
            e.insert(e.end(), ee);
        }

        std::vector<std::set<int>> set_vec;
        for(int i = 0; i < n; i++){//create all vertex set
            std::set<int> s;
            s.insert(i);
            set_vec.insert(set_vec.end(), s);
        }

        for(int i = 0; i < m; i++){
            int min_e = 0;
            for(int k = 1; k < e.size(); k++){//find the min weight now
                if(e[k].w < e[min_e].w)
                    min_e = k;
            }

            bool is_cycle = 0;
            int x_set = -1;//record which set x is in
            int y_set = -2;
            for(int k = 0; k < set_vec.size(); k++){//check no cycle (vertex not in the same set)
                if(set_vec[k].find(e[min_e].node_1) != set_vec[k].end())//found node_1
                    x_set = k;
                if(set_vec[k].find(e[min_e].node_2) != set_vec[k].end())//found node_2
                    y_set = k;
                if(x_set == y_set){//that's why x_set & y_set have the different initial value
                    is_cycle = 1; //cycle
                    break;
                }
                else if(x_set != -1 && y_set != -2)//all found
                    break;
            }
            if(!is_cycle){
                //union(x,y)
                set_vec[x_set].insert( set_vec[y_set].begin(), set_vec[y_set].end() );
                set_vec.erase(set_vec.begin() + y_set);

                out[times] += e[min_e].w;//add edge in min spanning tree
            }
            e.erase(e.begin() + min_e);//delete the used edge
        }
     }

     for(int i = 0; i < times; i++){//last input is (0,0) ,not need to output
        if(i == 0)
            std::cout<<out[0];
        else
            std::cout<<std::endl<<out[i];
     }
     return 0;
}
