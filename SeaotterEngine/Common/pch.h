#pragma once

// target Windows 10 and later
#define _WIN32_WINNT 0x0A00 
#include <sdkddkver.h>

#define NOMINMAX

#include <Windows.h>

#include <wrl/client.h>

#include <iostream>
#include <exception>

/* ========== code from Xbox ATG Samples ========== */
namespace DX {
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) noexcept : result(hr) {}

        const char* what() const override {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
            return s_str;
        }

    private:
        HRESULT result;
    };

    // Helper utility converts D3D API failures into exceptions.
    inline void ThrowIfFailed(HRESULT hr) {
        if (FAILED(hr))
        {
            throw com_exception(hr);
        }
    }
}