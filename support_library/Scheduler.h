#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

#include "Callback.h"

using SchedulerTaskId = uint8_t;
using SchedulerTaskPeriod = int32_t;
using IntervalMs = int32_t;

class Scheduler {
public:
    [[nodiscard]] SchedulerTaskId addPeriodicTask(Callback&& task, const SchedulerTaskPeriod period);
    bool removeTask(const SchedulerTaskId id);

    void tick(const IntervalMs interval_ms);

private:
    class PeriodicTask {
    public:
        PeriodicTask() = default;
        PeriodicTask(const Callback& callback, const SchedulerTaskPeriod period);
        void tick(const IntervalMs interval_ms);
        void cancel();
        bool isActive() const;

    private:
        void reset();

        Callback callback{};
        SchedulerTaskPeriod period{0};
        IntervalMs interval_till_next_call{0};
        bool active{false};
    };

    uint8_t next_task_slot{0};
    uint8_t total_tasks{0};
    PeriodicTask periodic_tasks[32];
};

#endif //SCHEDULER_H
