/*
 *  opTest1.h
 *  
 *  Copyright (C) 2024
 *  Author: Simon (dewen.wu@gmail.com)
 *  
 */

#pragma once

#include "testSuite.h"

class opTest1:public TestCase
{
private:
    /* data */
public:
    opTest1();
    ~opTest1();
    virtual int run();
};

opTest1::opTest1()
{
}

opTest1::~opTest1()
{
}