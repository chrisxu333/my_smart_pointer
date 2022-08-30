#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

template <typename T>
class my_shared_ptr {
 public:
  // constructors
  my_shared_ptr(T* other) {
    ptr_ = other;
    refcnt_ = new int(1);
  }
  // copy constructor
  my_shared_ptr(const my_shared_ptr& other) {
    ptr_ = other.ptr_;
    refcnt_ = other.refcnt_;
    (*refcnt_)++;
  }
  // destructor
  ~my_shared_ptr() {
    (*refcnt_)--;
    if (*refcnt_ == 0) {
      delete ptr_;
    }
  }
  // Replaces the managed object with the one managed by other.
  my_shared_ptr& operator=(const my_shared_ptr& other) noexcept {
    // deal with old ptr
    this->~my_shared_ptr();
    // assign to new pointer
    *refcnt_ = other.refcnt_;
    ptr_ = other.ptr_;
    return *this;
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
      *refcnt_ = 1;
    }
  }

  long use_count() const noexcept { return *refcnt_; }

  bool unique() const noexcept { return use_count() == 1; }

 private:
  int* refcnt_;
  T* ptr_;
};

#endif