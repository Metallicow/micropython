/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
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

#include "mpconfig.h"
#include "misc.h"
#include "qstr.h"
#include "obj.h"
#include "smallint.h"

bool mp_small_int_mul_overflow(machine_int_t x, machine_int_t y) {
    // Check for multiply overflow; see CERT INT32-C
    if (x > 0) { // x is positive
        if (y > 0) { // x and y are positive
            if (x > (MP_SMALL_INT_MAX / y)) {
                return true;
            }
        } else { // x positive, y nonpositive
            if (y < (MP_SMALL_INT_MIN / x)) {
                return true;
            }
        } // x positive, y nonpositive
    } else { // x is nonpositive
        if (y > 0) { // x is nonpositive, y is positive
            if (x < (MP_SMALL_INT_MIN / y)) {
                return true;
            }
        } else { // x and y are nonpositive
            if (x != 0 && y < (MP_SMALL_INT_MAX / x)) {
                return true;
            }
        } // End if x and y are nonpositive
    } // End if x is nonpositive
    return false;
}

machine_int_t mp_small_int_modulo(machine_int_t dividend, machine_int_t divisor) {
    machine_int_t lsign = (dividend >= 0) ? 1 :-1;
    machine_int_t rsign = (divisor >= 0) ? 1 :-1;
    dividend %= divisor;
    if (lsign != rsign) {
        dividend += divisor;
    }
  return dividend;
}


machine_int_t mp_small_int_floor_divide(machine_int_t num, machine_int_t denom) {
    machine_int_t lsign = num > 0 ? 1 : -1;
    machine_int_t rsign = denom > 0 ? 1 : -1;
    if (lsign == -1) {num *= -1;}
    if (rsign == -1) {denom *= -1;}
    if (lsign != rsign){
        return - ( num + denom - 1) / denom;
    } else {
        return num / denom;
    }
}
