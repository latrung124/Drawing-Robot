/*
 * thread_guard.h
 * Author: Trung La
 * Description: This file contains the ThreadGuard class which is responsible for managing the thread.
 */

#ifndef THREAD_GUARD_H
#define THREAD_GUARD_H

#include <thread>

namespace dev::utils {

class thread_guard
{
	std::thread &m_thread;

public:
	thread_guard(std::thread &thread)
	    : m_thread(thread)
	{
	}

	~thread_guard()
	{
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}

	thread_guard(const thread_guard &) = delete;
	thread_guard &operator=(const thread_guard &) = delete;
};

} // namespace dev::utils

#endif // THREAD_GUARD_H
