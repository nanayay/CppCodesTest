#pragma once

#include "Common.h"

#include <queue>
#include <iostream>
#include <functional>

namespace PriorityQueueTest
{
    class Task
    {
    private:
        unsigned int priority;

    public:
        explicit Task(unsigned int priority_) : priority(priority_) { }
        ~Task() { }
        Task(const Task& copy_) : priority(copy_.priority) { }
        Task operator=(const Task& assign_)
        {
            if (this != &assign_) {
                priority = assign_.priority;
            }
            return *this;
        }

        unsigned int getPriority() const { return priority; }
        bool operator<(const Task& rhs) const { return this->priority < rhs.priority; }
        bool operator>(const Task& rhs) const { return this->priority > rhs.priority; }
    };

    class TaskCmp
    {
    public:
        bool operator()(const Task& lhs, const Task& rhs) const
        {
            return lhs.getPriority() < rhs.getPriority();
        }
    };

    class PriorityQueueTest : public Common::Test
    {
    protected:
        virtual bool prepare()
        {
            return Common::Test::prepare();
        }

        virtual bool shutdown()
        {
            return Common::Test::shutdown();
        }

        virtual bool run()
        {
            std::cout << "less priority queue" << std::endl;
            std::priority_queue<Task> kernel;
            for (int i = 0; i < 100; i++) {
                kernel.push(Task(rand()));
            }

            while (!kernel.empty()) {
                std::cout << kernel.top().getPriority() << std::endl;
                kernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                kernel.push(Task(n));

            while (!kernel.empty())
            {
                std::cout << kernel.top().getPriority() << std::endl;
                kernel.pop();
            }

            std::cout << "greater priority queue" << std::endl;
            std::priority_queue<Task, std::vector<Task>, std::greater<Task>> gKernel;
            for (int i = 0; i < 100; i++) {
                gKernel.push(Task(rand()));
            }

            while (!gKernel.empty()) {
                std::cout << gKernel.top().getPriority() << std::endl;
                gKernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                gKernel.push(Task(n));

            while (!gKernel.empty())
            {
                std::cout << gKernel.top().getPriority() << std::endl;
                gKernel.pop();
            }

            std::cout << "Compare function object priority queue" << std::endl;
            std::priority_queue<Task, std::vector<Task>, TaskCmp> cKernel;
            for (int i = 0; i < 100; i++) {
                cKernel.push(Task(rand()));
            }

            while (!cKernel.empty()) {
                std::cout << cKernel.top().getPriority() << std::endl;
                cKernel.pop();
            }

            for (int n : {1, 8, 5, 6, 3, 4, 0, 9, 3, 2})
                cKernel.push(Task(n));

            while (!cKernel.empty())
            {
                std::cout << cKernel.top().getPriority() << std::endl;
                cKernel.pop();
            }

            return true;
        }
    };
}
