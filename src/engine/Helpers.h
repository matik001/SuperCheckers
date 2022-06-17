#ifndef CHECKERSAI_HELPERS_H
#define CHECKERSAI_HELPERS_H

#include <cstdlib>

const long long INF_PATH = (long long)1e18;


template<typename T>
inline void swap(T &a, T &b){
    T tmp = a;
    a = b;
    b = tmp;
}

inline bool randBool(double probability){
    return rand()/(RAND_MAX+1.0) < probability;
}

inline int randInt(int from, int to){
    return from + (rand()%(to-from+1));
}

template<typename T>
void reverse(T* begin, T* end){
    end--;
    while(begin<end){
        swap(*begin, *end);
        begin++;
        end--;
    }
}

template<typename T>
void fill(T* t, int n, T val){
    for(int i = 0; i<n; i++)
        t[i] = val;
}

template<typename T>
T max(T a, T b){
    return (a>b ? a : b);
}
template<typename T>
T min(T a, T b){
    return (a<b ? a : b);
}

#endif //CHECKERSAI_HELPERS_H
