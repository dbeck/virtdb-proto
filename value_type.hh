#pragma once

#include "common.pb.h"
#include <string>

// TODO : BytesValue
// TODO : IsNull
// TODO : polymorphic getter
// TODO : set kind-type in set() functions ...

namespace virtdb { namespace interface {

  template <typename T> struct value_type {};
  
  template <>
  struct value_type<std::string>
  {
    static const pb::Kinds kind = pb::Kinds::STRING;
    typedef std::string stored_type;

    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.stringvalue_size() )
        pb_vt.clear_stringvalue();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_stringvalue(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        const stored_type & v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }

    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.stringvalue_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.stringvalue_size() <= index )
        return default_value;
      else
        return pb_vt.stringvalue(index);
    }
  };
  
  template <>
  struct value_type<const char *>
  {
    static const pb::Kinds kind = pb::Kinds::STRING;
    typedef std::string stored_type;
    
    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.stringvalue_size() )
        pb_vt.clear_stringvalue();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_stringvalue(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        const char * v)
    {
      const char ** val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }

    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.stringvalue_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.stringvalue_size() <= index )
        return default_value;
      else
        return pb_vt.stringvalue(index);
    }
  };
  
  template <>
  struct value_type<int32_t>
  {
    static const pb::Kinds kind = pb::Kinds::INT32;
    typedef int32_t stored_type;
    
    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.int32value_size() )
        pb_vt.clear_int32value();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_int32value(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }

    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.int32value_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.int32value_size() <= index )
        return default_value;
      else
        return pb_vt.int32value(index);
    }
  };
  
  template <>
  struct value_type<int64_t>
  {
    static const pb::Kinds kind = pb::Kinds::INT64;
    typedef int64_t stored_type;

    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.int64value_size() )
        pb_vt.clear_int64value();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_int64value(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }
    
    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.int64value_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.int64value_size() <= index )
        return default_value;
      else
        return pb_vt.int64value(index);
    }
  };
  
  template <>
  struct value_type<uint32_t>
  {
    static const pb::Kinds kind = pb::Kinds::UINT32;
    typedef uint32_t stored_type;

    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.uint32value_size() )
        pb_vt.clear_uint32value();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_uint32value(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }
    
    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.uint32value_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.uint32value_size() <= index )
        return default_value;
      else
        return pb_vt.uint32value(index);
    }
  };
  
  template <>
  struct value_type<uint64_t>
  {
    static const pb::Kinds kind = pb::Kinds::UINT64;
    typedef uint64_t stored_type;
    
    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.uint64value_size() )
        pb_vt.clear_uint64value();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_uint64value(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }
    
    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.uint64value_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.uint64value_size() <= index )
        return default_value;
      else
        return pb_vt.uint64value(index);
    }
  };
  
  template <>
  struct value_type<double>
  {
    static const pb::Kinds kind = pb::Kinds::DOUBLE;
    typedef double stored_type;

    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.doublevalue_size() )
        pb_vt.doublevalue();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_doublevalue(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
              stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }
    
    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.doublevalue_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.doublevalue_size() <= index )
        return default_value;
      else
        return pb_vt.doublevalue(index);
    }
  };
  
  template <>
  struct value_type<float>
  {
    static const pb::Kinds kind = pb::Kinds::FLOAT;
    typedef float stored_type;
    
    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.floatvalue_size() )
        pb_vt.floatvalue();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_floatvalue(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        stored_type v)
    {
      const stored_type * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }
    
    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.floatvalue_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.floatvalue_size() <= index )
        return default_value;
      else
        return pb_vt.floatvalue(index);
    }
  };
  
  template <>
  struct value_type<bool>
  {
    static const pb::Kinds kind = pb::Kinds::BOOL;
    typedef bool stored_type;
    
    template <typename ITER>
    static void
    set(pb::ValueType & pb_vt,
        ITER begin,
        ITER end)
    {
      if( pb_vt.boolvalue_size() )
        pb_vt.boolvalue();
      for( auto it=begin ; it != end ; ++it )
        pb_vt.add_boolvalue(*it);
    }
    
    static void
    set(pb::ValueType & pb_vt,
        bool v)
    {
      const bool * val_ptr = &v;
      set(pb_vt, val_ptr, val_ptr+1);
    }

    static int
    size(pb::ValueType & pb_vt)
    {
      return pb_vt.boolvalue_size();
    }
    
    static stored_type
    get(pb::ValueType & pb_vt,
        int index,
        const stored_type & default_value)
    {
      if( pb_vt.boolvalue_size() <= index )
        return default_value;
      else
        return pb_vt.boolvalue(index);
    }
  };
  
}} // virtdb::interface
