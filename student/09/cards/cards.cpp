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

