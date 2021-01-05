#include "rod.hh"

Rod::Rod(int seed_value_for_top_disk_size)
{
    size_of_top_disk_ = seed_value_for_top_disk_size;
    order_of_disks_ = {};
    // Lets store the seed value for the later use.
    seed_value_for_top_disk = seed_value_for_top_disk_size;
}


bool Rod::add_disk(std::shared_ptr<Disk> new_disk)
{
    // Checks if the size of disk to be added is smaller than
    // rod's top disk size.
    if(new_disk->return_size() < size_of_top_disk_)
    {
        order_of_disks_.push_back(new_disk);
        size_of_top_disk_ = new_disk->return_size();
        return true;
    }
    return false;
}

void Rod::remove_disk()
{
    // Checks is removing possible.
    if(order_of_disks_.size()!=0)
    {
        order_of_disks_.pop_back();
        // Set new value to be size_of_top_disk.
        if(order_of_disks_.size()!=0)
        {
            size_of_top_disk_ = order_of_disks_.at(order_of_disks_.size()-1)
                                ->return_size();
        }
        else
        {
            // If rod is empty, let's set seed value to be
            // size of top disk.
            size_of_top_disk_ = seed_value_for_top_disk;
        }
    }
}

std::shared_ptr<Disk> Rod::pointer_to_top() const
{
    // Checks are there any disks on rod.
    if(order_of_disks_.size() != 0)
    {
        return order_of_disks_.at(order_of_disks_.size()-1);

    }
    return nullptr;
}

std::vector<std::shared_ptr<Disk>> Rod::return_structure() const
{
    return order_of_disks_;
}

void Rod::set_structure(std::vector<std::shared_ptr<Disk>> structure)
{
    order_of_disks_.clear();
    order_of_disks_ = structure;
}

void Rod::set_seed_value()
{
    size_of_top_disk_ = seed_value_for_top_disk;
}

void Rod::clear_structure()
{
    order_of_disks_.clear();
}



