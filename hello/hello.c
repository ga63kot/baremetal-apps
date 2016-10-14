/* Copyright (c) 2013-2015 by the author(s)
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
 *
 * =============================================================================
 *
 * Simple hello world example.
 *
 * Author(s):
 *   Stefan Wallentowitz <stefan.wallentowitz@tum.de>
 */

#include <stdio.h>
#include <optimsoc-baremetal.h>

int testfunc(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7, int arg8, int arg9) {
  return arg1 + arg2 + arg3 + arg4 + arg5 + arg6;
}

int main() {
  printf("Hello World! Core %d of %d in tile %d, my absolute core id is: %d\n",
         optimsoc_get_relcoreid(), optimsoc_get_tilenumcores(),
         optimsoc_get_tileid(), optimsoc_get_abscoreid());

  printf("There are %d compute tiles:\n", optimsoc_get_numct());

  for (int r = 0; r < optimsoc_get_numct(); ++r) {
	  printf(" rank %d is tile %d\n", r, optimsoc_get_ranktile(r));
  }

  int var = testfunc(1,2,3,4,5,6,7,8,9);
  printf("return value was %d\n", var);

  for (int i = 0; i < 100; ++i) {
	  printf("Wait loop %d", i);
  }
  return 0;
}
