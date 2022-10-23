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

//COMMENTS IN THIS FILE ARE MAINLY FOR DEBUGGING... Raul Guerra


#include <Log.h>
#include "Kernel.h"
#include "Scheduler.h"

 /*Modified*/
Queue<Process*, MAX_PROCS> m_queue1;
Queue<Process*, MAX_PROCS> m_queue2;
Queue<Process*, MAX_PROCS> m_queue3;
Queue<Process*, MAX_PROCS> m_queue4;
Queue<Process*, MAX_PROCS> m_queue5;
/*end Modified*/

Scheduler::Scheduler()
{
    DEBUG("");
}

Size Scheduler::count() const
{
    /*Modified*/
    uint totalCount = 0;
    totalCount = m_queue1.count() + m_queue2.count() + m_queue3.count() + m_queue4.count() + m_queue5.count();
    /*end Modified*/

    return totalCount;
}

Scheduler::Result Scheduler::enqueue(Process* proc, bool ignoreState)
{
    if (proc->getState() != Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " not in Ready state");
        return InvalidArgument;

    }
    //NOTICE("-------------------------Priority: " << proc->getPriority());
    switch (proc->getPriority()) {
    case 1:
        m_queue1.push(proc);
        //NOTICE("-------------------------m_queue1");
        return Success;
        break;
    case 2:
        m_queue2.push(proc);
        //NOTICE("-------------------------m_queue2");
        return Success;
        break;
    case 3:
        m_queue3.push(proc);
        //NOTICE("-------------------------m_queue3");
        return Success;
        break;
    case 4:
        m_queue4.push(proc);
        //NOTICE("-------------------------m_queue4");
        return Success;
        break;
    case 5:
        m_queue5.push(proc);
        //NOTICE("-------------------------m_queue5");
        return Success;
        break;
    default:
        return InvalidArgument;
    }

}

Scheduler::Result Scheduler::dequeue(Process* proc, bool ignoreState)
{
    if (proc->getState() == Process::Ready && !ignoreState)
    {
        ERROR("process ID " << proc->getID() << " is in Ready state");
        return InvalidArgument;
    }


    // Traverse the Queue to remove the Process
    int priorityTemp = proc->getPriority();
    switch (priorityTemp)
    {
    case 1:
        for (Size i = 0; i < m_queue1.count(); i++)
        {
            Process* p = m_queue1.pop();

            if (p == proc)
                return Success;
            else
                m_queue1.push(p);
        }
    case 2:
        for (Size i = 0; i < m_queue2.count(); i++)
        {
            Process* p = m_queue2.pop();

            if (p == proc)
                return Success;
            else
                m_queue2.push(p);
        }
    case 3:
        for (Size i = 0; i < m_queue3.count(); i++)
        {
            Process* p = m_queue3.pop();

            if (p == proc)
                return Success;
            else
                m_queue3.push(p);
        }
    case 4:
        for (Size i = 0; i < m_queue4.count(); i++)
        {
            Process* p = m_queue4.pop();

            if (p == proc)
                return Success;
            else
                m_queue4.push(p);
        }
    case 5:
        for (Size i = 0; i < m_queue5.count(); i++)
        {
            Process* p = m_queue5.pop();

            if (p == proc)
                return Success;
            else
                m_queue5.push(p);
        }

    default:
        break;
    }


    FATAL("process ID " << proc->getID() << " is not in the schedule");
    return InvalidArgument;
}

