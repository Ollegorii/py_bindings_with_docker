#include "svd.h"
#include <iostream>

double SVD::norm(const std::vector<double>& v){
    double sum = 0;
    for(int i = 0; i < v.size(); ++i)
        sum += v[i] * v[i];
    return std::sqrt(sum);
}

void SVD::svd(const std::vector<std::vector<double>>& A,
                   std::vector<std::vector<double>>& U,
                   std::vector<double>& S,
                   std::vector<std::vector<double>>& Vt,
                   int max_iter){
   size_t m = A.size();
   size_t n = A[0].size();
   size_t k = std::min(m, n);

    U.resize(m, std::vector<double>(k, 0.));
    S.resize(k, 0.);
    Vt.resize(k, std::vector<double>(n, 0.));
    
    std::vector<std::vector<double>> A_copy = A;
    std::vector<std::vector<double>> A_temp;

    for(int i = 0; i < k; ++i)
    {
        std::vector<double> v(n, 1. / std::sqrt(n));
        std::vector<double> v_old(n, 0.);
        int iter = 0;
        bool converged = false;
        while(iter < max_iter && !converged)
        {
            std::vector<double> tmp(m, 0.);
            std::vector<double> new_v(n, 0.);
            // tmp = A * v
            for(int row = 0; row < m; ++row)
                for(int col = 0; col < n; ++col)
                    tmp[row] += A_copy[row][col] * v[col];
            // new_v = A.T * tmp
            for(int col = 0; col < n; ++col)
                for(int row = 0; row < n; ++row)
                    new_v[col] += A_copy[row][col] * tmp[row]; 
            
            double norma = norm(new_v);
            for(int j = 0; j < n; ++j)
                new_v[j] /= norma;

            converged = true;
            for(int j = 0; j < n; ++j)
                if(std::abs(new_v[j] - v_old[j]) > 1e-10)
                {
                    converged = false;
                    break;
                }
            
            v_old = v;
            v = new_v;
            ++iter;
         }
        // calculate lambda
        std::vector<double> u(m, 0.);
        for(int row = 0; row < m; ++row)
            for(int col = 0; col < n; ++ col)
                u[row] += A_copy[row][col] * v[col];
        
        double lambda = norm(u);
        S[i] = lambda;

        if(lambda > 1e-10)
            for(int row = 0; row < m; ++row)
            {
                u[row] /= lambda;
                U[row][i] = u[row];
            }
        
        for(int col = 0; col < n; ++col) 
            Vt[i][col] = v[col];

        for(int row = 0; row < m; ++row)
            for(int col = 0; col < n; ++col)
                A_copy[row][col] -= lambda * u[row] * v[col];
    }
}