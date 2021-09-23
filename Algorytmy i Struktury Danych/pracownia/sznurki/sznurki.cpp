#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

vector <pair<unsigned long long, unsigned long long>> problem;

unsigned long set_bits_32(unsigned long sum) {
    sum = (sum & 0x55555555) + ((sum >> 1) & 0x55555555);
    sum = (sum & 0x33333333) + ((sum >> 2) & 0x33333333);
    sum = (sum & 0x0F0F0F0F) + ((sum >> 4) & 0x0F0F0F0F);
    sum = (sum & 0x00FF00FF) + ((sum >> 8) & 0x00FF00FF);
    sum = (sum & 0x0000FFFF) + ((sum >> 16) & 0x0000FFFF);

    return sum;
}

unsigned long set_bits(unsigned long long sum){
    unsigned long sum1 = sum >> 32;
    unsigned long sum2 = sum;
    return set_bits_32(sum1) + set_bits_32(sum2);
}

int pos_of_right_set_bit(unsigned long long number){
    if(number & 1){
        return 0;
    }
    number = number ^ (number & (number - 1));
    return log2(number);
}

int main(){
    long m;
    unsigned long long d;
    unsigned long long nd;
    int position;
    unsigned long long result = 0;
    unsigned long long sum = 0;
    scanf("%ld", &m);
    while(m--){
        scanf("%llu %llu", &d, &nd);
        position = pos_of_right_set_bit(d);
        problem.push_back(make_pair(d >> position, nd << position));
    }
    sort(problem.begin(), problem.end());
    for(long i = 0; i < problem.size(); ++i){
        sum += problem[i].second;
        if(i == problem.size() - 1 || problem[i].first != problem[i+1].first){
            result += set_bits(sum);
            sum = 0;
        }
    }
    printf("%llu", result);
    return 0;
}
