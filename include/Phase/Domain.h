/// Domain.h
/// Shaun Harker
/// 2015-05-24

#ifndef DSGRN_DOMAIN_H
#define DSGRN_DOMAIN_H

#include "common.h"

/// class Domain
///   This class allows for n-tuples with non-negative
///   entries less than specified limits (set in the
///   the constructor). It provides operator () to access
///   the components as well as increment operators. The
///   increment operator tries to increment the 0th
///   position; if limit is reached it resets to 0 and
///   carried to the next digit, and so forth. Incrementing
///   the largest domain within the limits results in an
///   invalid domain (and isValid stops returning true).
class Domain {
public:
  /// Domain_
  ///   Default constructor
  Domain ( void );

  /// Domain_
  ///   Construct domain object as
  ///   (0,0,...,0) in 
  ///   {0,1,..,limits[0]-1}x...x{0,1,..,limits[D]-1}
  Domain ( std::vector<uint64_t> const& limits );

  /// assign
  ///   Construct domain object as
  ///   (0,0,...,0) in 
  ///   {0,1,..,limits[0]-1}x...x{0,1,..,limits[D]-1}
  void
  assign ( std::vector<uint64_t> const& limits );

  /// operator []
  ///   Return dth component
  uint64_t 
  operator [] ( uint64_t d ) const;

  /// operator ++ (preincrement)
  ///   Advance through domain traversal pattern
  Domain & 
  operator ++ ( void );

  /// operator ++ (postincrement)
  ///   Advance through domain traversal pattern
  ///   but return copy of unadvanced domain
  Domain 
  operator ++ ( int );

  /// size
  ///   Return number of dimensions
  uint64_t 
  size ( void ) const;

  /// index
  ///   Return traversal index of domain
  uint64_t 
  index ( void ) const;

  /// setIndex 
  ///   Set the domain by index
  void
  setIndex ( uint64_t i );

  /// left
  ///   Return domain index to the left in dimension d
  ///   (If there is none, behavior is undefined)
  uint64_t
  left ( uint64_t d ) const;

  /// right
  ///   Return domain index to the right in dimension d
  ///   (If there is none, behavior is undefined)
  uint64_t
  right ( uint64_t d ) const;

  /// right
  /// isMin
  ///   Return true if dth component 
  ///   is 0 (i.e. is minimal)
  bool 
  isMin ( uint64_t d ) const;

  /// isMax
  ///   Return true if dth component 
  ///   is limits[d]-1 (i.e. is maximal)
  bool 
  isMax ( uint64_t d ) const;

  /// isValid
  ///   Return true if a valid domain.
  ///   (For use with ++, so one-past-the-end is not valid)
  bool
  isValid ( void ) const;

  /// operator <<
  ///   Output to stream
  friend std::ostream& operator << ( std::ostream& stream, Domain const& dom );

private:
  std::vector<uint64_t> data_;
  std::vector<uint64_t> limits_; 
  std::vector<uint64_t> offset_; 
  uint64_t index_;
  uint64_t max_;
  uint64_t D_;
  /// serialize
  ///   For use with BOOST Serialization library,
  ///   which is used by the cluster-delegator MPI package
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version) {
    ar & data_;
    ar & limits_;
    ar & offset_;
    ar & index_;
    ar & max_;
    ar & D_;
  }
};

#endif
