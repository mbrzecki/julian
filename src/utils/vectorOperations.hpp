#ifndef JULIAN_VECTOROPERATIONS_HPP
#define JULIAN_VECTOROPERATIONS_HPP

#include <numeric>
#include <vector>
#include <algorithm>
#include <iostream>

namespace julian {

  /**
   * @file   vectorOperations.hpp
   * @brief  File contains simple tools for std vectors.
   */

  /** \ingroup utils				       
   *
   * \fn std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2) 
   * \brief Combines vector v1 and v2 without duplicates.
   * 
   * \param v1 vector #1
   * \param v2 vector #2
   * \return Combined vector v1 and v2 without duplicates.
   */
  
  template<typename T>
  std::vector<T> combineVectors(std::vector<T> v1, std::vector<T> v2) {
    std::vector<T> result;

    int i = 0;
    int j = 0;
    int n1 = v1.size();
    int n2 = v2.size();

    do {
      if ( v1.at(i) < v2.at(j) ) {
	result.push_back(v1.at(i));
	i++;
      } else if ( v1.at(i) > v2.at(j) ) {
	result.push_back(v2.at(j));
	j++;
      } else if ( v1.at(i) == v2.at(j) ) {
	result.push_back(v2.at(j));
	i++;
	j++;
      }

      if (i == n1) {
      std::copy(v2.begin() + j, v2.end(), std::back_inserter(result));
      break;
      } else if (j == n2) {
	std::copy(v1.begin() + i, v1.end(), std::back_inserter(result));
	break;
      }
    } while (true);

  return result;
  }

  /** \ingroup utils				       
   *
   * \fn std::ostream& operator<<(std::ostream& s, std::vector<T>& v) 
   * \brief Overloaded << operator for vectors.
   */
  
  template< class T >
  std::ostream& operator<<(std::ostream& s, std::vector<T>& v) {
    int n = v.size();  
    
    for(int i = 0; i < n; i++)
      s << v.at(i) << std::endl;
    s << std::endl;
    return s;
  }

  /** \ingroup utils				       
   *
   * \fn sort_vectors(std::vector<T>& benchmark, std::vector<S>& sorted)
   * \brief Sorting one vector basic on contents of another. 
   * 
   * \param benchmark On basis of this vector another is sorted
   * \param sorted Vector that is sorted
   */
  
  template <typename T,typename S>
  void sort_vectors(std::vector<T>& benchmark, std::vector<S>& sorted) {
    // preparing permutation
    std::vector<std::size_t> p(benchmark.size());
    std::iota(p.begin(), p.end(), 0);
    std::sort(p.begin(), p.end(),[&](std::size_t i, std::size_t j){ return benchmark[i] < benchmark[j]; });

    std::vector<bool> done(benchmark.size());
    for (std::size_t i = 0; i < benchmark.size(); ++i) {
      if (done[i]) {
	continue;
      }
      done[i] = true;
      std::size_t prev_j = i;
      std::size_t j = p[i];
      while (i != j) {
	std::swap(benchmark[prev_j], benchmark[j]);
	std::swap(sorted[prev_j], sorted[j]);
	done[j] = true;
	prev_j = j;
	j = p[j];
      }
    }
  }
  
}  // namespace julian


#endif /* VECTOROPERATIONS_HPP */
