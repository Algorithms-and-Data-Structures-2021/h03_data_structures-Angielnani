#include "linked_queue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedQueue::Enqueue(Element e) {
    auto temp = new SinglyNode(e, nullptr);
    if (size_ == 0){
        back_ = temp;
        front_ = temp;
    }
    else {
        back_->next = temp;
        back_ = temp;
    }
    size_ += 1;
}


void LinkedQueue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("could not dequeue from empty queue");
  }
  else if (size_ == 1){
    delete front_;
    back_ = nullptr;
    front_ = nullptr;
}
  else
{
auto temp = front_->next;
delete front_;
front_ = temp;
}
size_ -= 1;
}

void LinkedQueue::Clear() {
    auto curr = front_;
    for (int i = 0; i < size_; i++)
    {
        auto temp = curr->next;
        delete curr;
        curr = temp;
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedQueue::~LinkedQueue() {
  Clear();
}

std::optional<Element> LinkedQueue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedQueue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedQueue::IsEmpty() const {
  return size_ == 0;
}
int LinkedQueue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedQueue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->next) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis