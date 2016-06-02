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

    Ponto deCasteljau(const std::vector<Ponto>& pontos, float t){
        if(pontos.size() == 1){
            return pontos[0];
        }

        std::vector<Ponto> pontosControle;

        for (int i = 0; i < pontos.size()-1; ++i)
        {
            Ponto p(0, 0);
            p.x = (1-t)*pontos[i].x + t*pontos[i+1].x;
            p.y = (1-t)*pontos[i].y + t*pontos[i+1].y;
            pontosControle.push_back(p);
        }

        return deCasteljau(pontosControle, t);
    }

    std::vector<Ponto> degreeElevation(const std::vector<Ponto>& pontos){
        
        std::vector<Ponto> novosPontos;
        novosPontos.push_back(pontos[0]);
        
        int n = pontos.size();

        for (int i = 0; i < pontos.size()-1; ++i)
        {
            Ponto p(0, 0);
            float q1 = (i+1.00)/(n+1.00);
            float q2 = 1-((i+1.00)/(n+1.00));
            p.x = q1*pontos[i].x + q2*pontos[i+1].x;
            p.y = q1*pontos[i].y + q2*pontos[i+1].y;
          
            novosPontos.push_back(p);
        }

        novosPontos.push_back(pontos[n-1]);
      
        return novosPontos;
    }
}

#endif