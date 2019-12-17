#ifndef FILTER_VIEW_HPP
#define FILTER_VIEW_HPP

#include <iterator>
#include <algorithm>

template <typename TContainer, typename TPredicate>
class filter_view {
private:
    typedef typename TContainer::const_iterator container_const_iterator_type;
public:
    typedef TContainer container_type;
    typedef TPredicate predicate_type;
    typedef typename TContainer::value_type value_type;
    friend class const_iterator;

    class const_iterator : std::iterator<std::forward_iterator_tag, value_type> {
    public:
        friend class filter_view;

        /**
         * @brief Param-less constructor.
         */
        const_iterator() {}

        /**
         * @brief Copy constructor.
         * @param other iterator to copy from
         */
        const_iterator(const const_iterator &other)
            : m_end(other.m_end), m_predicate(other.m_predicate), m_real_it(other.m_real_it) {}

        /**
         * @brief Prefix operator++, iterates to the next element of the container satisfying the predicate.
         * @return incremented this iterator
         */
        const_iterator & operator++()
        {
            m_real_it = std::find_if(++m_real_it, m_end, m_predicate);
            return *this;
        }

        /**
         * @brief Postfix operator++, iterates to the next element of the container satisfying the predicate.
         * @return incremented this iterator
         */
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            operator++();
            return tmp;
        }

        /**
         * @brief Compares this iterator with another one.
         * @param other other iterator
         * @return true if the same, false otherwise
         */
        bool operator==(const const_iterator &other)
        {
            return ((m_end == other.m_end) && (m_real_it == other.m_real_it));
        }

        /**
         * @brief Compares this iterator with another one.
         * @param other other iterator
         * @return true if different, false otherwise
         */
        bool operator!=(const const_iterator &other)
        {
            return (! operator==(other));
        }

        /**
         * @brief Works the same as the copy constructor.
         * @param other iterator to copy from
         */
        void operator=(const const_iterator &other)
        {
            m_end = other.m_end;
            m_predicate = other.m_predicate;
            m_real_it = other.m_real_it;
        }

        /**
         * @brief Returns reference to value pointed to by this iterator.
         * @return reference to value pointed to by this iterator
         */
        const value_type & operator*()
        {
            return *m_real_it;
        }

        /**
         * @brief Returns pointer to value pointed to by this iterator.
         * @return ponter to value pointed to by this iterator
         */
        const value_type * operator->()
        {
            return &(*m_real_it);
        }

    private:
        const_iterator(const container_const_iterator_type &end, const predicate_type predicate, container_const_iterator_type real_it)
            : m_end(end), m_predicate(predicate), m_real_it(real_it) {}

    private:
        const container_const_iterator_type m_end;
        const predicate_type m_predicate;
        container_const_iterator_type m_real_it;
    }; // const_iterator

    /**
     * @brief Constructor.
     * @param container container to filter
     * @param predicate predicate to filter with
     */
    filter_view(const container_type &container, const predicate_type &predicate)
        : m_container(container), m_predicate(predicate) {}

    /**
     * @brief Copy constructor.
     * @param other filter_view to copy from
     */
    filter_view(const filter_view &other)
        : m_container(other.m_container), m_predicate(other.m_predicate) {}

    /**
     * @brief Returns iterator to the first element of the container satisfying the predicate.
     * @return iterator to the first element of the container satisfying the predicate
     */
    const_iterator begin() const
    {
        container_const_iterator_type it = std::find_if(m_container.begin(), m_container.end(), m_predicate);
        return const_iterator(m_container.end(), m_predicate, it);
    }

    /**
     * @brief Returns iterator to the past-the-last element of the container.
     * @return iterator to the past-the-last element of the container
     */
    const_iterator end() const
    {
        return const_iterator(m_container.end(), m_predicate, m_container.end());
    }

    /**
     * @brief Checkes whether filter view is empty.
     * @return True if no element in the container satisfies the predicate, false otherwise.
     */
    bool empty() const
    {
        return (size() == 0);
    }

    /**
     * @brief Returns number of elements in the container satisfying the predicate.
     * @return number of elements in the container satisfying the predicate
     */
    size_t size() const
    {
        return std::count_if(m_container.begin(), m_container.end(), m_predicate);
    }

    /**
     * @brief Returns iterator to the first element of the container satisfying predicate.
     * @return iterator to the first element of the container satisfying predicate
     */
    const value_type & front() const
    {
        return *begin();
    }

    /**
     * @brief Returns iterator to the last element in the container satisfying the predicate.
     * @return iterator to the last element in the container satisfying the predicate
     */
    const value_type & back() const
    {
        return *std::find_if(m_container.rbegin(), m_container.rend(), m_predicate);
    }

    /**
     * @brief Returns the predicate used for filtering.
     * @return predicate used for filtering
     */
    const predicate_type & get_predicate() const
    {
        return m_predicate;
    }

private:
    const container_type &m_container;
    const predicate_type m_predicate;
}; // filter_view

#endif // FILTER_VIEW_HPP
