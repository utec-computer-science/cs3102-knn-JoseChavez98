#include <iostream>
#include <climits>
#include "kd_tree.cpp"

int main(){

    auto KD =  Kd_tree<int,int>("points.txt");
    // KD.print();
    auto testNode = new node<int,int>(6,3);
    KD.getNearestSamples(2,testNode);

    
    return 0;
}