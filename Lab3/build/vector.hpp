#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include <iostream>

namespace sjtu
{
    /**
 * a data container like std::vector
 * store data in a successive memory and support random access.
 */
    template <typename T>
    class vector
    {
    private:
        size_t cur_size;
        size_t total_size;
        T *storge;

    public:
        /**
     * TODO
     * a type for actions of the elements of a vector, and you should write
     *   a class named const_iterator with same interfaces.
     */
        /**
     * you can see RandomAccessIterator at CppReference for help.
     */
        class const_iterator;
        class iterator
        {
        private:
            T *storge_;
            int pos_; /**
         * TODO add data members
         *   just add whatever you want.
         */
        public:
            iterator(T *storge, int pos) : storge_(storge), pos_(pos) {}
            /**
         * return a new iterator which pointer n-next elements
         * as well as operator-
         */
            int display_pos_()
            {
                return pos_;
            }
            iterator operator+(const int &n) const
            {
                iterator iter(storge_, pos_);
                iter.pos_ += n;
                return iter;

                //TODO
            }
            iterator operator-(const int &n) const
            {
                iterator iter(storge_, pos_);
                iter.pos_ -= n;
                return iter; //TODO
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {
                if (storge_ != rhs.storge_)
                    throw invalid_iterator();
                return pos_ - rhs.pos_; //TODO
            }
            iterator &operator+=(const int &n)
            {
                pos_ += n;
                return *this; //TODO
            }
            iterator &operator-=(const int &n)
            {
                pos_ -= n;
                return *this; //TODO
            }
            /**
         * TODO iter++
         */
            iterator operator++(int)
            {
                iterator iter(storge_, pos_);
                pos_++;
                return iter;
            }
            /**
         * TODO ++iter
         */
            iterator &operator++()
            {
                pos_++;
                return *this;
            }
            /**
         * TODO iter--
         */
            iterator operator--(int)
            {
                iterator iter(storge_, pos_);
                pos_--;
                return iter;
            }
            /**
         * TODO --iter
         */
            iterator &operator--()
            {
                pos_--;
                return *this;
            }
            /**
         * TODO *it
         */
            T &operator*() const
            {
                return storge_[pos_];
            }
            /**
         * a operator to check whether two iterators are same (pointing to the same memory address).
         */
            bool operator==(const iterator &rhs) const { return pos_ == rhs.pos_; }
            bool operator==(const const_iterator &rhs) const { return pos_ == rhs.pos_; }
            /**
         * some other operator for iterator.
         */
            bool operator!=(const iterator &rhs) const { return pos_ != rhs.pos_; }
            bool operator!=(const const_iterator &rhs) const { return pos_ != rhs.pos_; }
            bool operator>(const iterator &rhs) const { return pos_ > rhs.pos_; }
            bool operator>(const const_iterator &rhs) const { return pos_ > rhs.pos_; }
            bool operator>=(const iterator &rhs) const { return pos_ >= rhs.pos_; }
            bool operator>=(const const_iterator &rhs) const { return pos_ >= rhs.pos_; }
            bool operator<(const iterator &rhs) const { return pos_ < rhs.pos_; }
            bool operator<(const const_iterator &rhs) const { return pos_ < rhs.pos_; }
            bool operator<=(const iterator &rhs) const { return pos_ <= rhs.pos_; }
            bool operator<=(const const_iterator &rhs) const { return pos_ <= rhs.pos_; }
        };
        /**
     * TODO
     * has same function as iterator, just for a const object.
     */
        class const_iterator
        {
        private:
            T *storge_;
            int pos_;

