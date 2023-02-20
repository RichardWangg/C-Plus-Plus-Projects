#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 1
//
Transaction::Transaction(std::string ticker_symbol,  unsigned int day_date,  unsigned int month_date,  
unsigned year_date, bool buy_sell_trans,  unsigned int number_shares,  double trans_amount): 
symbol{ticker_symbol}, day{day_date}, month{month_date}, year{year_date}, shares{number_shares},
amount{trans_amount}, p_next{} {
  trans_id = assigned_trans_id;
  assigned_trans_id++;
  if (buy_sell_trans) {
    trans_type = "Buy";
  } else {
    trans_type = "Sell";
  }
  acb = 0.00;
  acb_per_share = 0.00;
  share_balance = 0;
  cgl = 0.00;
}


// Destructor
// TASK 1
//

Transaction::~Transaction() {
  p_next = nullptr;
}

// Overloaded < operator.
// TASK 2
//
bool Transaction::operator<( Transaction const &other ) {

if(year > other.get_year()) {
    return false;
  } else if ((year == other.get_year()) && (month > other.get_month()))  {
    return false;
  } else if ((year == other.get_year()) && (month == other.get_month()) && day > other.get_day()) {
    return false;
  } else if((year == other.get_year()) && (month == other.get_month()) && (day == other.get_day()) && (trans_id < other.get_trans_id())) {
    return false;
  } else{
    return true;
  }
}


// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History(): p_head{nullptr} {

}
// Destructor
// TASK 3
//
History::~History() {
  Transaction *p_temp = p_head;

  if (p_temp != nullptr) {
    while(p_temp->get_next() != nullptr)  {
      Transaction *p_temp2 = p_temp;
      p_temp = p_temp->get_next();

      delete p_temp2;
      p_temp2 = nullptr;
    }

    delete p_temp;
    p_temp = nullptr;
    p_head = nullptr;
  }
  }
// read_history(...): Read the transaction history from file.
// TASK 4
//
void History::read_history() {
ece150::open_file();
while(ece150::next_trans_entry()) {
  std::string symbol = ece150::get_trans_symbol();
  unsigned int day = ece150::get_trans_day();
  unsigned int month = ece150::get_trans_month();
  unsigned int year = ece150::get_trans_year();
  bool type = ece150::get_trans_type();
  unsigned int shares = ece150::get_trans_shares();
  double amount = ece150::get_trans_amount();
  Transaction *p_new = new Transaction(symbol, day, month, year, type, shares, amount);
  History::insert(p_new); 
  }
ece150::close_file();
}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans) {
if (p_head == nullptr) {
  p_head = p_new_trans;
} else {
  Transaction *p_temp = p_head;
  while (p_temp->get_next() != nullptr) {
    p_temp = p_temp->get_next();
  }
  p_temp->set_next(p_new_trans);
}

}


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date() {

 Transaction *new_one = nullptr;
  Transaction *p_present = p_head;
  Transaction *begin = nullptr;
  Transaction *run = nullptr;
  Transaction *run_last = nullptr;

  Transaction *p_temp = p_head;

  while (p_present != nullptr){
    begin = p_present->get_next();
    p_temp = p_present;

    if (new_one == nullptr || (*p_temp < *new_one)) {
      p_temp->set_next(new_one);
      new_one = p_temp;
    }
    else  {
      run = new_one;
      while (run != nullptr && (*run < *p_temp)) {
        run_last = run;
        run = run->get_next();
      }
      run_last->set_next(p_temp);
      p_temp->set_next(run);
    }
    p_present = begin;
  }
  p_head = new_one;
}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//
void History::update_acb_cgl() {
  Transaction *current; 
  Transaction *previous;
  current = p_head;

  while (current != nullptr) {
    double curr_acb;
    double added_acb;
    bool broken;

    broken = current->get_trans_type();


    if (broken == true) {
      if (p_head == current) {
        current->set_acb(current->get_amount());
        current->set_share_balance(current->get_shares());
        current->set_acb_per_share(current->get_acb() / current->get_share_balance());
      } else  {
        current->set_acb(previous->get_acb() + current->get_amount());
        current->set_share_balance(previous->get_share_balance() + current->get_shares());
        current->set_acb_per_share(current->get_acb() / current->get_share_balance());
      }
    } else  {
      current->set_acb(previous->get_acb() - (current->get_shares() * previous->get_acb_per_share()));
      current->set_share_balance(previous->get_share_balance() - current->get_shares());
      current->set_acb_per_share(current->get_acb() / current->get_share_balance());
      current->set_cgl(current->get_amount() - (current->get_shares() * previous->get_acb_per_share()));
    }
    previous = current;
    current = current->get_next();
  }
}



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year) {
  double final{0.0};
  Transaction *current;
  current = p_head;

  while (current != nullptr)  {
    if (year == current->get_year()) {
      final = final + current->get_cgl();
    } current = current->get_next();
  }
  return final;
}


// print() Print the transaction history.
//TASK 9
//
void History::print() {
  std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl; 
  Transaction *p_temp = p_head;
  while (p_temp != nullptr) {
    p_temp->print();
    p_temp = p_temp->get_next();
  }
  std::cout << "========== END TRANSACTION HISTORY ============" <<std::endl;
}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
