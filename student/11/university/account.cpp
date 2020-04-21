#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"


Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::complete_course(Course *ptr){
    completed_.push_back(ptr);
}

bool Account::if_not_signed(Instance *ptr){

    if (find(current_.begin(), current_.end(), ptr)
            == current_.end()){
        return true;
    }
    return false;

}

void Account::add_course(Instance *ptr){
    current_.push_back(ptr);
    delete_instance(ptr);
    std::cout << "Course completed." << std::endl;
}



void Account::delete_instance(Instance *inst){

        std::vector<Instance*>::iterator iter =current_.begin();
       /* for (iter = current_.begin(); iter <= current_.end(); iter++){
            if (current_.at(iter)->get_instance() == inst){
                current_.erase(iter);
            }
        }
*/
        for(Instance* instance : current_){
            if(instance == inst){
                current_.erase(iter);
                return;
            }

            }
            ++iter;


}



