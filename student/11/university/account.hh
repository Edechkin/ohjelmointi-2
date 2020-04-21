/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    void complete_course(Course* ptr, Instance* inst);

    bool if_not_signed(Instance* ptr);

    void add_course(Instance* ptr);

    void delete_instance(Instance* inst);

    void print_current_courses();

    void print_completed();
    void add_credits();
    int get_account_number();
    std::string get_name();
    int get_credits();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
    int credits_;
};

#endif // ACCOUNT_HH
