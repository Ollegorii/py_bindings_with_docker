#pragma once
#include <vector>
#include <cmath>
#include <algorithm>
#include <stdexcept>

class SVD {
public:
    static void svd(const std::vector<std::vector<double>>& A,
                   std::vector<std::vector<double>>& U,
                   std::vector<double>& S, 
                   std::vector<std::vector<double>>& Vt,
                   int max_iter = 1000);
    
private:
    static double norm(const std::vector<double>& v);
};