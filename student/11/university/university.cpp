#include "university.hh"



University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_instance(Params params) {
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    if ( courses_.at(params.at(0))->has_instance(params.at(1))){
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    }

    Instance* n_instance = new Instance((params.at(0)), params.at(1));
    int year = utils::today.get_year();
    int month = utils::today.get_month();
    int day = utils::today.get_day();
    n_instance->set_starting_date(year, month, day);
    n_instance->set_course_ptr(courses_.at(params.at(0)));
    courses_.at(params.at(0))->new_instance(n_instance);

}

void University::sign_up_on_course(Params params){
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    if (!courses_.at(params.at(0))->has_instance(params.at(1))){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    if ( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return;
    }


    Account* acc = accounts_.at(std::stoi(params.at(2)));
    Instance* inst = courses_.at(params.at(0))->get_instance(params.at(1));
    int year = utils::today.get_year();
    int month = utils::today.get_month();
    int day = utils::today.get_day();
    if (!inst->check_date(year, month, day)){
        std::cout << LATE << std::endl;
        return;
    }

   if (!inst->if_not_signed(accounts_.at(std::stoi(params.at(2))))){
        std::cout << ALREADY_REGISTERED << std::endl;
        return;
    }
    inst->add_participant(accounts_.at(std::stoi(params.at(2))));
    acc->add_course(inst);
    std::cout << "Signed up on the course instance." << std::endl;
}

void University::complete_course(Params params){
    if(param_errors(params)){
        return;
    }
    Course* course = courses_.at(params.at(0));
    Instance* inst = course->get_instance(params.at(1));
    Account* acc = accounts_.at(std::stoi(params.at(2)));
    if (acc->if_not_signed(inst)){
        std::cout << "No signups found on this instance." << std::endl;
        return;
    }
    acc->complete_course(course, inst);
}

void University::print_signups(Params params){
    Course* course = courses_.at(params.at(0));
    std::vector<Instance*> instances = course->get_instances();
    std::vector<Instance*>::iterator iter = instances.begin();
    for (Instance* inst : instances){
        //Instance* inst = courses_.at(params.at(0))->get_instance(courses_.at(i));
        std::cout << inst->get_instance() << std::endl;
        std::vector<Account*> p = inst->get_participants();
        std::cout << INDENT << "Starting date: " << inst->get_starting_date() << std::endl;
        std::cout  << INDENT << "Among of students: " << p.size() << std::endl;
        for (Account* it : p){
            std::cout << INDENT << it->get_account_number() << ": " << it->get_name() <<
                         ", " << it->get_email() << std::endl;
        }
        ++iter;
    }
}



void University::print_study_state(Params params) {
    if ( accounts_.find(std::stoi(params.at(0))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    Account* acc = accounts_.at(stoi(params.at(0)));
    std::cout << "Current:" << std::endl;
    acc->print_current_courses();
    std::cout << "Completed:" << std::endl;
    acc->print_completed();

}

void University::print_completed(Params params) {
    if ( accounts_.find(std::stoi(params.at(0))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    Account* acc = accounts_.at(stoi(params.at(0)));
    acc->print_completed();
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

bool University::param_errors(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return true;
    }

    if (!courses_.at(params.at(0))->has_instance(params.at(1))){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return true;
    }

    if ( accounts_.find(std::stoi(params.at(2))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(2) << std::endl;
        return true;
    }
    return false;
}
