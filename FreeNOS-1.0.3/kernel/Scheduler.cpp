/*
 * Copyright (C) 2015 Niek Linnenbank
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    return m_queue.count();
}

Scheduler::Result Scheduler::enqueue(Process *proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;
    }
    switch(proc->getPriority()){
        case 5 :
            prio_queue_5.push(proc);
            break;
        case 4 :
            prio_queue_4.push(proc);
            break;
        case 3 :
            prio_queue_3.push(proc);
            break;
        case 2 :
            prio_queue_2.push(proc);
            break;
        case 1 :
            prio_queue_1.push(proc);
            break;
        default :
            ERROR("Invalid priority level");
            return InvalidArgument;
    }
    //m_queue.push(proc);
    return Success;
}

Scheduler::Result Scheduler::dequeue(Process *proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }

    Size count1 = prio_queue_1.count();
    Size count2 = prio_queue_2.count();
    Size count3 = prio_queue_3.count();
    Size count4 = prio_queue_4.count();
    Size count5 = prio_queue_5.count();

    switch(proc->getPriority()){
        case 5 :
            for (Size i = 0; i < count5; i++)
            {
                Process *p = prio_queue_5.pop();

                if (p == proc)
                    return Success;
                else
                    prio_queue_5.push(p);
            }
        case 4 :
            for (Size i = 0; i < count4; i++)
            {
                Process *p = prio_queue_4.pop();

                if (p == proc)
                    return Success;
                else
                    prio_queue_4.push(p);
            }
        case 3 :
            for (Size i = 0; i < count3; i++)
            {
                Process *p = prio_queue_3.pop();

                if (p == proc)
                    return Success;
                else
                    prio_queue_3.push(p);
            }
        case 2 :
            for (Size i = 0; i < count2; i++)
            {
                Process *p = prio_queue_2.pop();

                if (p == proc)
                    return Success;
                else
                    prio_queue_2.push(p);
            }
        case 1 :
            for (Size i = 0; i < count1; i++)
            {
                Process *p = prio_queue_1.pop();

                if (p == proc)
                    return Success;
                else
                    prio_queue_1.push(p);
            }
        default :
            FATAL("process ID " << proc->getID() << " is not in the schedule");
            return InvalidArgument;
    }
    // // Traverse the Queue to remove the Process
    // for (Size i = 0; i < count; i++)
    // {
    //     Process *p = m_queue.pop();

    //     if (p == proc)
    //         return Success;
    //     else
    //         m_queue.push(p);
    //}
}

Process * Scheduler::select()
{
    // if (prio_queue_1.count() > 0)
    // {
    //     Process *p = prio_queue_1.pop();
    //     prio_queue_1.push(p);

    //     return p;
    // }
    
    // else if (prio_queue_2.count() > 0)
    // {
    //     Process *p = prio_queue_2.pop();
    //     prio_queue_2.push(p);

    //     return p;
    // }

    // else if (prio_queue_3.count() > 0)
    // {
    //     Process *p = prio_queue_3.pop();
    //     prio_queue_3.push(p);
        
    //     return p;
    // }

    // else if (prio_queue_4.count() > 0)
    // {
    //     Process *p = prio_queue_4.pop();
    //     prio_queue_4.push(p);

    //     return p;
    // }

    // else if (prio_queue_5.count() > 0)
    // {
    //     Process *p = prio_queue_5.pop();
    //     prio_queue_5.push(p);

    //     return p;
    // }
    // if (m_queue.count() > 0)
    // {
    //         Process *p = m_queue.pop();
    //         m_queue.push(p);

    //         return p;
    // }
    return (Process *) NULL;
}
