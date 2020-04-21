#include "instance.hh"
#include "course.hh"

using namespace std;

Instance::Instance(string course_id, string instance):
    course_id_(course_id), instance_(instance)
{

}

void Instance::print() const  {
    std::cout << instance_ << std::endl;
}

bool Instance::is_named(const std::string& name) const{
    if (name == instance_){
        return true;
    }
    return false;
}

bool Instance::add_participant(Account* ptr){
    if (check_date()){
        if (find(participation_list_.begin(), participation_list_.end(), ptr)
                == participation_list_.end()){
            participation_list_.push_back(ptr);
            return true;
        }
    }
    return false;
}

bool Instance::check_date() {


}

void Instance::print_students() const{}
