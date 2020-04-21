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
    void add_participant(Account *ptr);
    bool if_not_signed(Account* ptr);

    /**
     * @brief check_date
     * @param year
     * @param month
     * @param day
     * @return false if current date is past instances starting date
     */
    bool check_date(int year, int month, int day);
    void set_starting_date(int year, int month, int day);
    std::string get_instance();
    std::vector<Account*> get_participants();
    std::string get_course_id();
    Course* get_course();
    std::string get_starting_date();

    void set_course_ptr(Course* ptr);

private:
    std::string course_id_;
    std::string starting_date_;
    int s_year_;
    int s_month_;
    int s_day_;
    std::string instance_;
    Course* course_ptr_;
    std::vector<Account*> participants_;
};

#endif // INSTANCE_HH
