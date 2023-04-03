/**
 *  Copyright (c) 2023 Alban Fichet
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <cstdint>


int32_t ordered_float_to_int(float in)
{
    union { float f; int32_t i; } v;
    v.f = in;

    // Depending on the sign bit, we need to compute
    // the two complement
    return (v.i & 0x80000000)
        ? ~(v.i & 0x7FFFFFFF) + 1
        : v.i;
}


// Just for testing...
#include <iostream>
#include <random>
#include <limits>


int main(int argc, char* argv[])
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(
        -std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max()
        );
    
    for (int i = 0; ; i++) {
        float fl1, fl2;
        fl1 = dis(gen);
        fl2 = dis(gen);

        int32_t i1, i2;
        i1 = ordered_float_to_int(fl1);
        i2 = ordered_float_to_int(fl2);

        // Check if the comparison works the same
        if ((fl1 < fl2  && !(i1 < i2)) ||
            (fl1 > fl2  && !(i1 > i2)) ||
            (fl1 == fl2 && !(i1 == i2))) {

            std::cout << "Missmatch detected!" << std::endl;
            std::cout << fl1 << " " << fl2 << std::endl;
            std::cout << i1  << " " << i2  << std::endl;
        }
    }

    return 0;
}
