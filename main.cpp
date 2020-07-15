#include <iostream>
#include<math.h>
#include <ctime>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;


#define pop_size 10
#define pm 0.25
#define pc  0.15
#define nr_noduri 4

int distante[4][4] = {
    {0,10,15,20},
    {10,0,35,25},
    {15,35,0,30},
    {20,25,30,0}
};


int eval[pop_size];
int T;
int p[pop_size];
int q[pop_size];
int selectie[pop_size];
int t;
;

int populatie[pop_size][nr_noduri ];
int newpopulation[pop_size][nr_noduri ];


void random_generator(){
    
    int random[5] = {1,2,3,4};
    
    
    for (int i = 0 ; i < pop_size; i++ ) {
        srand((unsigned)time(0));
        random_shuffle(random, random+4);
        for (int j = 0; j < nr_noduri ; j++) {
            populatie[i][j] = random[j];
        }
    }
}



float uniformRandom() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.1, 1.0);
    return (float)dis(gen);
}



int evaluation (int index) {
    int sum = 0;
    int i = 0;
    int j = 1;
    
    while (j < nr_noduri ) {
        sum += distante[populatie[index][i]-1][populatie[index][j]-1];
        i++;
        j++;
    }
    j--;
    sum += distante[populatie[index][0]-1][populatie[index][j]-1];
    return sum;
    
}

void roataNorocului(){
    for (int i = 0; i < pop_size; i++ ) {
        eval[i] = evaluation(i);
    }
    for (int i = 0; i < pop_size; i++ ) {
        T += eval[i];
    }
    for (int i = 0; i < pop_size; i++ ) {
        p[i] = eval[i]/T;
    }
    q[0] = 0;
    for (int i = 0; i < pop_size; i++ ) {
        q[i+1] = q[i] + p[i];
    }
    for (int i = 0; i < pop_size; i++ ) {
        int index=0;
        float r = uniformRandom();
        for (int j = 0; j< pop_size; j++) {
            if ((q[j] < r) && (r <= q[j+1])){
                index = j;
                break;
            }
        }
        
        for (int k = 0; k < nr_noduri; k ++ ){
            newpopulation[i][k] = populatie[index][k];
        }
        
    }
    for (int i = 0; i < pop_size; i++) {
        for (int j = 0; j < nr_noduri; j++) {
            populatie[i][j] =  newpopulation[i][j];
        }
    }
    
}


void alter() {
   
    for ( int i = 0 ; i < pop_size ;i++) {
        float m = uniformRandom();
        if ( m < pm ) {
            int k = rand() % nr_noduri;
            int l = rand() % nr_noduri;
//            populatie[i][k] ^= populatie[i][l];
//            populatie[i][l] ^= populatie[i][k];
//            populatie[i][k] ^= populatie[i][l];
            int aux;
            aux = populatie[i][k];
            populatie[i][k] =populatie[i][l];
            populatie[i][l] = aux;
        }
    }
   
    
    
    
    
    for (int i = 0; i < pop_size; i++ ) {
        float c = uniformRandom();
        if ( c < pc ) {
            selectie[i] = 1;
        }
    }
//    for (int i = 0; i < pop_size; i++ ) {
//        cout<<selectie[i];
//        cout<<endl;
//    }
    
    
    
    for (int i = 0 ;i < pop_size; i++ ){
        if (selectie[i]) {
            for (int j = i; j < pop_size; j++) {
                if(selectie[j]){
                    int frecv1[nr_noduri];
                    int frecv2[nr_noduri];
                    int copil1[nr_noduri];
                    int copil2[nr_noduri];
                    for (int y = 0; y < nr_noduri; y++) {
                        frecv1[y] = 0;
                        frecv2[y] = 0;
                        copil1[y] = 0;
                        copil2[y] = 0;
                    }
                        int pctTaiere1 = rand() % (nr_noduri);
                        int pctTaiere2 = rand() % (nr_noduri);
                        while (pctTaiere1 == pctTaiere2){
                            pctTaiere2 = rand() % (nr_noduri);
                        }

                        if (pctTaiere2 < pctTaiere1) {
                            int aux = pctTaiere1;
                            pctTaiere1 = pctTaiere2;
                            pctTaiere2 = aux;
                        }
                   // cout<<"pct1 : "<<pctTaiere1<<endl;
                    //cout<<"pct2 : "<<pctTaiere2<<endl;

                    for (int y = 0; y < nr_noduri; y++) {
                        if ((y >= pctTaiere1) && ( y <= pctTaiere2)) {
                            frecv1[populatie[i][y]] = 1;
                            frecv2[populatie[j][y]] = 1;
                            copil1[y] = populatie[i][y];
                            copil2[y] = populatie[j][y];
                        }
                    }
                    for (int i = 0 ; i < pop_size; i++ ) {
                                for (int j = 0; j < nr_noduri ; j++) {
                                    cout<<populatie[i][j];
                                }
                                cout<<endl;
                            }


                    
                    t = 0;
                    for (int y = 0; y < nr_noduri; y++) {
                        
                        while( t < nr_noduri ) {
                            if(frecv1[populatie[j][t]] == 0) {
                                copil1[y] = populatie[j][t];
                                frecv1[populatie[j][t]] = 1;
                                break;
                            }
                            t++;

                        }
                    }
                    t = 0;
                    for (int y = 0; y < nr_noduri; y++) {
                        while( t < nr_noduri ) {
                            if(frecv1[populatie[j][t]] == 0) {
                                copil1[y] = populatie[j][t];
                                frecv1[populatie[j][t]] = 1;
                                break;
                            }
                            t++;

                        }
                    }
                    for (int y = 0; y < nr_noduri; y++) {
                        populatie[i][y] = copil1[y];
                        populatie[j][y] = copil2[y];
                     }
                    }
                }
            }
        }

//    for (int i = 0 ; i < pop_size; i++ ) {
//        for (int j = 0; j < nr_noduri ; j++) {
//            cout<<populatie[i][j];
//        }
//        cout<<endl;
//    }
    
}





int main() {
    
    
    
    srand((unsigned)time(NULL));
    
    int t = 0;
    random_generator();
    
    int best = 0;
    
    for (int i = 0; i < pop_size; i++  ){
        int ev = evaluation(i);
        if (ev > best)
            best = evaluation(i);
    }
    
     cout<<best<<endl;
    
    while ( t < 100) {
        t++;
        roataNorocului();
        alter();
        for (int i = 0; i < pop_size; i++  ){
            int ev = evaluation(i);
            if (ev > best)
                best = evaluation(i);
            //cout<<best<<endl;
        }

    }
    cout<<" "<<best<<" "<<endl;
}
