#pragma once

#include <memory>
#include <mutex>

#include <interfaces/i_initialized.h>

/**
 * @brief   Base class of signleton object.
 *
 * @tparam	T		Type of the singleton object.
 * @tparam	Args	Types of the arguments of the constructor.
 */
template<class T, typename... Args>
class ISingleton : virtual protected IInitialized {
  protected:
    static ::std::shared_ptr<T> _instance;     ///< Instance.
    static ::std::mutex         _instanceLock; ///< Instance lock.

  protected:
    /**
     * @brief   Constructor.
     */
    ISingleton();

  public:
    /**
     * @brief   Destructor.
     */
    virtual ~ISingleton();

  public:
    /**
     * @brief       Initialize the instance.
     *
     * @param[in]   args        Arguments of constructor.
     *
     * @return      On success or the instance exists, the method returns
     *              the initialized instance, otherwise returns nullptr.
     */
    static ::std::shared_ptr<T> initialize(Args... args);

    /**
     * @brief       Get.
     *
     * @return      If the instalce has been initialized, the method
     *              returns the instance, otherwise returns nullptr.
     */
    static ::std::shared_ptr<T> instance();
};

#define SIGNLETON_OBJECT(T, ...) friend class ISingleton<T, ##__VA_ARGS__>;

template<class T, typename... Args>
::std::shared_ptr<T> ISingleton<T, Args...>::_instance = nullptr;

template<class T, typename... Args>
::std::mutex ISingleton<T, Args...>::_instanceLock;

/**
 * @brief   Constructor.
 */
template<class T, typename... Args>
ISingleton<T, Args...>::ISingleton()
{}

/**
 * @brief   Destructor.
 */
template<class T, typename... Args>
ISingleton<T, Args...>::~ISingleton()
{}

/**
 * @brief       Initialize the instance.
 */
template<class T, typename... Args>
::std::shared_ptr<T> ISingleton<T, Args...>::initialize(Args... args)
{
    ::std::lock_guard<::std::mutex> locker(_instanceLock);

    if (_instance == nullptr) {
        /// Create new instance
        _instance = ::std::shared_ptr<T>(new T(args...));

        if (! _instance->initialized()) {
            _instance = nullptr;
        }
    }

    return _instance;
}

/**
 * @brief       Get instance.
 */
template<class T, typename... Args>
::std::shared_ptr<T> ISingleton<T, Args...>::instance()
{
    return _instance;
}
