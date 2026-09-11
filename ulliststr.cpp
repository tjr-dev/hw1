#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::push_back(const std::string& val)
{
  // case 1: completely empty list
  if(head_ == NULL)
  {
    Item* temp = new Item;

    temp->first = 0;
    temp->last = 1;
    temp->val[0] = val;

    head_ = temp;
    tail_ = temp;

    size_++;
    return;
  }

  // case 2: tail still has space after its last item
  if(tail_->last < ARRSIZE)
  {
    tail_->val[tail_->last] = val;
    tail_->last++;

    size_++;
    return;
  }

  // case 3: tail is full, so make another node
  Item* temp = new Item;

  temp->first = 0;
  temp->last = 1;
  temp->val[0] = val;

  temp->prev = tail_;
  temp->next = NULL;

  tail_->next = temp;
  tail_ = temp;

  size_++;
}

void ULListStr::push_front(const std::string& val)
{
  // case 1: empty list
  if(head_ == NULL)
  {
    Item* temp = new Item;

    // Put the first value at the end of the array because
    // this is a push_front. This leaves room before it
    // for more future push_front calls.
    temp->first = ARRSIZE - 1;
    temp->last = ARRSIZE;
    temp->val[temp->first] = val;

    head_ = temp;
    tail_ = temp;

    size_++;
    return;
  }

  // case 2: there is room before the first element
  if(head_->first > 0)
  {
    head_->first--;
    head_->val[head_->first] = val;

    size_++;
    return;
  }

  // case 3: no room before first, so make a new head node
  Item* temp = new Item;

  temp->first = ARRSIZE - 1;
  temp->last = ARRSIZE;
  temp->val[temp->first] = val;

  temp->next = head_;
  temp->prev = NULL;

  head_->prev = temp;
  head_ = temp;

  size_++;
}

void ULListStr::pop_back()
{
  // Nothing to remove
  if(size_ == 0)
  {
    return;
  }


  tail_->last--;
  size_--;

  // first == last, this Item now contains no values
  if(tail_->first == tail_->last)
  {
    Item* oldTail = tail_;

    if(tail_->prev == NULL)
    {
      head_ = NULL;
      tail_ = NULL;
    }
    else
    {
      tail_ = tail_->prev;
      tail_->next = NULL;
    }

    delete oldTail;
  }
}

void ULListStr::pop_front()
{
  // Nothing to remove
  if(size_ == 0)
  {
    return;
  }

  // first is inclusive, so moving it forward removes
  // the first value.
  head_->first++;
  size_--;

  // Ii the node has become empty, remove the entire node
  if(head_->first == head_->last)
  {
    Item* oldHead = head_;

    // only node in the entire list
    if(head_->next == NULL)
    {
      head_ = NULL;
      tail_ = NULL;
    }
    else
    {
      head_ = head_->next;
      head_->prev = NULL;
    }

    delete oldHead;
  }
}

std::string const & ULListStr::back() const
{
  if(size_ == 0)
  {
    throw std::invalid_argument("Empty list");
  }

  // last points ONE AFTER the last item
  return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
  if(size_ == 0)
  {
    throw std::invalid_argument("Empty list");
  }

  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if(loc >= size_)
  {
    return NULL;
  }

  Item* current = head_;
  size_t numBefore = 0;

  while(current != NULL)
  {
    // number of actual strings in this node
    size_t numHere = current->last - current->first;

    // check if it bekongs here
    if(loc < numBefore + numHere)
    {
      size_t offset = loc - numBefore;
      size_t arrayIndex = current->first + offset;

      return &(current->val[arrayIndex]);
    }

    // skip all values
    numBefore = numBefore + numHere;
    current = current->next;
  }

  return NULL;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}