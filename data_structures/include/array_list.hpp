/* 
 * Implentation of a dynamic array in C++ 
 * This implementation uses the default allocator new 
 */

#pragma once
#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <cstddef>
#include <initializer_list> 
#include <algorithm>
#include <limits>


namespace ds {
    
    template <typename T>
    class array_list {
    
    public:
        typedef std::size_t size_type;
        typedef std::ptrdiff_t different_type;
        typedef T value_type;
        typedef T& reference;
        typedef T* iterator;
        typedef const T* const_iterator;

        /* Constructors */

        /* Initialize empty array */
        array_list() : size_(0), capacity_(0) {
            data_ = nullptr;
        }

        /* Initialize array with space allocated for n items */
        array_list(size_type n) : size_(0), capacity_(n) {
            data_ = new value_type[capacity_];
        }

        /* Initialize array with n items of value v*/
        array_list(size_type n, value_type v) : size_(n), capacity_(n) {
            data_ = new value_type[capacity_];
            std::fill_n(data_, n, v);
        }

        /* Initialize array with initializer_list {} */
        array_list(std::initializer_list<value_type> init_list) {
            size_ = init_list.size();
            capacity_ = init_list.size();
            data_ = new value_type[capacity_];

            std::copy(init_list.begin(), init_list.end(), data_);
        }


        /* Copy Constructor initialize array from a different array  */
        array_list(const array_list &a) {
            size_ = a.size();
            capacity_ = a.capacity_();
            data_ = new value_type[capacity_];

            std::copy(a.begin(), a.end(), data_);
        }

        /* Initialize from first iterator to last iterator */
        array_list(iterator first, iterator last) {
            size_ = last - first;
            capacity_ = size_;
            data_ = new value_type[capacity_];

            std::copy(first, last, data_);
        }

        /* Iterators */
        iterator begin() {
            return data_;
        }

        const_iterator cbegin() {
            return data_;
        }

        iterator end() {
            return data_ + size_;
        }

        const_iterator cend() {
            return data_ + size_;
        }
        /* Operators */

        /* 
         * Assignment operators
         * This assignment operators will copy the array, it does not make another reference 
         */
        array_list& operator=(const array_list& a) {
            return array_list(a);
        }

        /* Destructor */
        ~array_list() {
            delete[] data_;
        }

        /* Capacity */
        
        /* Return the current size of the array */
        size_type size() const noexcept {
            return size_; 
        }

        /* Return the current capacity of the array */
        size_type capacity() const noexcept {
            return capacity_;
        }

        /* Check if the array contains any element */
        bool empty() const noexcept {
            return size_ == 0;
        }

        /* Return maximum possible container size*/
        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }

        /* Allocate memory for new_cap elements*/
        void reserve(size_type new_cap) {
            if (new_cap > max_size()) {
                throw new std::length_error("Capacity can not exceed maximum size");
            }

            realloc(new_cap);
        }
        
        /* Shrink the empty memories to only the size*/
        void shrink_to_fit() {
            realloc(size_);
        }

        /* Element access */
        
        /* Access element with boundary checking */
        reference at(size_type pos) {
            if (pos < 0 || pos > size_) {
                throw new std::out_of_range("Can not access index at %p", data_ + pos);
            }    

            return data_[pos];
        }

        /* Return reference to the first element */
        reference front() {
            return data_[0];
        }

        /* Return reference to the last element */
        reference back() {
            return data_[size_ - 1];
        }

        /* Return the underlying pointer */
        iterator data() {
            return data_;
        }

        /* Access element without boundary checking */
        reference operator[](size_type pos) {
            return data_[pos];
        }

        /* Modifiers */

        /* 
         * Push an element to the end of the array  
         * Allocate memory twice the current capacity if full 
         */
        void push_back(const value_type& value) {
            if (size_ + 1 > capacity_) {
                capacity_ == 0 ? realloc(1) : realloc(capacity_ * 2);
            }

            data_[size_] = value;
            ++size_;
        }

        /* Clear the content of all elements in the array making */
        void clear() noexcept {
            std::fill(data_, data_ + size_, value_type());

            size_ = 0;
        }

        /* Pop the last element of the array */
        void pop_back() {
            if (size_ == 0) {
                throw new std::out_of_range("Can not pop_back() an empty array list");
            }
            data_[size_ - 1] = value_type();
            --size_;
        }

        /* Resize the array fill them with default values if count is larger than current size */
        void resize(size_type count) {
            realloc(count);

            if (size_ < count) {
                std::fill_n(begin() + size_, value_type());
            }
        }

        /* Resize the array fill them with the value specifed if count is larger than current size */
        void resize(size_type count, const value_type& value) {
            realloc(count);

            if (size_ < count) {
                std::fill_n(begin() + size_, value);
            }
        }

        /* Insert an element to the position specified by the iterator pos */
        iterator insert(const_iterator pos, const value_type& value) {
            const size_type index = pos - data_;

            if (index < 0 || index > size_) {
                throw new std::out_of_range("Iterator is out of range");
            }

            if (size_ + 1 > capacity_) {
                capacity_ == 0 ? realloc(1) : realloc(capacity_ * 2);
            }

            iterator it = data_ + index;

            std::copy(it, data_ + size_, it + 1);
            
            data_[index] = value;
            
            ++size_;

            return it;
        } 
        
        /* Erase an element at the position specified by the iterator pos */
        iterator erase(const_iterator pos) {
            const size_type index = pos - data_;

            if (index < 0 || index > size_) {
                throw new std::out_of_range("Iterator is out of range");
            }

            iterator it = data_ + index;

            std::copy(it + 1, data_ + size_, it);
            data_[size_ - 1] = value_type();
            --size_;

            return it;
        }        

    private:
        size_type size_;
        size_type capacity_;
        iterator data_; 

        /**********************************************
         * Internal use to reallocate array 
         * if new_cap < size_ values will be truncated 
         **********************************************/
        void realloc(size_type new_cap) {
            if (new_cap < size_) {
                iterator new_data = new value_type[new_cap];
                
                delete[] (data_ + new_cap);
                std::move(data_, data_ + new_cap, new_data);
                size_ = new_cap;
                capacity_ = new_cap;
                data_ = new_data;
                return;
            }

            iterator new_data = new value_type[new_cap];
            std::move(data_, data_ + size_, new_data);
            delete[] data_;
            capacity_ = new_cap;
            data_ = new_data;
        }
    };    
}


#endif