Process* Scheduler::select()
{
    /*
    NOTICE("------------------------- m_queue5.count() = " << m_queue5.count());
    NOTICE("------------------------- m_queue4.count() = " << m_queue4.count());
    NOTICE("------------------------- m_queue3.count() = " << m_queue3.count());
    NOTICE("------------------------- m_queue2.count() = " << m_queue2.count());
    NOTICE("------------------------- m_queue1.count() = " << m_queue1.count());
    NOTICE("-------------------------TESTING COUNT()   = " << count());
    */
    if (count() > 0)
    {

        //Checking if all processes are in their appropriate Queue, 
        //else switch them to right Queue

        //Checking Priority 5
        if (m_queue5.count() > 0)
        {
            for (Size i = 0; i < m_queue5.count(); i++)
            {
                Process* p = m_queue5.pop();

                switch (p->getPriority())
                {
                case 1:
                    m_queue1.push(p);
                    break;
                case 2:
                    m_queue2.push(p);
                    break;
                case 3:
                    m_queue3.push(p);
                    break;
                case 4:
                    m_queue4.push(p);
                    break;
                case 5:
                    m_queue5.push(p);
                    break;
                default: break;
                }
            }
        }
        
        //Checking Priority 4
        if (m_queue4.count() > 0)
        {
            for (Size i = 0; i < m_queue4.count(); i++)
            {
                Process* p = m_queue4.pop();

                switch (p->getPriority())
                {
                case 1:
                    m_queue1.push(p);
                    break;
                case 2:
                    m_queue2.push(p);
                    break;
                case 3:
                    m_queue3.push(p);
                    break;
                case 4:
                    m_queue4.push(p);
                    break;
                case 5:
                    m_queue5.push(p);
                    break;
                default: break;
                }
            }
        }
        
        //Checking Priority 3
        if (m_queue3.count() > 0)
        {
            for (Size i = 0; i < m_queue3.count(); i++)
            {
                Process* p = m_queue3.pop();

                switch (p->getPriority())
                {
                case 1:
                    m_queue1.push(p);
                    break;
                case 2:
                    m_queue2.push(p);
                    break;
                case 3:
                    m_queue3.push(p);
                    break;
                case 4:
                    m_queue4.push(p);
                    break;
                case 5:
                    m_queue5.push(p);
                    break;
                    //NOTICE("------------------------- SWITCHING FROM 3 TO 5 ");
                default: break;
                }
            }
        }
        
        //Checking Priority 2
        if (m_queue2.count() > 0)
        {
            for (Size i = 0; i < m_queue2.count(); i++)
            {
                Process* p = m_queue2.pop();

                switch (p->getPriority())
                {
                case 1:
                    m_queue1.push(p);
                    break;
                case 2:
                    m_queue2.push(p);
                    break;
                case 3:
                    m_queue3.push(p);
                    break;
                case 4:
                    m_queue4.push(p);
                    break;
                case 5:
                    m_queue5.push(p);
                    break;
                default: break;
                }
            }
        }
        
        //Checking Priority 1
        if (m_queue1.count() > 0)
        {
            for (Size i = 0; i < m_queue1.count(); i++)
            {
                Process* p = m_queue1.pop();

                switch (p->getPriority())
                {
                case 1:
                    m_queue1.push(p);
                    break;
                case 2:
                    m_queue2.push(p);
                    break;
                case 3:
                    m_queue3.push(p);
                    break;
                case 4:
                    m_queue4.push(p);
                    break;
                case 5:
                    m_queue5.push(p);
                    break;
                default: break;
                }
            }
        }
        
        //NOTICE("------------------------- ALL PRIORITIES IN ORDER ");
        /*********************************/

        //Selecting next process
        //checking count of all queues

        if (m_queue5.count() > 0)
        {
            //NOTICE("------------------------- m_queue5.count() = " << m_queue5.count());
            Process* p = m_queue5.pop();
            m_queue5.push(p);
            //NOTICE("------------------------- p->getPriority() = " << p->getPriority());
            //NOTICE("------------------------- SELECTING PRIORITY 5");

            return p;
        }

        else if (m_queue4.count() > 0)
        {
            Process* p = m_queue4.pop();
            m_queue4.push(p);
            //NOTICE("------------------------- SELECTING PRIORITY 4");

            return p;
        }

        else if (m_queue3.count() > 0)
        {
            Process* p = m_queue3.pop();
            m_queue3.push(p);
            //NOTICE("------------------------- SELECTING PRIORITY 3");

            return p;
        }

        else if (m_queue2.count() > 0)
        {
            Process* p = m_queue2.pop();
            m_queue2.push(p);
            //NOTICE("------------------------- SELECTING PRIORITY 2");

            return p;
        }

        else if (m_queue1.count() > 0)
        {
            Process* p = m_queue1.pop();
            m_queue1.push(p);
            //NOTICE("------------------------- SELECTING PRIORITY 1");

            return p;
        }
    }

    /*
   NOTICE("------------------------- m_queue5.count() = " << m_queue5.count());
   NOTICE("------------------------- m_queue4.count() = " << m_queue4.count());
   NOTICE("------------------------- m_queue3.count() = " << m_queue3.count());
   NOTICE("------------------------- m_queue2.count() = " << m_queue2.count());
   NOTICE("------------------------- m_queue1.count() = " << m_queue1.count());
   NOTICE("-------------------------TESTING COUNT()   = " << count());
   */
    return (Process*)NULL;
}
