#include <stdio.h>
#include <stdlib.h>
#include <iostream>


int calc_Score(int K,int N, int L,int* pattern,int* Array);
int combination(int K, int N, int L,int* pattern, int* Array, int* ArrayLen, int decided,int*score);

int main(){

    int L=0;
    int N=0;
    int K=0;
    

    std::cin >> N >> L;    
    std::cin >> K;

    //test

    int score = 0;

    //()をつけることでnewを0クリアする
    int* pattern = new int[N+2]();
    int* Array = new int[N+2]();    
    int* ArrayLen = new int[K+1]();

    for(int i=1;i<N+1;i++){
        std::cin >> Array[i] ;
    }
    Array[0] = 0;
    Array[N + 1] = L;
    pattern[0] = 1;
    pattern[N+1] = 1;

    score = combination(K,N,L,pattern,Array,ArrayLen,1,&score);

    std::cout << score << std::endl;


    delete[] Array;
    delete[] ArrayLen;
    delete[] pattern;

    return 0;
}

int combination(int K,int N,int L,int* pattern,int* Array,int* ArrayLen,int decided,int* score){
    
    int count = 0;
    int tmp_score = 0;

    int selected = 0;
    for (int i = 1; i <= N ; i++) {
        selected += pattern[i];
    }


    if (decided == N+1) {
        if (selected==K) {
            tmp_score = calc_Score(K, N, L,pattern, Array);
            if (tmp_score > *score) {
                *score = tmp_score;
            }
        }
        return *score;
    }


    pattern[decided]=0;
    combination(K,N,L,pattern,Array,ArrayLen,decided+1,score);

    pattern[decided]=1;
    combination(K,N,L,pattern,Array,ArrayLen,decided+1,score);

    return *score;
}

int calc_Score(int K,int N,int L,int* pattern,int* Array){

    int* ArrayLen = new int[K+1]();
    int before=-1;
    int after=-1;    
    int start=0;
    
    for(int ksub=0;ksub<K+1;ksub++){
        for(int i=start;i<N+2;i++){

            if(pattern[i]==1){
                if(before == -1){
                        before = Array[i];
                }else if(after==-1){
                        after = Array[i];
                        start=i;
                }
            }
            if(before!=-1 && after!=-1){
                ArrayLen[ksub]=after-before;
                after = -1;
                before = -1;
                break;
            }
        }
    }
    
    int score=L;

    for(int i=0;i<K+1;i++){
        if(ArrayLen[i]<score){
            score = ArrayLen[i];
        }
    }

    delete[] ArrayLen;
    
    return score;
}