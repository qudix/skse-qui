#pragma once

namespace Scaleform
{
    using FunctionHandlerCache = std::map<const std::type_info*, RE::GFxFunctionHandler*>;
    static FunctionHandlerCache functionHandlerCache;

    template <typename T>
    void CreateFunction(RE::GFxMovieView* a_view, RE::GFxValue* a_dst)
    {
        // either allocate the object or retrieve an existing instance from the cache
        RE::GFxFunctionHandler* func = nullptr;

        // check the cache
        auto iter = functionHandlerCache.find(&typeid(T));
        if (iter != functionHandlerCache.end())
            func = iter->second;

        if (!func) {
            // not found, allocate a new one
            func = new T;

            // add it to the cache
            // cache now owns the object as far as refcounting goes
            functionHandlerCache[&typeid(T)] = func;
        }

        // create the function object
        a_view->CreateFunction(a_dst, func);
    }

    template <typename T>
    void RegisterFunction(RE::GFxMovieView* a_view, RE::GFxValue* a_dst, const char* a_name)
    {
        RE::GFxValue function;
        CreateFunction<T>(a_view, &function);
        a_dst->SetMember(a_name, &function);
    }
}
