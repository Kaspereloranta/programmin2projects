/* Module: Disk
 *
 * Includes class Disk, which represents a single disk
 * on the Hanoi's Tower game.
 *
 * TIE-0220x S2019
 * Name: Kasper Eloranta
 * E-mail: kasper.eloranta@tuni.fi
 * */

#ifndef DISK_HH
#define DISK_HH

class Disk
{
public:
    // Constructor of class Disk. Takes two int parameters. Size represents the
    // size of disk and y represents height. Y means how many disks there are
    // under the disk at the time Disk is created.
    Disk(int size, unsigned int y);
    // Return size of the disk.
    int return_size();
    // Returns information how many disks there were under the disk
    // at the time disk was created.
    unsigned int original_y();

private:
    int size_;
    unsigned int y_;

};

#endif // DISK_HH
