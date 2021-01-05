/* Moudle: Rod
 *
 * Includes class Rod, which represents a single rod on Hanoi's tower game.
 *
 *  * TIE-0220x S2019
 * Name: Kasper Eloranta
 * E-mail: kasper.eloranta@tuni.fi
 * Student id: 274212
 *
 * */

#ifndef ROD_HH
#define ROD_HH
#include <disk.hh>
#include <vector>
#include <memory>

class Rod
{
public:
    // Preventing the use of unecessary copy-constructor and assignment operator.
    Rod(const Rod& alustusarvo) = delete;
    Rod& operator=(const Rod& sijoitusarvo) = delete;
    // Constructor of the rod. Takes int parameter which is used as a seed
    // value for the top disk's size.
    Rod(int seed_value_for_top_disk_size);
    // Adds new disk to rod if possible. Returns true if succeeded,
    // false otherwise.
    bool add_disk(std::shared_ptr<Disk> new_disk);
    // Removes rod's top disk if there is one.
    void remove_disk();
    // Returns pointer to top Disk -object.
    std::shared_ptr<Disk> pointer_to_top() const;
    // Returns the vector structure in which rod's disk's are in
    // certain order.
    std::vector<std::shared_ptr<Disk>> return_structure() const;
    // Clears se structure of disks and set new structure which is given
    // as a parameter.
    void set_structure(std::vector<std::shared_ptr<Disk>> sructure);
    // Sets size_of_top_disk_ to bee seed value. This is needed after
    // clearing the whole structure.
    void set_seed_value();
    // Clears the whole structure.
    void clear_structure();

private:
    // Vector structure which includes disks in legal order.
    std::vector<std::shared_ptr<Disk>> order_of_disks_;
    int size_of_top_disk_;
    int seed_value_for_top_disk;
};

#endif // ROD_HH
