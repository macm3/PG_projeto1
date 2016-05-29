#ifndef MATHUTIL_H
#define MATHUTIL_H

#include "ponto.h"
#include "math.h"
#include <vector>


namespace MathUtil {
    unsigned long long factorial(int n)
    {
        long long fat;
        
        if (n <= 1) {
            fat = 1;
        }
        else {
            fat = n;
            
            while (n > 1) {
                fat *= (n - 1);
                n--;
            }
        }
        
        return fat;
    }
    
    unsigned long long comb(int n, int p)
    {
        unsigned long long ret = factorial(n)/(factorial(p) * factorial(n - p));
        
        return ret;
    }
    
    inline void bezier(const std::vector<Ponto>& pontos, float t, Ponto& pout) {
        float x = 0.0;
        float y = 0.0;
        const unsigned int vertices = (unsigned int)pontos.size();
        
        for (int i = 0; i < vertices; i++) {
            x += comb(vertices - 1, i) * pow((1 - t), vertices-1-i) * pow(t, i) * pontos[i].x;
            y += comb(vertices - 1, i) * pow((1 - t), vertices-1-i) * pow(t, i) * pontos[i].y;
        }
        
        pout.x = x;
        pout.y = y;
    }

    int findPonto(const std::vector<Ponto>& pontos, float x, float y){
        int i = 0;
        int retorno = -1;
        for (auto p : pontos){
            if((p.x < x+5) && (p.x > x-5)){
                if((p.y < y+5) && (p.y > y-5))
                    retorno = i;
            }
            i++;
        }
        return retorno;
    }
}

#endif