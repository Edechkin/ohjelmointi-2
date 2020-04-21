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

void Instance::print_students() const{

}

bool Instance::is_named(const std::string& name) const{
    if (name == instance_){
        return true;
    }
    return false;
}


void Instance::add_participant(Account* ptr){
    participants_.push_back(ptr);
}

bool Instance::if_not_signed(Account* ptr){

    if (find(participants_.begin(), participants_.end(), ptr)
            == participants_.end()){
        return true;
    }
    return false;
}


bool Instance::check_date(int year, int month, int day) {
    if (year <= s_year_ ){
        if (month <= s_month_){
            if (day <= s_day_){
                return true;
            }
        }
    }
    return false;
}

void Instance::set_starting_date(int year, int month, int day){

    s_year_ = year;
    s_month_ = month;
    s_day_ = day;
}

string Instance::get_instance()
{
    return instance_;
}

std::vector<Account *> Instance::get_participants()
{
    return participants_;
}
