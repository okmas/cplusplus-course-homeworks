#ifndef BIND_FIRST_HPP
#define BIND_FIRST_HPP

template <typename TOperation, typename TReturnValue, typename TArg1>
class bind_first_1 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param first_arg argument of operation
     */
    bind_first_1(const TOperation &op, const TArg1 &first_arg)
        : m_operation(op) ,m_first_arg(first_arg) {}

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() ()
    {
        return m_operation(m_first_arg);
    }

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() () const
    {
        return m_operation(m_first_arg);
    }

private:
    TOperation m_operation;
    const TArg1 m_first_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2>
class bind_first_2 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param first_arg first argument of operation
     */
    bind_first_2(const TOperation &op, const TArg1 &first_arg)
        : m_operation(op) ,m_first_arg(first_arg) {}

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2)
    {
        return m_operation(m_first_arg, arg2);
    }

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2) const
    {
        return m_operation(m_first_arg, arg2);
    }

private:
    TOperation m_operation;
    const TArg1 m_first_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3>
class bind_first_3 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param first_arg first argument of operation
     */
    bind_first_3(const TOperation &op, const TArg1 &first_arg)
        : m_operation(op) ,m_first_arg(first_arg) {}

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3)
    {
        return m_operation(m_first_arg, arg2, arg3);
    }

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3) const
    {
        return m_operation(m_first_arg, arg2, arg3);
    }

private:
    TOperation m_operation;
    const TArg1 m_first_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3, typename TArg4>
class bind_first_4 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param first_arg first argument of operation
     */
    bind_first_4(const TOperation &op, const TArg1 &first_arg)
        : m_operation(op) ,m_first_arg(first_arg) {}

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3,
                             const TArg4 arg4)
    {
        return m_operation(m_first_arg, arg2, arg3, arg4);
    }

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3,
                             const TArg4 arg4) const
    {
        return m_operation(m_first_arg, arg2, arg3, arg4);
    }

private:
    TOperation m_operation;
    const TArg1 m_first_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3, typename TArg4, typename TArg5>
class bind_first_5 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param first_arg first argument of operation
     */
    bind_first_5(const TOperation &op, const TArg1 &first_arg)
        : m_operation(op) ,m_first_arg(first_arg) {}

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3,
                             const TArg4 arg4, const TArg5 arg5)
    {
        return m_operation(m_first_arg, arg2, arg3, arg4, arg5);
    }

    /**
     * @brief Performs binding of first argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg2 arg2, const TArg3 arg3,
                             const TArg4 arg4, const TArg5 arg5) const
    {
        return m_operation(m_first_arg, arg2, arg3, arg4, arg5);
    }

private:
    TOperation m_operation;
    const TArg1 m_first_arg;
};

#endif // BIND_FIRST_HPP
