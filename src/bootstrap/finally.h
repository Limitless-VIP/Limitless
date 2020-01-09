/**
 * Copyright (c) 2015-2018 COLX Developers
 * Copyright (c) 2018-2019 Galilel Developers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef LIMITLESS_FINALLY_H
#define LIMITLESS_FINALLY_H

#include <functional>
#include <exception>

/**
 * @brief Finalization pattern - call specified function on scope exit
 */
struct Finally
{
    typedef std::function<void ()> OnScopeExit;

    Finally(OnScopeExit fn) : fn_(fn) {
        if (!fn_) {
            throw std::logic_error("Finally: invalid argument fn");
        }
    }

    ~Finally() {
        bool exc = std::uncaught_exception();
        try {
            fn_();
        } catch (...) {
            if (exc) {
                assert(false);
            }
        }
    }

private:
    OnScopeExit fn_;
    Finally(const Finally&);
    Finally& operator = (const Finally&);
};

#endif /** LIMITLESS_FINALLY_H */
