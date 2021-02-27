#pragma once

#include <utility>
#include <Windows.h>

template<class T>
class encoded_ptr {
    T* m_encoded_pointer;

    T* decode_ptr()
    {
        return static_cast<T*>(DecodePointer(m_encoded_pointer));
    }

    encoded_ptr(T* pointer) : m_encoded_pointer{ static_cast<T*>(EncodePointer(pointer)) } {}
public:
    encoded_ptr(encoded_ptr<T> const&) = delete;
    encoded_ptr<T>& operator=(encoded_ptr<T> const&) = delete;

    encoded_ptr(encoded_ptr<T>&& o) : m_encoded_pointer{ o.m_encoded_pointer }
    {
        o.m_encoded_pointer = nullptr;
    }

    template<class... Args, class = std::enable_if_t<!std::is_array_v<T>>>
    static encoded_ptr<T> create(Args&&... args)
    {
        return encoded_ptr<T>(new T(std::forward<Args>(args)...));
    }

    explicit operator bool() const
    {
        return static_cast<bool>(decode_ptr());
    }

    T* operator->() const
    {
        return decode_ptr();
    }

    T operator*() const
    {
        return *decode_ptr();
    }

    ~encoded_ptr()
    {
        auto decoded_pointer = decode_ptr();
        if (decoded_pointer != nullptr)
        {
            delete decoded_pointer;
            decoded_pointer = nullptr;
        }
        m_encoded_pointer = nullptr;
    }
};