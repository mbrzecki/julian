#ifndef JULIAN_SMARTPOINTER_HPP
#define JULIAN_SMARTPOINTER_HPP

namespace julian {
  /**
   * @file   smartPointer.hpp
   * @brief  File contains template of deep-coping smart pointer.
   */
   
  /** \ingroup utils
   * \brief Template of deep-coping smart pointer 
   */
  template< class T>
  class SmartPointer {
  public:
    /** \brief Default constructor
     */
    SmartPointer() {
      data_ptr_ = 0;
    }
    /** \brief Constructor
     */    
    SmartPointer(const T& inner) {
      data_ptr_ = inner.clone();
    }
    /** \brief Destructor
     */  
    ~SmartPointer() {
      if (data_ptr_ != 0)
	delete data_ptr_;
    }
    /** \brief Copy constructor
     */  
    SmartPointer(const SmartPointer<T>& original) {
      if (original.data_ptr_ != 0) {
	data_ptr_ = original.data_ptr_->clone();
      } else {
	data_ptr_=0;
      }
    }
    
    /** \brief Assignment operator
     */   
    SmartPointer& operator=(const SmartPointer<T>& original) {
      if (this != &original) {
	if (data_ptr_ != 0) {
	  delete data_ptr_;
	}
	data_ptr_ = (original.data_ptr_ != 0) ? original.data_ptr_->clone() : 0;
      }
      return *this;
    }
     
    /** \brief Method dereferencing pointer
     */   
    T& operator*() {
      return *data_ptr_; 
    }

    /** \brief Method dereferencing pointer
     */   
    const T& operator*() const {
      return *data_ptr_; 
    }

    /** \brief Method dereferencing pointer
     */   
    T* operator->() {
      return data_ptr_;
    }

    /** \brief Method dereferencing pointer
     */   
    const T* operator->() const {
      return data_ptr_;
    }

    /** \brief Check if pointer owns any object
     */   
    bool isEmpty() const {
      if (data_ptr_) {
	return false;
      }
      return true;
    }
    
  private:
    T* data_ptr_; /*!< \brief Pointer to data owned by pointer*/  
  };
  
}  // namespace julian
#endif

/*
 *
 * Copyright (c) 2002
 * Mark Joshi
 *
 * Permission to use, copy, modify, distribute and sell this
 * software for any purpose is hereby
 * granted without fee, provided that the above copyright notice
 * appear in all copies and that both that copyright notice and
 * this permission notice appear in supporting documentation.
 * Mark Joshi makes no representations about the
 * suitability of this software for any purpose. It is provided
 * "as is" without express or implied warranty.
 */

