/*
  Copyright (C) 2014 by Andreas Lauser

  This file is part of the Open Porous Media project (OPM).

  OPM is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  OPM is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OPM.  If not, see <http://www.gnu.org/licenses/>.
*/
/*!
 * \file
 * \brief This file implements various objects which provide mutual exclusion
 *        capabilities for multi-threaded applications that use OpenMP.
 */
#ifndef EWOMS_LOCKS_HH
#define EWOMS_LOCKS_HH

#if HAVE_OPENMP || DOXYGEN
#include <omp.h>

/*!
 * \brief Implements a shallow wrapper around the "raw" locks provided by OpenMP.
 */
class OmpMutex
{
public:
    OmpMutex() { omp_init_lock(&lock_); }
    ~OmpMutex() { omp_destroy_lock(&lock_); }
    void lock() { omp_set_lock(&lock_); }
    void unlock() { omp_unset_lock(&lock_); }

    OmpMutex(const OmpMutex&) { omp_init_lock(&lock_); }
    OmpMutex& operator= (const OmpMutex&) { return *this; }

private:
    omp_lock_t lock_;
};
#else
/* A dummy mutex that doesn't actually exclude anything,
 * but as there is no parallelism either, no worries. */
class OmpMutex
{
public:
    void lock() {}
    void unlock() {}
};
#endif

/*!
 * \brief This class implements an exception-safe scoped lock-keeper.
 */
class ScopedLock
{
public:
    explicit ScopedLock(OmpMutex& m)
        : mutex_(m)
        , isLocked_(true)
    { mutex_.lock(); }

    ~ScopedLock()
    { unlock(); }

    void operator=(const ScopedLock&) = delete;
    ScopedLock(const ScopedLock&) = delete;

    void unlock()
    {
        if (!isLocked_)
            return;
        isLocked_ = false;
        mutex_.unlock();

    }

    void lockAgain()
    {
        if(isLocked_)
            return;
        mutex_.lock();
        isLocked_ = true;
    }

private:
    OmpMutex& mutex_;
    bool isLocked_;
};

#endif