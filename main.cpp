#include <iostream>
#include <climits>
#include "kd_tree.cpp"

int main(){

    auto KD =  Kd_tree<int,int>("points.txt");
    // KD.print();
    auto testNode = new node<int,int>(0,7);
    KD.computeNearestSamples(0,testNode);

    
    return 0;
}