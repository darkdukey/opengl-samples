#pragma once

using uint = unsigned int;
using uchar = unsigned char;

#define GETSET(type, var, func) \
   private:                     \
    type _##var;                \
                                \
   public:                      \
    type get##func() {          \
        return _##var;          \
    }                           \
    void set##func(type val) {  \
        _##var = val;           \
    }

#define GETSETR(type, var, func)        \
   private:                             \
    type _##var;                        \
                                        \
   public:                              \
    const type &get##func() const {     \
        return _##var;                  \
    };                                  \
    void set##func(const type &value) { \
        _##var = value;                 \
    }

#define GETSETB(type, var, func) \
   private:                      \
    type _##var;                 \
                                 \
   public:                       \
    type is##func() {            \
        return _##var;           \
    }                            \
    void set##func(type val) {   \
        _##var = val;            \
    }

#define GET(type, var, func) \
   private:                  \
    type _##var;             \
                             \
   public:                   \
    type get##func() const { \
        return _##var;       \
    }

#define GETR(type, var, func)       \
   private:                         \
    type _##var;                    \
                                    \
   public:                          \
    const type &get##func() const { \
        return _##var;              \
    }