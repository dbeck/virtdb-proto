#pragma once

#include "logger/macros.hh"
#include "logger/log_sink.hh"

#define LOG_INFO(MSG) \
  LOG_COMMON_( MSG, \
               virtdb::interface::pb::LogLevel::INFO, \
               LOG_INFO_IS_ENABLED, \
               0)

#define LOG_ERROR(MSG) \
  LOG_COMMON_( MSG, \
               virtdb::interface::pb::LogLevel::ERROR, \
               LOG_ERROR_IS_ENABLED, \
               0)

#define LOG_TRACE(MSG) \
  LOG_COMMON_( MSG, \
               virtdb::interface::pb::LogLevel::SIMPLE_TRACE, \
               LOG_TRACE_IS_ENABLED, \
               0)

#define LOG_SCOPED(MSG) \
  LOG_COMMON_( MSG, \
               virtdb::interface::pb::LogLevel::SCOPED_TRACE, \
               LOG_SCOPED_IS_ENABLED, \
               1); \
               virtdb::logger::on_return LOG_INTERNAL_LOCAL_VAR(_on_return_) \
                 ( LOG_INTERNAL_LOCAL_VAR(_log_record_)  )

#define V_(VARIABLE) virtdb::logger::make_variable( #VARIABLE, VARIABLE )
