#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;

Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    shared_ptr<Card_data> new_card
            = make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(ostream& s) {
   shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int& id) {
    if (top_ == nullptr) {
        return false;
    }
    else {
        shared_ptr<Card_data> card_to_be_removed = top_;
        id = card_to_be_removed->data;
        top_ = top_->next;
        

        return true;
    }
}


void Cards::reverse() {
    shared_ptr<Card_data> prev = nullptr;
    shared_ptr<Card_data> curr = top_;
    shared_ptr<Card_data> next = curr->next;
    curr->next = nullptr;
    while (next != nullptr) {
        prev = curr;
        curr = next;
        next = curr->next;
        curr->next = prev;
    }
    top_ = curr;
}

// Do not write the stubs of the methods remove and reverse by yourself here,
// but open the file cards.hh and click the declaration of the method
// by the right mouse button and select
// Refactor > Add definition in cards.cpp
