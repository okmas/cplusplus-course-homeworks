#ifndef BIND_LAST_HPP
#define BIND_LAST_HPP

template <typename TOperation, typename TReturnValue, typename TArg1>
class bind_last_1 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param last_arg argument of operation
     */
    bind_last_1(const TOperation &op, const TArg1 &last_arg)
        : m_operation(op) ,m_last_arg(last_arg) {}

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() ()
    {
        return m_operation(m_last_arg);
    }

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() () const
    {
        return m_operation(m_last_arg);
    }

private:
    TOperation m_operation;
    const TArg1 m_last_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2>
class bind_last_2 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param last_arg last argument of operation
     */
    bind_last_2(const TOperation &op, const TArg2 &last_arg)
        : m_operation(op) ,m_last_arg(last_arg) {}

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1)
    {
        return m_operation(arg1, m_last_arg);
    }

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1) const
    {
        return m_operation(arg1, m_last_arg);
    }

private:
    TOperation m_operation;
    const TArg2 m_last_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3>
class bind_last_3 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param last_arg last argument of operation
     */
    bind_last_3(const TOperation &op, const TArg3 &last_arg)
        : m_operation(op) ,m_last_arg(last_arg) {}

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2)
    {
        return m_operation(arg1, arg2, m_last_arg);
    }

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2) const
    {
        return m_operation(arg1, arg2, m_last_arg);
    }

private:
    TOperation m_operation;
    const TArg3 m_last_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3, typename TArg4>
class bind_last_4 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param last_arg last argument of operation
     */
    bind_last_4(const TOperation &op, const TArg4 &last_arg)
        : m_operation(op) ,m_last_arg(last_arg) {}

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2,
                             const TArg3 arg3)
    {
        return m_operation(arg1, arg2, arg3, m_last_arg);
    }

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2,
                             const TArg3 arg3) const
    {
        return m_operation(arg1, arg2, arg3, m_last_arg);
    }

private:
    TOperation m_operation;
    const TArg4 m_last_arg;
};

template <typename TOperation, typename TReturnValue, typename TArg1,
          typename TArg2, typename TArg3, typename TArg4, typename TArg5>
class bind_last_5 {
public:
    /**
     * @brief Constructor.
     * @param op operation to bing
     * @param last_arg last argument of operation
     */
    bind_last_5(const TOperation &op, const TArg5 &last_arg)
        : m_operation(op) ,m_last_arg(last_arg) {}

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2,
                             const TArg3 arg3, const TArg4 arg4)
    {
        return m_operation(arg1, arg2, arg3, arg4, m_last_arg);
    }

    /**
     * @brief Performs binding of last argument.
     * @return return value of operation
     */
    TReturnValue operator() (const TArg1 arg1, const TArg2 arg2,
                             const TArg3 arg3, const TArg4 arg4) const
    {
        return m_operation(arg1, arg2, arg3, arg4, m_last_arg);
    }

private:
    TOperation m_operation;
    const TArg5 m_last_arg;
};

#endif // BIND_LAST_HPP