        public:
            const_iterator(T *storge, int pos) : storge_(storge), pos_(pos) {}
            const_iterator operator+(const int &n) const
            {
                iterator iter(storge_, pos_);
                iter.pos_ += n;
                return *iter;
            };
            const_iterator operator-(const int &n) const
            {
                iterator iter(storge_, pos_);
                iter.pos_ -= n;
                return *iter;
            }
            const int operator-(const iterator &rhs) const
             { 
                 return pos_ - rhs.pos_; 
             }
            const_iterator &operator+=(const int &n)
            {
                return *this + n;
            }
            const_iterator &operator-=(const int &n)
            {
                return *this - n;
            }
            const_iterator operator++(int)
            {
                const_iterator iter(storge_, pos_);
                pos_++;
                return iter;
            }
            const_iterator &operator++()
            {
                pos_++;
                return *this;
            }
            const_iterator operator--(int)
            {
                const_iterator iter(storge_, pos_);
                pos_--;
                return iter;
            }
            const_iterator &operator--()
            {
                pos_--;
                return *this;
            }
            T &operator*() const
            {
                return storge_[pos_];
            }
            bool operator==(const const_iterator &rhs) const { return pos_ == rhs.pos_; }
            bool operator!=(const const_iterator &rhs) const { return pos_ != rhs.pos_; }
            bool operator>(const const_iterator &rhs) const { return pos_ > rhs.pos_; }
            bool operator>=(const const_iterator &rhs) const { return pos_ >= rhs.pos_; }
            bool operator<(const const_iterator &rhs) const { return pos_ < rhs.pos_; }
            bool operator<=(const const_iterator &rhs) const { return pos_ <= rhs.pos_; }
        };

        /**
     * TODO Constructs
     * Atleast two: default constructor, copy constructor
     */

        vector() : cur_size(0), total_size(4)
        {
            storge = (T *)operator new(total_size * sizeof(T));
            memset(storge, 0, total_size * sizeof(T));
        }
        vector(unsigned int cap) : cur_size(0), total_size(cap)
        {
            storge = (T *)operator new(total_size * sizeof(T));
            memset(storge, 0, total_size * sizeof(T));
        }
        vector(const vector &other)
        {
            storge = (T *)operator new(other.total_size * sizeof(T));
            memset(storge, 0, other.total_size * sizeof(T));
            total_size = other.total_size;
            cur_size = other.cur_size;
            for (unsigned int i = 0; i < other.cur_size; i++)
            {
                storge[i] = other.storge[i];
            }
        }
        /**
     * TODO Destructor
     */
        ~vector()
        {
            if (storge)
            {
                for (int i = 0; i < cur_size; i++)
                    storge[i].~T();
                operator delete(storge);
                storge = nullptr;
            }
            cur_size = 0;
            total_size = 0;
        }
        /**
     * TODO Assignment operator
     */
        vector &operator=(const vector &other)
        {

            if (storge)
            {
                for (int i = 0; i < cur_size; i++)
                    storge[i].~T();
                operator delete(storge);
                storge = nullptr;
            }

            cur_size = other.cur_size;
            total_size = other.total_size;
            storge = (T *)operator new(total_size * sizeof(T));
            memset(storge, 0, total_size * sizeof(T));
            for (unsigned int i = 0; i < cur_size; i++)
            {
                storge[i] = other.storge[i];
            }
            return *this;
        }
        /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     */
        T &at(const unsigned int &pos)
        {
            if (pos < 0 || pos >= cur_size)
                throw index_out_of_bound();
            return storge[pos];
        }
        const T &at(const unsigned int &pos) const
        {
            if (pos < 0 || pos >= cur_size)
                throw index_out_of_bound();
            return storge[pos];
        }
        /**
     * assigns specified element with bounds checking
     * throw index_out_of_bound if pos is not in [0, size)
     * !!! Pay attentions
     *   In STL this operator does not check the boundary but I want you to do.
     */
        T &operator[](const unsigned int &pos)
        {
            if (pos < 0 || pos >= cur_size)
                throw index_out_of_bound();
            return storge[pos];
        }
        const T &operator[](const unsigned int &pos) const
        {
            if (pos < 0 || pos >= cur_size)
                throw index_out_of_bound();
            return storge[pos];
        }
        /**
     * access the first element.
     * throw container_is_empty if size == 0
     */
        const T &front() const
        {
            if (cur_size == 0)
                throw container_is_empty();
            return *storge;
        }
        /**
     * access the last element.
     * throw container_is_empty if size == 0
     */
        const T &back() const
        {
            return *(storge + cur_size - 1);
        }
        /**
     * returns an iterator to the beginning.
     */
        iterator begin() { return iterator(storge, 0); }
        const_iterator cbegin() const { return const_iterator(storge, 0); }
        /**
     * returns an iterator to the end.
     */
        iterator end() { return iterator(storge, cur_size); }
        const_iterator cend() const { return const_iterator(storge, cur_size); }
        /**
     * checks whether the container is empty
     */
        bool empty() const { return cur_size == 0; }
        /**
     * returns the number of elements
     */
        unsigned int size() const { return cur_size; }
        /**
     * clears the contents
     */
        void resize(unsigned int k)
        {
            T *new_storge;
            new_storge = (T *)operator new(k * sizeof(T));
            memset(new_storge, 0, k * sizeof(T));
            total_size = k;
            for (unsigned int i = 0; i < cur_size; i++)
            {
                new_storge[i] = T(storge[i]);
            }

            for (unsigned int i = 0; i < cur_size; i++)
            {

                storge[i].~T();
            }
            operator delete(storge);
            storge = new_storge;
            new_storge = nullptr;
        }
        void clear()
        {
            cur_size = 0;
            resize(4);
        }

