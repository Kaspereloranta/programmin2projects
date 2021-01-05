#include "disk.hh"


Disk::Disk(int size, unsigned int y):
    size_(size),
    y_(y)
{
}

int Disk::return_size()
{
    return size_;
}

unsigned int Disk::original_y()
{
    return y_;
}






