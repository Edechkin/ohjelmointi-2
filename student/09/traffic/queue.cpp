#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle) {
    this->cycle_ = cycle;
    this->vehicles_passed = 0;
}

Queue::~Queue()
{

}


void Queue::enqueue(string reg)
{

    if (is_green_ and vehicles_passed <= cycle_) {
        vehicles_passed++;
        cout << "GREEN: The vehicle " << reg << " need not stop to wait" << endl;

        return;
    }

    if (first_ == nullptr) {

        first_ = new Vehicle({reg, nullptr});
        last_ = first_;

    } else {
        Vehicle* next_in_queue = new Vehicle({reg, nullptr});
        last_->next = next_in_queue;
        last_ = next_in_queue;
    }

}

bool Queue::dequeue()
{
    if (first_ == nullptr) {
        return false;
    }
    Vehicle* second = first_->next;

    if (second == nullptr) {

        cout << first_->reg_num << " ";
        delete first_;
        last_->next = nullptr;
        last_ = nullptr;
        first_ = last_;
        return true;
    }

    cout << first_->reg_num << " ";
    delete first_;
    first_ = second;

    return true;
}

void Queue::switch_light()
{
    is_green_ = !is_green_;
    string light_color = (is_green_) ? "GREEN" : "RED";
    cout << light_color << ": ";

    if (is_green_) {
        if (first_ != nullptr) {
            cout << "Vehicle(s) ";
            for (vehicles_passed = 0; vehicles_passed < cycle_; vehicles_passed++) {
                if (!dequeue()) {
                    break;
                }
            }
            cout << "can go on" << endl;
            this->is_green_ = false;

        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {
        if (first_ != nullptr) {
            cout << "Vehicle(s) ";
        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

        vehicles_passed = 0;
    }
}

void Queue::update()
{
    if (!is_green_) {
        this->vehicles_passed = 0;
    }


    if (this->vehicles_passed >= this->cycle_) {
        this->is_green_ = false;
        this->vehicles_passed = 0;
    }
}


void Queue::reset_cycle(unsigned int cycle)
{
    this->cycle_ = cycle;
}

void Queue::print()
{
    this->update();
    string lightColor = (is_green_) ? "GREEN" : "RED";
    cout << lightColor << ": ";

    if (is_green_) {

        if (first_ != nullptr) {
            Vehicle* vehicle_in_queue = first_;
            cout << "Vehicle(s) ";

            while (vehicle_in_queue != nullptr) {
                cout << vehicle_in_queue->reg_num << " ";
                vehicle_in_queue = vehicle_in_queue->next;
            }
            cout << "are waiting in traffic lights" << endl;
        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }

    } else {
        if (first_ != nullptr) {
            Vehicle* vehicle_in_queue = first_;
            cout << "Vehicle(s) ";

            while (vehicle_in_queue != nullptr) {
                cout << vehicle_in_queue->reg_num << " ";
                vehicle_in_queue = vehicle_in_queue->next;
            }

            cout << "waiting in traffic lights" << endl;

        } else {
            cout << "No vehicles waiting in traffic lights" << endl;
        }
    }

}
