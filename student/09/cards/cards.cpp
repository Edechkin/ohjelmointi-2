#include "cards.hh"


using namespace std;

Cards::Cards(): top_(nullptr), bottom_(nullptr){
}

Cards::~Cards() {
   while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_;
      top_ = top_->next;

      delete item_to_be_released;
   }
}

void Cards::add(int id){
   Card_data* new_item = new Card_data{id, top_};
    top_ = new_item;
}

void Cards::print_from_top_to_bottom(ostream& s) const{
    Card_data* item_to_be_printed = top_;
    int running_number = 1;

    while ( item_to_be_printed != nullptr) {
       s << running_number << ": " << item_to_be_printed->data << endl;
       ++running_number;
       item_to_be_printed = item_to_be_printed->next;
    }
}

bool Cards::remove(int &id) {
    if (top_ == nullptr) {
        return false;
    }
    else {
        Card_data* card_to_be_removed = top_;
        id = card_to_be_removed->data;
        top_ = top_->next;
        delete card_to_be_removed;

        return true;
    }
}

bool Cards::bottom_to_top() {
    if (top_ == nullptr) {
        return false;
    }
    if(top_->next == nullptr){
        return true;
    }
    Card_data* one_from_bottom = top_;
    while (one_from_bottom->next->next != nullptr) {
        one_from_bottom = one_from_bottom->next;
    }
    Card_data* bottom = one_from_bottom->next;
    bottom->next = top_;
    top_ = bottom;
    one_from_bottom->next = nullptr;

    return true;
}


bool Cards::top_to_bottom() {
    if (top_ == nullptr) {
        return false;
    }
    Card_data* bottom = top_;
    while(bottom->next != nullptr){
        bottom = bottom->next;
    }
    bottom->next = top_;
    top_ = top_->next;
    bottom->next->next = nullptr;

    return true;
}


void Cards::print_from_bottom_to_top(ostream &s)
{
    s << "";
}

