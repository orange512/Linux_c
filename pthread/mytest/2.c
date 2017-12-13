/*************************************************************************
	> File Name: 2.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月19日 星期二 20时34分15秒
 ************************************************************************/

#include<stdio.h>
#include <bits/stdc++.h>

int main()
{
        int num = 10;

        std::default_random_engine e; //引擎
        std::normal_distribution<double> n(1.5, 4); //均值, 方差
        std::vector<unsigned> vals(num);
    for(std::size_t i=0; i < 100000; ++i) {
                unsigned v = std::lround(n(e)); //取整-最近的整数
                if (v < vals.size())
                    ++vals[v];
            
        int sum = std::accumulate(vals.begin(), vals.end(), 0);
        std::cout << "sum = " << sum << std::endl;
        for (std::size_t j=0; j != vals.size(); ++j)
            std::cout << j << " : " << (double)vals[j]/sum << std::endl;

        return 0;

}

