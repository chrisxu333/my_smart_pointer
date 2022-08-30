#ifndef MY_SHARED_PTR_H_
#define MY_SHARED_PTR_H_

#include <mutex>

template <typename T>
class my_shared_ptr {
 public:
  // constructors
  my_shared_ptr(T* other)
      : ptr_(other), refcnt_(new int(1)), refcnt_lock_(new std::mutex) {}
  // copy constructor
  my_shared_ptr(const my_shared_ptr<T>& other)
      : ptr_(other.ptr_),
        refcnt_(other.refcnt_),
        refcnt_lock_(other.refcnt_lock_) {
    inc_ref_count();
  }
  // destructor
  ~my_shared_ptr() { release(); }
  // Replaces the managed object with the one managed by other.
  my_shared_ptr<T>& operator=(const my_shared_ptr<T>& other) noexcept {
    if (ptr_ != other.ptr_) {
      release();
      ptr_ = other.ptr_;
      refcnt_ = other.refcnt_;
      refcnt_lock_ = other.refcnt_lock_;
      inc_ref_count();
    }
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
      reset_ref_count();
    }
  }

  long use_count() const noexcept { return *refcnt_; }
  bool unique() const noexcept { return use_count() == 1; }

 private:
  std::mutex* refcnt_lock_;
  int* refcnt_;
  T* ptr_;

  void inc_ref_count() {
    refcnt_lock_->lock();
    (*refcnt_)++;
    refcnt_lock_->unlock();
  }

  void reset_ref_count() {
    refcnt_lock_->lock();
    *refcnt_ = 1;
    refcnt_lock_->unlock();
  }

  void release() {
    refcnt_lock_->lock();
    (*refcnt_)--;
    if (*refcnt_ == 0) {
      delete ptr_;
      delete refcnt_;
      refcnt_lock_->unlock();
      delete refcnt_lock_;
    }
    refcnt_lock_->unlock();
  }
};

#endif