        /**
     * inserts value before pos
     * returns an iterator pointing to the inserted value.
     */
        iterator insert(iterator pos, const T &value)
        {

            int ind = pos.display_pos_() - begin().display_pos_();
            if (cur_size >= total_size)
                resize(total_size * 2);
            cur_size++;
            for (unsigned int i = cur_size - 1; i > ind; i--)
            {
                storge[i] = storge[i - 1];
            }
            storge[ind] = T(value);
            return iterator(storge, ind);
        }
        /**
     * inserts value at index ind.
     * after inserting, this->at(ind) == value
     * returns an iterator pointing to the inserted value.
     * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
     */
        iterator insert(const unsigned int &ind, const T &value)
        {
            if (ind > cur_size)
                throw index_out_of_bound();

            if (cur_size >= total_size)
                resize(total_size * 2);
            cur_size++;
            for (unsigned int i = cur_size - 1; i > ind; i--)
            {
                storge[i] = storge[i - 1];
            }
            storge[ind] = T(value);
            return iterator(storge, ind);
        }
        /**
     * removes the element at pos.
     * return an iterator pointing to the following element.
     * If the iterator pos refers the last element, the end() iterator is returned.
     */
        iterator erase(iterator pos)
        {
            if (pos >= iterator(storge, 0) && pos < iterator(storge, cur_size))
            {
                for (iterator i = pos; i < iterator(storge, cur_size - 1); i++)
                    *i = *(i + 1);

                cur_size--;

                if (pos == iterator(storge, cur_size))
                {
                    return end();
                }
            }
            return pos;
        }
        /**
     * removes the element with index ind.
     * return an iterator pointing to the following element.
     * throw index_out_of_bound if ind >= size
     */
        iterator erase(const unsigned int &ind)
        {
            if (ind >= cur_size)
                throw index_out_of_bound();
            if (ind >= 0 && ind < cur_size)
            {
                for (unsigned int i = ind; i < cur_size - 1; i++)
                    storge[i] = storge[i + 1];
                cur_size--;
            }
            return iterator(storge, ind);
        }
        /**
     * adds an element to the end.
     */
        void push_back(const T &value)
        {

            if (cur_size >= total_size)
                resize(total_size * 2);
            cur_size++;
            storge[cur_size - 1] = T(value);
        }
        /**
     * remove the last element from the end.
     * throw container_is_empty if size() == 0
     */
        void pop_back()
        {
            if (cur_size == 0)
                throw container_is_empty();
            cur_size--;
        }
    };
};

#endif