#ifndef JULIAN_ALL_RNGS_HPP
#define JULIAN_ALL_RNGS_HPP

  /**
   * @file   _all_RNGs.hpp
   * @brief  Random number generators module
   */

/** \defgroup rngs Pseudo-Random Numbers
 * \ingroup mathematics
 *
 * \brief Implementations of random number generators.
 *
 * A random number generator (RNG), also known as a deterministic random bit generator (DRBG), is an algorithm for generating a sequence of numbers 
 * whose properties approximate the properties of sequences of random numbers. The RNG-generated sequence is not truly random, because it is completely determined by an initial value, 
 * called the PRNG's seed (which may include truly random values). Although sequences that are closer to truly random can be generated using hardware random number generators, 
 * pseudo-random number generators are important in practice for their speed in number generation and their reproducibility.  
 * (compare  <a href="https://en.wikipedia.org/wiki/Pseudorandom_number_generator">Wikipedia definition</a>)
 *
 *  See more: \cite intphys  \cite NumRec
 */

#include <mathematics/RNGs/uniformRNG.hpp>
#include <mathematics/RNGs/mersenneTwister.hpp>
#include <mathematics/RNGs/RANLUX.hpp>
#include <mathematics/RNGs/Tausworthe.hpp>

#endif 
