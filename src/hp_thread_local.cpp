// Copyright (c) 2020-2020 Alexander Gaev
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <cds/gc/hp.h>
#include <map>

namespace cds { namespace gc { namespace hp { namespace details {

    // for DefaultTLS Manager
    thread_local thread_data *tls_ = nullptr;

    // for StrangeTLSManager
    thread_local std::pair<thread_data *, thread_data *> *tls2_ = new std::pair<thread_data *, thread_data *>(
            nullptr,
            nullptr);

    /*static*/ CDS_EXPORT_API thread_data *DefaultTLSManager::getTLS() {
        return tls_;
    }

    /*static*/ CDS_EXPORT_API void DefaultTLSManager::setTLS(thread_data *new_tls) {
        tls_ = new_tls;
    }

    /*static*/ CDS_EXPORT_API thread_data *StrangeTLSManager::getTLS() {
        if (cds::OS::get_current_thread_id() % 2 == 0) { // % 2 with ThreadId structure?
            return tls2_->second;
        } else {
            return tls2_->first;
        }
    }

    /*static*/ CDS_EXPORT_API void StrangeTLSManager::setTLS(thread_data *new_tls) {
        if (cds::OS::get_current_thread_id() % 2 == 0) { // % 2 with ThreadId structure?
            tls2_->second = new_tls;
        } else {
            tls2_->first = new_tls;
        }
    }

}}}} // namespace cds::gc::hp::details
