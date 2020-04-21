/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 *
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course, so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED = "Error: Student has already registered on this course.";
const std::string LATE = "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";

class Instance
{
public:
    Instance( std::string course_id,  std::string instance);
    void print() const;
    void print_students() const;
    bool is_named(const std::string& name) const;
    bool add_participant(Account *ptr);
    bool check_date();
private:
    std::string starting_date_;
    std::string instance_;
    Course* course_ptr_;
    std::string course_id_;
    std::vector<Account*> participation_list_;
};

#endif // INSTANCE_HH
