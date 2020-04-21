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

void Account::complete_course(Course *ptr, Instance* inst){
    completed_.push_back(ptr);
    delete_instance(inst);
    //add_credits();
    std::cout << "Course completed." << std::endl;
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

}



void Account::delete_instance(Instance *inst){

        std::vector<Instance*>::iterator iter = current_.begin();
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
            ++iter;
            }



}

void Account::print_current_courses()
{

    for (Instance* i : current_){
        std::cout << i->get_course_id() << " : " << i->get_course()->get_name()
                  << " " << i->get_instance() << std::endl;

    }

}

void Account::print_completed()
{

    if (!completed_.empty()){
        for (Course* i : completed_){
            std::cout << i->get_code() << " : " << i->get_name() << std::endl;
        }
    }
    credits_ = 5 * completed_.size();
    std::cout << "Total credits: " << credits_ << std::endl;

}

/*void Account::add_credits()
{
    credits_ += 5;
}
*/
int Account::get_account_number()
{
    return account_number_;
}

std::string Account::get_name()
{
    return full_name_;
}

int Account::get_credits()
{
    return credits_;
}



