#ifndef MY_UNIQUE_PTR_H_
#define MY_UNIQUE_PTR_H_

template <typename T>
class my_unique_ptr {
 public:
  // constructors
  my_unique_ptr(T* other = nullptr) : ptr_(other) {}

  // copy constructor and copy assign constructor
  my_unique_ptr(my_unique_ptr& other) {
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
  }
  my_unique_ptr& operator=(my_unique_ptr&& other) {
    if (*this != other) {
      if (ptr_) delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  // const copy constructor and copy assign constructor
  my_unique_ptr(const my_unique_ptr& other) = delete;
  my_unique_ptr& operator=(const my_unique_ptr& other) = delete;
  // destructor
  ~my_unique_ptr() {
    if (ptr_) delete ptr_;
  }

  // observer
  T& operator*() const noexcept { return *ptr_; }
  T* operator->() const noexcept { return ptr_; }

  // Return the stored pointer.
  T* get() const noexcept { return ptr_; }

  void reset(T* ptr = nullptr) noexcept {
    if (ptr != ptr_) {
      if (ptr_) delete ptr_;
      ptr_ = ptr;
    }
  }

  T* release() {
    T* res = ptr_;
    ptr_ = nullptr;
    return res;
  }

 private:
  int* refcnt_;
  T* ptr_;
};

#endif