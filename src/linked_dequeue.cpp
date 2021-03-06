#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e)
{
    auto new_node = new DoublyNode(e, nullptr, back_);
    if (size_ == 0){
        front_ = new_node;
        back_ = new_node;
    }
    else
    {
        back_->previous = new_node;
        back_ = new_node;
    }
    size_ += 1;
}

void LinkedDequeue::EnqueueFront(Element e) {
    auto new_node = new DoublyNode(e, front_, nullptr);
    if (size_ == 0){
        front_ = new_node;
        back_ = new_node;
    }
    else
    {
        front_->next = new_node;
        front_ = new_node;
    }
    size_ += 1;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
  else if (size_ == 1)
  {
        delete front_;
        back_ = nullptr;
        front_ = nullptr;
  } else
  {
        auto temp = front_->previous;
        delete front_;
        front_ = temp;
        front_->next = nullptr;
    }
    size_ -=1;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }
  else if (size_ == 1)
  {
      delete front_;
      back_ = nullptr;
      front_ = nullptr;
  }
  else
  {
      auto temp = back_->next;
      delete back_;
      back_ = temp;
      back_->previous = nullptr;
  }
    size_ -=1;
}

void LinkedDequeue::Clear() {
    auto curr = front_;
    for (int i = 0; i < size_; i++)
    {
        auto temp = curr->previous;
        delete curr;
        curr = temp;
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
}

// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
