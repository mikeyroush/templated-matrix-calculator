//
//  main.cpp
//  program1_part2
//
//  Created by Mikey Roush on 2/4/18.
//  Copyright © 2018 Michael Roush. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "TemplatedMy_matrix.h"

int main() {
    // Test 1
    cout << "test 1" << endl;
    TemplatedMy_matrix<int> m1(2, 2);
    m1(0,0) = 1;
    m1.elem(0, 1) = 3;
    m1(1,0) = 1;
    m1.elem(1, 1) = 2;
    cout << m1;
    
    // Test 2
    cout << "test 2" << endl;
    ifstream in;
    in.open("in.txt");
    
    if(!in.is_open()){
        cerr << "Error: Could not open input file" << endl;
        return 1;
    }
    
    TemplatedMy_matrix<int> m2(2,2);
    in >> m2;
    in.close();
    
    ofstream out;
    out.open("out.txt");
    out << m2;
    cout << m2;
    out.close();
    
    //Test 3
    cout << "test 3" << endl;
    TemplatedMy_matrix<int> m3;
    cout << "adding" << endl;
    m3 = m1 + m2;
    cout << m3;
    cout << "multiplying" << endl;
    m3 = m1 + m2;
    cout << m3;
    
    //Test 4
    cout << "test 4" << endl;
    TemplatedMy_matrix<double> m4(2,2);
    m4(0,0) = 1.1;
    m4.elem(0, 1) = 3.1;
    m4(1,0) = 1.1;
    m4.elem(1, 1) = 2.1;
    cout << m4;
    
    //Test 5
    cout << "test 5" << endl;
    TemplatedMy_matrix<long> m5(2,2);
    m5(0,0) = 11111111111111;
    m5.elem(0, 1) = 11111111111111;
    m5(1,0) = 11111111111111;
    m5.elem(1, 1) = 11111111111111;
    cout << m5;
}
