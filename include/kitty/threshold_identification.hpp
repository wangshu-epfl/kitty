/* kitty: C++ truth table library
 * Copyright (C) 2017-2020  EPFL
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*!
  \file threshold_identification.hpp
  \brief Threshold logic function identification

  \author CS-472 2020 Fall students
*/

#pragma once

#include <vector>
#include <lpsolve/lp_lib.h> /* uncomment this line to include lp_solve */
#include "traits.hpp"

#include <iostream> // need to be deleted
using namespace std;

namespace kitty
{

/*! \brief Threshold logic function identification

  Given a truth table, this function determines whether it is a threshold logic function (TF)
  and finds a linear form if it is. A Boolean function is a TF if it can be expressed as

  f(x_1, ..., x_n) = \sum_{i=1}^n w_i x_i >= T

  where w_i are the weight values and T is the threshold value.
  The linear form of a TF is the vector [w_1, ..., w_n; T].

  \param tt The truth table
  \param plf Pointer to a vector that will hold a linear form of `tt` if it is a TF.
             The linear form has `tt.num_vars()` weight values and the threshold value
             in the end.
  \return `true` if `tt` is a TF; `false` if `tt` is a non-TF.
*/
template<typename TT, typename = std::enable_if_t<is_complete_truth_table<TT>::value>>
bool is_threshold( const TT& tt, std::vector<int64_t>* plf = nullptr )
{
  std::vector<int64_t> linear_form;

  /* TODO */

  // Get some params
  int32_t num_bits = static_cast<uint32_t>( tt.num_bits() );
  int32_t num_vars = static_cast<uint32_t>( tt.num_vars() );
  auto tt_flip = tt;
  // Print truth table
  std::cout << "Truth table of f is:";
  for ( int32_t i = num_bits - 1; i >= 0; i-- )
  {
    std::cout << get_bit( tt, i );
  }
  std::cout << endl;
  
  // Get cofactor
  for ( int32_t i = 0u; i < num_vars ; ++i )
  {
    auto fxi     = cofactor1(tt, i);
    auto fxi_bar = cofactor0(tt, i);
    /*
    // Print out cofactor
    std::cout << "Truth table of fx" << i << "     is: ";
    for ( int32_t j = static_cast<uint32_t>( fxi.num_bits() ) - 1; j >= 0; j-- )
    {
      std::cout << get_bit( fxi, j );
    }
    std::cout << endl;
    std::cout << "Truth table of fx" << i << "_bar is: ";
    for ( int32_t j = static_cast<uint32_t>( fxi_bar.num_bits() ) - 1; j >= 0; j-- )
    {
      std::cout << get_bit( fxi_bar, j );
    }
    std::cout << endl;
    */
    // Check whether f is positive or negative unate
    if ( implies( fxi, fxi_bar ) )
    {
      std::cout << "f is negative unate in x" << i << endl;
      tt_flip = flip( tt_flip, i ); // Flip xi so f_flip is positive unate in xi
    }
    else if ( implies( fxi_bar, fxi ) )
    {
      std::cout << "f is positive unate in x" << i << endl;
    }
    else
    {
      std::cout << "f is binate in x" << i << endl;
      // return false;
    }
  }
  /*
  // check tt_flip
  // Print truth table of f_flip
  std::cout << "Truth table of f_flip is:";
  for ( int32_t i = num_bits - 1; i >= 0; i-- )
  {
    std::cout << get_bit( tt_flip, i );
  }
  std::cout << endl;
  for ( int32_t i = 0u; i < num_vars; ++i )
  {
    auto fxi = cofactor1( tt_flip, i );
    auto fxi_bar = cofactor0( tt_flip, i );
    // Check whether f_flip is positive or negative unate
    if ( implies( fxi, fxi_bar ) )
    {
      std::cout << "f_flip is negative unate in x" << i << endl;
    }
    else if ( implies( fxi_bar, fxi ) )
    {
      std::cout << "f_flip is positive unate in x" << i << endl;
    }
    else
    {
      std::cout << "f_flip is binate in x" << i << endl;
    }
  }
  */
  // Build ILP problem with tt_flip


  /* if tt is non-TF: */
  return false;

  /* if tt is TF: */
  /* push the weight and threshold values into `linear_form` */
  if ( plf )
  {
    *plf = linear_form;
  }
  return true;
}

} /* namespace kitty */
